#include "../test_harness/test.h"
#include "../include/identity.h"

using namespace osoasso;

Define(Identity)
{
    It("Produces the 2x2 identity matrix")
    {
        auto size = std::shared_ptr<matrix<double>>(new matrix<double>({{2}}));
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0}, {0, 1}}));

        identity identity_command;

        auto result = identity_command.call(size, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Produces the 3x3 identity matrix")
    {
        auto size = std::shared_ptr<matrix<double>>(new matrix<double>({{3}}));
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));

        identity identity_command;

        auto result = identity_command.call(size, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Overloaded () operator converts integer input to a matrix")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0}, {0, 1}}));

        identity identity_command;

        auto result = identity_command(2);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Throws an exception when called with an input of a size that is not 1,1")
    {
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));

        identity identity_command;

        bool exception_thrown = false;
        try
        {
            identity_command.call(matrix1, 1);
        }
        catch(const std::invalid_argument&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done
}
