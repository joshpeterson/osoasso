#ifndef __BLOB_H
#define __BLOB_H

#include <vector>

namespace osoasso
{

union double_blobber
{
    double value;
    unsigned char bytes[sizeof(double)];
};

class blob
{
public:
    blob(std::vector<double> values);
    std::vector<unsigned char> data() const;
    std::vector<double> double_data() const;

private:
    std::vector<unsigned char> data_;
};

}

#endif // __BLOB_H
