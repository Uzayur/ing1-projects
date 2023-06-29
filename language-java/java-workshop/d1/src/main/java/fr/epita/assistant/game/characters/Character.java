package fr.epita.assistant.game.characters;

public abstract class Character {
    protected String name;
    public String getName() { return name; }

    protected int health;
    public int getHealth() { return health; }
    public void setHealth(int newHealth) {
        if (newHealth > 0) {
            health = newHealth;
        }
        else {
            health = 0;
        }
    }

    protected boolean isAlive;
    public boolean getIsAlive() {
        return isAlive;
    }
    public void setIsAlive(boolean isAlive) {
        this.isAlive = isAlive;
    }
    public boolean isDead() {
        return !(isAlive);
    }

    protected int armour;
    public int getArmour() { return armour; }
    public void setArmour(int newArmour) {
        if (newArmour > 0) {
            armour = newArmour;
        }
        else {
            armour = 0;
        }
    }

    abstract void printStats();
    abstract int getDamage();
    abstract void takeDamage(int damage);
}