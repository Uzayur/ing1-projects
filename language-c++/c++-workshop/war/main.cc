#include "assassin.hh"
#include "knight.hh"
#include "regiment.hh"
#include "soldier.hh"

int main()
{
    Soldier s1;
    Knight k1;
    Assassin a1;
    Regiment r1;
    r1.add_soldier(&s1);
    r1.add_soldier(&k1);
    r1.add_soldier(&a1);
    r1.scream();
    r1.print_state();
    Soldier enemy;
    enemy.attack(s1);
    enemy.attack(a1);
    r1.print_state();

    Regiment r2;
    r2.join_by(r1);
    std::cout << "######\n";
    r2.print_state();

    return 0;
}
