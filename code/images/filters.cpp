#include "filters.h"

using namespace PTG;

static float cut(float x)
{
    if(x > 255)
        return 255;
    if(x < 0)
        return 0;
    return x;
}

void normalize_filter_matrix(float ** matrix, int size_x, int size_y)
{
    float sum = 0;

    for(int x = 0; x < size_x; x++)
        for(int y = 0; y < size_y; y++)
            sum += matrix[x][y];

    for(int x = 0; x < size_x; x++)
        for(int y = 0; y < size_y; y++)
            matrix[x][y] /= sum;
}

void worker_apply_filter(void ** input)
{
    greyscale * source = (greyscale *)(input[0]);
    greyscale * result = (greyscale *)(input[1]);
    int radius_x = *((int*)(input[2]));
    int radius_y = *((int*)(input[3]));
    float ** matrix = (float **)(input[4]);
    int start_x = *((int*)(input[5]));
    int end_x = *((int*)(input[6]));

    for(int x = start_x; x < end_x; x++)
        for(int y = 0; y < source->size; y++)
        {
            for(int dx = -radius_x; dx <= radius_x; dx++)
                for(int dy = -radius_y; dy <= radius_y; dy++)
                {
                    int real_x = x + dx;
                    int real_y = y + dy;

                    if(real_x < 0)
                        real_x = source->size - real_x;
                    if(real_y < 0)
                        real_y = source->size - real_y;

                    real_x %= source->size;
                    real_y %= source->size;

                    float value = source->data[real_x][real_y] * matrix[dx + radius_x][dy + radius_y];
                    result->data[x][y] += value;
                }

            result->data[x][y] = cut(result->data[x][y]);
        }
}

void apply_filter(greyscale & source, int radius_x, int radius_y, float ** matrix)
{
    int thread_count = std::thread::hardware_concurrency();
    if(thread_count == 0)
        thread_count = 1;

    ThreadChief threader(thread_count, thread_count);

    int * limits = new int[thread_count + 1];

    limits[0] = 0;
    for(int i = 1; i < thread_count; i++)
        limits[i] = (source.size / thread_count) * i;
    limits[thread_count] = source.size;

    greyscale result(source.size);
    result.clear();

    for(int i = 0; i < thread_count; i++)
    {
        threader.tasks[i] = worker_apply_filter;
        threader.args[i] = new void*[7];
        threader.args[i][0] = (void*)(&source);
        threader.args[i][1] = (void*)(&result);
        threader.args[i][2] = (void*)(&radius_x);
        threader.args[i][3] = (void*)(&radius_y);
        threader.args[i][4] = (void*)(matrix);
        threader.args[i][5] = (void*)(&limits[i]);
        threader.args[i][6] = (void*)(&limits[i + 1]);
    }

    threader.start();

    source = result;

    delete[] limits;
}

static float gaussian_distribution(int sigma, int x)
{
    return exp(-powf(x,2)/(powf(sigma,2)*2));
}

void PTG::Filters::gaussian_blur(greyscale & source, int sigma, float quality)
{
    int radius = sigma * quality;

    int size = radius * 2 + 1;

    float ** horizontal = new float * [size];
    for(int i = 0; i < size; i++)
    {
        int x = i - radius;
        if(x < 0)
            x = -x;
        horizontal[i] = new float(gaussian_distribution(sigma,x));
    }

    normalize_filter_matrix(horizontal, size, 1);
    apply_filter(source, radius, 0, horizontal);

    for(int i = 0; i < size; i++)
        delete horizontal[i];
    delete[] horizontal;

    float ** vertical = new float * [1];
    vertical[0] = new float[size];
    for(int i = 0; i < size; i++)
    {
        int y = i - radius;
        if(y < 0)
            y = -y;
        vertical[0][i] = gaussian_distribution(sigma,y);
    }

    normalize_filter_matrix(vertical, 1, size);
    apply_filter(source, 0, radius, vertical);

    delete[] vertical[0];
    delete[] vertical;
}

void PTG::Filters::emboss(greyscale & source, int radius)
{
    int size = radius * 2 + 1;
    float ** matrix = new float*[size];
    for(int x = 0; x < size; x++)
    {
        matrix[x] = new float[size];
        for(int y = 0; y < size; y++)
        {
            if(y > x)
                matrix[x][y] = -1;
            else
                if(y < x)
                    matrix[x][y] = 1;
                else
                    matrix[x][y] = 0;
        }
    }

    apply_filter(source, radius,radius,matrix);

    for(int x = 0; x < size; x++)
        delete[] matrix[x];
    delete[] matrix;
}

void PTG::Filters::gain(greyscale & source, float coef, int offset)
{
    int size = source.size;
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = value * coef + offset;
            source.data[x][y] = cut(value);
        }
}

void PTG::Filters::split(greyscale & source, float coef)
{
    coef = 1.0 / coef;
    int size = source.size;
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = value / 255 * 2 - 1;
            if(value < 0)
                value = -pow(-value, coef);
            else
                value = pow(value, coef);
            value = (value + 1) / 2 * 255;
            source.data[x][y] = cut(value);
        }
}

void PTG::Filters::gamma(greyscale & source, float coef)
{
    coef = 1.0 / coef;
    int size = source.size;
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = value / 255;
            value = pow(value, coef);
            value = value *  255;
            source.data[x][y] = cut(value);
        }
}

void PTG::Filters::invert(greyscale & source)
{
    int size = source.size;
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = 255 - value;
            source.data[x][y] = cut(value);
        }
}


/*void PTG::Filters::normalize(greyscale & source)
{
    int size = source.size;
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = (value + 1) / 2 * 255;
            source.data[x][y] = cut(value);
        }
}*/

void PTG::Filters::maximize_contrast(greyscale & source)
{
    int size = source.size;
    float max = std::numeric_limits<float>::lowest();
    float min = std::numeric_limits<float>::max();

    for(int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (source.data[x][y] < min)
                min = source.data[x][y];

            if (source.data[x][y] > max)
                max = source.data[x][y];
        }
    }

    max = max - min;

    for(int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = (value - min) * 255.0 / max;
            source.data[x][y] = cut(value);
        }
    }
}

void PTG::Filters::contrast(greyscale & source, float coef, int offset)
{
    int size = source.size;
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
        {
            float value = source.data[x][y];
            value = value / 255 * 2 - 1;
            value = value * coef;
            value = (value + 1) / 2 * 255;
            value += offset;
            source.data[x][y] = cut(value);
        }
}
