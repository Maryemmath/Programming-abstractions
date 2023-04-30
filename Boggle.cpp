/*
* File: Boggle.cpp
* ----------------
* Name: [TODO: enter name here]
* Section: [TODO: enter section leader here]
* This file is the main starter file for Assignment #4, Boggle.
* [TODO: extend the documentation]
*/
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
 
using namespace std;
 
/* Constants */
 
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int NROWS = 4;
const int NCOLS = 4;
const string STANDARD_CUBES[16] = {
	"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
	"AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
	"DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
	"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25] = {
	"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
	"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
	"CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
	"DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
	"FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};
 
/* Function prototypes */
 
void welcome();
void giveInstructions();
 
/* Main program */
 
 
bool recursionOnTable(int x, int y, string word, Grid<bool> &visitedChars, Grid<char> &charsOnTable) {
	if (word == "")
		return true;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (visitedChars.inBounds(i, j) && !visitedChars[i][j] && charsOnTable[i][j] == word[0]) {
				visitedChars[i][j] = true;
				if (recursionOnTable(i, j, word.substr(1), visitedChars, charsOnTable)) {
					highlightCube(i, j, true);		
					return true;
 
				}
				visitedChars[i][j] = false;
			}
		}
	}
	return false;
}
 
 
bool foundOnTable(string word, Grid<char> &charsOnTable) {
	for (int i = 0; i < NROWS; i++) {
		for (int j = 0; j < NCOLS; j++) {
			Grid<bool> visitedChars(NROWS, NCOLS);
			visitedChars[i][j] = true;
			if (recursionOnTable(i, j, word, visitedChars, charsOnTable)){
				return true;
			}
		}
	}
	return false;
 
}
 
bool checkIfPossible(string word, Grid<char> &charsOnTable, Set<string> &usedWords) {
		if (foundOnTable(word, charsOnTable)) {
			usedWords.add(word);
			return true;
	}
	return false;
}
 
void gameOnForPlayer(Grid<char> &charsOnTable, Set<string> &usedWords, Lexicon &WordsLexicon) {
	while (true) {
		string word = toUpperCase(getLine("Enter a word: "));
		if(word == ""){
			break;
		}
		if (word.length() < 4) {
			cout << "I'm sorry, but we have our standards."
				<< "That word doesn't meet the minimum word length." << endl;	
		}else if (!WordsLexicon.contains(word)){
			cout << "This is not a word! "<<endl;
		}else if(usedWords.contains(word)){
			cout<<"This word is already guessed"<<endl;
		}else if(checkIfPossible(word, charsOnTable, usedWords)){	
			recordWordForPlayer(word, HUMAN);
		}else{
			cout<<"you can't make that word!"<<endl;
		}

		pause(500);
		for(int i =0;i < NROWS; i++){
			for(int j = 0; j < NCOLS; j++){
				highlightCube(i, j, false);		
			}
		}
	}
}
 
void addCharsToTable(Vector<char> &charVec, Grid<char> &charsOnTable) {
	int k = 0;
	for (int i = 0; i < NROWS; i++) {
		for (int j = 0; j < NCOLS; j++) {
			charsOnTable[i][j] = charVec[k];
			labelCube(i, j, charVec[k]);
			k++;
		}
	}
}
 
void randSequencesTable(Vector<string> &chars, Grid<char> &charsOnTable) {
	Vector<char> randomChars;
	for (int i = 0; i < 16; i++) {
		int randIndex = randomInteger(0, 5);
		randomChars.add(chars[i][randIndex]);
	}
	addCharsToTable(randomChars, charsOnTable);
}
void generateRandTable(Grid<char> &charsOnTable) {
	Vector<string> characters;
	for (int i = 0; i < 16; i++) {
		characters.add(STANDARD_CUBES[i]);
	}
	for (int i = 0; i < characters.size(); i++) {
		int index = randomInteger(i, characters.size() - 1);
		swap(characters[i], characters[index]);
	}
	randSequencesTable(characters, charsOnTable);
}
 
void generateTableWithStr(string characters, Grid<char> &charsOnTable) {
	Vector<char> charVec;
	for (int i = 0; i < characters.length(); i++) {
		charVec.add(characters[i]);
	}
	addCharsToTable(charVec, charsOnTable);
}
 
void makeConfiguration(Grid<char> &charsOnTable) {
	string characters = toUpperCase(getLine("Enter the string: "));
	while (true) {
		if (characters.length() == 16) {
			generateTableWithStr(characters, charsOnTable);
			break;
		}
		if (characters.length() != 16) {
			cout << "String must include 16 characters! Try again: " << endl;
			characters = getLine();
		}
	}
}
 
