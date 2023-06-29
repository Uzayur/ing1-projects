package fr.epita.assistant.game.food;

public abstract class Food {
    protected int calories;
    protected String name;

    public int getCalories() {
        return this.calories;
    }
    public String getName() {
        return this.name;
    }

    @Override
    public String toString() {
        return "F";
    }
}
