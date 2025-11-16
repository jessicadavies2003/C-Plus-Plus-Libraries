#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "DictionaryClass.h"

/*
Heavily inspired by Rivescript, this class allows you to build your own (NON-AI) chatbot,
as well as customise its behaviour, provide substitutions (such as "what's" becoming "what is") and store variables,
allowing the bot to learn about the user!

Requirements: "DictionaryClass.h"
*/
class Chatbot {
	private:
		StrVecDictionary allResponses;
		StrStrDictionary substitutions;
		vector<string> userInputs;
		vector<string> varTags = {"<username>", "<botname>" };

		string botname;
		string username;

		vector<int> findAllOccurences(vector<string> arr, string query) {
			vector<int> result;
			for (int i = 0; i < arr.size(); i++) {
				if (arr[i] == query) {
					result.push_back(i);
				}
			}
			return result;
		}

		vector<int> findNonOccurences(vector<string> arr, string query) {
			vector<int> result;
			for (int i = 0; i < arr.size(); i++) {
				if (arr[i] != query) {
					result.push_back(i);
				}
			}
			return result;
		}

		string toLower(string s) {
			string result;
			for (int i = 0; i < s.size(); i++) {
				result = result + (char)tolower(s.at(i));
			}
			return result;
		}

		int findElementStr(vector<string> arr, string searchQuery) {
			for (int i = 0; i < arr.size(); i++) {
				if (searchQuery == arr[i]) {
					return i;
				}
			}
			return -1;
		}

		int findElementInt(vector<int> arr, int searchQuery) {
			for (int i = 0; i < arr.size(); i++) {
				if (searchQuery == arr[i]) {
					return i;
				}
			}
			return -1;
		}

