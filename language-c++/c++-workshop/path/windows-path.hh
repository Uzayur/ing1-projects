#pragma once

#include <array>

#include "path.hh"

class WindowsPath : public Path
{
public:
    WindowsPath(char drive);
    virtual ~WindowsPath() = default;

    virtual std::string to_string() const override;
    virtual Path& join(const std::string& tail, bool is_file = false) override;

private:
    const char drive_;

    static bool check_name(const std::string& name);
};
