package fr.epita.assistant;
import fr.epita.assistant.dto.BoardDTO;
import fr.epita.assistant.game.Board;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.*;
import java.util.*;


public final class GameEngine {
    private final Scanner scanner;
    private final Random random;
    private final String pathToJson;
    private final String pathToCommands;
    private Board board;

    public GameEngine(String pathToJson, String pathToCommands) {
        this.pathToJson = pathToJson;
        this.pathToCommands = pathToCommands;
        scanner = new Scanner(System.in);
        random = new Random();
    }

    public void play() {
        System.out.println("Welcome to the fr.epita.assistant.game!");
        this.initializeBoard();
        this.playCLIGame();
    }

    /*
     * =======================================================
     *
     *                PLAY CLI Game
     *
     * =======================================================
     * */

    private void playCLIGame() {
        System.out.println(board.printBoard());
    }

    /*
     * =======================================================
     *
     *                INITIALIZE THE BOARD
     *
     * =======================================================
     * */


    private void initializeBoard() {
        if (!pathToJson.isEmpty()) {
            System.out.println(
                    "The board will be created thanks to the JSON file given.");
            boardFromJson();
        } else {
            System.out.println("Let's create our board !");
            boardFromCLI();
        }
    }

    private void boardFromCLI() {
        System.out.println(
                "What will be the size of your board (m x m)? The minimum size is 5.");
        int maxElementOnTheBoard;
        int size = -1;
        do {
            try {
                maxElementOnTheBoard =
                        Integer.parseInt(this.scanner.nextLine());
                if (maxElementOnTheBoard < 5) {
                    System.out.println("The minimum size is 5");
                } else {
                    size = maxElementOnTheBoard;
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid input");
                e.printStackTrace();
            }
        } while (size == -1);
        this.board = new Board(size);
        System.out.println("Do you want to save the board in a json file ? (y/n)");
        String answer = this.scanner.nextLine();
        if (answer.equals("y")) {
            saveBoard();
        }
    }

    private void saveBoard() {
        System.out.println("What is the name of the json file ?");
        String fileName = this.scanner.nextLine();
        ArrayList<BoardDTO.Infos> monsters = new ArrayList<>();
        ArrayList<BoardDTO.Infos> foods = new ArrayList<>();
        BoardDTO.Coord playerCoord =
                new BoardDTO.Coord(-1, -1);
        BoardDTO.Coord wizardCoord =
                new BoardDTO.Coord(-1, -1);
        BoardDTO boardDTO =
                new BoardDTO(this.board.getSize(), playerCoord,
                        wizardCoord, monsters, foods);
        try {
            ObjectMapper mapper = new ObjectMapper();
            mapper.writeValue(new File(fileName), boardDTO);
        } catch (IOException e) {
            System.err.println(
                    "An error occured while saving the board in a json file");
        }
    }

    private void boardFromJson() {
        BoardDTO boardDTO = null;
        ObjectMapper mapper = new ObjectMapper();
        try {
            boardDTO = mapper.readValue(new File(this.pathToJson),
                    BoardDTO.class);
        } catch (IOException e) {
            e.printStackTrace();
        }

        assert boardDTO != null;
        int size = boardDTO.getSize();
        this.board = new Board(size);
    }
}