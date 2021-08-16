#include "algos.h"

using namespace PTG;

float Algos::halton(int index, int base)
{
    float result = 0;
    float f = 1;
    int i = index;

    while(i > 0)
    {
        f /= base;
        result += f * (i % base);
        i /= base;
    }

    return result;
}
