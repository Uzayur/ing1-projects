#pragma once

#include <string>

class DirectoryInfo
{
public:
    DirectoryInfo(const std::string& name, unsigned int size,
                  unsigned int rights, const std::string& owner)
        : name_(name)
        , size_(size)
        , rights_(rights)
        , owner_(owner)
    {}

    std::string get_name() const
    {
        return name_;
    }

    unsigned int get_size() const
    {
        return size_;
    }

    unsigned int get_rights() const
    {
        return rights_;
    }

    std::string get_owner() const
    {
        return owner_;
    }

private:
    std::string name_;
    unsigned int size_;
    unsigned int rights_;
    std::string owner_;
};
