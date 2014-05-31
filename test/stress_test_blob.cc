#include <vector>
#include <iostream>
#include <random>
#include "../test_harness/test.h"
#include "../include/timer.h"
#include "../include/blob.h"

using namespace osoasso;

std::vector<double> load_doubles()
{
    double lower_bound = 0;
    double upper_bound = 10000;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;

    std::vector<double> many(1000000);
    for (auto i = 0; i < 1000000;++i)
        many.push_back(unif(re));

    return many;
}

Define(StressTestBlob)
{
    It("Blobs 1 Million Doubles")
    {
        std::vector<double> input_vector = load_doubles();

        timer blob_timer;

        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());

        std::cout << " Time to blob: " << blob_timer.elapsed() << "s" << std::endl;
    } Done

    It("Converts Blob Of 1 Million Doubles Back To Doubles")
    {
        std::vector<double> input_vector = load_doubles();

        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());

        timer values_timer;

        std::vector<double> doubles = test_blob.values();

        std::cout << " Time to convert: " << values_timer.elapsed() << "s" << std::endl;
    } Done
}
