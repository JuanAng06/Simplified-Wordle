#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

const int MAX_BAD_GUESS_COUNT = 6; //Max bad guess count

////////////////////////////// Intialization ///////////////////////////////////////

//Initialize guessedWord with '_'
string guessedWord(string secret) {
	string guessed = string(secret.length(), '_');
	return guessed;
}

////////////////////////////// Generate a word //////////////////////////////////////

//Check if it's a word
bool isWord(string word) {
	for (char c : word) {
		if (c < 'A' || 'Z' < c && c < 'a' || c > 'z') return false;
	}
	if (word.size() != 5) return false;
	return true;
}

const int WORD_LENGTH = 5;

//Generate a random word
string secretWord() {

	//Read a file
	string filePath = "wordlist.txt";
	ifstream dic(filePath);

	//Create a dictionary
	vector<string> dictionary;
	string word;

	//Get the words
	if (dic.is_open()) {
		while (dic >> word) {
			int letterCount = word.length();
			if (letterCount == WORD_LENGTH && isWord(word)) dictionary.push_back(word);
		}
	}
	int dicSize = dictionary.size();

	//Generate the word
	if (dicSize > 0) {
		int randomIndex = rand() % dicSize;
		string secretWord = dictionary[randomIndex];
		return secretWord;
	}

	//If dictionary size == 0
	return "ERROR. There's no word on: filePath.txt";
}

///////////////////////// End ///////////////////////////////////

//////////////////////// Guess the word ////////////////////////////

//Generate guess word
string input() {
	string word;
	cout << "Choose a 5 letter word: ";
	cin >> word;
	for (char &c : word) {
		c = tolower(c);
	}
	return word;
}

//Check if it's a valid word
bool isValidWord(string word) {
	if (isWord(word)) return true;
	cout << "Hey! That's not a valid word. Try again!" << endl;
	return false;
}

//////////////////////// End ////////////////////////////

/////////////////////// Update the word /////////////////////

//Check: Correct letter + position
bool contains(string secretWord, char guess) {
	for (size_t i = 0; i < secretWord.size(); i++) {
		if (guess == secretWord[i]) {
			return true;
		}
	}
	return false;
}

//Update word
void update(const string &secretWord, string &guessedWord, string guess, vector<string> &guesses, vector<vector<char>> &wrongPos, vector<char> &wrongLetter) {

	//Save letters of secretWord
	int searchLetter[255] = {0};
	for (char c : secretWord) {
		searchLetter[c]++;
	}

	//Lower the letter
	for (char c : guess) {
		c = tolower(c);
	}

	//Correct letter + position => Update guessedWord + update letterSearch
	for (size_t i = 0; i < guess.size(); i++) {
		if ( guess[i] == secretWord[i] ) {
			guessedWord[i] = guess[i];
			searchLetter[guess[i]]--;
		}
	}

	//Correct letter + wrong position (Haven't count dupplicate letter yet) => Update wrongPos
	vector<char> currentWrongPos;
	for (size_t i = 0; i < guess.size(); i++) {
		if ( guess[i] != secretWord[i] && contains(secretWord, guess[i]) && searchLetter[guess[i]] > 0) {
			currentWrongPos.push_back(guess[i]);
			searchLetter[guess[i]]--;
		}
	}
	sort(currentWrongPos.begin(), currentWrongPos.end());
	currentWrongPos.erase(unique(currentWrongPos.begin(), currentWrongPos.end()), currentWrongPos.end());
	wrongPos.push_back(currentWrongPos);

	//Wrong letter => Update wrongLetter
	for (size_t i = 0; i < guess.size(); i++) {
		if ( !contains(secretWord, guess[i]) ) wrongLetter.push_back(guess[i]);
	}

	//Remove duplicate
	sort(wrongLetter.begin(), wrongLetter.end());
	wrongLetter.erase(unique(wrongLetter.begin(), wrongLetter.end()), wrongLetter.end());

	//Update guesses (correct pos = UPPERCASE)
	for (size_t i = 0; i < guess.size(); i++) {
		if ( guess[i] == secretWord[i] ) {
			guess[i] = toupper(guess[i]);
		}
	}
	guesses.push_back(guess);
}

/////////////////////// End of "Update the word" /////////////////////

////////////////////// Render Game //////////////////////////////////
void renderGame(vector<string> guesses, vector<vector<char>> wrongPos, vector<char> wrongLetter, string guessedWord, int badGuessCount) {

	for (int i = 0; i < 40; i++) {
		cout << endl;
	}
	cout << "Previous guesses (Note: uppercase letters are right characters + positions) :" << endl;
	for (size_t i = 0; i < guesses.size(); i++) {
		cout << guesses[i] << " ";
		cout << "(Wrong positions: ";
		for (char c : wrongPos[i]) {
			cout << c << " ";
		}
		cout << ")" << endl;
	}
	cout << string(10, '-') << endl;

	cout << endl;

	cout << "Wrong characters: ";
	for (size_t i = 0; i < wrongLetter.size(); i++) {
		cout << wrongLetter[i] << " ";
	}
	cout << endl;

	cout << "Wrong guess count: " << badGuessCount << "/" << MAX_BAD_GUESS_COUNT << endl;

	cout << "Current word: " << guessedWord << endl << endl;
	cout << string(10, '-') << endl;
}

//////////////////////// End of "Render Game" ////////////////////////////

/////////////////////// Print result ////////////////////////////////////
void printResult(int badGuessCount, string secretWord) {
	if (badGuessCount == MAX_BAD_GUESS_COUNT) {
		cout << "Game over! The Secret word is: " << secretWord;
	}
	else
		cout << "Congratulations! You won! The secret word is: " << secretWord;
}
/////////////////////// End of "Print result" ////////////////////////////////////

/////////////////////// Play again? ///////////////////////////////////////
bool restart() {
	string c;
	cout << endl << "Do you want to play again? (Y / N): ";
	cin.ignore();
	cin >> c;
	while (c != "y" && c != "Y" && c != "n" && c != "N") {
		cout << "Invalid answer! Try again: ";
		cin >> c;
	}
	if (c.length() == 1 && (c == "Y" || c == "y")) {
		for (int i = 0; i < 30; i++) {
			cout << endl;
		}
		cout << "Okay! Lemme find a new word for you..." << endl;
		return true;
	}

	cout << endl << "Okay! Thanks for playing!";
	return false;
}
////////////////////// End of "Play again?" /////////////////////////////

int main() {

	srand(time(NULL));

	do {
		//Initialization
		int badGuessCount_ = 0;
		string secretWord_ = secretWord();
		string guessedWord_ = guessedWord(secretWord_);
		vector<string> guesses_ ;
		vector<vector<char>> wrongPos_ ;
		vector<char> wrongLetter_;
		guesses_.clear();
		wrongPos_.clear();
		wrongLetter_.clear();
		string guess_ = "";
		int count = 0;

		//Game loop
		do {
			sleep(1);
			renderGame(guesses_, wrongPos_, wrongLetter_, guessedWord_, badGuessCount_);
			guess_ = input();

			bool validWord = isValidWord(guess_);

			if (validWord) {
				update(secretWord_, guessedWord_, guess_, guesses_, wrongPos_, wrongLetter_);
				badGuessCount_ ++;
			}
		} while(badGuessCount_ < MAX_BAD_GUESS_COUNT && guessedWord_ != secretWord_);

		renderGame(guesses_, wrongPos_, wrongLetter_, guessedWord_, badGuessCount_);
		printResult(badGuessCount_, secretWord_);
	} while (restart());
}
