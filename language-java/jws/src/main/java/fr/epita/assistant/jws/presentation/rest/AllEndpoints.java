package fr.epita.assistant.jws.presentation.rest;

import fr.epita.assistant.jws.data.model.GameModel;
import fr.epita.assistant.jws.data.model.GameState;
import fr.epita.assistant.jws.domain.service.GameService;
import fr.epita.assistant.jws.presentation.rest.request.CreateGameRequest;
import fr.epita.assistant.jws.presentation.rest.request.JoinGameRequest;
import fr.epita.assistant.jws.presentation.rest.response.GameDetailResponse;
import fr.epita.assistant.jws.presentation.rest.response.GameListResponse;
import fr.epita.assistant.jws.presentation.rest.response.Player;

import javax.enterprise.context.ApplicationScoped;
import javax.inject.Inject;
import javax.ws.rs.*;
import javax.ws.rs.core.Response;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;


@ApplicationScoped
@Path("/games")
public class AllEndpoints {

    @Inject
    GameService gameService;

    @GET
    public List<GameListResponse> getAllGames() {
        return gameService.getAllGames()
                .stream()
                .map(elt -> new GameListResponse(elt.id, elt.players, elt.state))
                .collect(Collectors.toList());
    }

    @GET
    @Path("/{gameId}")
    public Response getGameInfo(@PathParam("gameId") long gameId) {
        GameDetailResponse gameInfo = gameService.getDetailGame()
                .stream()
                .map(elt -> new GameDetailResponse(elt.startTime, elt.state, elt.players.stream().map(el ->new Player(el.id, el.name, el.lives, el.posX, el.posY)).collect(Collectors.toList()), elt.map, elt.id))
                .filter(elt -> Objects.equals(elt.id, gameId))
                .findFirst()
                .orElse(null);

        if (gameInfo == null)
            return Response.status(404, "Cannot found game with this id").build();
        return Response.ok(gameInfo).build();
    }

    @POST
    public Response CreateNewGame(CreateGameRequest gameDTO) {
        if (gameDTO == null || gameDTO.name == null)
            return Response.status(400, "Bad request (request or name is null)").build();

        var id = gameService.addGame(gameDTO);
        return getGameInfo(id);
    }

    @POST
    @Path("/{gameId}")
    public Response JoinGame(@PathParam("gameId") long gameId, JoinGameRequest player) {
        if (player == null || player.name == null)
            return Response.status(400, "The request is null, or the player name is null or the game cannot be started (already started, too many players)").build();



        var gameInfo = gameService.addPlayer(gameId, player);
        if (gameInfo == 1)
            return Response.status(404, "Game with this ID does not exist").build();

        if (gameInfo == 2)
            return Response.status(400, "The request is null, or the player name is null or the game cannot be started (already started, too many players)").build();

        return getGameInfo(gameId);
    }


    @PATCH
    @Path("/{gameId}/start")
    public Response StartGame(@PathParam("gameId") long gameId) {
        GameModel game = gameService.StartGame(gameId);

        if (game == null)
            return Response.status(404, "The game with this ID does not exist").build();

        return getGameInfo(gameId);
    }
}