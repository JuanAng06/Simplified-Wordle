#include "wordManager.hpp"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

Dictionary::Dictionary(){
    srand(time(0));
}

bool Dictionary::isValidWord(const std::string word){
    //word size != 5
    if (word.size() != 5) return false;

    //Check the word
    for (char c : word) {
		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return false;
	}
	return true;
}

void Dictionary::getDictionary(const std::string& filename){
    std::ifstream dic(filename);

	//Create a dictionary
	std::string word;

	//Get the words
	if (dic.is_open()) {
		while (dic >> word) {
			int letterCount = word.length();
			if (letterCount == WORD_LENGTH && isValidWord(word)) dictionary.push_back(word);
		}
	}
    else{
        std::cerr << "Error: Cannot open dictionary file " << filename << "\n";
    }
}

std::string Dictionary::getRandomWord(){
    int dicSize = dictionary.size();

	//Generate the word
	if (dicSize > 0) {
		int randomIndex = rand() % dicSize;
		std::string secretWord = dictionary[randomIndex];
		return secretWord;
	}

	//If dictionary size == 0
	return "ERROR. There's no word on: filePath.txt";
}