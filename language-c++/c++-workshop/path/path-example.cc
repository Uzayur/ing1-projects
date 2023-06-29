#include <iostream>

#include "unix-path.hh"
#include "windows-path.hh"

int main()
{
    //    auto windows = WindowsPath('E');

    //  std::cout << windows.join("Users").join("YAKA").join("cpp").to_string()
    //           << '\n'; /* E:\Users\YAKA\cpp\ */

    auto unix = UnixPath();

    std::cout << unix.join("home").join("yaka").join("cpp").to_string()
              << '\n'; // /home/yaka/cpp/

    std::cout << unix.join("main.cc", true).to_string()
              << '\n'; // /home/yaka/cpp/main.cc
}
