package fr.epita.assistant.tracker;

import static fr.epita.assistant.tracker.Note.Modifier.FLAT;
import static fr.epita.assistant.tracker.Note.Modifier.NATURAL;
import static fr.epita.assistant.tracker.Note.Modifier.SHARP;

/**
 * Enum for notes.
 */
public enum Note {
    An0('a', NATURAL, 0, 21),
    As0('a', SHARP, 0, 22),
    Bf0('b', FLAT, 0, 22),
    Bn0('b', NATURAL, 0, 23),

    Cn1('c', NATURAL, 1, 24),
    Cs1('c', SHARP, 1, 25),
    Df1('d', FLAT, 1, 25),
    Dn1('d', NATURAL, 1, 26),
    Ds1('d', SHARP, 1, 27),
    Ef1('e', FLAT, 1, 27),
    En1('e', NATURAL, 1, 28),
    Fn1('f', NATURAL, 1, 29),
    Fs1('f', SHARP, 1, 30),
    Gf1('g', FLAT, 1, 30),
    Gn1('g', NATURAL, 1, 31),
    Gs1('g', SHARP, 1, 32),
    Af1('a', FLAT, 1, 32),
    An1('a', NATURAL, 1, 33),
    As1('a', SHARP, 1, 34),
    Bf1('b', FLAT, 1, 34),
    Bn1('b', NATURAL, 1, 35),

    Cn2('c', NATURAL, 2, 36),
    Cs2('c', SHARP, 2, 37),
    Df2('d', FLAT, 2, 37),
    Dn2('d', NATURAL, 2, 38),
    Ds2('d', SHARP, 2, 39),
    Ef2('e', FLAT, 2, 39),
    En2('e', NATURAL, 2, 40),
    Fn2('f', NATURAL, 2, 41),
    Fs2('f', SHARP, 2, 42),
    Gf2('g', FLAT, 2, 42),
    Gn2('g', NATURAL, 2, 43),
    Gs2('g', SHARP, 2, 44),
    Af2('a', FLAT, 2, 44),
    An2('a', NATURAL, 2, 45),
    As2('a', SHARP, 2, 46),
    Bf2('b', FLAT, 2, 46),
    Bn2('b', NATURAL, 2, 47),

    Cn3('c', NATURAL, 3, 48),
    Cs3('c', SHARP, 3, 49),
    Df3('d', FLAT, 3, 49),
    Dn3('d', NATURAL, 3, 50),
    Ds3('d', SHARP, 3, 51),
    Ef3('e', FLAT, 3, 51),
    En3('e', NATURAL, 3, 52),
    Fn3('f', NATURAL, 3, 53),
    Fs3('f', SHARP, 3, 54),
    Gf3('g', FLAT, 3, 54),
    Gn3('g', NATURAL, 3, 55),
    Gs3('g', SHARP, 3, 56),
    Af3('a', FLAT, 3, 56),
    An3('a', NATURAL, 3, 57),
    As3('a', SHARP, 3, 58),
    Bf3('b', FLAT, 3, 58),
    Bn3('b', NATURAL, 3, 59),

    Cn4('c', NATURAL, 4, 60),
    Cs4('c', SHARP, 4, 61),
    Df4('d', FLAT, 4, 61),
    Dn4('d', NATURAL, 4, 62),
    Ds4('d', SHARP, 4, 63),
    Ef4('e', FLAT, 4, 63),
    En4('e', NATURAL, 4, 64),
    Fn4('f', NATURAL, 4, 65),
    Fs4('f', SHARP, 4, 66),
    Gf4('g', FLAT, 4, 66),
    Gn4('g', NATURAL, 4, 67),
    Gs4('g', SHARP, 4, 68),
    Af4('a', FLAT, 4, 68),
    An4('a', NATURAL, 4, 69),
    As4('a', SHARP, 4, 70),
    Bf4('b', FLAT, 4, 70),
    Bn4('b', NATURAL, 4, 71),

