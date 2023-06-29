package fr.epita.assistant.tracker;

import fr.epita.assistant.tracker.service.OutputService;

import java.util.function.Supplier;

/**
 * The interface that you need to implement.
 */
public interface Tracker {

    /**
     * Open the provided file, and play it using provided output service.
     *
     * @param modulePath
     *         The path to the module to play.
     * @param outputServiceSupplier
     *         An output service supplier. This will need to be executed to get a fresh output service for every channel.
     */
    void play(final String modulePath, final Supplier<OutputService> outputServiceSupplier);
}
