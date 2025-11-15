#pragma once

#include <string>
#include <vector>
#include <ctime>

// a c++ library for all things time related.
class TimePlusPlus {
private:
	std::vector<std::string> months = { "Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec" };
	std::vector<int> numDays = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	time_t timeObj;
	int timeInSeconds; // since Jan 1 1970 00:00
	int startingYear = 1970;

	int numYears2Seconds(int numYears, int leapYearStartIdx = 3) {
		if (numYears == 1) {
			return (86400 * 365);
		}

		int result = 0;
		std::vector<int> daysPerYear;

		int idx = 0;
		for (int i = 4; i < numYears + 1; i++) {
			idx = i + leapYearStartIdx + 1;

			if (idx % 4 == 0) {
				result += (86400 * 366);
				daysPerYear.push_back(366);
			}
			else {
				result += (86400 * 365);
				daysPerYear.push_back(365);
			}

			//displayIntVector(daysPerYear);
			//std::cout << "=================================" << std::endl;
		}

		return result;
	}

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

	// replaces a substring with a new substring.
	std::string replaceSubstr(std::string s, std::string oldSubStr, std::string newSubStr) {
		std::vector<int> allOccurences = findSubStrings(s, oldSubStr);
		std::string result = s;
		int len = oldSubStr.size();

		for (int index : allOccurences) {
			result.replace(index, len, newSubStr);
		}

		return result;
	}

	std::vector<int> getLeapYears(int year1, int year2) {
		std::vector<int> leapYears;
		for (int i = year1; i < year2 + 1; i++) {
			if (i % 4 == 0) {
				leapYears.push_back(i);
			}
		}
		return leapYears;
	}

public:
	int storedYear = 0;
	int storedMonth = 0;
	int storedDate = 0;
	int storedHour = 0;
	int storedMinute = 0;
	int storedSeconds = 0;

	TimePlusPlus(int seconds) {
		time_t t = seconds;
		timeObj = t;
		timeInSeconds = (int)timeObj;
	}

	// stores the current time
	TimePlusPlus() {
		timeObj = time(NULL);
		timeInSeconds = (int)timeObj;
	}

	TimePlusPlus(time_t timeObject) {
		timeObj = timeObject;
		timeInSeconds = (int)timeObj;
	}

	/*
Parameters:
- (int) year - 
- (int) month -
- (int) day -
- (int) hour - A specific hour in the 24-hour format
- (int) minute -
- (int) seconds - 
	*/
	time_t makeDate(int year, int month, int day, int hour = 0, int minute = 0, int seconds = 0) {
		struct tm tm = { 0 };

		tm.tm_hour = hour;
		tm.tm_min = minute;
		tm.tm_sec = seconds;
		tm.tm_year = year - 1900;
		tm.tm_mon = month - 1;
		tm.tm_mday = day;

		tm.tm_isdst = -1;
		return mktime(&tm);
	}

	TimePlusPlus(int year, int month, int day, int hour = 0, int minute = 0, int seconds = 0) {
		storedYear = year;
		storedMonth = month;
		storedDate = day;
		storedHour = hour;
		storedMinute = minute;
		storedSeconds = seconds;
		
		timeObj = makeDate(year, month, day, hour, minute, seconds);
		timeInSeconds = (int)timeObj;
	}

	int timetObjToSeconds() {
		return timeInSeconds;
	}

	time_t secondsToTimetObj() {
		return timeObj;
	}

	time_t secondsToTimetObj_defineSeconds(int seconds) {
		time_t myT = seconds;
		return myT;
	}

	std::string formatDate() {
		const int strSize = 26;

		char chars[strSize];
		asctime_s(chars, strSize, gmtime(&timeObj));

		std::string formatted;
		for (int i = 0; i < strSize; i++) {
			formatted += chars[i];
		}

		return formatted;
	}

	int year2Seconds(int year) {
		std::vector<int> fourYears = { year, year + 1, year + 2, year + 3 };

		// checks for a leap year
		for (int i = 0; i < fourYears.size(); i++) {
			if (fourYears[i] % 4 == 0) {
				return numYears2Seconds(year - startingYear, i);
			}
		}
	}

	float secondsToYear(int seconds) {
		int temp = seconds;
		int numYears = startingYear;

		while (temp > 0) {
			if (temp % 31536000 == 0) {
				numYears++;
			}

			temp -= 86400;
			//std::cout << temp << std::endl;
		}

		return numYears;
	}

	bool operator>(TimePlusPlus dateObj) {
		return (this->timetObjToSeconds() > dateObj.timetObjToSeconds());
	}

	int calculateDurationInSeconds(TimePlusPlus dateObj) {
		int calculatedSeconds;
		TimePlusPlus &currTimeObj = *this;

		if (currTimeObj > dateObj) {
			calculatedSeconds = (currTimeObj.timetObjToSeconds() - dateObj.timetObjToSeconds());
		}
		else {
			calculatedSeconds = (dateObj.timetObjToSeconds() - currTimeObj.timetObjToSeconds());
		}

		return calculatedSeconds;
	}
};
