#include "../include/blob.h"

using namespace osoasso;

std::vector<unsigned char> blob::data() const
{
    return data_;
}

std::vector<double> blob::double_data() const
{
    std::vector<double> doubles;

    auto i = data_.cbegin();
    while (i != data_.cend())
    {
        blobber<double> blobber;
        for (size_t j = 0; j < sizeof(double); ++j)
        {
            blobber.bytes[j] = *i;
            ++i;
        }

        doubles.push_back(blobber.value);
    }

    return doubles;
}
