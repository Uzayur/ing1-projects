package fr.epita.assistant.game.characters;

public abstract class Monster extends Character implements Attacker {
    protected int damage;
    protected String name;

    @Override
    public int getDamage() {
        return damage;
    }
    public String getName() {
        return name;
    }

    public void attack(Character character) {
        var stringBuilder = new StringBuilder(this.name);
        stringBuilder.append(" attacks ");
        stringBuilder.append(character.getName());
        System.out.println(stringBuilder.toString());
    }

    @Override
    public String toString() {
        return "M";
    }

    @Override
    public void printStats() {
        var stringBuilder = new StringBuilder("Health: ");
        stringBuilder.append(this.getHealth());
        stringBuilder.append("\nDamage: ");
        stringBuilder.append(this.getDamage());
        stringBuilder.append("\nArmour: ");
        stringBuilder.append(this.getArmour());

        System.out.println(stringBuilder.toString());
    }

    @Override
    public void takeDamage(int damage) {
        int realDamage = damage - this.armour / 10;

        if (realDamage <= 0) {
            return;
        }

        var stringBuilder = new StringBuilder(this.getName());
        stringBuilder.append(" takes ");
        stringBuilder.append(damage);
        stringBuilder.append(" damage");

        this.setHealth(this.getHealth() - realDamage);
        this.setArmour(this.getArmour() - 1);

        if (this.getHealth() <= 0) {
            this.setHealth(0);
            this.setIsAlive(false);
            stringBuilder.append("\n" + this.getName() + " is dead");
        }
        System.out.println(stringBuilder.toString());
    }
}
