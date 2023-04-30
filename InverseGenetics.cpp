#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;


/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);


/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map.*/
    Map<char, Set<string> > codons = loadCodonMap();
	while(true) {
		string input = toUpperCase(getLine("Enter the protein: "));
		listAllRNAStrandsFor(input, codons);
	}
    return 0;
}
/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }
    return result;
}

//wrappered function 
void wrapper(string input, Map<char, Set<string> >& codons, Vector<string>& RNAStrands) {
	if(input == "") {
		cout << RNAStrands.toString() << endl;
	} else {
			Set<string> set = codons[input[0]];
			foreach(string str in set){
				RNAStrands += str;
				wrapper(input.substr(1), codons, RNAStrands);
				RNAStrands.remove(RNAStrands.size()-1);
		}
	}
}
//wrapper class
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
	Vector<string> RNAStrands;
		wrapper(protein, codons, RNAStrands);
}