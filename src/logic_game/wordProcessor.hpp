#ifndef WORD_PROCESSOR_HPP
#define WORD_PROCESSOR_HPP

#include <vector>
#include <string>

#include "../defs.hpp"
#include "../dictionary/wordManager.hpp"
#include "handleInput.hpp"

class WordProcessor {
    private:
        std::vector<std::vector<int>> gridState;
        std::string previousGuess = "";
        std::string secretWord = "";
        Dictionary dictionary;

    public:
        WordProcessor(); 
        void loadDictionary(const std::string &filepath); 
        void setSecretWord(); 
        std::string getSecretWord() const { return secretWord; } 

        void updatePreviousGuess(const HandleInput* inputHandler){
            previousGuess = inputHandler->getPreviousWord();
        }

        std::string getPreviousGuess () const { return previousGuess; } 

        // Check the word per guess
        void checkGuess(const std::string &getPreviousGuess, int row);
        const std::vector<std::vector<int>>& getGridState() const { return gridState; } // Get vector gridState

        // RESET GRIDSTATE
        void reset();
};

#endif