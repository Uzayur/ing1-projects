package fr.epita.assistant.game.characters;

public class Skalah extends Monster {
    public Skalah() {
        this.health = 100;
        this.armour = 10;
        this.damage = 20;
        this.name = "Skalah";
        this.isAlive = true;
    }

    public boolean isAlive() {
        return this.isAlive;
    }

    public void attack(Character character) {
        super.attack(character);
        character.takeDamage(this.getDamage());
    }
}
