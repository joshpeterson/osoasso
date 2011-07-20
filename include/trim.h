#ifndef __TRIM_H
#define __TRIM_H

inline std::string trim(const std::string& value)
{
    std::string::size_type first_non_whitespace = value.find_first_not_of(" \t\n\r");
    if (first_non_whitespace == std::string::npos)
    {
        return std::string();
    }

    std::string::size_type last_non_whitespace = value.find_last_not_of(" \t\n\r");

    return value.substr(first_non_whitespace, last_non_whitespace - first_non_whitespace + 1);
}

#endif // __TRIM_H

