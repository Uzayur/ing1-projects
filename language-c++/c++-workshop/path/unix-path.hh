#pragma once

#include "path.hh"

class UnixPath : public Path
{
public:
    UnixPath() = default;
    virtual ~UnixPath() = default;

    virtual std::string to_string() const override;
};
