package fr.epita.assistant.mytinyepita;

public class Assistant extends Person implements Observer<Student> {
    protected String login;

    public Assistant(String login) {
        this.login = login;
    }

    @Override
    public void onEvent(Student event) {
        var stringBuilder = new StringBuilder(this.login);

        if (event.getStatus() == Status.ASKING_FOR_HELP) {
            stringBuilder.append(" helps him.");
            System.out.println(stringBuilder.toString());

            event.setStatus(Status.OK);
        }
        else if (event.getStatus() == Status.TIRED) {
            stringBuilder.append(" suggests ");
            stringBuilder.append(event.getLogin());
            stringBuilder.append(" to go to sleep.");
            System.out.println(stringBuilder.toString());
        }
    }

    @Override
    public void postNews(Newsgroup newsgroup, String message) {
        newsgroup.postNews(this, message);
    }
}
