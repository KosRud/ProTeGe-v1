#include "ImageLib.h"
#include "wx/filedlg.h"
#include "filters.h"

using namespace PTG;


static float cut(float x)
{
    if(x > 255)
        return 255;
    if(x < 0)
        return 0;
    return x;
}

float PTG::s_curve(float x)
{
    return powf(x,5) * 6 - powf(x,4) * 15 + powf(x, 3) * 10;
    //return x*x * 3 - 2 * x*x*x;
    //return x;
}

greyscale::greyscale(greyscale && x)
{
    size = x.size;

    data = x.data;

    x.data = 0;
}

greyscale::greyscale()
{
    size = 0;
    data = 0;
}

greyscale::greyscale(greyscale & g)
{
    data = 0;
    *this = g;
}

greyscale::greyscale(int x)
{
    size = x;

    data = new float * [size];

    for (int i = 0; i < size; i++)
        data[i] = new float[size];
}

void greyscale::clear()
{
    for(int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            data[x][y] = 0;
    return;
}

void greyscale::downscale(int new_size)
{
    int coef = size / new_size;

    int sqr_coef = coef * coef;

    greyscale scaled(new_size);

    for(int x = 0; x < new_size; x++)
        for(int y = 0; y < new_size; y++)
        {
            float sum = 0;
            for(int ix = 0; ix < coef; ix ++)
                for(int iy = 0; iy < coef; iy ++)
                {
                    sum += data[x * coef + ix][y * coef + iy];
                }
            sum /= sqr_coef;
            scaled.data[x][y] = cut(sum);
        }

    *this = scaled;
}

void greyscale::upscale(int new_size)
{
    int coef = new_size / size;

    greyscale scaled(new_size);

    float precalculated[coef];

    for(int i = 0; i < coef; i++)
        precalculated[i] = s_curve( ((float)i) / coef );

    for(int y = 0; y < new_size; y += coef)
    {
        for(int x = 0; x < new_size; x++)
        {
            int left = x / coef;
            int right = left + 1;

            int value = x - left * coef;

            float left_color = data[left][y / coef];
            float right_color = data[right % size][y / coef];

            float delta = right_color - left_color;

            scaled.data[x][y] = left_color + precalculated[value] * delta;

            //scaled.data[x][y] = left_color * (1 - value) + right_color * value;
        }
    }


    for(int x = 0; x < new_size; x++)
    {
        for(int y = 0; y < new_size; y ++)
        {
            int lower = y / coef;
            int upper = lower + 1;

            int value = y - lower * coef;

            float lower_color = scaled.data[x][lower * coef];
            float upper_color = scaled.data[x][upper * coef % new_size];

            float delta = upper_color - lower_color;

            scaled.data[x][y] = lower_color + precalculated[value] * delta;

            //scaled.data[x][y] = lower_color * (1 - value) + upper_color * value;
        }
    }

    (*this) = scaled;
}



void greyscale::set_image(wxStaticBitmap * dest, int scale)
{
    wxImage * temp_wximage = new wxImage(size, size, true);

     for (int x = 0; x < size; x++)
     {
         for (int y = 0; y < size; y ++)
         {
             int rounded = (int)roundf(data[x][y]);
             temp_wximage->SetRGB(x, y, rounded, rounded, rounded);
         }
     }

     if(scale)
        temp_wximage->Rescale(scale, scale, wxIMAGE_QUALITY_NEAREST);

     wxBitmap * temp_wxbitmap = new wxBitmap(*temp_wximage);

     dest->SetBitmap(*temp_wxbitmap);

     delete temp_wximage;
     delete temp_wxbitmap;

     return;
}

greyscale & greyscale::operator = (greyscale && x)
{
    size = x.size;
    data = x.data;
    x.data = 0;

    return *this;
}

greyscale & greyscale::operator = (greyscale & x)
{
    if(data && size != x.size)
    {
        for (int i = 0; i < size; i++)
            delete[] data[i];
        delete[] data;
        data = 0;
    }

    if(!data)
    {
        size = x.size;

        data = new float * [size];

        for (int i = 0; i < size; i++)
        {
            data[i] = new float[size];
        }
    }


    for(int xc = 0; xc < size; xc++)
        for(int y = 0; y < size; y++)
            data[xc][y] = x.data[xc][y];

    return *this;
}

void greyscale::save_to_file(wxString & s)
{
    wxImage * temp_wximage = new wxImage(size, size, true);

     for (int x = 0; x < size; x++)
     {
         for (int y = 0; y < size; y ++)
         {
             int rounded = (int)roundf(data[x][y]);
             temp_wximage->SetRGB(x, y, rounded, rounded, rounded);
         }
     }

    temp_wximage->SaveFile(s);

     delete temp_wximage;
}

void greyscale::load_file(wxString & s)
{
    wxImage * temp_wximage = new wxImage(size, size, true);

    temp_wximage->LoadFile(s);

     for (int x = 0; x < size; x++)
     {
         for (int y = 0; y < size; y ++)
         {
             int rounded = (int)roundf(data[x][y]);
             data[x][y] = temp_wximage->GetRed(x,y);
         }
     }

     delete temp_wximage;
}

void greyscale::operator += (greyscale & g)
{
    int min_size = size < g.size ? size : g.size;

    for(int x = 0; x < min_size; x++)
        for(int y = 0; y < min_size; y++)
            data[x][y] = cut(data[x][y] + g.data[x][y]);
}

void greyscale::operator -= (greyscale & g)
{
    int min_size = size < g.size ? size : g.size;

    for(int x = 0; x < min_size; x++)
        for(int y = 0; y < min_size; y++)
            data[x][y] = cut(data[x][y] - g.data[x][y]);
}

void greyscale::operator *= (greyscale & g)
{
    int min_size = size < g.size ? size : g.size;

    for(int x = 0; x < min_size; x++)
        for(int y = 0; y < min_size; y++)
            data[x][y] =  cut(data[x][y] * g.data[x][y] / 255);
}

greyscale greyscale::operator + (greyscale & g)
{
    greyscale result = *this;

    result += g;

    return result;
}

greyscale greyscale::operator - (greyscale & g)
{
    greyscale result = *this;

    result -= g;

    return result;
}

greyscale greyscale::operator * (greyscale & g)
{
    greyscale result = *this;

    result *= g;

    return result;
}




/*
void greyscale::set_image(wxStaticBitmap * dest, int scale, float RH, float GH, float BH, int RL, int GL, int BL)
{
    wxImage * temp_wximage = new wxImage(size, size, true);

    float RC, GC, BC;

    RC = (RH - RL) / 255.0;
    GC = (GH - GL) / 255.0;
    BC = (BH - BL) / 255.0;

     for (int x = 0; x < size; x++)
     {
         for (int y = 0; y < size; y ++)
         {
             temp_wximage->SetRGB(x, y, (int)(data[x][y] * RC + RL) ,(int)(data[x][y] * GC + GL), (int)(data[x][y] * BC + BL));
         }
     }


     temp_wximage->Rescale(scale, scale, wxIMAGE_QUALITY_HIGH);

     wxBitmap * temp_wxbitmap = new wxBitmap(*temp_wximage);

     dest->SetBitmap(*temp_wxbitmap);

     delete temp_wximage;
     delete temp_wxbitmap;

     return;
}*/

greyscale::~greyscale()
{
    if(data)
    {
        for (int i = 0; i < size; i++)
            delete[] data[i];
        delete[] data;
    }
}

