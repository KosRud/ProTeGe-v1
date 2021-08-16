#pragma once

#include "../images/ImageLib.h"

namespace PTG
{
    namespace Noises
    {
        PTG::greyscale wavelet(int size, float distribution_coef);
        PTG::greyscale wavelet(int size, float * distribution);
    }
}

