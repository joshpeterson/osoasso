#ifndef __PARALELL_TASK_H
#define __PARALELL_TASK_H

#include <vector>

namespace osoasso
{

template <typename IteratorType, typename TaskType>
class parallel_task
{
public:
    parallel_task(IteratorType begin, IteratorType end, TaskType& task, int number_of_threads) : begin_(begin), end_(end), original_task_(task),
                                                                                                 created_tasks_(), number_of_threads_(number_of_threads)
    {
    }

    void start()
    {
        int range_size = std::distance(begin_, end_);
        int task_range_size = range_size / number_of_threads_;

        auto it = begin_;
        for (int i = 0; i < number_of_threads_; ++i)
        {
            TaskType created_task;
            created_tasks_.push_back(created_task);
            auto task_begin = it;
            std::advance(it, task_range_size);
            created_tasks_[i].map(task_begin, it);
        }
    }

    void complete()
    {
        for (auto created_task = created_tasks_.begin(); created_task != created_tasks_.end(); ++created_task)
        {
            original_task_.reduce(*created_task);
        }
    }

private:
    IteratorType begin_;
    IteratorType end_;
    TaskType& original_task_;
    std::vector<TaskType> created_tasks_;
    int number_of_threads_;

    struct task_thread_data
    {
        IteratorType begin;
        IteratorType end;
        TaskType task;
    };

    static void* ApplyTask(void* thread_data_input)
    {
        task_thread_data* thread_data = static_cast<task_thread_data*>(thread_data_input);
        thread_data->task.map(thread_data->begin, thread_data->end);

        return NULL;
    }
};

template <typename IteratorType, typename TaskType>
parallel_task<IteratorType, TaskType> make_parallel_task(IteratorType begin, IteratorType end, TaskType& task, int number_of_threads)
{
    return parallel_task<IteratorType, TaskType>(begin, end, task, number_of_threads);
}

}

#endif // __PARALELL_TASK_H
