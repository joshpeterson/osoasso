#ifndef __SSE2_ALIGNED_ALLOCATOR_H
#define __SSE2_ALIGNED_ALLOCATOR_H

#include <stddef.h>
#include <new>
#include <stdexcept>
#include <malloc.h> 

// Based on Stephan T. Lavavej's blog post here: http://blogs.msdn.com/b/vcblog/archive/2008/08/28/the-sse2_aligned_allocator.aspx
template <typename T> class sse2_aligned_allocator
{
public:
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
 
    T* address(T& r) const
	{
        return &r;
    }
 
    const T* address(const T& s) const
	{
        return &s;
    }
 
    size_t max_size() const
	{
        return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T);
    }
 
    template <typename U> struct rebind
	{
        typedef sse2_aligned_allocator<U> other;
    };
 
    bool operator!=(const sse2_aligned_allocator& other) const
	{
        return !(*this == other);
    }
 
    void construct(T* const p, const T& t) const
	{
        void * const pv = static_cast<void *>(p);
        new (pv) T(t);
    }
 
    void destroy(T* const p) const;
 
    bool operator==(const sse2_aligned_allocator& other) const
	{
        return true;
    }
 
    sse2_aligned_allocator() { }
    sse2_aligned_allocator(const sse2_aligned_allocator&) { }
    template <typename U> sse2_aligned_allocator(const sse2_aligned_allocator<U>&) { }
    ~sse2_aligned_allocator() { }
 
    T* allocate(const size_t n) const
	{ 
        if (n == 0)
		{
            return NULL;
        }

        if (n > max_size())
		{
            throw std::length_error("sse2_aligned_allocator<T>::allocate() - Integer overflow.");
        }

        void* pv = memalign(16, n * sizeof(T));
 
        if (pv == NULL)
		{
            throw std::bad_alloc();
        }
 
        return static_cast<T*>(pv);
    }
 
    void deallocate(T* const p, const size_t n) const
	{
        free(p);
    }
 
    template <typename U> T* allocate(const size_t n, const U* /* const hint */) const
	{
        return allocate(n);
    }
 
private:
    sse2_aligned_allocator& operator=(const sse2_aligned_allocator&);
};
 
template <typename T> void sse2_aligned_allocator<T>::destroy(T* const p) const
{
    p->~T();
}

#endif // __SSE2_ALIGNED_ALLOCATOR_H
