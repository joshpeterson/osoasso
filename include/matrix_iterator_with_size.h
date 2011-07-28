#ifndef __MATRIX_ITERATOR_WITH_SIZE_H
#define __MATRIX_ITERATOR_WITH_SIZE_H

#include <iterator>
#include "matrix.h"

namespace osoasso
{

template<typename ValueType>
class matrix_iterator_with_size : public std::iterator<std::forward_iterator_tag, ValueType, ptrdiff_t,
                                                const ValueType*, const ValueType&>
{
public:
    matrix_iterator_with_size() : rows_(0), row_size_returned_(false), columns_(0),
                                  column_size_returned_(false), matrix_iterator_()
    {
    }

    explicit matrix_iterator_with_size(const matrix<ValueType>* matrix) : rows_(matrix->rows()),
                                                                          row_size_returned_(false),
                                                                          columns_(matrix->columns()),
                                                                          column_size_returned_(false),
                                                                          matrix_iterator_(matrix)
    {
    }

    const ValueType& operator*() const
    {
        if (!row_size_returned_)
        {
            return rows_;
        }
        else if (!column_size_returned_)
        {
            return columns_;
        }

        return *matrix_iterator_;
    }

    const ValueType* operator->() const
    {
        return &(*this);
    }

    matrix_iterator_with_size& operator++()
    {
        if (!row_size_returned_)
        {
            row_size_returned_ = true;
        }
        else if (!column_size_returned_)
        {
            column_size_returned_ = true;
        }
        else
        {
            ++matrix_iterator_;
        }

        typename matrix<ValueType>::iterator end;
        if (matrix_iterator_ == end)
        {
            // Signal the end iterator
            rows_ = 0;
            row_size_returned_ = false;
            columns_ = 0;
            column_size_returned_ = false;
            matrix_iterator_ = end;
        }

        return *this;
    }

    matrix_iterator_with_size operator++(int)
    {
        matrix_iterator_with_size previous = *this;
        ++(*this);

        return previous;
    }

    bool equal(const matrix_iterator_with_size& other) const
    {
        return row_size_returned_ == other.row_size_returned_ &&
               column_size_returned_ == other.column_size_returned_ &&
               matrix_iterator_ == other.matrix_iterator_;
    }

    bool operator==(const matrix_iterator_with_size& other) const
    {
        return equal(other);
    }

    bool operator!=(const matrix_iterator_with_size& other) const
    {
        return !equal(other);
    }

private:
    double rows_;
    bool row_size_returned_;
    double columns_;
    bool column_size_returned_;
    typename matrix<ValueType>::iterator matrix_iterator_;
};

}

#endif // __MATRIX_ITERATOR_WITH_SIZE_H
