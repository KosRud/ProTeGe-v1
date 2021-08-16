#pragma once

#include "ImageLib.h"
#include "../threading/threading.h"

namespace PTG
{
    namespace Filters
    {
        void gaussian_blur(greyscale & source, int sigma, float quality = 3);
        void emboss(greyscale & source, int radius);
        void maximize_contrast(greyscale & source);
        void split(greyscale & source, float coef);
        void gamma(greyscale & source, float coef);
        void contrast(greyscale & source, float coef, int offset = 0);
        void gain(greyscale & source, float coef, int offset);
        void invert(greyscale & source);
        //void normalize(greyscale & source);
    }
}
