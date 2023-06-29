package fr.epita.assistant.jws.presentation.rest.response;

import fr.epita.assistant.jws.data.model.GameState;

public class GameListResponse {
    public long id;
    public Integer players;
    public GameState state;

    public GameListResponse(long id, Integer players, GameState state) {
        this.id = id;
        this.players = players;
        this.state = state;
    }
}
