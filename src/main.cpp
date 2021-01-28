#include <iostream>
#include <cstring>

#include "ImageProcessing.h"

using namespace std;

int main(){
    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[262144];
    unsigned char imgOutBuffer[262144];
    
    const char imgName[]        = "images/lena512.bmp";
    const char newImgName[]     = "images/lenaBrihtness.bmp";
    ImageProcessing *myimage    = new ImageProcessing(imgName, newImgName, &imgHeight, &imgWidth, &imgBitDepth, imgHeader, imgColorTable, imgInBuffer, imgOutBuffer);
    myimage->readImage();
    int imgSize = imgWidth * imgHeight;
    myimage->brightnessDown(imgInBuffer, imgOutBuffer, imgSize, 50);
    myimage->writeImage();
    std::cout << "Terminado!" << std::endl;
    std::cout << "Alto de la imagen: " << imgHeight << std::endl;
    std::cout << "Anchoo de la imagen: " << imgWidth << std::endl;
    return 0;
}