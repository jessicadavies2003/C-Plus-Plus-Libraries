#ifndef key1
#define key1

#include <string>
#include <vector>
using namespace std;

// a string class with more advanced functions for all your string needs! Including substrings, finding characters, and more.
class BetterString {
private:
	string s;

public:
	int length;
	BetterString(string str = "") {
		s = str;
		length = s.size();
	}

	// returns a vector with `str` as the only element if `sep` isn't found in `str`. Default seperator is " ".
	vector<string> split(string sep = " ") {
		if (s.find(sep) == -1) {
			return { s };
		}

		string currStr = s;
		vector<string> result = {};
		int foundIdx = 0;

		while (foundIdx != -1) {
			foundIdx = currStr.find(sep);
			result.push_back(currStr.substr(0, foundIdx));
			currStr.erase(0, foundIdx + 1);
		}

		return result;
	}

	// returns a substring between 2 given indexes
	string subString(int startIdx, int endIdx, bool makeLower = true) {
		string result;
		for (int i = startIdx; i < endIdx; i++) {
			if (makeLower) {
				result = result + (char)tolower(s.at(i));
			}
			else {
				result = result + s.at(i);
			}
		}
		return result;
	}

	// returns the index of `chr`, or -1 if not found
	int indexOf(char chr) {
		for (int i = 0; i < s.size(); i++) {
			if (s.at(i) == chr) {
				return i;
			}
		}
		return -1;
	}

	// converts the string to uppercase
	string toUpper() {
		string result;
		for (int i = 0; i < s.size(); i++) {
			result = result + (char)toupper(s.at(i));
		}
		return result;
	}

	// converts the string to uppercase
	string toLower() {
		string result;
		for (int i = 0; i < s.size(); i++) {
			result = result + (char)tolower(s.at(i));
		}
		return result;
	}

	// converts the first character of string to uppercase, then everything else lowercase
	string capitalise() {
		return (char)toupper(s.at(0)) + this->subString(1, s.size());
	}

	// converts the string to a vector of its characters
	// return type: vector<char>
	vector<char> toCharsVector() {
		vector<char> result;
		for (int i = 0; i < s.size(); i++) {
			result.push_back((char)s.at(i));
		}
		return result;
	}

	// finds and returns the character at a given index
	char charAt(int idx) {
		return s.at(idx);
	}

	// Reverses the string
	string reverse() {
		string result = "";
		for (int i = s.length() - 1; i > -1; i--) {
			result = result + s.at(i);
		}
		return result;
	}

	// counts the number of character occurences in a string/
	int countOccurence(char c) {
		int result = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s.at(i) == c) {
				result++;
			}
		}
		return result;
	}

	// checks if the string ends with the given substring
	bool endsWith(string ending) {
		int endingLen = ending.size();
		string snippedStr = this->subString((s.size() - endingLen), s.size(), false);
		return snippedStr == ending;
	}

	// fills a string with the given value
	void fill(char c, int length) {
		for (int i = 0; i < length; i++) {
			s = s + c;
		}
	}

	// outputs the string
	void print(bool endLine = false) {
		if (endLine) {
			cout << s << endl;
		} else  {
			cout << s;
		}
	}

	// checks if the string has whitespace
	bool hasWhitespace() {
		for (int i = 0; i < s.size(); i++) {
			cout << s[i] << endl;
			if (s[i] == ' ') {
				return true;
			}
		}
		return false;
	}

	// checks if a string contains digits
	bool hasDigits() {
        vector<string> digits = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        for (string digit : digits) {
            if (s.find(digit) != -1) {
                return true;
            }
        }
        return false;
    }
};

#endif