    Cn5('c', NATURAL, 5, 72),
    Cs5('c', SHARP, 5, 73),
    Df5('d', FLAT, 5, 73),
    Dn5('d', NATURAL, 5, 74),
    Ds5('d', SHARP, 5, 75),
    Ef5('e', FLAT, 5, 75),
    En5('e', NATURAL, 5, 76),
    Fn5('f', NATURAL, 5, 77),
    Fs5('f', SHARP, 5, 78),
    Gf5('g', FLAT, 5, 78),
    Gn5('g', NATURAL, 5, 79),
    Gs5('g', SHARP, 5, 80),
    Af5('a', FLAT, 5, 80),
    An5('a', NATURAL, 5, 81),
    As5('a', SHARP, 5, 82),
    Bf5('b', FLAT, 5, 82),
    Bn5('b', NATURAL, 5, 83),

    Cn6('c', NATURAL, 6, 84),
    Cs6('c', SHARP, 6, 85),
    Df6('d', FLAT, 6, 85),
    Dn6('d', NATURAL, 6, 86),
    Ds6('d', SHARP, 6, 87),
    Ef6('e', FLAT, 6, 87),
    En6('e', NATURAL, 6, 88),
    Fn6('f', NATURAL, 6, 89),
    Fs6('f', SHARP, 6, 90),
    Gf6('g', FLAT, 6, 90),
    Gn6('g', NATURAL, 6, 91),
    Gs6('g', SHARP, 6, 92),
    Af6('a', FLAT, 6, 92),
    An6('a', NATURAL, 6, 93),
    As6('a', SHARP, 6, 94),
    Bf6('b', FLAT, 6, 94),
    Bn6('b', NATURAL, 6, 95),

    Cn7('c', NATURAL, 7, 96),
    Cs7('c', SHARP, 7, 97),
    Df7('d', FLAT, 7, 97),
    Dn7('d', NATURAL, 7, 98),
    Ds7('d', SHARP, 7, 99),
    Ef7('e', FLAT, 7, 99),
    En7('e', NATURAL, 7, 100),
    Fn7('f', NATURAL, 7, 101),
    Fs7('f', SHARP, 7, 102),
    Gf7('g', FLAT, 7, 102),
    Gn7('g', NATURAL, 7, 103),
    Gs7('g', SHARP, 7, 104),
    Af7('a', FLAT, 7, 104),
    An7('a', NATURAL, 7, 105),
    As7('a', SHARP, 7, 106),
    Bf7('b', FLAT, 7, 106),
    Bn7('b', NATURAL, 7, 107),

    Cn8('c', NATURAL, 8, 108);

    /**
     * The actual note, in english notation (A is La, B is Si, C is Do etc...)
     */
    public final char note;

    /**
     * A modifier (flat, natural or sharp).
     */
    public final Modifier modifier;

    /**
     * The octave, we use tradition midi/piano octaves, from 0 to 8.
     */
    public final int octave;

    /**
     * The equivalent midi code.
     */
    public final int midi;

    /**
     * Ctor.
     *
     * @param note
     *         field value.
     * @param modifier
     *         field value.
     * @param octave
     *         field value.
     * @param midi
     *         field value.
     */
    Note(char note, Modifier modifier, int octave, int midi) {
        this.note = note;
        this.modifier = modifier;
        this.octave = octave;
        this.midi = midi;
    }

    @Override public String toString() {
        return ("" + note).toUpperCase() + modifier + octave;
    }

    /**
     * Modifier enum.
     */
    enum Modifier {
        FLAT("b"), // flat, half a tone lower
        NATURAL("-"), // natural, just as expected
        SHARP("#"); // sharp, half a tone higher

        /**
         * Symbol, used for display.
         */
        public final String symbol;

        /**
         * Ctor
         *
         * @param symbol
         *         field value.
         */
        Modifier(String symbol) {
            this.symbol = symbol;
        }

        @Override public String toString() {
            return symbol;
        }
    }
}