		// returns a vector with `str` as the only element if `sep` isn't found in `str`. Default seperator is " ".
		vector<string> split(string s, string sep = " ") {
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

		string join(vector<string> arr, string sep = "") {
			string result;
			for (string e : arr) {
				result += e + (sep + " ");
			}
			return result;
		}

		bool allTrue(vector<bool> results) {
			int countTrue = count(results.begin(), results.end(), true);
			return countTrue == results.size();
		}

		void displayVector(vector<bool> results) {
			for (bool e : results) {
				if (e == true) { cout << "true" << endl; }
				else { cout << "false" << endl; }
			}
		}

		vector<int> findSubStrings(string s, string sub) {
			vector<int> allOccurences;
			string temp = s;

			while (temp.find(sub) != -1) {
				int idx = temp.find(sub);
				allOccurences.push_back(temp.find(sub));
				temp.erase(idx, sub.size());
			}

			return allOccurences;
		}

		string replaceSubstr(string s, string oldSubStr, string newSubStr) {
			vector<int> allOccurences = findSubStrings(s, oldSubStr);
			string result = s;
			int len = oldSubStr.size();

			for (int index : allOccurences) {
				result.replace(index, len, newSubStr);
			}

			return result;
		}

		string removePunctuation(string s) {
			string result = s;
			vector<string> punct = { "/", ",", "!", "?", ">", "<", "."};

			for (string oldSubStr : punct) {
				result = replaceSubstr(result, oldSubStr, "");
			}

			return result;
		}

		bool followsPattern(string keyMsg, string userMsg) {
			// substitutions
			for (int i = 0; i < substitutions.getKeys().size(); i++) {
				string currKey = substitutions.key(i);
				string currVal = substitutions.value(currKey);

				userMsg = replaceSubstr(userMsg, currKey, currVal);
			}

			//cout << "================" << endl;
			//cout << "Message: " << userMsg << endl;
			//cout << "Key: " << keyMsg << endl;
			//cout << (keyMsg == toLower(userMsg)) << endl;
			//cout << "================" << endl;

			vector<string> userMsgSplit = split(userMsg);

			if (keyMsg == userMsg) {
				//cout << "same" << endl;
				return true;
			}

			vector<string> splitKeyMsg = split(keyMsg);
			vector<bool> results;

			vector<int> allAstericksIdx = findAllOccurences(splitKeyMsg, "*");
			vector<int> allWordIdx = findNonOccurences(splitKeyMsg, "*");

			vector<bool> wordsInMsg;
			for (int idx : allWordIdx) {
				//cout << "curr word: " << splitKeyMsg[idx] << endl;

				//cout << "finding element" << endl;
				//cout << findElementStr(userMsgSplit, splitKeyMsg[idx]) << endl;
				if (findElementStr(userMsgSplit, splitKeyMsg[idx]) != -1) {
					wordsInMsg.push_back(true);
				}
				else {
					wordsInMsg.push_back(false);
				}
			}

			//displayVector(wordsInMsg);

			if (allTrue(wordsInMsg)) {
				string curr;
				string previousKey = splitKeyMsg[0];
				int foundIdx;
				for (int i = 1; i < splitKeyMsg.size(); i++) {
					curr = splitKeyMsg[i];

					//cout << "debugging" << endl;
					//cout << "================" << endl;
					//cout << "current str: " << curr << endl;
					//cout << "previous str: " << previousKey << endl;
					//cout << "================" << endl;

					// "[word] *"
					if ((curr == "*") && (previousKey != "*")) {
						foundIdx = findElementStr(userMsgSplit, previousKey);
						//cout << "foundIdx: " << foundIdx << endl;
						//cout << "[word] *" << endl;

						bool boolExp = foundIdx + 1 <= userMsgSplit.size() - 1;

						if (boolExp) {
							// allows the chatbot to learn
							userInputs.push_back(userMsgSplit[foundIdx + 1]);
							results.push_back(true);
						}
						else {
							results.push_back(false);
						}
					}
					// "* [word]"
					else if ((curr != "*") && (previousKey == "*")) {
						foundIdx = findElementStr(userMsgSplit, curr);
						//cout << "foundIdx: " << foundIdx << endl;
						//cout << "* [word]" << endl;
						results.push_back(!(userMsgSplit[foundIdx - 1].empty()));
					}
					// "[word] [word]"
					else if ((curr != "*") && (previousKey != "*")) {
						string str = previousKey + " " + curr;
						//cout << "[word] [word]" << endl;
						//cout << "str: " << str << endl;
						results.push_back(userMsg.find(str) != -1);
					}

					//cout << "results vector " << endl;
					//displayVector(results);
					//cout << "================" << endl;

					previousKey = curr;
				}
			}
			else {
				return false;
			}

			return allTrue(results);
		}

		string getRandomResponse(string currKey) {
			string response;
			vector<string> val = allResponses.value(currKey);

			if (val.size() == 1) {
				response = val[0];
			}
			else {
				srand(time(NULL));
				int randIdx = rand() % val.size();
				response = val[randIdx];
			}

			return response;
		}

		string grabResponse(string userMsg) {
			vector<string> splitMsg = split(userMsg);
			vector<string> userMsgs = allResponses.getKeys();
			string response = "";

			for (int i = 0; i < userMsgs.size(); i++) {
				string currKey = userMsgs[i];

				if ((splitMsg.size() == 1 && toLower(splitMsg[0]) == currKey)) {
					response = getRandomResponse(currKey);
					//userInputs.clear();

				}
				else if (followsPattern(currKey, userMsg)) {
					//cout << "follows pattern" << endl;
					response = getRandomResponse(currKey);
				}
				else if (!followsPattern(currKey, userMsg)) {
					//cout << "does not follows pattern" << endl;
					continue;
				}

				vector<int> starIdxs = findSubStrings(response, "<star");
				//cout << "number of <star> vars found: " << starIdxs.size() << endl;

				if ((response != "") && (starIdxs.size() == 1)) {
					string sub = "<star1>";
					response = replaceSubstr(response, sub, userInputs[0]);
				}
				else if ((response != "") && (starIdxs.size() > 1)) {
					for (int i = 0; i < starIdxs.size(); i++) {
						//cout << userInputs[i] << endl;
						string sub = "<star" + (i + 1) + '>';
						response = replaceSubstr(response, sub, userInputs[i]);
					}
				}

				// var names
				string curr;
				for (string each : varTags) {
					curr = replaceSubstr(each, "<", "");
					curr = replaceSubstr(curr, ">", "");

					if (findSubStrings(response, each).size() != 0) {
						response = replaceWithVar(response, curr);
					}
				}

				//userInputs.clear();
				return response;
			}

			return "Sorry, I didn't get that. Could you rephrase it?";
		}

		string grabVariable(string varName) {
			if (varName == "username") {
				return username;
			}
			else if (varName == "botname") {
				return botname;
			}
		}

		string replaceWithVar(string botResponse, string varname) {
			string old = "<" + varname + ">";
			return replaceSubstr(botResponse, old, grabVariable(varname));
		}

	public:
		Chatbot(string botName = "Bot", bool addDefaultPairs = true, bool addDefaultSubs = true) {
			//username = nameUser;
			botname = botName;
			
			if (addDefaultPairs) {
				// default pairs
				this->addUserChatPair("hello", { "Hello, user!", "Hi user! Great to chat with you." });
				this->addUserChatPair("exit", { "Goodbye for now!" });
				this->addUserChatPair("hello bot", { "Hello, user!" });
				this->addUserChatPair("who are you", { "I'm a simple chatbot, that doesn't use AI, who is here to chat!", "Just call me Bot. I'm just here to relax and chat with you!" });
				this->addUserChatPair("what is your name", { "I'm a simple chatbot, that doesn't use AI, who is here to chat!", "Just call me Bot. I'm just here to relax and chat with you!" });
				this->addUserChatPair("how are you", { "I'm a chatbot, so I don't necessarily have feelings. But for you, I'm feeling good!", "I don't have feelings, but for you, I feel great! How are you?" });
				this->addUserChatPair("i don't know what to talk about", { "That's okay, let's talk about you! What's your name?" });
				this->addUserChatPair("nice to meet you", { "Nice to meet you too!" });
			}

			if (addDefaultSubs) {
				// default substitutions
				this->addSubstitution("hi", "hello");
				this->addSubstitution("hey", "hello");
				this->addSubstitution("who're", "who are");
				this->addSubstitution("what's", "what is");
				this->addSubstitution("name's", "name is");
				this->addSubstitution("how're", "how are");
				this->addSubstitution("fav", "favourite");
				this->addSubstitution("color", "colour");
				this->addSubstitution(" u", " you");
				this->addSubstitution("you alright", "how are you");
				this->addSubstitution("you okay", "how are you");
				this->addSubstitution("i'm not sure", "i don't know");
				this->addSubstitution("thanks", "thank you");
				this->addSubstitution("chat", "talk");
				this->addSubstitution("got", "have");
			}
		}

		void addSubstitution(string oldStr, string newStr) {
			substitutions.addKeyValue(oldStr, newStr);
		}

		void modifySubstitution(string oldStr, string newStr) {
			substitutions.removeKeyValue(oldStr);
			substitutions.addKeyValue(oldStr, newStr);
		}
		
		void removeSubstitution(string oldStr) {
			substitutions.removeKeyValue(oldStr);
		}

		// example: addUserChatPair("* apples *", {"I love apples they're cool"})
		void addUserChatPair(string msgPattern, vector<string> botMsg) {
			allResponses.addKeyValue(msgPattern, botMsg);
		}

		void removeUserChatPair(string msgPattern) {
			allResponses.removeKeyValue(msgPattern);
		}

		void modifyUserChatPair(string msgPattern, vector<string> newBotMsg) {
			allResponses.removeKeyValue(msgPattern);
			allResponses.addKeyValue(msgPattern, newBotMsg);
		}

		void setStrVariable(string varName, string value) {
			if (varName == "username") {
				username = value;
			} else if (varName == "botname") {
				botname = value;
			}
		}

		void talkWithBot() {
			cout << "Talking with " << botname << ". Type 'exit' to leave chat." << endl;
			cout << "============================================" << endl;
			cout << endl;

			string userMsg;
			while (userMsg != "exit") {
				cout << "----------------------" << endl;
				cout << username << ": ";
				getline(cin >> ws, userMsg);
				cout << "----------------------" << endl;

				// format msg
				userMsg = removePunctuation(toLower(userMsg));

				cout << "Bot: " << grabResponse(userMsg) << endl;
			}
		}
};
