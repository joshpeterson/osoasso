#ifndef __MATRIX_BLOBBER_H
#define __MATRIX_BLOBBER_H

#include <memory>
#include "matrix.h"
#include "blob.h"
#include "matrix_iterator_with_size.h"

namespace osoasso
{

template <typename ValueType>
class matrix_blobber
{
public:
    std::shared_ptr<const blob<ValueType>> make_blob(std::shared_ptr<const matrix<ValueType>> matrix) const
    {
        matrix_iterator_with_size<ValueType> it(matrix.get());
        matrix_iterator_with_size<ValueType> end;

        return std::shared_ptr<const blob<ValueType>>(new blob<ValueType>(it, end));
    }

private:
};

}

#endif // __MATRIX_BLOBBER_H
