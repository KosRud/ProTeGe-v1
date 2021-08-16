#include "Perlin_noise.h"
#include "../threading/threading.h"
#include "../images/filters.h"

using namespace PTG;

static float(*modes[])(float) = {
    [](float a) -> float{return a;},//Default
    [](float a) -> float{if(a > 0) return -a * 2 + 1; else return a * 2 + 1;},//Modulus inverted
    [](float a) -> float{if(a < 0) return -a * 2 - 1; else return a * 2 - 1;}//Modulus
};

class perlin_vector
{
public:
    float x;
    float y;

    perlin_vector()
    {
        if (rand() > RAND_MAX / 2)
        {
            y = (float)rand() * 2.0 / (float)RAND_MAX - 1;
            x = sqrt(1 - y * y);
            if (rand() > RAND_MAX / 2) x = -x;
        }
        else
        {
            x = (float)rand() * 2.0 / (float)RAND_MAX - 1;
            y = sqrt(1 - x * x);
            if (rand() > RAND_MAX / 2) y = -y;
        }
    }
};

inline static void perlin_noise(int size, greyscale ** result, int detail_level, perlin_vector ** vectors, int mode)
{
    int detail_coef = size / detail_level;

    float detail_coef_sqr = sqrt(2) / (float)detail_coef;

    float ** precomputed_distances = new float*[detail_coef];

    for (int i = 0; i < detail_coef + 1; i++)
    {
        precomputed_distances[i] = new float[detail_coef];
    }

    for (int px = 0; px <= detail_coef; px ++)
    {
        for (int py = 0; py <= detail_coef; py ++)
        {
            precomputed_distances[px][py] = s_curve((1 - (float)px / detail_coef) * (1 - (float)py / detail_coef) );
        }
    }

    // do it

    float point_colors[4];

    int vector_field_x;
    int vector_field_y;
    int vector_field_x_real;
    int vector_field_y_real;
    float x_mult;
    float y_mult;
    int x_dist;
    int y_dist;
    float distance;
    float distance_sum;

    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            distance_sum = 0;

            //make each pixel

            vector_field_x = x * detail_level / size;
            vector_field_y = y * detail_level / size;

            x_dist = x - vector_field_x * detail_coef;
            y_dist = y - vector_field_y * detail_coef;

            x_mult = (float)x_dist * vectors[vector_field_x][vector_field_y].x * detail_coef_sqr;
            y_mult = (float)y_dist * vectors[vector_field_x][vector_field_y].y * detail_coef_sqr;

            distance = precomputed_distances[x_dist][y_dist];

            distance_sum += distance;

            point_colors[0] = (x_mult + y_mult) / 2.0 * distance;

            // right

            vector_field_x = x * detail_level / size + 1;
            vector_field_y = y * detail_level / size;

            x_dist = x - vector_field_x * detail_coef;
            y_dist = y - vector_field_y * detail_coef;

            vector_field_x_real = vector_field_x % detail_level;

            x_mult = (float)x_dist * vectors[vector_field_x_real][vector_field_y].x * detail_coef_sqr;
            y_mult = (float)y_dist * vectors[vector_field_x_real][vector_field_y].y * detail_coef_sqr;

            distance = precomputed_distances[0 - x_dist][y_dist];

            distance_sum += distance;

            point_colors[1] = (x_mult + y_mult) / 2.0 * distance;

            //top

            vector_field_x = x * detail_level / size;
            vector_field_y = y * detail_level / size + 1;

            x_dist = x - vector_field_x * detail_coef;
            y_dist = y - vector_field_y * detail_coef;

            vector_field_y_real = vector_field_y % detail_level;

            x_mult = (float)x_dist * vectors[vector_field_x][vector_field_y_real].x * detail_coef_sqr;
            y_mult = (float)y_dist * vectors[vector_field_x][vector_field_y_real].y * detail_coef_sqr;

            distance = precomputed_distances[x_dist][0 - y_dist];
            distance_sum += distance;

            point_colors[2] = (x_mult + y_mult) / 2.0 * distance;

            //diagonal

            vector_field_x = x * detail_level / size + 1;
            vector_field_y = y * detail_level / size + 1;

            x_dist = x - vector_field_x * detail_coef;
            y_dist = y - vector_field_y * detail_coef;

            vector_field_y_real = vector_field_y % detail_level;
            vector_field_x_real = vector_field_x % detail_level;

            x_mult = (float)x_dist * vectors[vector_field_x_real][vector_field_y_real].x * detail_coef_sqr;
            y_mult = (float)y_dist * vectors[vector_field_x_real][vector_field_y_real].y * detail_coef_sqr;

            distance = precomputed_distances[0 - x_dist][0 - y_dist];

            distance_sum += distance;

            point_colors[3] = (x_mult + y_mult) / 2.0 * distance;

            (*result)->data[x][y] = (point_colors[0] + point_colors[1] + point_colors[2] + point_colors[3])  / distance_sum;
            (*result)->data[x][y] = modes[mode]((*result)->data[x][y]);
        }

    }

    for (int i = 0; i < detail_coef + 1; i++)
    {
        delete[] precomputed_distances[i];
    }

    delete[] precomputed_distances;

    return;
}

