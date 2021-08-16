#pragma once

#include "../images/ImageLib.h"

namespace PTG
{
    namespace Noises
    {
        PTG::greyscale fractal_perlin(int size, float * distribution, int mode = 0);
        PTG::greyscale fractal_perlin(int size, float distribution_coef, int mode = 0);
    }
}
