#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

// Функция для проверки открытия файла
void checkFile(const ifstream& file, const string& filename) 
{
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
}

// Функция для извлечения номеров телефонов из строки
vector<string> PhoneNumbers(const string& line)
{
    vector<string> phoneNumbers;
    regex pattern(R"((^|\s)(\+7|8)\(\d{3}\)\d{3}-\d{2}-\d{2}($|\s))");
    smatch matches;
    string::const_iterator search(line.cbegin());

    while (regex_search(search, line.cend(), matches, pattern))
    {
        phoneNumbers.push_back(matches[0]);
        search = matches[0].second;
    }

    return phoneNumbers;
}

// Функция для обработки файла и вывода результатов
void process(const string& filename)
{
    ifstream file(filename);
    checkFile(file, filename);

    string line;
    while (getline(file, line))
    {
        vector<string> numbers = PhoneNumbers(line);
        for (const auto& number : numbers)
        {
            cout << number << endl;
        }
    }

    file.close();
}

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    process(argv[1]);
    return 0;
}