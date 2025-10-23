#ifndef key2
#define key2

#include <string>
#include <vector>
using namespace std;

// desc to be added
class Dictionary {
private:
	vector<string> keys;
	vector<string> values;
	int indexOf(string key) {
		for (int i = 0; i < keys.size(); i++) {
			if (keys[i] == key) {
				return i;
			}
		}
		return -1;
	}

public:
	Dictionary() {
		
	}

	// appends a given key-value pair to the dictionary.
	void addKeyValue(string key, string value) {
		keys.push_back(key);
		values.push_back(value);
	}

	// returns the key at a given index.
	string key(int index) {
		return keys[index];
	}

	// returns the value with a given key.
	string value(string key) {
		if (indexOf(key) == -1) {
			return "null";
		}
		else {
			return values[indexOf(key)];
		}
	}

	// returns a vector of all keys in the dictionary
	vector<string> getKeys() {
		return keys;
	}

	// returns a vector of all values in the dictionary
	vector<string> getValues() {
		return values;
	}

	// removes a key-value pair given the key value.
	void removeKeyValue(string key) {
		int idx = indexOf(key);

		if (idx == 0) {
			keys.erase(keys.begin());
			values.erase(values.begin());
		}
		else {
			keys.erase(keys.begin() + idx);
			values.erase(values.begin() + idx);
		}
	}

	// removes the last key-value pair inserted.
	void popItem() {
		keys.erase(keys.end());
		values.erase(values.end());
	}
};

#endif