void boardConfiguration(Grid<char> &charsOnTable) {
	cout << "I'll give you a chance to set up the board to your specification"
		<< "which makes it easier to confirm your boggle program is working" << endl;
	string confAnsw = getLine("Do you want to force the board configuration? ");
	if (confAnsw == "yes") {
		cout << "Enter a 16-character string to identify which letters you want on the cubes."
			<< "The first 4 letters are the cubes on the top row from left to right,"
			<< "the next 4 letters are the second row, and so on. " << endl;
		makeConfiguration(charsOnTable);
 
	}
	if (confAnsw == "no") {
		generateRandTable(charsOnTable);
		cout << "Ok, take all the time you want and find all the words you can!"
			<< "Signal that you're finished by entering an empty line. " << endl;
		getLine();
	}
}
void intro(Grid<char> &charsOnTable) {
	while (true) {
		string answer = getLine("Do you need instructions? ");
		if (answer == "yes") {
			giveInstructions();
			boardConfiguration(charsOnTable);
			break;
		}
		if (answer == "no") {
			drawBoard(NROWS, NCOLS);
			boardConfiguration(charsOnTable);
			break;
		}
		cout << "Please, answer yes or no " << endl;
	}
}
bool strIsValid(string &soFar, Lexicon &WordsLexicon, Set<string> &usedWords){
	if(soFar.length() > 3  && WordsLexicon.contains(soFar) && !usedWords.contains(soFar))return true;
	else return false;

}
void recursionForComputer(int x, int y, string soFar, Set<string> &usedWords, Lexicon &WordsLexicon, Grid<char> &charsOnTable, Grid <bool> &compVisited){
	if(strIsValid(soFar, WordsLexicon,usedWords)){
		usedWords.add(soFar);
		recordWordForPlayer(soFar, COMPUTER);
	
	}
	for (int i = x- 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (compVisited.inBounds(i, j) && !compVisited[i][j] && WordsLexicon.containsPrefix(soFar)) {
				compVisited[i][j] = true;
				string temp = soFar + charsOnTable[i][j];
				recursionForComputer(i,j,temp, usedWords, WordsLexicon,charsOnTable, compVisited);
				compVisited[i][j] = false;
			}
		}
	}

}
void gameOnForComputer(Set<string> &usedWords, Lexicon &WordsLexicon, Grid<char> &charsOnTable){
	string soFar = "";
	Grid <bool> compVisited(NROWS, NCOLS);
	for(int i = 0; i < NROWS; i++){
		for(int j = 0; j < NROWS; j++){
			compVisited[i][j]= true;
			recursionForComputer(i, j, soFar + charsOnTable[i][j], usedWords, WordsLexicon, charsOnTable, compVisited);
			compVisited[i][j] = false;
		}
	}

}
 
 
int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	
	welcome();
	initGBoggle(gw);
	while(true){
	Grid<char>charsOnTable(NROWS, NCOLS);
	Set<string> usedWords;
	Lexicon WordsLexicon("EnglishWords.dat");
	intro(charsOnTable);
	gameOnForPlayer(charsOnTable, usedWords, WordsLexicon);
	gameOnForComputer(usedWords, WordsLexicon, charsOnTable);
	string restart = getLine("Do you want to restart the game? ");
	if(restart != "yes")break;
	}
	return 0;
}
 
/*
* Function: welcome
* Usage: welcome();
* -----------------
* Print out a cheery welcome message.
*/
 
void welcome() {
	cout << "Welcome!  You're about to play an intense game ";
	cout << "of mind-numbing Boggle.  The good news is that ";
	cout << "you might improve your vocabulary a bit.  The ";
	cout << "bad news is that you're probably going to lose ";
	cout << "miserably to this little dictionary-toting hunk ";
	cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}
 
/*
* Function: giveInstructions
* Usage: giveInstructions();
* --------------------------
* Print out the instructions for the user.
*/
 
void giveInstructions() {
	cout << endl;
	cout << "The boggle board is a grid onto which I ";
	cout << "I will randomly distribute cubes. These ";
	cout << "6-sided cubes have letters rather than ";
	cout << "numbers on the faces, creating a grid of ";
	cout << "letters on which you try to form words. ";
	cout << "You go first, entering all the words you can ";
	cout << "find that are formed by tracing adjoining ";
	cout << "letters. Two letters adjoin if they are next ";
	cout << "to each other horizontally, vertically, or ";
	cout << "diagonally. A letter can only be used once ";
	cout << "in each word. Words must be at least four ";
	cout << "letters long and can be counted only once. ";
	cout << "You score points based on word length: a ";
	cout << "4-letter word is worth 1 point, 5-letters ";
	cout << "earn 2 points, and so on. After your puny ";
	cout << "brain is exhausted, I, the supercomputer, ";
	cout << "will find all the remaining words and double ";
	cout << "or triple your paltry score." << endl << endl;
	cout << "Hit return when you're ready...";
	getLine();
	drawBoard(NROWS, NROWS);
}