#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdexcept>

namespace osoasso
{

template<typename ValueType>
class matrix
{
public:
    matrix(std::initializer_list<std::initializer_list<ValueType>> list) : rows_(list.size()), columns_(0)
    {
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            if (columns_ == 0)
            {
                columns_ = i->size();
            }
        }
    }

    matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns)
    {
    };

    size_t rows() const
    {
        return rows_;
    }

    size_t columns() const
    {
        return columns_;
    }

private:
    size_t rows_;
    size_t columns_;
};

}

#endif // __MATRIX_H
