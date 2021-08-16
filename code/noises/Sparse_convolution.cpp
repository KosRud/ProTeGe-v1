#include "Sparse_convolution.h"
#include "../algos/algos.h"
#include "Base_figures.h"

using namespace PTG;

static float gaussian_distribution(int sigma, int x)
{
    return exp(-powf(x,2)/(powf(sigma,2)*2));
}

static float gaussian_distribution(int sigma, int x, int y)
{
    return gaussian_distribution(sigma, x) * gaussian_distribution(sigma, y);
}

class position
{
public:
    int x;
    int y;
    float coef;

    int xd(int x)
    {
        int dist = this->x - x;
        return dist > 0 ? dist : -dist;
    }

    int yd(int y)
    {
        int dist = this->y - y;
        return dist > 0 ? dist : -dist;
    }
};

using namespace PTG;

greyscale Noises::sparse_convolution(int size, greyscale & base, int count,
                                     float contrast, bool use_gaussian)
{
    greyscale result(size);

    result.clear();

    position * positions = new position[count];

    for(int i = 0; i < count; i++)
    {
        positions[i].x = Algos::halton(i, 2) * size;
        positions[i].y = Algos::halton(i, 3) * size;
        positions[i].coef = 1.0 - (float)(rand()) / RAND_MAX * contrast;
    }

    if(use_gaussian)
    {
        greyscale alpha = Base_figures::gaussian(base.size);

        for(int i = 0; i < count; i++)
        {
            for(int base_x = 0; base_x < base.size; base_x++)
                for(int base_y = 0; base_y < base.size; base_y++)
                {

                    int real_x = (base_x + positions[i].x) % size;
                    int real_y = (base_y + positions[i].y) % size;

                    float value;

                    float b = base.data[base_x][base_y];
                    b *= positions[i].coef;
                    float a = result.data[real_x][real_y];
                    float coef = alpha.data[base_x][base_y] / 255;
                    value = b * coef + a * (1.0 - coef);
                    result.data[real_x][real_y] = value;

                }
        }
    }
    else
    {

        for(int i = 0; i < count; i++)
        {
            for(int base_x = 0; base_x < base.size; base_x++)
                for(int base_y = 0; base_y < base.size; base_y++)
                {

                    int real_x = (base_x + positions[i].x) % size;
                    int real_y = (base_y + positions[i].y) % size;

                    float value;

                    if(base.data[base_x][base_y] > 1)
                    {
                        value = base.data[base_x][base_y];
                        value *= positions[i].coef;
                        result.data[real_x][real_y] = value;
                    }

                }
        }
    }

    return result;
}

greyscale Noises::sparse_convolution(int size, greyscale && base, int count,
                                     float contrast, bool use_gaussian)
{
    greyscale result(size);

    result.clear();

    position * positions = new position[count];

    for(int i = 0; i < count; i++)
    {
        positions[i].x = Algos::halton(i, 2) * size;
        positions[i].y = Algos::halton(i, 7) * size;
        positions[i].coef = 1.0 - (float)(rand()) / RAND_MAX * contrast;
    }

    if(use_gaussian)
    {
        greyscale alpha = Base_figures::gaussian(base.size);

        for(int i = 0; i < count; i++)
        {
            for(int base_x = 0; base_x < base.size; base_x++)
                for(int base_y = 0; base_y < base.size; base_y++)
                {

                    int real_x = (base_x + positions[i].x) % size;
                    int real_y = (base_y + positions[i].y) % size;

                    float value;

                    float b = base.data[base_x][base_y];
                    b *= positions[i].coef;
                    float a = result.data[real_x][real_y];
                    float coef = alpha.data[base_x][base_y] / 255;
                    value = b * coef + a * (1.0 - coef);
                    result.data[real_x][real_y] = value;

                }
        }
    }
    else
    {

        for(int i = 0; i < count; i++)
        {
            for(int base_x = 0; base_x < base.size; base_x++)
                for(int base_y = 0; base_y < base.size; base_y++)
                {

                    int real_x = (base_x + positions[i].x) % size;
                    int real_y = (base_y + positions[i].y) % size;

                    float value;

                    if(base.data[base_x][base_y] > 1)
                    {
                        value = base.data[base_x][base_y];
                        value *= positions[i].coef;
                        result.data[real_x][real_y] = value;
                    }

                }
        }
    }

    return result;
}
