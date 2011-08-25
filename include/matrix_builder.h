#ifndef __MATRIX_BUILDER_H
#define __MATRIX_BUILDER_H

#include <vector>
#include <sstream>
#include <stdexcept>
#include "matrix.h"

namespace osoasso
{

template <typename ValueType>
class matrix_builder
{
public:
    matrix_builder() : matrix_(), current_row_(), done_called_(false)
    {
    }

    void add(ValueType value)
    {
        current_row_.push_back(value);
        if (current_row_.size() > matrix_.columns_)
        {
            if (matrix_.rows_ == 1)
            {
                // This is still the first row, keep adding columns
                ++matrix_.columns_;
            }
            else
            {
                std::stringstream message;
                message << "Matrix being built already has a size of " << matrix_.rows_ << "x" << matrix_.columns_ << ". Unable to add another column.";
                throw std::logic_error(message.str());
            }
        }
    }

    void new_row()
    {
        ++matrix_.rows_;
        if (matrix_.rows_ > 1)
        {
            matrix_.data_.push_back(current_row_);
            current_row_.clear();
        }
    }

    matrix<ValueType> done()
    {
        if (done_called_)
        {
            throw std::logic_error("The done method can only be called once on a matrix_builder instance.");
        }

        done_called_ = true;

        matrix_.data_.push_back(current_row_);
        current_row_.clear();

        return matrix_;
    }

private:
    matrix<ValueType> matrix_;
    std::vector<ValueType> current_row_;
    bool done_called_;
};

}

#endif // __MATRIX_BUILDER_H
