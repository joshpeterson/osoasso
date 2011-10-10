#include "../test_harness/test.h"
#include "../include/utility.h"

using namespace osoasso;

Define(DoubleEqual)
{
    It("Should compare two literal doubles equal")
    {
        AssertTrue(double_equal(0.38, 0.38));
    } Done

    It("Should compare two unequal literal ints not equal")
    {
        AssertFalse(double_equal(6, 7));
    } Done

    It("Should compare two doubles four ulps apart equal when rhs > lhs")
    {
        double_bytes converter;

        converter.int_value = 4622854945503266734LL;
        double lhs = converter.double_value;

        converter.int_value = 4622854945503266738LL;
        double rhs = converter.double_value;

        AssertTrue(double_equal(lhs, rhs));
    } Done

    It("Should compare two doubles four ulps apart equal when lhs > rhs")
    {
        double_bytes converter;

        converter.int_value = 4622854945503276739LL;
        double lhs = converter.double_value;

        converter.int_value = 4622854945503276735LL;
        double rhs = converter.double_value;

        AssertTrue(double_equal(lhs, rhs));
    } Done

    It("Should compare compare zero and negative zero equal")
    {
        double_bytes converter;

        double lhs = 0.0;

        converter.int_value = 0x8000000000000000LL;
        double rhs = converter.double_value;

        AssertTrue(double_equal(lhs, rhs));
    } Done
}
