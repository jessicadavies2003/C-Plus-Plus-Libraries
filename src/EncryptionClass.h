#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Encryption {
private:
	vector<char> char2ASCIILookup = { ' ', '!', '"', '#', '$', ' ', '%', ' ', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', };
	vector<char> base64alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
	vector<int> nums = { (int)pow(2, 7) , (int)pow(2, 6), (int)pow(2, 5), (int)pow(2, 4), (int)pow(2, 3), (int)pow(2, 2), (int)pow(2, 1), (int)pow(2, 0) };
	// backspace copy paste '\'

	// converts a character into its ASCII code equivalent.
	int char2ASCII(char a) {
		// start at idx 32		
		for (int i = 0; i < char2ASCIILookup.size(); i++) {
			if (char2ASCIILookup[i] == a && isupper(a)) {
				return i + 32;
			}
			else if (char2ASCIILookup[i] == a && islower(a)) {
				return i + 33;
			}
		}

		return -1;
	}

	int ascii2Char(int n) {
		return base64alphabet[n];
	}

	string subString(string s, int startIdx, int endIdx, bool makeLower = false) {
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

	vector<string> splitStringByIndex(string str, int idx) {
		int currIdx = 0;
		vector<string> result;

		while (currIdx < str.size()) {
			if (currIdx + idx >= str.size()) {
				result.push_back(subString(str, currIdx, str.size()));
				break;
			}

			result.push_back(subString(str, currIdx, currIdx + idx));
			currIdx += idx;
		}

		return result;
	}

	void displayStrVector(vector<string> s) {
		cout << "{ ";
		for (string each : s) {
			cout << each << ", ";
		}
		cout << " }" << endl;
	}

	string repeatStr(char a, int numTimes) {
		string result;
		for (int i = 0; i < numTimes; i++) {
			result += a;
		}
		return result;
	}

	string repeatUntilAmount(string str, char a, int len) {
		string result = str;
		while (result.size() != len) {
			result += a;
		}
		return result;
	}

public:
	string int2Binary(int n) {
		int tempNum = n;
		string result;

		for (int each : nums) {
			int currResult = tempNum - each;
			if (currResult >= 0) {
				tempNum = currResult;
				result += "1";
			}
			else {
				result += "0";
			}
		}
		return result;
	}

	int bin2Int(string bin) {
		int startIdx = nums.size() - bin.size();
		int binIdx = 0;
		int result = 0;

		for (int i = startIdx; i < nums.size(); i++) {
			char currBit = (char)bin.at(binIdx);

			if (currBit == '1') {
				result += nums[i];
			}

			binIdx++;
		}
		return result;
	}

	string base64Encode(string s) {
		string result;
		string binaryStuff;

		for (int i = 0; i < s.size(); i++) {
			char current = (char)s[i];
			binaryStuff += int2Binary(char2ASCII(current));
		}

		int numEach = 6;
		vector<string> splitBinary = splitStringByIndex(binaryStuff, numEach);
		for (string each : splitBinary) {
			if (each.size() < numEach) {
				string newEach = repeatUntilAmount(each, '0', numEach);
				result += ascii2Char(bin2Int(newEach));
				result += repeatStr('=', (numEach - each.size())/2);
			}
			else {
				result += ascii2Char(bin2Int(each));
			}
		}

		return result;
	}

	// TODO: finish
	string base64Decode(string encoded) {
		string result;
		string binaryStuff;

		for (int i = 0; i < encoded.size(); i++) {
			char current = (char)encoded[i];
			if (current == '=') {

			}
			else {
				binaryStuff += int2Binary(char2ASCII(current));
			}
		}

		return result;
	}
};
