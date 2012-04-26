#include <vector>
#include "../test_harness/test.h"
#include "../include/parallel_task.h"

using namespace osoasso;

class integer_summer
{
public:
    integer_summer(int& result) : sum_(0), result_(result)
    {
    }

    template <typename IteratorType>
    void map(IteratorType begin, IteratorType end)
    {
        for (auto i = begin; i != end; ++i)
        {
            sum_ += *i;
        }
    }

    void reduce()
    {
        result_ += sum_;
    }

private:
    int sum_;
    int& result_;
};

Define(ParallelTask)
{
    It("Can sum a vector of integers serially")
    {
        std::vector<int> values(10, 1);
        int result = 0;

        integer_summer summer(result);

        auto task = make_parallel_task(values.begin(), values.end(), summer);
        task.start();
        task.complete();

        AssertEqual(10, result);
    } Done
}
