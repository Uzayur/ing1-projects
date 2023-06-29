#include "stack-creation-failed.hh"

StackCreationFailed::StackCreationFailed(const std::string& msg)
    : msg_(msg)
{}

const char* StackCreationFailed::what() const noexcept
{
    return msg_.c_str();
}
