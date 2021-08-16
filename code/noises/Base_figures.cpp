#include "Base_figures.h"

using namespace PTG;


static float cut(float x)
{
    if(x > 255)
        return 255;
    if(x < 0)
        return 0;
    return x;
}


static float gaussian_distribution(int sigma, int x)
{
    return exp(-powf(x,2)/(powf(sigma,2)*2));
}

static float gaussian_distribution(int sigma, int x, int y)
{
    return gaussian_distribution(sigma, x) * gaussian_distribution(sigma, y);
}

greyscale Base_figures::star(int size, float power)
{
    float coef = 1.0 / power;

    greyscale base(size);
    for(int x = 0; x < base.size; x++)
        for(int y = 0; y < base.size; y++)
        {
            float dx = x - base.size / 2;
            float dy = y - base.size / 2;
            dx = dx > 0 ? dx : -dx;
            dy = dy > 0 ? dy : -dy;
            dx /= base.size / 2;
            dy /= base.size / 2;
            float dist = powf( powf(dx, coef) + powf(dy, coef), power );
            base.data[x][y] = dist < 1 ? (1 - dist) * 255 : 0;
            base.data[x][y] = cut(base.data[x][y]);
        }

    return base;
}

greyscale Base_figures::gaussian(int size)
{
    greyscale base(size);
    for(int x = 0; x < base.size; x++)
        for(int y = 0; y < base.size; y++)
        {
            base.data[x][y] = gaussian_distribution(size / 6, x - size / 2, y - size / 2)*255;
            base.data[x][y] = cut(base.data[x][y]);
        }

    return base;
}

greyscale Base_figures::square(int size)
{
    greyscale base(size);
    for(int x = 0; x < base.size; x++)
        for(int y = 0; y < base.size; y++)
            base.data[x][y] = 255;

    return base;
}
