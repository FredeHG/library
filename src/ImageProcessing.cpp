#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(
                                const char *_inImgName,
                                const char *_outImgName,
                                int *_height,
                                int *_width,
                                int *_bitDepth,
                                unsigned char *_header,
                                unsigned char *_colorTable,
                                unsigned char *_inBuf,
                                unsigned char *_outBuf
                                )
{
    inImgName   = _inImgName;
    outImgName  = _outImgName;
    height      = _height;
    width       = _width;
    bitDepth    = _bitDepth;
    header      = _header;
    colorTable  = _colorTable;
    inBuf       = _inBuf;
    outBuf      = _outBuf;
}

void ImageProcessing::readImage(){
    FILE *streamIn;
    streamIn = fopen(inImgName, "rb");
    if(!streamIn){
        std::cout << "No se puede abrir el archivo" << std::endl;
        exit(0);
    }

    fread(header, sizeof(unsigned char), BMP_HEADER_SIZE, streamIn);
    *width              = *(int *) &(header[18]);
    *height             = *(int *) &(header[22]);
    *bitDepth           = *(int *) &(header[28]);
    int sizeImage      = (*width) * (*height);

    if(*bitDepth <= 8){
        fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
    }

    fread(inBuf, sizeof(unsigned char), sizeImage, streamIn);
    fclose(streamIn);
}

void ImageProcessing::writeImage(){
    FILE * fo = fopen(outImgName, "wb");
    if(!fo){
        std::cout << "No se pudo crear la imagen" << std::endl;
        exit(0);
    }

    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fo);
    if(*bitDepth <= 8){
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fo);
    }

    fwrite(outBuf, sizeof(unsigned char), (*height) * (*width), fo);
    fclose(fo);

}

void ImageProcessing::binarizeImage(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int threshold){
    for(int i=0;i<imgSize;i++){
        _outImgData[i] =  (_inImgData[i] > threshold) ? WHITE : BLACK;
    }
}

void ImageProcessing::brightnessUp(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int brightness){
    for (int i = 0; i < imgSize; i++)
    {
        int temp = _inImgData[i] + brightness;
        _outImgData[i] = temp > MAX_COLOR? MAX_COLOR : temp;
    }
}

void ImageProcessing::brightnessDown(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int brightness){
    for (int i = 0; i < imgSize; i++)
    {
        int temp = _inImgData[i] - brightness;
        _outImgData[i] = temp < MIN_COLOR? MIN_COLOR : temp;
    }
}

void ImageProcessing::computeHistogram(unsigned char *_imgData, int imgRows, int imgCols, float hist[], const char *output){
    FILE *fptr;
    fptr = fopen(output, "w");
    int col, row, gray_level;
    long int ihist[NO_OF_GRAYLEVELS], sum;
    memset(ihist, 0, sizeof(ihist));
    sum = 0;
    for(row = 0; row < imgRows; row++){
        for(col = 0; col < imgCols; col++){
            gray_level = *(_imgData+col+row*imgCols);
            ihist[gray_level] = ihist[gray_level] + 1;
            sum++;
        }
    }
    for(int i = 0; i < NO_OF_GRAYLEVELS; i++){
        hist[i] = (float)ihist[i]/(float)sum;
    }

    for (int i = 0; i < NO_OF_GRAYLEVELS; i++){
        fprintf(fptr, "\n%f", hist[i]);
    }
    fclose(fptr);
}

void ImageProcessing::equalizeHistogram(unsigned char *_inImgData, unsigned char *_outImgData, int imgRows, int imgCols){
    int histeq[NO_OF_GRAYLEVELS];
    float hist[NO_OF_GRAYLEVELS];
    float sum;
    const char initHist[]   = "init_hist.dat";
    const char finalHist[]  = "final_hist.dat";
    computeHistogram(_inImgData, imgRows, imgCols, hist, initHist);

    for (int i = 0; i < NO_OF_GRAYLEVELS; i++){
        sum = 0.0;
        for (int j = 0; j < i; j++){
            sum = sum+hist[j];
        }
        histeq[i] = (int) (NO_OF_GRAYLEVELS*sum+0.5);
    }
    
    for (int row = 0; row < imgRows; row++){
        for (int col = 0; col < imgCols; col++){
            *(_outImgData + col + row*imgCols) = histeq[*(_inImgData+col+row*imgCols)];
        }
    }
    
    computeHistogram(_outImgData, imgRows, imgCols, hist, finalHist);

}

void ImageProcessing::rotate(unsigned char *_inImgData, unsigned char *_outImgdata, int mode){
    switch (mode)
    {
    case 1:
         for (int i = 0; i < *width; i++){
            for (int j = 0; j < *height; j++){
                _outImgdata[j*(*height) + (*height - 1 - i)] = _inImgData[i*(*height) + j];
            }
        }
        break;

    case 2:
        for (int i = 0; i < *width; i++){
            for (int j = 0; j < *height; j++){
                _outImgdata[j**width + i] = _inImgData[i**height + j];
            }
        }
        break;
     case 3:
        for (int i = 0; i < *width; i++){
            for (int j = 0; j < *height; j++){
                _outImgdata[(*width - 1 - i)**height + j] = _inImgData[i**height + j];
            }
        }
        break;
    default:
        std::cout << "Opcion invalida!" << std::endl;
        exit(0);
        break;
    }
}

ImageProcessing::~ImageProcessing()
{
}