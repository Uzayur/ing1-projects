#include "singleton.hh"

template <>
void Singleton<Logger>::open_log_file(const std::string& file)
{
    std::cout << "LOG: Opening file " << file << '\n';
}

template <>
void Singleton<Logger>::write_to_log_file()
{
    std::cout << "LOG: Writing into log file ..." << '\n';
}

template <>
void Singleton<Logger>::close_log_file()
{
    std::cout << "LOG: Closing log file ..." << '\n';
}
