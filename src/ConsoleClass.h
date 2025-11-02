#pragma once

#include <iostream>
#include <string>
#include <vector>

// a C++ class for styling text in a console.
class Console {
private:
    std::vector<std::string> colours = { "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white" };
    std::vector<std::string> orderedColours = { "white", "bright red", "red", "yellow", "bright yellow", "bright green", "green", "blue", "bright blue", "cyan", "bright cyan", "bright magenta", "magenta", "black" };

    std::vector<int> findSubStrings(std::string s, std::string sub) {
        std::vector<int> allOccurences;
        std::string temp = s;

        while (temp.find(sub) != -1) {
            int idx = temp.find(sub);
            allOccurences.push_back(temp.find(sub));
            temp.erase(idx, sub.size());
        }

        return allOccurences;
    }

    std::string replaceSubstr(std::string s, std::string oldSubStr, std::string newSubStr) {
        std::vector<int> allOccurences = findSubStrings(s, oldSubStr);
        std::string result = s;
        int len = oldSubStr.size();

        for (int index : allOccurences) {
            result.replace(index, len, newSubStr);
        }

        return result;
    }

    int colour2Num(std::string colour, bool isBackground = false) {
        bool bright = colour.find("bright") != -1;
        int foundIdx = findColour(replaceSubstr(colour, "bright ", ""), colours);
        int result = 0;

        if ((bright) && (foundIdx != -1)) {
            result = foundIdx + 90;
        }
        else if (!(bright) && (foundIdx != -1)) {
            result = foundIdx + 30;
        }

        if (isBackground) {
            result += 10;
        }

        return result;
    }

    int findColour(std::string c, std::vector<std::string> arr) {
        for (int i = 0; i < arr.size(); i++) {
            if (c == arr[i]) {
                return i;
            }
        }
        return -1;
    }

    std::vector<std::string> subVector(std::vector<std::string> arr, int startIdx, int endIdx) {
        std::vector<std::string> result;
        for (int i = startIdx; i < endIdx+1; i++) {
            result.push_back(arr[i]);
        }
        return result;
    }

    int indexOf(std::string colour) {
        for (int i = 0; i < orderedColours.size(); i++) {
            if (orderedColours[i] == colour) {
                return i;
            }
        }
        return -1;
    }

public:
    //printf("\033[3;47;35mTexting\033[0m\t\t");
    //static void italicsText(std::string text, bool addEndLine = true) {
    //    if (addEndLine) {
    //        std::cout << "\033[" << textColour << "m" << text << std::endl;
    //    }
    //    else {
    //        std::cout << "\033[1;" << textColour << "m" << text;
    //    }
    //    std::cout << "\033[0m"; // resets console colour
    //}

    void colourText(std::string colourName, std::string text, bool addEndLine = true) {
        int textColour = this->colour2Num(colourName);

        if (addEndLine) {
            std::cout << "\033[" << textColour << "m" << text << std::endl;
        }
        else {
            std::cout << "\033[" << textColour << "m" << text;
        }
        std::cout << "\033[0m"; // resets console colour
    }

    void colourBGOfTxt(std::string bgColourName, std::string textColourName, std::string text, bool addEndLine = true) {
        int bgColour = this->colour2Num(bgColourName, true);
        int textColour = this->colour2Num(textColourName);

        if (addEndLine) {
            std::cout << "\033[1;" << bgColour << ";" << textColour << "37m" << text << std::endl;
        }
        else {
            std::cout << "\033[1;" << bgColour << ";" << textColour << "37m" << text;
        }

        std::cout << "\033[0m"; // resets console colour
    }

    void textGradient(std::string text, std::string colour1, std::string colour2) {
        int textLen = text.size();
        int colour1Num = this->colour2Num(colour1);
        int colour2Num = this->colour2Num(colour2);

        std::vector<std::string> colours = subVector(orderedColours, indexOf(colour1), indexOf(colour2));
    }

    std::vector<std::string> getOrderedColours() {
        return orderedColours;
    }
};
