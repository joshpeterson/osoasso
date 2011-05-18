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

    std::vector<T> values() const
    {
        std::vector<T> values;

        auto i = data_.cbegin();
        while (i != data_.cend())
        {
            blobber<T> blobber;
            for (size_t j = 0; j < sizeof(T); ++j)
            {
                blobber.bytes[j] = *i;
                ++i;
            }

            values.push_back(blobber.value);
        }

        return values;
    }

private:
    std::vector<unsigned char> data_;
};

}

#endif // __BLOB_H
