#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string isValid(string s) {
	map<char,int> myMap;
	int result=0;
	for(int i = 0; i < s.size(); i++) 
		myMap[s[i]]++;
	sort(s.begin(), s.end());
	string::iterator iter;
	iter = unique(s.begin(), s.end());
	s.resize(distance(s.begin(), iter));
	for(int i = 1; i < s.size(); i++){
		if(myMap[s[i]] != myMap[s[0]]) result++;
		}
	if(result > 1) return "NO";
	return "YES";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
