package fr.epita.assistant.tracker;

import fr.epita.assistant.tracker.service.OutputService;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Supplier;
import java.util.stream.Stream;

public class MyTracker implements Tracker {

    public static class Song {
        protected Note note;
        protected int instrument;
        protected int velocity;
        protected int volume;
        protected Song previousSong;

        public void setPreviousSong(Song previousSong) { this.previousSong = previousSong; }
        public void setVolume(int volume) { this.volume = volume; }

        public Song(String partition, Song previousSong) {
            this.note = createNote(partition);
            this.instrument = createInstrument(partition);
            this.velocity = createVelocity(partition);
            this.volume = createVolume(partition);
            this.previousSong = previousSong;
        }

        public Note createNote(String partition) {
            String note = partition.substring(0,3);

            if (note.equals("..."))
                return previousSong.note;

            else if (note.charAt(1) == 'b')
                note = note.replace('b', 'f');

            else if (note.charAt(1) == '-')
                note = note.replace('-', 'n');

            else
                note = note.replace("#", "s");

            return Note.valueOf(note);
        }

        public static int convertToHex(String partition) {
            String hex = "0123456789ABCDEF";
            return hex.indexOf(partition.charAt(0)) * 16 + hex.indexOf(partition.charAt(1));
        }

        public int createInstrument(String partition) {
            String substring = partition.substring(3,5);

            if (substring.equals(".."))
                return previousSong.instrument;
            return convertToHex(substring);
        }

        public int createVelocity(String partition) {
            String substring = partition.substring(5,7);
            if (substring.equals(".."))
                return previousSong.velocity;
            return convertToHex(substring);
        }

        public int createVolume(String partition) {
            String substring = partition.substring(7, 9);
            if (substring.equals(".."))
                return previousSong.volume;
            return convertToHex(substring);
        }
    }

    public Song newNote(String partition, Song previous) {
        if (partition.equals("........."))
            return previous;

        else if (partition.equals("===......"))
            return null;

        else
            return new Song(partition, previous);
    }

    public void playSong(List<Song> list) {
        
    }

    @Override
    public void play(String modulePath, Supplier<OutputService> outputServiceSupplier) {
        List<String> lines = new ArrayList<>();

        try (Stream<String> stream = Files.lines(Paths.get(modulePath))) {
            stream.forEach(line -> lines.add(line));
        } catch (IOException e) {
            e.printStackTrace();
        }

        List<Song> firstSong = new ArrayList<>();
        List<Song> secondSong = new ArrayList<>();
        Song firstPreviouSong = null;
        Song secondPreviousSong = null;

        int index = 0;
        for (String line : lines) {
            if (index < 3) {
                index++;
                continue;
            }

            if (!(line.matches("(\\|([A-G][b\\-#][0-8]|\\.{3}|={3})([0-8][0-9]|.{2})([0-7][0-9]|.{2})([0-9]|[A-F]|.{1})([0-9]|[A-Z]|.{1})){2}$")))
                return;

            String firstNote = line.substring(1,10);
            String secondNote = line.substring(11, 20);

            firstSong.add(newNote(firstNote, firstPreviouSong));
            firstPreviouSong = newNote(firstNote, firstPreviouSong);

            secondSong.add(newNote(secondNote, secondPreviousSong));
            secondPreviousSong = newNote(firstNote, firstPreviouSong);
        }

        playSong(firstSong);


        return;
    }
}
