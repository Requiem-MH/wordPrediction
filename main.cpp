#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>

// Code provided by instructor for reading dictionary into tree
std::shared_ptr<WordTree> readDictionary(std::string filename);

int main()
{
    std::shared_ptr<WordTree> wordTree = readDictionary("dictionary.txt");

    rlutil::cls();
    std::string word;
    while (true)
    {
        auto key = rlutil::getkey();

        if (key == rlutil::KEY_BACKSPACE)
        {
            word.pop_back();
        }
        else
        {
            char let = static_cast<char>(key);
            word.push_back(let);
        }
        rlutil::locate(1, 1);

        //Loop for screen update between key presses
        for (int j = 1; j < rlutil::trows() - 1; j++)
        {
            std::cout << "                                 " << std::endl;
        }
        rlutil::locate(1, 1);
        std::cout << word << std::endl;

        std::cout << "--- predictions ---" << std::endl;
        auto predictions = wordTree->predict(word, rlutil::trows() - 4);
        for (auto i : predictions)
        {
            std::cout << i << std::endl;
        }
        rlutil::locate(word.size() + 1, 1);
    }

    return 0;
}

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it
        // exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send
        // isalpha an unsigned char or it will throw exception on negative values;
        // e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(),
                        [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(),
                           [](char c) { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}
