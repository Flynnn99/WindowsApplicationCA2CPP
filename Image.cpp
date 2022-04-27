//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"
#include "math.h"



bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users
    try {
        if (ifs.fail())
        {
            throw("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0] ;
            this->pixels[i].g = pix[1] ;
            this->pixels[i].b = pix[2] ;
        }
        ifs.close();
    }
    catch (const char *err)
    {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }

    return true;
}
bool Image::loadRaw(string filename)
{

    return false;
}
bool Image::savePPM(string filename)
{
   if (this->w == 0 || this->h == 0) {return false; }

   std::ofstream ofs;

        ofs.open(filename, std::ios::binary);

        // need to spec. binary mode for Windows users
        if (ofs.fail()) return false;

        ofs << "P6\n" << this->w << " " << this->h << "\n255\n";

        unsigned char  r, g, b;

        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < this->w * this->h; i++)
        {
            r = this->pixels[i].r;
            g = this->pixels[i].g;
            b = this->pixels[i].b;
            ofs << r << g << b;
        }

        ofs.close();

        return true;
    }





void Image::filterRed()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].g = 0;
        this->pixels[c].b = 0;
    }

}
void Image::filterGreen()
{
    for(int c = 0; c< w*h; c++)
    {
        this->pixels[c].r = 0;
        this->pixels[c].b = 0;
    }
}
void Image::filterBlue()
{
    for(int c = 0; c< w*h; c++)
    {
#
        this->pixels[c].r = 0.5;
        //this->pixels[c].r = 0;
    }
}
void Image::greyScale()
{

    for(int c = 0; c< w*h; c++)
    {

            int greyscale = (this->pixels[c].r  +this->pixels[c].g) /3;

            this->pixels[c].b = greyscale;
            this->pixels[c].g =greyscale;
            this->pixels[c].r = greyscale;

    }
}
void Image::flipHorizontal()
{
    int pixels[3];
    unsigned int tempPixel;
    unsigned int tempPixel1;


    for(int y= 0; y < h; y++)
    {
        for(int x =0; x <w/2; x++)
        {
            tempPixel = x + y * w;
            tempPixel1 = (w - 1 - x) + y * w;

            pixels[0] = this->pixels[tempPixel].r;
            pixels[1] = this->pixels[tempPixel].g;
            pixels[2] = this->pixels[tempPixel].b;

            this->pixels[tempPixel].r = this->pixels[tempPixel1].r;
            this->pixels[tempPixel].g = this->pixels[tempPixel1].g;
            this->pixels[tempPixel].b = this->pixels[tempPixel1].b;

            this->pixels[tempPixel1].r = pixels[0];
            this->pixels[tempPixel1].g = pixels[1];
            this->pixels[tempPixel1].b = pixels[2];
        }
    }




}
void Image::flipVertically()
{
    int pixels[3];
    unsigned int tempPixel;
    unsigned int tempPixel1;


    for(int x= 0; x < w; x++)
    {
        for(int y =0; y <h/2; y++)
        {
            tempPixel = x + y * w;
            tempPixel1 = x +  (h - 1 - y)  * w;


            pixels[0] = this->pixels[tempPixel].r;
            pixels[1] = this->pixels[tempPixel].g;
            pixels[2] = this->pixels[tempPixel].b;

            this->pixels[tempPixel].r = this->pixels[tempPixel1].r;
            this->pixels[tempPixel].g = this->pixels[tempPixel1].g;
            this->pixels[tempPixel].b = this->pixels[tempPixel1].b;

            this->pixels[tempPixel1].r = pixels[0];
            this->pixels[tempPixel1].g = pixels[1];
            this->pixels[tempPixel1].b = pixels[2];
        }
    }




}
void Image::AdditionalFunction2()
{
    /*Darkens the image -- probably going remove this as I don't think its 10 mark worthy :(
    for(int c = 0; c< w*h; c++)
    {

         this->pixels[c].b = (this->pixels[c].b + this->pixels[c].b) /2.5;
         this->pixels[c].g =(this->pixels[c].g + this->pixels[c].g) /2.5;
         this->pixels[c].r = (this->pixels[c].r +this->pixels[c].r) /2.5;
    }*/


    for(int c = 0; c<w*h; c++)
    {
        int newRed = 255 - this->pixels[c].r;
        int newGreen = 255 - this->pixels[c].g;
        int newBlue = 255 - this->pixels[c].b;


        this->pixels[c].r = newRed;
        this->pixels[c].g = newGreen;
        this->pixels[c].b = newBlue;

    }
}
void Image::AdditionalFunction3()
{

    for(int c = 0; c< w*h; c++)
    {

        int newRed = 0.393*this->pixels[c].r + 0.769*this->pixels[c].g + 0.189*this->pixels[c].b;
        int newGreen = 0.349*this->pixels[c].r + 0.686*this->pixels[c].g+ 0.168*this->pixels[c].b;
        int newBlue =  0.272*this->pixels[c].r + 0.534*this->pixels[c].g + 0.131*this->pixels[c].b;

        if(newRed > 255)
        {
        this->pixels[c].r = 255;
        }
        else
        {
            this->pixels[c].r = newRed;
        }

        if(newGreen > 255)
        {
            this->pixels[c].g = 255;
        }
        else
        {
            this->pixels[c].g = newGreen;
        }

        if(newBlue > 255)
        {
            this->pixels[c].b = 255;
        }
        else
        {
            this->pixels[c].b = newBlue;
        }




    }
}
void Image::AdditionalFunction1()
{
    for(int c = 0; c< w*h; c++)
    {

        pixels[c].r = pixels[c].g = pixels[c].b;
    }

}
void Image::Gamma()
{
    for(int c = 0; c< w*h; c++)
    {
        float gamma=1/2.2f;

        pixels[c].r = pow(pixels[c].r /255.0f, gamma) * 255;
        pixels[c].g = pow(pixels[c].g /255.0f, gamma) * 255;
        pixels[c].b = pow(pixels[c].b /255.0f, gamma) * 255;
    }
}

void Image::AdvancedFeature()
{
    int pixels[3];
    unsigned int tempPixel;
    unsigned int tempPixel1;

    for(int x= 0; x < w; x++)
    {
        for(int y =0; y <h/2; y++)
        {
            tempPixel = x + y * w;
            tempPixel1 = x +  (h - 1 - y) ;


            pixels[0] = this->pixels[tempPixel].r;
            pixels[1] = this->pixels[tempPixel].g;
            pixels[2] = this->pixels[tempPixel].b;

            this->pixels[tempPixel].r = this->pixels[tempPixel1].r;
            this->pixels[tempPixel].g = this->pixels[tempPixel1].g;
            this->pixels[tempPixel].b = this->pixels[tempPixel1].b;

            this->pixels[tempPixel1].r = pixels[0];
            this->pixels[tempPixel1].g = pixels[1];
            this->pixels[tempPixel1].b = pixels[2];
        }
    }

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}