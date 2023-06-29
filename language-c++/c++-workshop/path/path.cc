#include "path.hh"

Path& Path::join(const std::string& tail, bool is_file)
{
    if (final_)
        return Path();

    path_.push_back(tail);
    final_ = is_file;

    return &path_;
}
