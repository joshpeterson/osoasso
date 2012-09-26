#include <memory>
#include "../test_harness/test.h"
#include "../include/max_off_diagonal_index.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(MaxOffDiagonalIndex)
{
    It ("Finds the index of the non-diagonal entry which has the greatest value")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                         {1.0, 1.0, 9.41},
                                                                         {3.10, 9.41, 3.14}}));
        std::pair<size_t, size_t> expected = {2, 3};
        auto result = find_max_off_diagonal_index(*input);
        
        AssertEqual(expected, result);
    } Done

    It ("Finds the index of the non-diagonal entry which has the greatest absolute value")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, -10.10},
                                                                         {1.0, 1.0, 9.41},
                                                                         {-10.10, -9.41, 3.14}}));
        std::pair<size_t, size_t> expected = {1, 3};
        auto result = find_max_off_diagonal_index(*input);
        
        AssertEqual(expected, result);
    } Done
}
