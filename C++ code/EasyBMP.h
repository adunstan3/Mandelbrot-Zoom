//
// Created by Andrew Dunstan on 10/10/20.
//

#ifndef UNTITLED_EASYBMP_H
#define UNTITLED_EASYBMP_H

/*
Original repository: https://github.com/izanbf1803/EasyBMP
License: MIT
*/
#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace EasyBMP
{
    using std::string;
    using std::int64_t;
    using std::uint32_t;
    using std::uint8_t;
    using std::ofstream;


    class RGBColor{
    public:
        RGBColor() {}; // Don't use void constructor, just for variable definition
        ~RGBColor() {};
        RGBColor(uint8_t _r, uint8_t _g, uint8_t _b);
        void SetColor(uint8_t _r, uint8_t _g, uint8_t _b);

        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    class Image{
    public:
        ~Image();
        Image() { width = height = 0; }; // Don't use default constructor, just for variable definition
        Image(int64_t _width, int64_t _height);
        Image(int64_t _width, int64_t _height, const string& _outFileName);
        Image(int64_t _width, int64_t _height, const RGBColor& _backgroundColor);
        Image(int64_t _width, int64_t _height, const string& _outFileName, const RGBColor& _backgroundColor);
        void SetPixel(int64_t x, int64_t y, const RGBColor& color, bool ignore_err);
        void DrawLine(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);
        void DrawCircle(int64_t x0, int64_t y0, int64_t r, const RGBColor& color, bool fill);
        void SetFileName(const string& _outFileName);
        void Write(const string& _outFileName);
        void Write();
        inline int64_t w() const { return width; }
        inline int64_t h() const { return height; }

    private:
        void Init(int64_t _width, int64_t _height);
        void Setup();
        void DrawLineLow(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);
        void DrawLineHigh(int64_t x0, int64_t y0, int64_t x1, int64_t y1, const RGBColor& color);

        int64_t width;
        int64_t height;
        ofstream outFile;
        string outFileName;
        RGBColor backgroundColor;
        RGBColor** buffer;
    };
}


#endif //UNTITLED_EASYBMP_H
