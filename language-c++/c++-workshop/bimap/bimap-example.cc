#include <iostream>
#include <string>

#include "bimap.hh"

int main()
{
    Bimap<int, std::string> bm;

    bm.insert(16, "Test.");
    bm.insert("Prologin", 29);

    std::cout << "The bimap contains: " << bm.size() << " elements\n";

    auto it1 = bm.find("Test.");
    auto it2 = bm.find(29);

    std::cout << it1->first << ' ' << it1->second << '\n';
    std::cout << it2->first << ' ' << it2->second << '\n';

    bm.erase(16);
    bm.erase("Prologin");

    bm.clear();
    return 0;
}
