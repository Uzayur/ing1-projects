#pragma once

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

class WordChecker
{
public:
    WordChecker(std::string path)
        : path_(path)
    {}

    bool operator()(std::string word);

private:
    std::string path_;
};
