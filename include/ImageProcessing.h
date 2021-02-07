#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#define BMP_COLOR_TABLE_SIZE    1024
#define BMP_HEADER_SIZE         54
#define   MAX_COLOR             255
#define   MIN_COLOR             0
#define   WHITE                 MAX_COLOR
#define   BLACK                 MIN_COLOR
#define NO_OF_GRAYLEVELS        255
#include <iostream>
#include <stdio.h>
#include <string.h>

class ImageProcessing
{
private:
    const char *inImgName;
    const char *outImgName;
    int *height;
    int *width;
    int *bitDepth;
    unsigned char *header;
    unsigned char *colorTable;
    unsigned char *inBuf;
    unsigned char *outBuf;
public:
    ImageProcessing(
                    const char *_inImgName,
                    const char *_outImgName,
                    int *_height,
                    int *_width,
                    int *_bitDepth,
                    unsigned char *_header,
                    unsigned char *_colorTable,
                    unsigned char *_inBuf,
                    unsigned char *_outBuf
                    );
    void readImage();
    void writeImage();

    void binarizeImage(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int threshold);
    void brightnessUp(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int brightness);
    void brightnessDown(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int brightness);
    void computeHistogram(unsigned char *_imgData, int imgRows, int imgCols, float hist[], const char *output);
    void equalizeHistogram(unsigned char *_inImgData, unsigned char *_outImgData, int imgRows, int imgCols);
    void rotateImage(unsigned char *_inImgData, unsigned char *_outImgdata, int mode);
    virtual ~ImageProcessing();
};


#endif // !IMAGEPROCESSING_H