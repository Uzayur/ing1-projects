#include <iostream>

#include "game.hh"
#include "invalid-argument.hh"
#include "player.hh"

int main()
{
    Game g;
    std::string n1 = "Toto";
    std::string n2 = "Jesus";
    std::string n3 = "God";
    std::string n4 = "Pikachu";
    std::string n5 = "";

    try
    {
        Player p1 = Player(n1, 9);
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        Player p2 = Player(n2, 33);
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        Player p3 = Player(n3, 5000); // Approximative.
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        Player p4 = Player(n4, 25);
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        Player p5 = Player(n5, 19);
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        Player p1 = Player(n1, 9);
        Player p2 = Player(n2, 33);
        g.play(p1, p2);
        g.play(p1, p1);
    }
    catch (InvalidArgumentException& e)
    {
        std::cout << e.what() << std::endl;
    }
}
