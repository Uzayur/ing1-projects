package fr.epita.assistant.game.characters;

public class Coatlin extends Monster {
    public Coatlin() {
        this.health = 100;
        this.armour = 10;
        this.damage = 10;
        this.name = "Coatlin";
        this.isAlive = true;
    }

    public boolean isAlive() {
        return this.isAlive;
    }

    public void attack(Character character) {
        super.attack(character);
        character.takeDamage(this.getDamage() + this.health / 10);
    }
}
