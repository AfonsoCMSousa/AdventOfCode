#ifndef FILE_IO_CPP
#define FILE_IO_CPP

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<char>> read_char(const char *filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return std::vector<std::vector<char>>();
    }

    std::vector<std::vector<char>> lines;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<char> charLine(line.begin(), line.end());
        lines.push_back(charLine);
    }

    file.close();
    return lines;
}

std::vector<std::vector<int>> read_int(const char *filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return std::vector<std::vector<int>>();
    }

    std::vector<std::vector<int>> lines;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> longlongLine;
        int number;
        while (iss >> number)
        {
            longlongLine.push_back(number);
        }
        lines.push_back(longlongLine);
    }

    file.close();
    return lines;
}

std::vector<std::vector<uint64_t>> read_int_seperator(const char *filePath, std::vector<char> seperators)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return std::vector<std::vector<uint64_t>>();
    }

    std::vector<std::vector<uint64_t>> lines;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<uint64_t> longlongLine;
        std::string numberStr;
        for (char ch : line)
        {
            if (std::find(seperators.begin(), seperators.end(), ch) != seperators.end())
            {
                if (!numberStr.empty())
                {
                    longlongLine.push_back(std::stoll(numberStr));
                    numberStr.clear();
                }
            }
            else
            {
                numberStr += ch;
            }
        }
        if (!numberStr.empty())
        {
            longlongLine.push_back(std::stoll(numberStr));
        }
        lines.push_back(longlongLine);
    }

    file.close();
    return lines;
}

std::vector<uint64_t> get_digits(uint64_t number) {
    std::vector<uint64_t> _return_vec;
	while (number != 0) {
		_return_vec.push_back(number % 10);
		number /= 10;
	}
	return _return_vec;
}

#endif // FILE_IO_CPP
