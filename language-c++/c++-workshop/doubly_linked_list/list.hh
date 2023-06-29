#pragma once

#include <optional>
#include <ostream>

#include "node.hh"

class List
{
public:
    List();

    void push_front(int i);
    void push_back(int i);
    std::optional<int> pop_front();
    std::optional<int> pop_back();
    void print(std::ostream& os) const;
    int length() const;

private:
    int nb_elts_;
    std::shared_ptr<Node> first_;
    std::shared_ptr<Node> last_;
};
