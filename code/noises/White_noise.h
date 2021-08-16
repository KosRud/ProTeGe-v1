#pragma once

#include "../images/ImageLib.h"

namespace PTG
{
    namespace Noises
    {
        PTG::greyscale fractal_white(int size, float distribution_coef);
        PTG::greyscale fractal_white(int size, float * distribution);
    }
}

