package fr.epita.assistant.game.characters;

import fr.epita.assistant.game.utils.Coord;

public class Wizard extends Character {
    private int manaPoint;
    private Coord coord;

    public Wizard(Coord newCoord) {
        coord = newCoord;
        health = 100;
        armour = 15;
        isAlive = true;
        manaPoint = 100;
        name = "Intelli Jee";
    }

    public boolean isAlive() {
        return this.isAlive;
    }

    @Override
    public int getDamage() { return 0; }
    public Coord getCoord() { return coord; }

    public int getManaPoint() { return manaPoint; }
    public void setManaPoint(int newPoint) {
        if (newPoint <= 0)
            manaPoint = 0;

        else if (newPoint >= 100)
            manaPoint = 100;

        else
            manaPoint = newPoint;
    }

    @Override
    public void printStats() {
        var stringBuilder = new StringBuilder("Health: ");
        stringBuilder.append(this.getHealth());
        stringBuilder.append("\nDamage: ");
        stringBuilder.append(this.getDamage());
        stringBuilder.append("\nArmour: ");
        stringBuilder.append(armour);
        stringBuilder.append("\nMana Point: ");
        stringBuilder.append(this.getManaPoint());

        System.out.println(stringBuilder.toString());
    }

    public void heal(Player player) {
        if (player.isAlive == false)
            System.out.println("You are dead, you can't be healed");

        else if (manaPoint < 20)
            System.out.println("Intelli Jee doesn\'t have enough mana to heal");

        else if (player.health >= 100)
            System.out.println("You already have the maximum health");

        else {
            player.health = player.health + 10;
            manaPoint = manaPoint - 20;
            var stringBuilder = new StringBuilder("Intelli Jee healed you, you now have ");
            stringBuilder.append(player.health);
            stringBuilder.append(" health");
            System.out.println(stringBuilder.toString());
        }
    }

    public boolean enchant(Player player) {
        if (manaPoint < 15) {
            System.out.println("Intelli Jee doesn\'t have enough mana to use the Eclipse spell and enchant your weapon");
            return false;
        }

        else {
            player.setDamage(player.getDamage() + 10);
            manaPoint = manaPoint - 15;
            var stringBuilder = new StringBuilder("Intelli Jee screams \"Eclipse !\" and enchants your weapon, you deal now ");
            stringBuilder.append(player.getDamage());
            stringBuilder.append(" damage at each attack");
            System.out.println(stringBuilder.toString());
            return true;
        }
    }

    @Override
    public void takeDamage(int damage) {
        health = health - damage;

        if (health <= 0) {
            health = 0;
            isAlive = false;
        }
    }

    @Override
    public String toString() {
        return "W";
    }
}










