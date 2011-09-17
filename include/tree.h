#ifndef __TREE_H
#define __TREE_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <stack>

namespace osoasso
{

template <typename T>
struct node
{
    T value;
    size_t parent;
    std::vector<size_t> children;
};

// Invariant: No two elements with the same value are ever added (this is not enforced)
template <typename T>
class tree
{
public:
    tree() : nodes_(), head_index_(0)
    {
        node<T> root;
        nodes_.push_back(root);
    }

    T head() const
    {
        return nodes_[head_index_].value;
    }

    void insert(T value)
    {
        node<T> node;
        node.value = value;
        node.parent = head_index_;

        // The child will always have the index at the end of the vector.
        nodes_[head_index_].children.push_back(nodes_.size());

        nodes_.push_back(node);
        head_index_++;
    }

    void set_head(T new_head)
    {
        bool new_head_found = false;
        for (size_t i = 0; i < nodes_.size(); ++i)
        {
            if (nodes_[i].value == new_head)
            {
                head_index_ = i;
                new_head_found = true;
                break;
            }
        }

        if (!new_head_found)
        {
            std::stringstream message;
            message << "Unable to find a node with the value: " << new_head;
            throw std::domain_error(message.str());
        }
    }

    class iterator : public std::iterator<std::forward_iterator_tag, T, ptrdiff_t, const T*, const T&>
    {
    public:
        iterator() : tree_(NULL), parent_states_()
        {
            state_.node_index = 0;
            state_.child_index = 0;
        }

        explicit iterator(const tree<T>* tree) : tree_(tree), parent_states_()
        {
            state_.node_index = 1;
            state_.child_index = 0;
        }

        const T& operator*() const
        {
            return tree_->nodes_[state_.node_index].value;
        }

        const T* operator->() const
        {
            return &(*this);
        }

        iterator& operator++()
        {
            while (true)
            {
                if (tree_->nodes_[state_.node_index].children.size() > state_.child_index)
                {
                    // Traverse to the next child node
                    parent_states_.push(state_);
                    state_.node_index = tree_->nodes_[state_.node_index].children[state_.child_index];
                    state_.child_index = 0;
                    break;
                }
                else if (!parent_states_.empty())
                {
                    // No more children
                    state_ = parent_states_.top();
                    state_.child_index++;
                    parent_states_.pop();
                }
                else
                {
                    // Signal the end iterator
                    tree_ = NULL;
                    state_.node_index = 0;
                    state_.child_index = 0;
                    break;
                }
            }

            return *this;
        }

        iterator operator++(int)
        {
            iterator previous = *this;
            ++(*this);

            return previous;
        }

        bool equal(const iterator& other) const
        {
            return tree_ == other.tree_ && state_.node_index == other.state_.node_index &&
                   state_.child_index == other.state_.child_index;
        }

        bool operator==(const iterator& other) const
        {
            return equal(other);
        }

        bool operator!=(const iterator& other) const
        {
            return !equal(other);
        }

    private:
        const tree<T>* tree_;

        struct iterator_state
        {
            size_t node_index;
            size_t child_index;
        };

        std::stack<iterator_state> parent_states_;
        iterator_state state_;
    };

    iterator begin() const
    {
        return iterator(this);
    }

    iterator end() const
    {
        return iterator();
    }

    class head_branch_iterator : public std::iterator<std::forward_iterator_tag, T, ptrdiff_t, const T*, const T&>
    {
    public:
        head_branch_iterator() : tree_(NULL), current_index_(0)
        {
        }

        explicit head_branch_iterator(const tree<T>* tree) : tree_(tree), current_index_(tree->head_index_)
        {
        }

        const T& operator*() const
        {
            return tree_->nodes_[current_index_].value;
        }

        const T* operator->() const
        {
            return &(*this);
        }

        head_branch_iterator& operator++()
        {
            current_index_ = tree_->nodes_[current_index_].parent;
            if (current_index_ == 0)
            {
                // Signal the end iterator
                tree_ = NULL;
            }

            return *this;
        }

        head_branch_iterator operator++(int)
        {
            iterator previous = *this;
            ++(*this);

            return previous;
        }

        bool equal(const head_branch_iterator& other) const
        {
            return tree_ == other.tree_ && current_index_ == other.current_index_;
        }

        bool operator==(const head_branch_iterator& other) const
        {
            return equal(other);
        }

        bool operator!=(const head_branch_iterator& other) const
        {
            return !equal(other);
        }

    private:
        const tree<T>* tree_;
        size_t current_index_;
    };

    head_branch_iterator head_branch_begin() const
    {
        return head_branch_iterator(this);
    }

    head_branch_iterator head_branch_end() const
    {
        return head_branch_iterator();
    }

private:
    std::vector<node<T>> nodes_;
    size_t head_index_;
};

}

#endif // __TREE_H
