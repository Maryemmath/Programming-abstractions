
#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

//this method gets two strings for isSubsequence method 
int main() { 
	while (true){
	string subs = getLine("enter substring");
	string word = getLine("enter word");
	cout<<isSubsequence(word, subs);
   

	}
	 return 0;
}
/*
/this method defines whether entered string is
subsequence of the entered word recursively.
*/
bool isSubsequence(string word, string subs) {
	if(subs.length() > word.length())return false;
	if(subs == "") {
		return true;
	} else if (word == "") {
		if(subs == "") return true;
		else return false;
	} else {
		if(word[0] == subs[0]) {
			return isSubsequence(word.substr(1), subs.substr(1));
		} else {
			return isSubsequence(word.substr(1), subs);
		}
	}
}