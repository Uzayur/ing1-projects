#include "termcolor.hh"

namespace termcolor
{
    /* CONSTRUCTORS */
    my_ostream::my_ostream(std::ostream& stream, background background)
        : stream_(stream)
        , bg_(background)
        , fg_(foreground::white)
    {
        stream_ << "\x1B[" << static_cast<int>(background) << "m";
    }

    my_ostream::my_ostream(std::ostream& stream, foreground foreground)
        : stream_(stream)
        , bg_(background::black)
        , fg_(foreground)
    {
        stream_ << "\x1B[" << static_cast<int>(foreground) << "m";
    }

    /* DESTRUCTOR */
    my_ostream::~my_ostream()
    {
        stream_ << "\x1B[0m";
    }

    /* OPERATORS IN CLASS */
    my_ostream& my_ostream::operator<<(const background& bg)
    {
        stream_ << "\x1B[" << static_cast<int>(bg) << "m";
        return *this;
    }

    my_ostream& my_ostream::operator<<(const foreground& fg)
    {
        stream_ << "\x1B[" << static_cast<int>(fg) << "m";
        return *this;
    }

    my_ostream& my_ostream::operator<<(std::ostream& (*fun)(std::ostream&))
    {
        stream_ << fun;
        return *this;
    }

    /* OPERATORS OUT OF CLASS */
    my_ostream operator<<(std::ostream& out, background val)
    {
        return my_ostream(out, val);
    }

    my_ostream operator<<(std::ostream& out, foreground val)
    {
        return my_ostream(out, val);
    }
} // namespace termcolor
