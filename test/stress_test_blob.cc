#include <vector>
#include "../test_harness/test.h"
#include "../test/timer.h"
#include "../test/million_doubles.h"
#include "../include/blob.h"

using namespace osoasso;

std::vector<double> load_doubles();

Define(StressTestBlob)
{
    It("Blobs 1 Million Doubles")
    {
        std::vector<double> input_vector = load_doubles();

        timer blob_timer;

        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());

        std::cout << " Time to blob: " << blob_timer.elapsed() << "s" << std::endl;
    }

    It("Converts Blob Of 1 Million Doubles Back To Doubles")
    {
        std::vector<double> input_vector = load_doubles();

        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());

        timer values_timer;

        std::vector<double> doubles = test_blob.values();

        std::cout << " Time to convert: " << values_timer.elapsed() << "s" << std::endl;
    }
}
