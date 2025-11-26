#include "utils.hpp"

bool isIdentical(const std::vector<char> &vect, const std::string &str)
{
    if (vect.size() < str.size())
        return false;
    for (size_t i = 0; i < str.size(); i++)
    {
        if(vect[i] != str[i])
            return (false);
    }
    return (true);
}

void cut_vect(std::vector<char> &vect, size_t size)
{
    if (size > vect.size())
        size = vect.size();
    vect.erase(vect.begin(), vect.begin() + size);
}
