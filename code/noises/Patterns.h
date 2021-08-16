#pragma once

#include "../images/ImageLib.h"

namespace PTG
{
    namespace Patterns
    {
        void marble(greyscale & source, int cycles, float noise_coef);
        void wood(greyscale & source, int cycles, float noise_coef);
    }
}
