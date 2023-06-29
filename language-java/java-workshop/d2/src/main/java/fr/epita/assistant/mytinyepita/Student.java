package fr.epita.assistant.mytinyepita;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class Student extends Person implements Observable<Student>, Observer<Newsgroup> {
    int energy;
    Status status = Status.OK;
    protected Set<Observer<Student>> observers;

    public Student(final String login, final int energy) {
        this.login = login;
        this.energy = energy;
        this.observers = new HashSet<>();
    }

    public Status getStatus() {
        return status;
    }
    public void setStatus(Status status) {
        this.status = status;
    }

    @Override
    public Set<Observer<Student>> getObservers() {
        return observers;
    }

    @Override
    public void register(Observer<Student>... observers) {
        for (var a : observers)
            this.observers.add(a);
    }

    @Override
    public void unregister(Observer<Student> observer) {
        this.observers.remove(observer);
    }

    @Override
    public void fire(Student event) {
        for (Observer trigger : observers)
            trigger.onEvent(this);
    }

    @Override
    public void onEvent(Newsgroup event) {
        var stringBuilder = new StringBuilder(login);
        stringBuilder.append(" reads the news.");
        System.out.println(stringBuilder.toString());
    }

    public void subscribeToNewsgroup(Newsgroup newsgroup) {
        newsgroup.register(this);
    }

    public void unsubscribeToNewsgroup(Newsgroup newsgroup)0
        if (newsgroup.getObservers().contains(this))
            newsgroup.unregister(this);
        else
            throw new IllegalArgumentException("Student is not subscribed to this newsgroup.");
    }

    @Override
    public void postNews(Newsgroup newsgroup, String message) {
        if (newsgroup.getObservers().contains(this)) {
            newsgroup.postNews(this, message);
        }
        else
            throw new IllegalArgumentException("Student cannot post in a newsgroup he is not subscribed to.");
    }

    public void work() {
        var stringBuilder = new StringBuilder(login);
        if (this.isAvailable() == true) {
            throw new IllegalStateException("Student must be in a room to work.");
        }
        else if (this.getStatus() == Status.TIRED) {
            stringBuilder.append(" is too tired to work.");
            System.out.println(stringBuilder.toString());
        }
        else {
            stringBuilder.append(" is working.");
            this.energy -= 1;

            if (this.energy == 0)
                this.setStatus(Status.TIRED);

            System.out.println(stringBuilder.toString());
        }
    }

    public void goToSleep() {
        if (this.isAvailable() == false)
            throw new IllegalStateException("Student must leave the room before going to sleep.");
        else {
            this.setStatus(Status.OK);
            this.energy = 5;
        }
    }

    public void askForHelp() {
        var stringBuilder = new StringBuilder(this.getLogin());

        if (this.observers.isEmpty()) {
            stringBuilder.append(" wishes he could be helped...");
            System.out.println(stringBuilder.toString());
        }
        else {
            if (this.getStatus() != Status.TIRED)
                this.setStatus(Status.ASKING_FOR_HELP);

            stringBuilder.append(" is asking for help.");
            System.out.println(stringBuilder.toString());

            this.fire(this);
        }
    }
}
