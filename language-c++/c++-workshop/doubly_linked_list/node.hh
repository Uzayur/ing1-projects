#pragma once

#include <memory>

class Node
{
public:
    Node(int v);

    int val_get() const;
    void val_set(int val);
    std::shared_ptr<Node> next_get() const;
    void next_set(std::shared_ptr<Node> next);
    std::shared_ptr<Node> prev_get() const;
    void prev_set(std::shared_ptr<Node> prev);

private:
    int val_;
    std::shared_ptr<Node> next_;
    std::weak_ptr<Node> prev_;
};
