#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "tree.hh"

class Builder
{
public:
    Builder(const std::string& filename);
    std::shared_ptr<tree::Tree> create_leaf(int c, bool neg);
    std::shared_ptr<tree::Tree> build();

private:
    std::shared_ptr<tree::Tree> create_node(const std::string& op);
    std::stringstream in_;
};
