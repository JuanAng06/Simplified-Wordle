#include "wordProcessor.hpp"

WordProcessor::WordProcessor() {
    gridState = std::vector<std::vector<int>>(ROWS, std::vector<int>(WORD_LENGTH, -1));
}

//Load dictionary
void WordProcessor::loadDictionary(const std::string& filepath){
    dictionary.getDictionary(filepath);
}

//Choose a word
void WordProcessor::setSecretWord(){
    secretWord = dictionary.getRandomWord();
}

void WordProcessor::checkGuess(const std::string& previousGuess, int row){
    if (previousGuess.length() != WORD_LENGTH) return; //if it's not long enough => End this immidiately

    std::vector<int> rowState (WORD_LENGTH, -1); //default: -1
    int searchLetter[255] = {0}; //Count the time the letter appeared on secretLetter

    //Save them
    for (char c : secretWord) { searchLetter[c]++; }

    // Convert previousGuess to lower char (Just in case :3c / Backup ykyk)
    std::string lowerGuess = previousGuess;
    for (char &c : lowerGuess){ c = tolower(c); }

    //Correct letter
    for (size_t i = 0; i < lowerGuess.size(); i++){
        if (lowerGuess[i] == secretWord[i]){
            rowState[i] = 2;
            searchLetter[lowerGuess[i]]--;
        }
    }

    //Misplaced letter + wrong letter
    for (size_t i = 0; i < lowerGuess.size(); i++){
        if (rowState[i] == 2) continue;

        if (searchLetter[lowerGuess[i]] > 0){
            rowState[i] = 1; //Misplaced letter
            searchLetter[lowerGuess[i]]--;
        } else {
            rowState[i] = 0; //wrong letter
        }
    }

    // Update grid
    if (row < gridState.size()){
        gridState[row] = rowState;
    }
}