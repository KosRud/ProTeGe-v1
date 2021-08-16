#include "Cellular_noise.h"
#include "../images/filters.h"

using namespace PTG;


float root = powf(2,0.5);

float modulus(float x)
{
    if(x < 0)
        return -x;
    return x;
}

static float(*modes[])(float,float) = {
    [](float T1, float T2) -> float{return T1;}, //Inverted bubble
    [](float T1, float T2) -> float{return 1 - T1;}, //Bubble
    [](float T1, float T2) -> float{return T2;},  //Stones
    [](float T1, float T2) -> float{return T2-T1;},  //Deep stones
    [](float a, float b) -> float{return powf(a * a + b * b, 0.5) / root;}, //Inverted bubbles net
    [](float a, float b) -> float{return 1 - powf(a * a + b * b, 0.5) / root;}, //3D bubbles
};

static float(*dists[])(float,float) = {
    [](float a, float b) -> float{return powf(a * a + b * b, 0.5) / root;}, //Stones
    [](float a, float b) -> float{return (modulus(a) + modulus(b)) / 2;},  //Pyramids
    [](float a, float b) -> float{return modulus(a) > modulus(b) ? modulus(a) : modulus(b);}, //Square stones
};

static float(*cell_coef_modes[])(float,float, float) = {
    [](float a, float b, float c) -> float{return a;},  //No mosaic
    [](float a, float b, float c) -> float{return b;},  //Flat mosaic
    [](float a, float b, float c) -> float{return pow(a,c)*b;}, //Shiny mosaic
};

class cell
{
public:
    float point_x;
    float point_y;
    float coef;

    cell()
    {
        point_x = ((float)rand()) / RAND_MAX * 0.7 + 0.15;
        point_y = ((float)rand()) / RAND_MAX * 0.7 + 0.15;
    }
};

greyscale PTG::Noises::celluar(int size, int detail, int mode, int dist_mode, int cell_coef_mode, float dist_power)
{
    cell ** cells = new cell*[detail];
    for(int x = 0; x < detail; x++)
        cells[x] = new cell[detail];

    greyscale result(size);

    for(int i = 0; i < detail; i++)
        cells[i] = new cell[detail];

    if(cell_coef_mode)
        if(cell_coef_mode == 2)
            for(int x = 0; x < detail; x++)
                    for(int y = 0; y < detail; y++)
                        cells[x][y].coef = ((float)rand()) / RAND_MAX * 0.525 + 0.475;

        else

            for(int x = 0; x < detail; x++)
                for(int y = 0; y < detail; y++)
                cells[x][y].coef = ((float)rand()) / RAND_MAX;

    int coef = size / detail;

    int moves[9][2] = {{0,0},{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}};

    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            float pre = std::numeric_limits<float>::max();
            float min_distance = std::numeric_limits<float>::max();
            float min_cell_coef = 0;

            for(int i = 0; i < 9; i++)
            {
                int cell_x = x * detail / size + moves[i][0];
                int cell_y = y * detail / size + moves[i][1];

                if(cell_x < 0)
                    cell_x = detail - cell_x;

                if(cell_y < 0)
                    cell_y = detail -cell_y;

                cell_x %= detail;
                cell_y %= detail;

                float point_x = cells[cell_x][cell_y].point_x + moves[i][0] - (float)(x % coef) / coef;
                float point_y = cells[cell_x][cell_y].point_y + moves[i][1] - (float)(y % coef) / coef;

                float distance = dists[dist_mode](point_x, point_y);

                if(distance < min_distance)
                {
                    pre = min_distance;
                    min_distance = distance;
                    min_cell_coef = cells[cell_x][cell_y].coef;
                }
                else
                    if(distance <pre)
                        pre = distance;

            }

            min_distance = modes[mode](min_distance, pre);

            min_distance = cell_coef_modes[cell_coef_mode](min_distance, min_cell_coef, dist_power);
            min_distance = min_distance * 2 - 1;

            result.data[x][y] = min_distance;
        }
    }

    for(int x = 0; x < detail; x++)
        delete[] cells[x];
    delete[] cells;

    Filters::maximize_contrast(result);

    return result;
}
