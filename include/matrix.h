#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdexcept>
#include <sstream>
#include <vector>
#include "blob.h"

namespace osoasso
{
template <typename T> class matrix_builder;

template<typename ValueType>
class matrix
{
public:
    matrix() : rows_(0), columns_(0), data_()
    {
    }

    matrix(std::initializer_list<std::initializer_list<ValueType>> list) : rows_(list.size()), columns_(0),
                                                                           data_()
    {
        int row_number = 1;
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            if (columns_ == 0)
            {
                columns_ = i->size();
            }
            else if (columns_ != i->size())
            {
                std::stringstream message;
                message << "Invalid number of columns in row " << row_number << " - Expected: " 
                        << columns_ << " Actual: " << i->size() << std::endl;
                throw std::invalid_argument(message.str());
            }

            data_.push_back(std::vector<ValueType>(i->begin(), i->end()));

            row_number++;
        }
    }

    matrix(const matrix<ValueType>& other) : rows_(other.rows_), columns_(other.columns_),
                                             data_(other.data_)
    {
    }

    matrix(matrix<ValueType>&& other) : rows_(other.rows_), columns_(other.columns_),
                                        data_(std::move(other.data_))
    {
    }

    matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns), data_()
    {
        for (size_t i = 0; i < rows_; ++i)
        {
            data_.push_back(std::vector<ValueType>(columns_));
        }
    }

    matrix& operator=(const matrix<ValueType>& other)
    {
        rows_ = other.rows_;
        columns_ = other.columns_;
        data_ = other.data_;

        return *this;
    }

    size_t rows() const
    {
        return rows_;
    }

    size_t columns() const
    {
        return columns_;
    }

    ValueType operator()(size_t row, size_t column) const
    {
        validate_row(row);
        validate_column(column);

        return data_[row-1][column-1];
    }

    ValueType& operator()(size_t row, size_t column)
    {
        validate_row(row);
        validate_column(column);

        return data_[row-1][column-1];
    }

    class iterator : public std::iterator<std::forward_iterator_tag, ValueType, ptrdiff_t,
                                          const ValueType*, const ValueType&>
    {
    public:
        iterator() : matrix_(NULL), current_row_index_(0), current_column_index_(0)
        {
        }

        explicit iterator(const matrix<ValueType>* matrix) : matrix_(matrix), current_row_index_(0),
                                                             current_column_index_(0)
        {
        }

        const ValueType& operator*() const
        {
            return matrix_->data_[current_row_index_][current_column_index_];
        }

        const ValueType* operator->() const
        {
            return &(*this);
        }

        iterator& operator++()
        {
            ++current_column_index_;
            if (current_column_index_ >= matrix_->columns_)
            {
                current_column_index_ = 0;
                ++current_row_index_;
            }

            if (current_row_index_ >= matrix_->rows_)
            {
                // Signal the end iterator
                matrix_ = NULL;
                current_row_index_ = 0;
                current_column_index_ = 0;
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator previous = *this;
            ++(*this);

            return previous;
        }

        bool equal(const iterator& other) const
        {
            return matrix_ == other.matrix_ && current_row_index_ == other.current_row_index_ &&
                   current_column_index_ == other.current_column_index_;
        }

        bool operator==(const iterator& other) const
        {
            return equal(other);
        }

        bool operator!=(const iterator& other) const
        {
            return !equal(other);
        }

    protected:
        const matrix<ValueType>* matrix_;

    private:
        size_t current_row_index_;
        size_t current_column_index_;
    };

    iterator begin() const
    {
        return iterator(this);
    }

    iterator end() const
    {
        return iterator();
    }

    template <typename T> friend class matrix_builder;

private:
    size_t rows_;
    size_t columns_;
    std::vector<std::vector<ValueType>> data_;

    void validate_row(size_t row) const
    {
        if (row == 0 || row > rows_)
        {
            std::stringstream message;
            message << "Invalid index - actual number of rows: " << rows_ << " requested index:  "
                    << row << std::endl;
            throw std::invalid_argument(message.str());
        }
    }

    void validate_column(size_t column) const
    {
        if (column == 0 || column > columns_)
        {
            std::stringstream message;
            message << "Invalid index - actual number of columns: " << columns_ << " requested index:  "
                    << column << std::endl;
            throw std::invalid_argument(message.str());
        }
    }
};

}

#endif // __MATRIX_H
