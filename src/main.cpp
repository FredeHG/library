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
    
    const char imgName[]        = "images/cameraman.bmp";
    const char newImgName[]     = "images/cameramanopt1.bmp";
    ImageProcessing *myimage    = new ImageProcessing(imgName, newImgName, &imgHeight, &imgWidth, &imgBitDepth, imgHeader, imgColorTable, imgInBuffer, imgOutBuffer);
    myimage->readImage();
    myimage->getImageNegative(imgInBuffer, imgOutBuffer);
    myimage->writeImage();
    std::cout << "Terminado!" << std::endl;
    std::cout << "Alto de la imagen: " << imgHeight << std::endl;
    std::cout << "Anchoo de la imagen: " << imgWidth << std::endl;
    return 0;
}