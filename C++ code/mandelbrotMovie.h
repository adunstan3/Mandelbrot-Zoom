//
// Created by Andrew Dunstan on 9/20/20.
//

#ifndef TESTIMAGE_MANDELBROTMOVIE_H
#define TESTIMAGE_MANDELBROTMOVIE_H

#include <string>
#include <vector>
#include "EasyBMP.h"

class MandelbrotMovie{
private:
    int frameWidthPixels;
    int frameHeightPixels;

    double frameLengthReal;
    double frameLengthImag;
    double pixelLength;

    double centerR;
    double centerI;
    double upLeftCornerR;
    double upLeftCornerI;

    std::vector<EasyBMP::RGBColor> colorPalet;
    std::vector<EasyBMP::RGBColor> loadColors(std::string colorFile);

public:
    MandelbrotMovie(int _frameWidthPixels, int _frameHeightPixels, double _frameLengthReal, double _centerR,
            double _centerI, std::string colorFile);
    void setFramePosition(double centerReal, double centerImag, double widthReal);
    void renderFrame(std::string frameName);
};

#endif //TESTIMAGE_MANDELBROTMOVIE_H
