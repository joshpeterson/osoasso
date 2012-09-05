#include <memory>
#include "../test_harness/test.h"
#include "../include/max_off_diagonal_indexes.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(MaxOffDiagonalIndexes)
{
    It ("Finds a vector of the non-diagonal indexes which have the greatest value in each row")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                          {1.0, 1.0, 9.41},
                                                                          {3.10, 9.41, 3.14}}));
        /*auto result = */max_off_diagonal_indexes(input);
    } Done
}
