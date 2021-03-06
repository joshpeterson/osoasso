#include <vector>
#include "../test_harness/test.h"
#include "../include/blob.h"

using namespace osoasso;

Define(Blob)
{
    It("Generates the correct data with doubles as input")
    {
        std::vector<double> input_vector = { 3.14, 2.72, 4.5 };
        std::vector<unsigned char> expected_data = { 31, 133, 235, 81, 184, 30, 9, 64, 195, 245, 40, 92, 143, 194, 5, 64, 0, 0, 0, 0, 0, 0, 18, 64 };

        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());

        AssertElementsEqual(expected_data, test_blob.data());
    } Done

    It("Converts from a blob back to a vector of doubles")
    {
        std::vector<double> input_vector = { 3.14, 2.72, 4.5 };

        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());

        AssertElementsEqual(input_vector, test_blob.values());
    } Done

    It("Generates the correct SHA1 hash for the data")
    {
        std::vector<double> input_vector = { 3.14, 2.72, 4.5 };
        blob<double> test_blob(input_vector.cbegin(), input_vector.cend());
        AssertEqual("6cb55993 6305f293 2afa1187 a2e3ef96 edd191b7", test_blob.name());
    } Done
}

