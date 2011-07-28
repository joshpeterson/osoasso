#ifndef __MATRIX_BLOBBER_H
#define __MATRIX_BLOBBER_H

#include "matrix.h"
#include "blob.h"
#include "matrix_iterator_with_size.h"

namespace osoasso
{

template <typename ValueType>
class matrix_blobber
{
public:
    blob<ValueType> make_blob(const matrix<ValueType>& matrix) const
    {
        matrix_iterator_with_size<ValueType> it(&matrix);
        matrix_iterator_with_size<ValueType> end;

        return blob<double>(it, end);
    }

private:
};

}

#endif // __MATRIX_BLOBBER_H