static void set_perlin_iteration(void ** input)
{
    int size = *((int*)(input[0]));
    greyscale ** base =  (greyscale**)(input[1]);
    int detail = *((int*)(input[2]));
    perlin_vector ** vectors = (perlin_vector**)(input[3]);
    int mode = *((int*)(input[4]));

    perlin_noise(size, base, detail, vectors, mode);
}

greyscale PTG::Noises::fractal_perlin(int size, float * distribution, int mode)
{
    int vectors_amount = size / 2;
    perlin_vector ** vectors = new perlin_vector*[vectors_amount];
    for(int i = 0; i < vectors_amount; i++)
        vectors[i] = new perlin_vector[vectors_amount];

    int detail_level = log2(size) - 1;

    greyscale ** bases = new greyscale*[detail_level];
    for(int i = 0; i < detail_level; i++)
        //if(distribution[i] != 0)
            bases[i] = new greyscale(size);

    int thread_count = std::thread::hardware_concurrency();

    if(thread_count == 0)
        thread_count = 1;

    int work_amount = 0;
    for(int i = 0; i < detail_level; i++)
        if(distribution[i] != 0)
            work_amount ++;

    ThreadChief threader(thread_count, work_amount);

    int k = 0; //real i

    int  * details = new int[detail_level];
    for(int i = 0; i < detail_level; i++)
        details[i] = powf(2,i + 1);

    for(int i = 0; i < detail_level; i++)
    {
        if(distribution[i] != 0)
        {
            threader.tasks[k] = set_perlin_iteration;
            threader.args[k] = new void*[5];
            threader.args[k][0] = (void*)(&size);
            threader.args[k][1] = (void*)(&(bases[i]));
            threader.args[k][2] = (void*)(details+i);
            threader.args[k][3] = (void*)vectors;
            threader.args[k][4] = (void*)(&mode);

            //set_perlin_iteration(threader.args[k]);
            k++;
        }
    }

    threader.start();

    greyscale result(size);

    result.clear();

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            float distribution_sum = 0;
            for (int i = 0; i < detail_level; i++)
            {
                if (distribution[i] != 0)
                    result.data[x][y] += bases[i]->data[x][y] * distribution[i];
                distribution_sum += distribution[i];
            }
            result.data[x][y] /= distribution_sum;
        }
    }

    delete[] details;

    for(int i = 0; i < vectors_amount; i++)
        delete[] vectors[i];
    delete[] vectors;

    for(int i = 0; i < detail_level; i++)
        if(distribution[i] != 0)
            delete bases[i];
    delete[] bases;

    Filters::maximize_contrast(result);

    return result;
}

greyscale PTG::Noises::fractal_perlin(int size, float distribution_coef, int mode)
{
    int iterations = log2(size);

    float * distribution = new float[iterations];

    distribution[iterations - 1] = 1;

    for (int i = iterations - 2; i >= 0; i--)
        distribution[i] = distribution[i + 1] * distribution_coef;

    greyscale result = Noises::fractal_perlin(size, distribution, mode);

    delete[] distribution;

    return result;
}
