package fr.epita.assistant.tracker;

public class Main {
    public static void main(String[] args) {
        MyTracker.Song song = new MyTracker.Song("E-6013123", null);

        System.out.println("instrument: " + song.instrument);
        System.out.println("Velocity: " + song.velocity);
        System.out.println("volume: " + song.volume);
        System.out.println("note octave: " + song.note.octave);
        System.out.println("note midi: " + song.note.midi);

        if (Note.En6 == song.note)
            System.out.println("OK FOR NOTE");
    }
}
