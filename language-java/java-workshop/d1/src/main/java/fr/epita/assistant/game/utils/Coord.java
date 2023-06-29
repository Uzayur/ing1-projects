package fr.epita.assistant.game.utils;

import java.util.Objects;

public class Coord {
    private int x;
    private int y;

    public Coord(int x, int y) {
        if (x > 0) {
            this.x = x;
        }
        else {
            this.x = 0;
        }
        if (y > 0) {
            this.y = y;
        }
        else {
            this.y = 0;
        }
    }

    public int getX() {
        return x;
    }
    public int getY() {
        return y;
    }

    public void setX(int x) {
        if (x >= 0) {
            this.x = x;
        }
    }
    public void setY(int y) {
        if (y >= 0) {
            this.y = y;
        }
    }

    @Override
    public boolean equals(Object second) {
        if (second instanceof Coord test) {
            return test.getX() == this.getX() && test.getY() == this.getY();
        }
        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString() {
        var stringBuilder = new StringBuilder("(x=");
        stringBuilder.append(getX());
        stringBuilder.append(", y=");
        stringBuilder.append(getY());
        stringBuilder.append(")");
        return stringBuilder.toString();
    }
}