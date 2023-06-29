package fr.epita.assistant.game;

import fr.epita.assistant.game.characters.Monster;
import fr.epita.assistant.game.characters.Player;
import fr.epita.assistant.game.characters.Wizard;
import fr.epita.assistant.game.food.Food;
import fr.epita.assistant.game.utils.Coord;
import fr.epita.assistant.game.utils.Direction;

import java.util.HashMap;

public class Board {
    private int size;
    private Player player;
    private Wizard wizard;
    private HashMap<Coord, Monster> monsters;
    private HashMap<Coord, Food> foods;


    public Board(int size, Player player, Wizard wizard, HashMap<Coord, Monster> monsters, HashMap<Coord, Food> foods) {
        this.size = size;
        this.player = player;
        this.wizard = wizard;
        this.monsters = monsters;
        this.foods = foods;
    }

    public Player getPlayer() {
        return player;
    }
    public Wizard getWizard() {
        return wizard;
    }
    public HashMap<Coord, Monster> getMonsters() {
        return this.monsters;
    }
    public HashMap<Coord, Food> getFoods() {
        return this.foods;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int NewSize) {
        size = NewSize;
    }

    public String printBoard () {
        var stringBuilder = new StringBuilder();
        for (int y = 0; y < this.getSize(); y++) {
            stringBuilder.append("|");
            for (int x = 0; x < this.getSize(); x++) {
                int test = 0;
                stringBuilder.append(" ");

                if (this.foods.get(new Coord(x,y)) != null) {
                    stringBuilder.append(this.foods.get(new Coord(x, y)).toString());
                    test = 1;
                }

                if (this.monsters.get(new Coord(x,y)) != null) {
                    stringBuilder.append(this.monsters.get(new Coord(x, y)).toString());
                    test = 1;
                }

                if (this.wizard.getCoord().getX() == x && this.wizard.getCoord().getY() == y && this.wizard.getIsAlive()) {
                    stringBuilder.append(this.wizard.toString());
                    test = 1;
                }

                if (this.player.getCoord().getX() == x && this.player.getCoord().getY() == y) {
                    stringBuilder.append(this.player.toString());
                    test = 1;
                }

                if (test == 0)
                    stringBuilder.append(" ");

                stringBuilder.append(" |");
            }
            stringBuilder.append("\n");
        }
        return stringBuilder.toString();
    }

    public boolean movePlayer(Direction direction) {
        var y = player.getCoord().getY();
        var x = player.getCoord().getX();
        var stringBuilder = new StringBuilder("You moved to ");

        if (direction == Direction.UP && y == 0) {
                System.out.println("You can't move there!");
                return false;
        }
        else if (direction == Direction.DOWN && y == size - 1) {
                System.out.println("You can't move there!");
                return false;
        }
        else if (direction == Direction.LEFT && x == 0) {
                System.out.println("You can't move there!");
                return false;
        }
        else if (direction == Direction.RIGHT && x == size - 1) {
            System.out.println("You can't move there!");
            return false;
        }
        player.move(direction);
        stringBuilder.append(player.getCoord().toString());
        System.out.println(stringBuilder.toString());
        return true;
    }
}