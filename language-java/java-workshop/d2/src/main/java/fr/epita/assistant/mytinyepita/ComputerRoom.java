package fr.epita.assistant.mytinyepita;

import java.util.ArrayList;
import java.util.List;

public class ComputerRoom {
    protected String name;
    protected int capacity;
    protected List<Student> students;
    protected List<Assistant> assistants;

    public ComputerRoom(final String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
        this.students = new ArrayList<>();
        this.assistants = new ArrayList<>();
    }

    public List<Student> getStudents() {
        return students;
    }

    public List<Assistant> getAssistants() {
        return assistants;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getSize() {
        return students.size();
    }

    public String getName() {
        return name;
    }

    public void addStudent(final Student student) throws InsertionException {
        if (this.getCapacity() <= this.getSize()) {
            throw new InsertionException("Room is full.");
        }
        else if (this.students.contains(student)) {
            throw new InsertionException("Student already inside the room.");
        }
        else if (student.isAvailable() == false) {
            throw new InsertionException("Student already inside another room.");
        }
        else {
            this.students.add(student);

            for (Assistant a : this.assistants)
                student.register(a);

            student.setAvailable(false);
        }
    }

    public void addStudents(final Student... students) throws InsertionException {
        for (Student s : students)
            this.addStudent(s);
    }

    public void addAssistant(final Assistant assistant) throws InsertionException {
        if (this.assistants.contains(assistant))
            throw new InsertionException("Assistant already inside the room.");
        else if (assistant.isAvailable() == false)
            throw new InsertionException("Assistant already inside another room.");
        else {
            this.assistants.add(assistant);

            for (Student s : students)
                s.register(assistant);

            assistant.setAvailable(false);
        }
    }

    public void addAssistants(final Assistant... assistants) throws InsertionException {
        for (Assistant a : assistants)
            this.addAssistant(a);
    }

    public void removeStudent(final Student student) {
        if (this.students.contains(student)) {
            this.students.remove(student);
            student.setAvailable(true);

            for (Assistant a : this.assistants)
                student.unregister(a);
        }
        else {
            throw new IllegalArgumentException("Student is not inside the room.");
        }
    }

    public void removeStudents(final Student... students) {
        for (Student s : students)
            removeStudent(s);
    }

    public void removeAssistant(final Assistant assistant) {
        if (this.assistants.contains(assistant)) {
            this.assistants.remove(assistant);
            assistant.setAvailable(true);

            for (Student s : this.students)
                s.unregister(assistant);
        }
        else {
            throw new IllegalArgumentException("Assistant is not inside the room.");
        }
    }

    public void removeAssistants(final Assistant... assistants) {
        for (Assistant a : assistants)
            removeAssistant(a);
    }
}














