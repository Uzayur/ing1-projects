package fr.epita.assistant.tracker.service;

import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Synthesizer;

/**
 * An output service that transmit all events to the standard midi synthesizer.
 */
public class SynthOutputService implements OutputService {

    /**
     * The system synthesizer instance.
     */
    private static Synthesizer synthesizer;

    // Reminder, this is a static block: it's loaded once at class initialization.
    static {
        try {
            synthesizer = MidiSystem.getSynthesizer();
            synthesizer.open();
            var instruments = synthesizer.getDefaultSoundbank().getInstruments();
            synthesizer.loadInstrument(instruments[0]);
        } catch (final MidiUnavailableException exception) {
            System.err.println("Midi not available, exiting.");
            System.exit(1);
        }
    }

    /**
     * The channel this output will manage.
     */
    private MidiChannel channel;

    /**
     * Initialization flag.
     */
    private boolean initialized = false;

    /**
     * Check if the channel has been initialized, exit if not.
     */
    private void checkChannelInitialization() {
        if (!initialized) {
            System.err.println("Channel has not been initialized, exiting.");
            System.exit(1);
        }
    }

    @Override public void init(int channel, int bpm) {
        if (this.initialized) {
            System.err.println("channel has already been initialized, exiting.");
            System.exit(1);
        }
        var mChannels = synthesizer.getChannels();
        this.channel = mChannels[channel];
        this.initialized = true;
    }

    @Override public void noteOff() {
        checkChannelInitialization();
        channel.allNotesOff();
    }

    @Override public void play(final int midi, final int velocity, final int ms) {
        checkChannelInitialization();
        channel.allNotesOff();
        channel.noteOn(midi, velocity * 2);
        try {Thread.sleep(ms);} catch (InterruptedException ignored) {}
    }

    @Override public void setInstrument(final int instrumentId) {
        checkChannelInitialization();
        channel.programChange(instrumentId);
    }

    @Override public void setVolume(final int volume) {
        checkChannelInitialization();
        channel.controlChange(7, volume);
    }

    @Override public void startTick(int currentTick) {}
}
