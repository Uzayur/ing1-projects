#pragma once

#include <string>
#include <vector>

class Path
{
public:
    Path() = default;
    virtual ~Path() = default;

    /*
     ** Return the complete path as a string.
     */
    virtual std::string to_string() const = 0;

    /*
     ** Add a directory or a file at the end of the path.
     */
    virtual Path& join(const std::string& tail, bool is_file = false);

protected:
    std::vector<std::string> path_;
    bool final_ = false;
};
