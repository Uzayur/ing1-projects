#pragma once

#include <iostream>
#include <memory>
#include <optional>

class MyIntContainer
{
public:
    MyIntContainer(size_t size);

    // Print the content of the container
    void print() const;

    // Get the current number of elements inside the array
    size_t get_len() const;

    // Add an element inside the array
    bool add(int elem);

    // Get the last element inside the array and remove it
    std::optional<int> pop();

    // Get the element at a given position
    std::optional<int> get(size_t position) const;

    // Get the index inside the array of a given element
    std::optional<size_t> find(int elem) const;

    // Sort the array
    void sort();

    // Checks if the array is sorted
    bool is_sorted() const;

private:
    // Current size of the elems_ array
    size_t current_size_;

    // Maximum size of the elems_ array
    size_t max_size_;

    // Array containing the elements
    std::unique_ptr<int[]> elems_;
};
