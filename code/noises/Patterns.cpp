#include "Patterns.h"

using namespace PTG;

inline static float cut(float x)
{
    if(x > 255)
        return 255;
    if(x < 0)
        return 0;

    return x;
}

void PTG::Patterns::marble(greyscale & source, int cycles, float noise_coef)
{
    int size = source.size;
    float scale = (float)size / cycles;
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            float value = (source.data[x][y] / 255) * 2 - 1;
            value = sin(float(x) * M_PI / scale + value * noise_coef * M_PI);
            value = (value + 1) / 2 * 255;
            source.data[x][y] = cut(value);
        }
    }
}

void PTG::Patterns::wood(greyscale & source, int cycles, float noise_coef)
{
    int size = source.size;
    float scale = (float)size / cycles;
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            float value = (source.data[x][y] / 255) * 2 - 1;
            value = sin(sqrt(pow(x - size / 2,2) + pow(y - size / 2,2)) * M_PI /  scale + value * noise_coef * M_PI);
            value = (value + 1) / 2 * 255;
            source.data[x][y] = cut(value);
        }
    }
}
