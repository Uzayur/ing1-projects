package fr.epita.assistant.jws.presentation.rest.response;

public class Player {
    public Long id;
    public String name;
    public Integer lives;
    public Integer posX;
    public Integer posY;

        public Player(Long id, String name, Integer lives, Integer posX, Integer posY) {
            this.id = id;
            this.lives = lives;
            this.name = name;
            this.posX = posX;
            this.posY = posY;
        }
    }
