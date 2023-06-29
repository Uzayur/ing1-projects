package fr.epita.assistant.jws.domain.service;

import fr.epita.assistant.jws.data.model.GameModel;
import fr.epita.assistant.jws.data.model.GameState;
import fr.epita.assistant.jws.data.model.PlayerModel;
import fr.epita.assistant.jws.data.repository.GameRepository;
import fr.epita.assistant.jws.data.repository.PlayerRepository;
import fr.epita.assistant.jws.domain.entity.GameDetailEntity;
import fr.epita.assistant.jws.domain.entity.GameEntity;
import fr.epita.assistant.jws.presentation.rest.request.CreateGameRequest;
import fr.epita.assistant.jws.presentation.rest.request.JoinGameRequest;
import lombok.val;

import javax.enterprise.context.ApplicationScoped;
import javax.inject.Inject;
import javax.transaction.Transactional;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

@ApplicationScoped
public class GameService {

    @Inject
    GameRepository gameRepository;

    @Inject
    PlayerRepository playerRepository;

    public Set<GameEntity> getAllGames() {
        return gameRepository.listAll().stream().map(elt -> new GameEntity(elt.id, elt.state, elt.listPlayers.size())).collect(Collectors.toSet());
    }

    public Set<GameDetailEntity> getDetailGame() {
        return gameRepository.listAll()
                .stream()
                .map(elt -> new GameDetailEntity(elt.startTime.toString(), elt.state, elt.listPlayers, elt.map, elt.id))
                .collect(Collectors.toSet());
    }

    @Transactional public long addGame(CreateGameRequest gameDTO) {
        var map = new ArrayList<String>();
        String path = System.getenv("JWS_MAP_PATH");

        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line;
            while ((line = br.readLine()) != null) {
                map.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        var newList = new ArrayList<PlayerModel>();
        GameModel newGame = new GameModel().withStartTime(LocalDateTime.now()).withMap(map).withState(GameState.STARTING).withListPlayers(newList);

        val newPlayer = new PlayerModel().withLives(3).withPosX(1).withPosY(1).withGameModel(newGame).withName(gameDTO.name);
        playerRepository.persist(newPlayer);
        newGame.listPlayers.add(newPlayer);

        gameRepository.persist(newGame);
        return newGame.id;
    }

    @Transactional public GameModel StartGame(long gameId) {
        var game = gameRepository.listAll()
                .stream()
                .filter(elt -> Objects.equals(elt.id, gameId))
                .findFirst()
                .orElse(null);

        if (game == null || game.state == GameState.FINISHED)
            return null;

        if (game.getListPlayers().size() == 1)
            game.state = GameState.FINISHED;
        else
            game.state = GameState.RUNNING;

        return game;
    }

    public GameModel getGameModel(long gameId) {
        return gameRepository.listAll()
                .stream()
                .filter(elt -> Objects.equals(elt.id, gameId))
                .findFirst()
                .orElse(null);
    }

    @Transactional public long addPlayer(long gameId, JoinGameRequest player) {
        var game = gameRepository.listAll()
                .stream()
                .filter(elt -> Objects.equals(elt.id, gameId))
                .findFirst()
                .orElse(null);

        if (game == null)
            return 1;

        if (game.getListPlayers().size() > 3 || game.state != GameState.STARTING)
            return 2;

        Integer posX = 1;
        Integer posY = 1;

        if (game.getListPlayers().size() == 1)
            posX = 15;
        else if (game.getListPlayers().size() == 3)
            posY = 13;
        else if (game.getListPlayers().size() == 2) {
            posX = 15;
            posY = 13;
        }

        val newPlayer = new PlayerModel().withLives(3).withPosX(posX).withPosY(posY).withGameModel(game).withName(player.name);
        playerRepository.persist(newPlayer);
        game.listPlayers.add(newPlayer);

        return 0;
    }
}
