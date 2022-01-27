//
// Created by Andrew Dunstan on 9/20/20.
//
#include "mandelbrotMovie.h"
#include "EasyBMP.h"

#include <string>
#include <math.h>
#include <vector>
#include <sstream>

using namespace EasyBMP;
using namespace std;


MandelbrotMovie::MandelbrotMovie(int _frameWidthPixels, int _frameHeightPixels, double _frameLengthReal, double _centerR,
        double _centerI, string colorPaletFileName){
    //set up movie variables
    frameWidthPixels = _frameWidthPixels;
    frameHeightPixels = _frameHeightPixels;
    setFramePosition(_centerR, _centerI, _frameLengthReal);

    //Load the color pallet
    colorPalet = MandelbrotMovie::loadColors(colorPaletFileName);
}

void MandelbrotMovie::setFramePosition(double centerReal, double centerImag, double widthReal){
    frameLengthReal = widthReal;
    frameLengthImag = frameLengthReal * (double(frameHeightPixels)/frameWidthPixels);
    pixelLength  = frameLengthReal/frameWidthPixels;

    centerR = centerReal;
    centerI = centerImag;

    upLeftCornerR = centerR-frameLengthReal/2;
    upLeftCornerI = centerI+frameLengthImag/2;

    //cout<< "curent center: " << centerR << ", " << centerI << endl;
    //cout << "current frame width: " << frameLengthReal << endl;
}

void MandelbrotMovie::renderFrame(string frameName) {
    //set up required variables
    Image img(frameWidthPixels, frameHeightPixels, frameName);
    double cR; double cI; double zR; double zI; double tempZR; double magnitude;
    int maxIter = 200;

    //Start main calculation loop for every pixel
    for(int col=0; col < frameWidthPixels; col ++){
        for(int row=0; row < frameHeightPixels; row++){
            cR = upLeftCornerR + (col*pixelLength) + pixelLength/2;
            cI = upLeftCornerI - (row*pixelLength) - pixelLength/2;
            zR = 0;
            zI = 0;

            for(int i=0; i<maxIter; i++){
                tempZR = (zR*zR) - (zI*zI) + cR;
                zI = 2*zR*zI + cI;
                zR = tempZR;

                magnitude = (zR*zR) + (zI*zI);
                if(magnitude > 10000){
                    int gradiantScale = 256;
                    double smoothedEscape = log((log(magnitude)/2.0)/log(2.0))/log(2.0);
                    int colorI = (int)(sqrt(i + 10 - smoothedEscape) * gradiantScale) % colorPalet.size();

                    img.SetPixel(col,row, colorPalet[colorI], false);

                    break;
                }
            }
        }
    }

    img.Write();
}

vector<RGBColor> MandelbrotMovie::loadColors(string colorFile){
    vector<RGBColor> colors;

// Read from the text file
    ifstream file(colorFile);
    string myText;
    int redValue; int greenValue; int blueValue;

// Use a while loop together with the getline() function to read the file line by line
    while (getline (file, myText)) {
        // Output the text from the file

        stringstream myRedStreem(myText.substr(0, myText.find(",")));
        myRedStreem >> redValue;

        myText = myText.substr(myText.find(",")+1);

        stringstream myGreenStreem(myText.substr(0, myText.find(",")));
        myGreenStreem >> greenValue;

        stringstream myBlueStreem(myText.substr(myText.find(",")+1));
        myBlueStreem >> blueValue;

        //cout << redValue << ", " << greenValue << ", " << blueValue << endl;
        RGBColor newColor = RGBColor(redValue, greenValue, blueValue);
        colors.push_back(newColor);
    }
    //cout << endl;

// Close the file
    file.close();

    //--------------------------------------------------------------------------------------------------------
    //Finished loading colors now we combine them
    Image newPaletImage(colors.size(), 300);
    for(int width =0; width < colors.size(); width ++){
        for(int height = 0; height < 300; height ++){
            newPaletImage.SetPixel(width, height, colors[width], false);
        }
    }
    cout << colors.size() << endl;

    newPaletImage.Write("NewPaletImage.bmp");

    return colors;
}