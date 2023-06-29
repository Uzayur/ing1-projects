/**
** \file stack.hh
** \brief Declaration of Stack.
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>

template <class T>
class Stack
{
public:
    /**
    ** Expose stack iterator type
    */
    using const_iterator = typename std::vector<T>::const_reverse_iterator;
    using iterator = typename std::vector<T>::reverse_iterator;

    Stack(size_t max_size = 100)
    {
        {
            max_size_ = max_size;

            try
            {
                vec_.reserve(max_size);
            }

            catch (std::length_error& e)
            {
                throw StackCreationFailed("Max stack size is too big.");
            }

            catch (std::bad_alloc& e)
            {
                throw StackCreationFailed("Allocation failed.");
            }
        }
    }

    /**
    ** Push element item on the stack
    ** and return the stack reference for chaining
    */
    Stack<T>& push(const T& item);
    Stack<T>& operator+=(const T& elt);
    Stack<T>& operator<<(const T& elt);

    /**
    ** Pop an element from the stack, return a copy of it
    */
    T pop();
    T operator--();

    /**
    ** Return the i-th element of the stack starting from the top of
    ** the stack and following a zero-based indexing
    ** for exemple stack[0] should return the top element value.
    */
    T operator[](size_t i);

    /**
    ** Compare two stacks, returns true if all elements
    ** from each stack have the same value and if the stacks
    ** have the same max sizes
    */
    bool operator==(Stack<T> stack);

    /**
    ** Print *this on the stream s
    ** All the elements must be separated by a single space,
    ** the top of the stack being the last displayed element.
    ** Do not add a newline nor space at the end!
    */
    std::ostream& print(std::ostream& s) const;

    /**
    ** begin returns the top of the stack
    ** end returns the bottom
    */
    const_iterator begin() const;
    iterator begin();

    const_iterator end() const;
    iterator end();

    /**
    ** Change the max size of the stack. If the new max_size is lower than the
    ** current_size pop the stack until the stack size match the new stack size
    */
    void resize(size_t t);
    /**
    ** Getter of the max_size of the stack
    */
    size_t max_size() const;

private:
    std::vector<T> vec_;
    size_t max_size_;
};

/**
** Print a stack on a stream using the stream operator<<
** We'll use this function to grade your work.
*/
template <class T>
std::ostream& operator<<(std::ostream& ostr, const Stack<T>& p);

#include "stack.hxx"
