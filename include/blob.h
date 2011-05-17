#ifndef __BLOB_H
#define __BLOB_H

#include <vector>

namespace osoasso
{

template <typename T>
union blobber
{
    T value;
    unsigned char bytes[sizeof(double)];
};

template<typename T>
class blob
{
public:
    template <typename U>
    blob(U start, U end)
    {
        static_assert(std::is_same<typename U::value_type, T>::value, "The template parameter for the blob be the same as the value_type of the iterator.");
        for (U i = start; i != end; ++i)
        {
            blobber<typename U::value_type> blobber;
            blobber.value = *i;
            for (size_t j = 0; j < sizeof(typename U::value_type); ++j)
            {
                data_.push_back(blobber.bytes[j]);
            }
        }
    }

    std::vector<unsigned char> data() const
    {
        return data_;
    }

    std::vector<double> double_data() const
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

private:
    std::vector<unsigned char> data_;
};

}

#endif // __BLOB_H
