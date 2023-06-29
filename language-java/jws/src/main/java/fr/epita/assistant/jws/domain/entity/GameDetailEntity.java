package fr.epita.assistant.jws.domain.entity;

import fr.epita.assistant.jws.data.model.GameState;
import fr.epita.assistant.jws.data.model.PlayerModel;

import java.sql.Timestamp;
import java.util.List;

public class GameDetailEntity {
    public String startTime;
    public GameState state;
    public List<PlayerModel> players;
    public List<String> map;
    public Long id;

    public GameDetailEntity(String startTime, GameState state, List<PlayerModel> players, List<String> map, Long id) {
        this.startTime = startTime;
        this.state = state;
        this.players = players;
        this.map = map;
        this.id = id;
    }
}
