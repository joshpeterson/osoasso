#ifndef __PARALELL_TASK_H
#define __PARALELL_TASK_H

#include <vector>
#include <utility>
#include <memory>

namespace osoasso
{

template <typename IteratorType, typename TaskType, typename TaskConstructorArgumentType>
class parallel_task
{
private:
    struct task_thread_data;

public:
    parallel_task(IteratorType begin, IteratorType end, TaskType& task, TaskConstructorArgumentType argument, int number_of_threads)
        : begin_(begin), end_(end), original_task_(task), argument_(argument), created_tasks_(), number_of_threads_(number_of_threads)
    {
    }

    void start()
    {
        int range_size = std::distance(begin_, end_);
        int task_range_size = range_size / number_of_threads_;
        int number_of_leftover_tasks_for_last_range = range_size % number_of_threads_;

        auto it = begin_;
        for (int i = 0; i < number_of_threads_; ++i)
        {
            auto thread_data = std::make_shared<task_thread_data>(argument_);
            thread_data->begin = it;
            std::advance(it, task_range_size);
            if (i == number_of_threads_ - 1)
                std::advance(it, number_of_leftover_tasks_for_last_range);
            thread_data->end = it;
            
            pthread_t task_handle;
            pthread_create(&task_handle, NULL, &ApplyTask, thread_data.get());

            created_tasks_.push_back(std::make_pair(task_handle, thread_data));
        }
    }

    void complete()
    {
        for (auto created_task = created_tasks_.begin(); created_task != created_tasks_.end(); ++created_task)
        {
            pthread_join(created_task->first, NULL);
            original_task_.reduce(created_task->second->task);
        }
    }

private:
    struct task_thread_data
    {
        task_thread_data(TaskConstructorArgumentType argument) : task(argument)
        {
        }

        IteratorType begin;
        IteratorType end;
        TaskType task;
    };

    IteratorType begin_;
    IteratorType end_;
    TaskType& original_task_;
    TaskConstructorArgumentType argument_;
    std::vector<std::pair<pthread_t, std::shared_ptr<task_thread_data>>> created_tasks_;
    int number_of_threads_;

    static void* ApplyTask(void* thread_data_input)
    {
        task_thread_data* thread_data = static_cast<task_thread_data*>(thread_data_input);
        thread_data->task.map(thread_data->begin, thread_data->end);

        return NULL;
    }
};

template <typename IteratorType, typename TaskType, typename TaskConstructorArgumentType>
parallel_task<IteratorType, TaskType, TaskConstructorArgumentType> make_parallel_task(IteratorType begin, IteratorType end, TaskType& task,
                                                                                      TaskConstructorArgumentType argument, int number_of_threads)
{
    return parallel_task<IteratorType, TaskType, TaskConstructorArgumentType>(begin, end, task, argument, number_of_threads);
}

}

#endif // __PARALELL_TASK_H
