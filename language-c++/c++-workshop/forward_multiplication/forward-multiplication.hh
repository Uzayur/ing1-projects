#pragma once

#include <functional>

using lambda_type = std::function<std::function<int(int)>(int)>;
lambda_type create_lambda();
