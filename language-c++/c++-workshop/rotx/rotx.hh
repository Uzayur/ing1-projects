#pragma once

#include <iostream>

#include "encrypt.hh"

class RotX : public Encrypt
{
public:
    RotX(std::string message, int key);

    void process() const override;

protected:
    std::string message_;
    int key_;
};
