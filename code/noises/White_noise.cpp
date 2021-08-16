#include "White_noise.h"
#include "../threading/threading.h"
#include "../images/filters.h"

using namespace PTG;

static void white_noise_worker(greyscale ** base, int size, int base_size)
{
    for(int x = 0; x < base_size; x++)
        for(int y = 0; y < base_size; y++)
            (*base)->data[x][y] = ((float)rand()) / RAND_MAX * 3 - 1;

    if(size > base_size)
    {
        (**base).upscale(size);
    }
}

static void set_white_noise_iteration(void ** input)
{
    greyscale ** base = ((greyscale**)(input[0]));
    int size = *((int*)(input[1]));
    int detail = *((int*)(input[2]));

    white_noise_worker(base, size, detail);
}

greyscale PTG::Noises::fractal_white(int size, float * distribution)
{
    int iterations = log2(size);

    int thread_count = std::thread::hardware_concurrency();
    if(thread_count == 0)
        thread_count = 1;

    int work_amount = 0;
    for(int i = 0; i < iterations; i++)
        if(distribution[i] != 0)
            work_amount ++;

    ThreadChief threader(thread_count, work_amount);

    int k = 0; //real i

    int * details = new int[iterations];
    for(int i = 0; i < iterations; i++)
        details[i] = powf(2,i+1);

    greyscale ** bases = new greyscale*[iterations];
    for(int i = 0; i < iterations; i++)
        if(distribution[i] != 0)
            bases[i] = new greyscale(details[i]);

    for(int i = 0; i < iterations; i++)
    {
        if(distribution[i] != 0)
        {
            threader.tasks[k] = set_white_noise_iteration;
            threader.args[k] = new void*[3];
            threader.args[k][0] = (void*)(bases+i);
            threader.args[k][1] = (void*)(&size);
            threader.args[k][2] = (void*)(details+i);
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
            for (int i = 0; i < iterations; i++)
            {
                if (distribution[i])
                    result.data[x][y] += bases[i]->data[x][y] * distribution[i];
                distribution_sum += distribution[i];
            }
            result.data[x][y] /= distribution_sum;
        }
    }

    delete[] details;

    for(int i = 0; i < iterations; i++)
        if(distribution[i] != 0)
            delete bases[i];

    delete[] bases;

    Filters::maximize_contrast(result);

    return result;

}

greyscale PTG::Noises::fractal_white(int size, float distribution_coef)
{
    int iterations = log2(size);

    float * distribution = new float[iterations];

    distribution[iterations - 1] = 1;

    for (int i = iterations - 2; i >= 0; i--)
        distribution[i] = distribution[i + 1] * distribution_coef;

    return Noises::fractal_white(size, distribution);
}
