package fr.epita.assistant.jws.domain.entity;

import javax.persistence.*;

public class PlayerEntity {
    public Long id;
    public String name;
    public Integer lives;
    public Integer posx;
    public Integer posy;

    public PlayerEntity(Long id, Integer lives, String name, Integer posx, Integer posy) {
        this.id = id;
        this.lives = lives;
        this.name = name;
        this.posx = posx;
        this.posy = posy;
    }
}