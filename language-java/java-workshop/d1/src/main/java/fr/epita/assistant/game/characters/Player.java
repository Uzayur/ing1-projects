package fr.epita.assistant.game.characters;

import fr.epita.assistant.game.food.Food;
import fr.epita.assistant.game.utils.Coord;
import fr.epita.assistant.game.utils.Direction;

import java.util.ArrayList;
import java.util.List;


public final class Player extends Character implements Attacker {
    private int damage;
    private Coord coord;
    private ArrayList<Food> inventory;

    public Player(Coord newCoord) {
        coord = newCoord;
        damage = 10;
        health = 100;
        armour = 15;
        name = "Player";
        isAlive = true;
        this.inventory = new ArrayList<>();
    }

    @Override
    public int getDamage() {
        return damage;
    }

    public boolean isAlive() {
        return this.isAlive;
    }

    public void setDamage(int newDamage) {
        if (newDamage >= 0) {
            damage = newDamage;
        }
    }

    public Coord getCoord() { return coord; }

    public ArrayList<Food> getInventory() {
        return this.inventory;
    }

    @Override
    public void attack(Character character) {
        if (damage <= 0) {
            return;
        }

        character.takeDamage(this.getDamage());
        if (character.getHealth() <= 0) {
            character.setHealth(0);
            character.isAlive = false;
        }
        this.setDamage(this.getDamage() - 1);
    }

    @Override
    public void printStats() {
        var stringBuilder = new StringBuilder("Health: ");
        stringBuilder.append(health);
        stringBuilder.append("\nDamage: ");
        stringBuilder.append(damage);
        stringBuilder.append("\nArmour: ");
        stringBuilder.append(armour);

        if (this.inventory.size() != 0) {
            stringBuilder.append("\nInventory:");
            for (Food newFood : this.inventory) {
                stringBuilder.append("\n" + newFood.getName());
            }
        }

        System.out.println(stringBuilder.toString());
    }

    public void takeDamage(int damage) {
        var stringBuilder = new StringBuilder("You take ");
        int realDamage = damage - (this.armour / 2);

        if (realDamage <= 0) {
            return;
        }
        else {
            this.setHealth(this.getHealth() - realDamage);
            stringBuilder.append(damage);
            stringBuilder.append(" damage");
        }

        if (health <= 0) {
            health = 0;
            isAlive = false;
            stringBuilder.append("\nYou are dead");
        }
        this.setArmour(this.getArmour() - 1);
        System.out.println(stringBuilder.toString());
    }

    public void heal(int hp) {
        if (hp <= 0) {
            return;
        }
        health = health + hp;
    }

    @Override
    public String toString() {
        return "P";
    }

    public void move(Direction direction) {
        if (direction == Direction.UP) {
            coord.setY(coord.getY() - 1);
        }
        else if (direction == Direction.DOWN) {
            coord.setY(coord.getY() + 1);
        }
        else if (direction == Direction.LEFT) {
            coord.setX(coord.getX() - 1);
        }
        else {
            coord.setX(coord.getX() + 1);
        }
    }

    public void addFood(Food food) {
        this.inventory.add(food);
    }

    public Food takeFood(String foodName) {
        for (Food food : this.getInventory()) {
            if (food.getName().equals(foodName)) {
                Food returnFood = food;
                this.getInventory().remove(food);
                return food;
            }
        }
        return null;
    }

    public void eatFood(Food food) {
        this.setHealth(this.getHealth() + food.getCalories());
    }

}