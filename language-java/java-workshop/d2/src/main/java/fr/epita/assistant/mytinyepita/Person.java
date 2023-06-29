package fr.epita.assistant.mytinyepita;

public abstract class Person {
    protected String login;
    protected boolean available = true;

    public String getLogin() {
        return login;
    }
    public boolean isAvailable() {
        return available;
    }
    public void setAvailable(boolean available) {
        this.available = available;
    }

    public abstract void postNews(final Newsgroup newsgroup, final String message);
}
