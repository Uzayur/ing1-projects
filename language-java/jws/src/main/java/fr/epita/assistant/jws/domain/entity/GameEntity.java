package fr.epita.assistant.jws.domain.entity;

import fr.epita.assistant.jws.data.model.GameState;
import fr.epita.assistant.jws.data.model.PlayerModel;

import java.sql.Timestamp;
import java.util.List;

public class GameEntity {
    public Long id;
    public GameState state;
    public Integer players;

    public GameEntity(Long id, GameState state, int players) {
        this.id = id;
        this.state = state;
        this.players = players;
    }
}
