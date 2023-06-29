#include "word-checker.hh"

bool WordChecker::operator()(std::string word)
{
    std::ifstream input_file;
    input_file.open(path_);
    std::string token;

    if (word.size() == 1)
    {
        while (input_file >> token)
        {
            if (token == word)
                return true;
        }
        return false;
    }

    else
    {
        input_file.close();

        for (size_t k = 0; k < word.size() - 1; k++)
        {
            std::string first_pair = "";
            first_pair += word[k];
            first_pair += word[k + 1];

            input_file.open(path_);

            auto test = 0;
            while (input_file >> token)
            {
                for (size_t p = 0; p < token.size() - 1; p++)
                {
                    std::string second_pair = "";
                    second_pair += token[p];
                    second_pair += token[p + 1];

                    if (second_pair == first_pair)
                        test = 1;
                }
            }
            if (test != 1)
                return false;
            test = 0;

            input_file.close();
        }
    }
    return true;
}
