#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<std::string>> parse_csv(const std::string& file_name);
