#include <iostream>

#include "auction.hh"
#include "person.hh"

int main(void)
{
    auto p1 = Person("JP", 100);
    auto p2 = Person("Claude", 50);

    p1.add_nft(create_nft("Singe"));

    std::cout << p1;
    std::cout << p2;

    p2.add_nft(p1.remove_nft("Singe"));

    std::cout << p1;
    std::cout << p2;

    auto p3 = Person("Marie", 20);
    std::cout << p1;
    std::cout << p2;
    std::cout << p3;

    {
        Auction auction(p2, p2.remove_nft("Singe"), 10);
        std::cout << p1;
        std::cout << p2;
        std::cout << p3;

        auction.bid(p1, 20);
    }
    std::cout << p1;
    std::cout << p2;
    std::cout << p3;
}
