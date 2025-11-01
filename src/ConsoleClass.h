#pragma once

#include <iostream>
#include <string>

// a C++ class for styling text in a console.
class Console {
public:
    int colour2Num(std::string colour) {
        if (colour == "red") {
            return 31;
        }
        else if (colour == "green") {
            return 32;
        }
        else if (colour == "yellow") {
            return 33;
        }
        else if (colour == "blue") {
            return 34;
        }
    }

    static void colourText(int textColour, std::string text, bool addEndLine = true) {
        if (addEndLine) {
            std::cout << "\033[" << textColour << "m" << text << std::endl;
        }
        else {
            std::cout << "\033[" << textColour << "m" << text;
        }
        std::cout << "\033[0m"; // resets console colour
    }
};
