#ifndef WORD_MANAGER_HPP
#define WORD_MANAGER_HPP

#include <vector>
#include <string>
#include "../defs.hpp"

class Dictionary{
    private:
        std::vector<std::string> dictionary;
        std::string filename = WORD_LIST_TXT;

    public:
        Dictionary();
        bool isValidWord(const std::string word);
        void getDictionary(const std::string& filename);
        std::string getRandomWord();
};

#endif