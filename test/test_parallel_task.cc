#include <vector>
#include "../test_harness/test.h"
#include "../include/parallel_task.h"

using namespace osoasso;

class integer_summer
{
public:
    integer_summer() : sum_(0)
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

    void reduce(const integer_summer& other)
    {
        sum_ += other.sum_;
    }

    int get_sum() const
    {
        return sum_;
    }

private:
    int sum_;
};

Define(ParallelTask)
{
    It("Can sum a vector of integers serially")
    {
        std::vector<int> values(10, 1);

        integer_summer summer;

        auto task = make_parallel_task(values.begin(), values.end(), summer, 1);
        task.start();
        task.complete();

        AssertEqual(10, summer.get_sum());
    } Done

    It("Can sum a vector of integers on two threads")
    {
        std::vector<int> values(10, 1);

        integer_summer summer;

        auto task = make_parallel_task(values.begin(), values.end(), summer, 2);
        task.start();
        task.complete();

        AssertEqual(10, summer.get_sum());
    } Done

    It("Can sum a vector of integers on three threads")
    {
        std::vector<int> values(10, 1);

        integer_summer summer;

        auto task = make_parallel_task(values.begin(), values.end(), summer, 3);
        task.start();
        task.complete();

        AssertEqual(10, summer.get_sum());
    } Done

    It("Can sum a vector of many integers on two threads")
    {
        std::vector<int> values(10000, 1);

        integer_summer summer;

        auto task = make_parallel_task(values.begin(), values.end(), summer, 2);
        task.start();
        task.complete();

        AssertEqual(10000, summer.get_sum());
    } Done
}
