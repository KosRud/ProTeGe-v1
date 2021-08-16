#pragma once

#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>

#include <math.h>
#include <limits.h>

namespace PTG
{
    float s_curve(float x);

    class greyscale
    {
    private:
        float get_hor_neighbour(int x, int y, int offset);
        float get_vert_neighbour(int x, int y, int offset);

    public:
        int size;
        float ** data;

        greyscale();
        greyscale(int x);
        greyscale(greyscale &);
        greyscale(greyscale &&);

        greyscale & operator = (greyscale &);
        greyscale & operator = (greyscale &&);

        void operator += (greyscale &);
        void operator -= (greyscale &);
        void operator *= (greyscale &);

        greyscale operator + (greyscale &);
        greyscale operator - (greyscale &);
        greyscale operator * (greyscale &);

        void upscale(int new_size);
        void downscale(int new_size);

        void set_image(wxStaticBitmap * dest, int scale = 0);
        void save_to_file(wxString & s);
        void load_file(wxString & s);
        //void set_image(wxStaticBitmap * dest, int scale, float RH, float GH, float BH, int RL, int GL, int BL);

        void clear();

        ~greyscale();
    };
}
