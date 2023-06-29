package fr.epita.assistant.tracker.service;

/**
 * A service with the charge of producing the output for the events from a specific channel.
 * <p/>
 * Each channel must have its own instance.
 * <p/>
 * You need to call the init method before any other event is played on the service.
 */
public interface OutputService {

    /**
     * Set the channel and bpm value, initialize internal state. Mandatory before any other method is called.
     *
     * @param channel
     *         The channel index.
     * @param bpm
     *         The beats per minutes of the module.
     */
    void init(final int channel, final int bpm);

    /**
     * Call a note off.
     */
    void noteOff();

    /**
     * Play the given midi note, with the given velocity for the given duration (in milliseconds).
     * <p/>
     * This design is dubious (at best), but will make sure you can't shortcut working with async constructions. Win !
     *
     * @param midi
     *         The midi code for the note to play (provided in {@link fr.epita.assistant.tracker.Note}).
     * @param velocity
     *         The velocity of the stroke, range is 0-127.
     * @param ms
     *         The duration of the note, in milliseconds.
     */
    void play(final int midi, final int velocity, final int ms);

    /**
     * Set the instrument on the channel.
     *
     * @param instrumentId
     *         The instrument id, , range is 1-128.
     */
    void setInstrument(final int instrumentId);

    /**
     * The volume of the channel.
     *
     * @param volume
     *         The volume value, range is 0-127.
     */
    void setVolume(final int volume);

    /**
     * Method to use to indicate that a tick has started.
     * <p/>
     * You need to call this method at the start of every tick.
     *
     * @param currentTick
     *         The index of the current tick.
     */
    void startTick(final int currentTick);
}
