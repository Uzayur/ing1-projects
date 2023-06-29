#include "replace.hh"

std::string replace_token(std::string& token, const std::string& src_token,
                          const std::string& dst_token)
{
    for (size_t k = 0; k < token.size(); k++)
    {
        if (token[k] == src_token[0])
        {
            size_t index = k;
            size_t count = 0;
            while (token[index] == src_token[count] && token[index] != '\0')
            {
                count++;
                index++;
            }

            if (count == src_token.size())
            {
                token.replace(k, src_token.size(), dst_token);
                k += dst_token.size();
            }
        }
    }
    return token;
}

void replace(const std::string& input_filename,
             const std::string& output_filename, const std::string& src_token,
             const std::string& dst_token)
{
    std::ofstream file_out;
    std::ifstream file_in;

    file_in.open(input_filename);
    file_out.open(output_filename);

    if (!file_in.is_open())
    {
        std::cerr << "Cannot open input file\n";
        return;
    }
    if (!file_out.is_open())
    {
        std::cerr << "Cannot write output file\n";
        return;
    }

    for (std::string token; std::getline(file_in, token);)
    {
        file_out << replace_token(token, src_token, dst_token) << "\n";
    }
}
