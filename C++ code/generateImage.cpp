//
// Created by Andrew Dunstan on 10/13/20.
//
#include "mandelbrotMovie.h"

#include <iostream>>
#include <fstream>
#include <string>

using namespace std;
int main(){
    //Initialise your variables
    fstream myReadFile;
    myReadFile.open("targets.txt");
    string line;
    double centerReal, centerImag, widthReal;
    int frameWidthPixels, frameHeightPixels;
    string centerRealStr, centerImagStr, widthRealStr, frameWidthPixelsStr, frameHeightPixelsStr;

    //Get the frame resolution from the first line of the file and convert it to ints
    getline(myReadFile, line);
    frameWidthPixelsStr = line.substr(0, line.find(","));
    line = line.substr(line.find(", ")+1);
    frameHeightPixelsStr = line.substr(0, line.find(","));
    frameWidthPixels = stoi(frameWidthPixelsStr);
    frameHeightPixels = stoi(frameHeightPixelsStr);

    //Gets the doubles on the last line of the file by overwriting the same strings until the file ends.
    while( getline(myReadFile, line)){
        centerRealStr = line.substr(0, line.find(","));
        line = line.substr(line.find(", ")+1);
        centerImagStr = line.substr(0, line.find(","));
        line = line.substr(line.find(", ")+1);
        widthRealStr = line.substr(0, line.find(","));
        line = "";
    }
    myReadFile.close();

    cout << centerRealStr << ", " << centerImagStr << ", " << widthRealStr  << endl;

    //Convert all the strings to doubles
    centerReal = stod(centerRealStr);
    centerImag = stod(centerImagStr);
    widthReal = stod(widthRealStr);

    //Set up the movie and render the frame for the io system to display
    MandelbrotMovie myMovie(frameWidthPixels, frameHeightPixels, widthReal, centerReal,
            centerImag, "colorPalet.txt");

    myMovie.renderFrame("testFrame.bmp");

    return 0;
}

