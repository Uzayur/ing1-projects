package fr.epita.assistant.mytinyepita;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class School {
    protected List<ComputerRoom> computerRooms;

    public School() {
        computerRooms = new ArrayList<>();
    }

    public List<ComputerRoom> getComputerRooms() {
        return computerRooms;
    }

    public List<ComputerRoom> getAvailableRooms() {
        List<ComputerRoom> available = new ArrayList<>();

        for (ComputerRoom room : this.getComputerRooms()) {
            if (room.getSize() != room.getCapacity())
                available.add(room);
        }
        return available;
    }

    public void addComputerRooms(final ComputerRoom... computerRooms) throws InsertionException {
        for (ComputerRoom room : computerRooms) {
            for (var rooms : this.getComputerRooms())
            {
                if (rooms.getName().equals(room.getName()) == true)
                    throw new InsertionException("Another room with the same name already exists.");
            }
            this.getComputerRooms().add(room);
        }
    }

    public Optional<ComputerRoom> findStudent(final String login) {
        for (ComputerRoom room : this.computerRooms) {
            for (Student student : room.students) {
                if (student.login == login) {
                    return Optional.of(room);
                }
            }
        }
        return Optional.empty();
    }

    public int numberOfStudents() {
        int test = 0;
        for (ComputerRoom room : this.computerRooms) {
            test += room.getSize();
        }
        return test;
    }

    public void printState() {
        int test = 0;
        for (ComputerRoom room : this.computerRooms) {
            var stringBuilder = new StringBuilder();
            if (test != 0) {
                stringBuilder.append("---\n");
            }
            stringBuilder.append(room.getName());

            stringBuilder.append(" (" + room.getSize() + "/" + room.getCapacity() + ")");

            stringBuilder.append("\nAssistants:");

            for (Assistant a : room.getAssistants()) {
                stringBuilder.append("\n" + a.login);
            }

            stringBuilder.append("\nStudents:");
            for (Student s : room.getStudents()) {
                stringBuilder.append("\n" + s.login);
            }
            System.out.println(stringBuilder.toString());
            test = 1;
        }
    }
}