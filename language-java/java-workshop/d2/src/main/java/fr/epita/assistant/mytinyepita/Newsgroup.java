package fr.epita.assistant.mytinyepita;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Newsgroup implements Observable<Newsgroup> {
    protected String name;
    protected Set<Observer<Newsgroup>> observers;

    public Newsgroup(final String name) {
        this.name = name;
        this.observers = new HashSet<>();
    }

    public String getName() {
        return name;
    }

    public void postNews(final Person person, final String message) {
        var stringBuilder = new StringBuilder(person.login + " sends a news in " + name + ".\nMessage: ");
        stringBuilder.append(message);
        System.out.println(stringBuilder.toString());
        fire(this);
    }

    @Override
    public Set<Observer<Newsgroup>> getObservers() {
        return observers;
    }

    @Override
    public void register(Observer<Newsgroup>... observers) {
        for (var a : observers)
            this.observers.add(a);
    }

    @Override
    public void unregister(Observer<Newsgroup> observer) {
        this.observers.remove(observer);
    }

    @Override
    public void fire(Newsgroup event) {
        for (Observer trigger: observers)
            trigger.onEvent(this);
    }
}


