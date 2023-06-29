#include "stack-empty.hh"

const char* StackEmpty::what() const noexcept
{
    return msg_.c_str();
}
