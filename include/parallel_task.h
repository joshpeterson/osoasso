#ifndef __PARALELL_TASK_H
#define __PARALELL_TASK_H

namespace osoasso
{

template <typename IteratorType, typename TaskType>
class parallel_task
{
public:
    parallel_task(IteratorType begin, IteratorType end, TaskType task) : begin_(begin), end_(end), task_(task)
    {
    }

    void start()
    {
        task_.map(begin_, end_);
    }

    void complete()
    {
        task_.reduce();
    }

private:
    IteratorType begin_;
    IteratorType end_;
    TaskType task_;
};

template <typename IteratorType, typename TaskType>
parallel_task<IteratorType, TaskType> make_parallel_task(IteratorType begin, IteratorType end, TaskType task)
{
    return parallel_task<IteratorType, TaskType>(begin, end, task);
}

}

#endif // __PARALELL_TASK_H
