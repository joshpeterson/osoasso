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

class blob
{
public:
    template<typename T>
    blob(T start, T end)
    {
        for (T i = start; i != end; ++i)
        {
            blobber<typename T::value_type> blobber;
            blobber.value = *i;
            for (size_t j = 0; j < sizeof(typename T::value_type); ++j)
            {
                data_.push_back(blobber.bytes[j]);
            }
        }
    }

    std::vector<unsigned char> data() const;
    std::vector<double> double_data() const;

private:
    std::vector<unsigned char> data_;
};

}

#endif // __BLOB_H
