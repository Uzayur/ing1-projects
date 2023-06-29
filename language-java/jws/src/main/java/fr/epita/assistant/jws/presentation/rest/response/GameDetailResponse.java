package fr.epita.assistant.jws.presentation.rest.response;

import fr.epita.assistant.jws.data.model.GameState;

import java.util.List;

public class GameDetailResponse {
    public String startTime;
    public GameState state;
    public List<Player> players;
    public List<String> map;
    public long id;

    public GameDetailResponse(String startTime, GameState state, List<Player> players, List<String> map, long id) {
        this.startTime = startTime;
        this.state = state;
        this.players = players;
        this.map = map;
        this.id = id;
    }
}
