#include "game.hh"

void Game::play(Player& p1, Player& p2)
{
    if (&p1 == &p2)
        throw InvalidArgumentException("Stop playing by yourself!");
}
