#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdexcept>
#include <sstream>
#include <vector>

namespace osoasso
{

template<typename ValueType>
class matrix
{
public:
    matrix(std::initializer_list<std::initializer_list<ValueType>> list) : rows_(list.size()), columns_(0), data_()
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
                message << "Invalid number of columns in row " << row_number << " - Expected: " << columns_ << " Actual: " << i->size() << std::endl;
                throw std::invalid_argument(message.str());
            }

            data_.push_back(std::vector<ValueType>(i->begin(), i->end()));

            row_number++;
        }
    }

    size_t rows() const
    {
        return rows_;
    }

    size_t columns() const
    {
        return columns_;
    }

    ValueType operator()(size_t row, size_t column)
    {
        if (column == 0 || column > columns_)
        {
            std::stringstream message;
            message << "Invalid index - actual number of columns: " << columns_ << " requested index:  " << column << std::endl;
            throw std::invalid_argument(message.str());
        }
        else if (row == 0 || row > rows_)
        {
            std::stringstream message;
            message << "Invalid index - actual number of rows: " << columns_ << " requested index:  " << column << std::endl;
            throw std::invalid_argument(message.str());
        }

        return data_[row-1][column-1];
    }

    class iterator : public std::iterator<std::forward_iterator_tag, ValueType, ptrdiff_t, const ValueType*, const ValueType&>
    {
    public:
        iterator() : matrix_(NULL), current_row_index_(0), current_column_index_(0)
        {
        }

        iterator(const matrix<ValueType>* matrix) : matrix_(matrix), current_row_index_(0), current_column_index_(0)
        {
        }

        const ValueType& operator*() const
        {
            return matrix_->data_[current_row_index_][current_column_index_];
        }

        //const ValueType* operator->() const;
        iterator& operator++()
        {
            ++current_column_index_;
            if (current_column_index_ >= matrix_->columns_)
            {
                current_column_index_ = 0;
                ++current_row_index_;
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator previous = *this;
            ++(*this);

            return previous;
        }

        //bool equal(iterator const& rhs) const;
    private:
        const matrix<ValueType>* matrix_;
        size_t current_row_index_;
        size_t current_column_index_;
    };


private:
    size_t rows_;
    size_t columns_;
    std::vector<std::vector<ValueType>> data_;

    // Prevent default construction, copy construction, and assignment
    matrix();
    matrix(const matrix& other);
    matrix& operator=(const matrix& other);
};

/*
template<typename T>
inline bool operator==(iterator<T> const& lhs, iterator<T> const& rhs)
{
    return lhs.equal(rhs);
}
*/

}

#endif // __MATRIX_H
