#include "rotx.hh"

RotX::RotX(std::string message, int key)
    : Encrypt::Encrypt(message)
    , key_(key)
{}

void RotX::process() const
{
    std::string output;

    for (size_t k = 0; k < input_.size(); ++k)
    {
        int key_char = key_;
        int key_digit = key_;
        if (key_ < 0)
        {
            key_char = 26 - (-key_ % 26);
            key_digit = 10 - (-key_ % 10);
        }

        char c;
        if (std::isdigit(input_[k]))
            c = (input_[k] - '0' + key_digit) % 10 + '0';

        else if (std::isupper(input_[k]))
            c = (input_[k] + key_char - 'A') % 26 + 'A';

        else if (std::islower(input_[k]))
            c = (input_[k] + key_char - 'a') % 26 + 'a';

        else
            c = input_[k];

        output += c;
    }

    std::cout << output << '\n';
}
