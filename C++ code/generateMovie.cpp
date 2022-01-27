//
// Created by Andrew Dunstan on 10/14/20.
//
#include "mandelbrotMovie.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(){
    //Clear out any old frames
    try{
        system("rm movieImages/*");
    }catch (int error){
        cout << "Error number: " << to_string(error) << endl;
    }

    //Count the number of frames in the file for percentage updates
    int numFrames = -1;
    string line;
    ifstream myfile("frameCordinates.txt");

    while (getline(myfile, line))
        ++numFrames;

    //Get the information out of the file
    fstream myReadFile;
    myReadFile.open("frameCordinates.txt");
    double centerReal=0, centerImag=0, widthReal=0, timeBetweenTargets;

    int frameWidthPixels, frameHeightPixels, frameRate;
    string centerRealStr, centerImagStr, widthRealStr, frameWidthPixelsStr, frameHeightPixelsStr, frameRateStr;
    string timeBetweenTargetsStr, movieTital;

    //Get the frame resolution from the first line of the file and convert it to ints
    getline(myReadFile, line);
    frameWidthPixelsStr = line.substr(0, line.find(','));
    line = line.substr(line.find(", ")+2);
    frameHeightPixelsStr = line.substr(0, line.find(','));
    line = line.substr(line.find(", ")+2);
    frameRateStr = line.substr(0, line.find(','));
    line = line.substr(line.find(", ")+2);
    timeBetweenTargetsStr = line.substr(0, line.find(','));
    line = line.substr(line.find(", ")+2);
    movieTital = line.substr(0, line.find(','));

    frameWidthPixels = stoi(frameWidthPixelsStr);
    frameHeightPixels = stoi(frameHeightPixelsStr);
    frameRate = stoi(frameRateStr);

    movieTital += ".mpg";

    //Set up variables for the main movie generation loop
    unique_ptr<MandelbrotMovie> myMovie;
    string frameName;
    int i = 0;
    bool firstLine = true;

    //Main loop for generating each frame
    while( getline(myReadFile, line)){
        //Read in the new frame target from the file
        centerRealStr = line.substr(0, line.find(','));
        line = line.substr(line.find(", ")+1);
        centerImagStr = line.substr(0, line.find(','));
        line = line.substr(line.find(", ")+1);
        widthRealStr = line.substr(0, line.find(','));
        line = "";

        //Convert all the strings to doubles
        centerReal = stod(centerRealStr);
        centerImag = stod(centerImagStr);
        widthReal = stod(widthRealStr);


        if(firstLine){ //Make the movie object
            myMovie = make_unique<MandelbrotMovie>( MandelbrotMovie(frameWidthPixels, frameHeightPixels, widthReal,
                                                                    centerReal, centerImag, "colorPalet.txt"));
            firstLine=false;
        }else{ //switch the position of the frame
            myMovie->setFramePosition(centerReal, centerImag, widthReal);
        }

        //render the frame
        frameName = "movieImages/MandelbrotFrame"+ to_string(i) +".bmp";
        myMovie->renderFrame(frameName);

        cout << to_string(int((double(i)/numFrames)*100)) << "% Done" << endl;
        i += 1;
    }
    myReadFile.close();

    //get ffmpeg to compress the frames down into a movie saved to finished movies
    string mergeImagesCall = R"(cd movieImages; ffmpeg -r )"+to_string(frameRate)+R"( -f image2 -i MandelbrotFrame%d.bmp ../movieClips/)"+movieTital;
    cout << mergeImagesCall << endl;
    cout << movieTital << endl;
    system(mergeImagesCall.c_str());

    //Clear out any old frames
    system("rm movieImages/*");

    return 0;
}

/* Notes on timing if I want to start doing that
        auto start = std::chrono::high_resolution_clock::now();
        frameName = "../movieImages/MandelbrotFrame"+ to_string(i) +".bmp";
        myMovie.renderFrame(frameName);
        myMovie.changeFramePosition(.95, 0.0, 0.0);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);

        cout << "Time to render frame: " << duration.count()/1000 << " miliseconds %" << int((double(i)/numFrames)*100) << endl;
    }
*/