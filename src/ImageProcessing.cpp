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


ImageProcessing::~ImageProcessing()
{
}