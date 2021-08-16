#pragma once

#include "../images/ImageLib.h"

namespace PTG
{
    namespace Noises
    {
        PTG::greyscale sparse_convolution(
                int size, PTG::greyscale & base, int count,
                float contrast, bool use_gaussian);

        PTG::greyscale sparse_convolution(
                int size, PTG::greyscale && base, int count,
                float contrast, bool use_gaussian);
    }
}
