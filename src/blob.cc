#include "../include/blob.h"

using namespace osoasso;

blob::blob(std::vector<double> values)
{
    for (auto i = values.cbegin(); i != values.cend(); ++i)
    {
        double_blobber blobber;
        blobber.value = *i;
        for (size_t j = 0; j < sizeof(double); ++j)
        {
            data_.push_back(blobber.bytes[j]);
        }
    }
}

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
        double_blobber blobber;
        for (size_t j = 0; j < sizeof(double); ++j)
        {
            blobber.bytes[j] = *i;
            ++i;
        }

        doubles.push_back(blobber.value);
    }

    return doubles;
}
