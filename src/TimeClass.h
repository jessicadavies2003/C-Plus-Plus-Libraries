#pragma once

#include <string>
#include <vector>
#include <ctime>

// a c++ library for all things time related.
class TimePlusPlus {
private:
	time_t timeObj;
	int timeInSeconds; // since Jan 1 1970 00:00

	int startingYear = 1970;

	int storedYear;
	int storedMonth;
	int storedDate;
	int storedHour;
	int storedMinute;
	int storedSeconds;

	void displayIntVector(std::vector<int> arr) {
		cout << "{ ";
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << ", ";
		}
		cout << "}" << endl;
	}

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

public:
	// stores the current time
	TimePlusPlus() {
		timeObj = time(NULL);
		timeInSeconds = (int)timeObj;
	}

	TimePlusPlus(time_t timeObject) {
		timeObj = timeObject;
		timeInSeconds = (int)timeObj;
	}

	time_t dateToTimeObj(int year, int month, int day, int hour = 0, int minute = 0, int seconds = 0) {

	}

	TimePlusPlus(int year, int month, int day, int hour = 0, int minute = 0, int seconds = 0) {
		storedYear = year;
		storedMonth = month;
		storedDate = day;
		storedHour = hour;
		storedMinute = minute;
		storedSeconds = seconds;
		
		timeObj = dateToTimeObj(year, month, day, hour, minute, seconds);
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
};
