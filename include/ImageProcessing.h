#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#define BMP_COLOR_TABLE_SIZE    1024
#define BMP_HEADER_SIZE         54
#define   MAX_COLOR             255
#define   MIN_COLOR             0
#define   WHITE                 MAX_COLOR
#define   BLACK                 MIN_COLOR

#include <iostream>
#include <stdio.h>


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
    virtual ~ImageProcessing();
};


#endif // !IMAGEPROCESSING_H