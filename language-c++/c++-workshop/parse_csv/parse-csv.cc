#include "parse-csv.hh"

std::vector<std::vector<std::string>> parse_csv(const std::string& file_name)
{
    std::ifstream input_file;
    input_file.open(file_name);

    if (!input_file.is_open())
        throw std::ios_base::failure("Error opening file");

    std::vector<std::vector<std::string>> vector;
    std::string word;

    int count_line = 0;
    int right_op = 0;

    while (std::getline(input_file, word))
    {
        count_line++;
        std::vector<std::string> column;
        std::stringstream line_s(word);
        std::string token_word;

        int right_op_bis = 0;

        while (std::getline(line_s, token_word, ','))
        {
            right_op_bis++;
            column.push_back(token_word);
        }

        if (*(word.end() - 1) == ',')
        {
            right_op_bis++;
            column.push_back("");
        }

        if (count_line != 1 && right_op != right_op_bis)
        {
            std::stringstream error_stream;
            error_stream << "Non consistent number of columns at line "
                         << count_line;
            throw std::ios_base::failure(error_stream.str());
        }

        right_op = right_op_bis;
        vector.push_back(column);
    }
    return vector;
}
