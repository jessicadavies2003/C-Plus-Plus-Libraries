#pragma once

#include <string>
#include <vector>
#include <ctime>

/*
This C++ time library makes working with `time_t` much easier, as well
as being able to format the date into a readable format!
*/
class TimePlusPlus {
private:
	time_t timeObj;
	int timeInSeconds; // since Jan 1 1970 00:00
	int startingYear = 1970;

public:
	int storedYear = 0;
	int storedMonth = 0;
	int storedDate = 0;
	int storedHour = 0;
	int storedMinute = 0;
	int storedSeconds = 0;

	TimePlusPlus(int seconds = 0) {
		if (seconds == 0) {
			timeObj = time(NULL);
		}
		else {
			time_t t = seconds;
			timeObj = t;
		}

		timeInSeconds = (int)timeObj;
	}

	TimePlusPlus(time_t timeObject) {
		timeObj = timeObject;
		timeInSeconds = (int)timeObj;
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

	tm timetToTmStruct(time_t obj) {
		struct tm date;
		gmtime_s(&date, &timeObj); // stores time info about `timeObj` into `date`.
		return date;
	}

	int toSeconds() {
		return timeInSeconds;
	}

	time_t toTimeTObj() {
		return timeObj;
	}

	time_t toTimeTObj_defineSeconds(int seconds) {
		time_t myT = seconds;
		return myT;
	}

	std::string formatDate() {
		const int strSize = 25;
		struct tm date;
		char chars[strSize];
		gmtime_s(&date, &timeObj); // stores time info about `timeObj` into `date`.
		strftime(chars, strSize, "%a %b %d %H:%M:%S %Y", &date);

		std::string formatted;
		for (int i = 0; i < strSize; i++) {
			formatted += chars[i];
		}

		return formatted;
	}

	bool operator>(TimePlusPlus dateObj) {
		return (this->toSeconds() > dateObj.toSeconds());
	}

	int calculateDurationInSeconds(TimePlusPlus dateObj) {
		int calculatedSeconds;
		TimePlusPlus& currTimeObj = *this;

		if (currTimeObj > dateObj) {
			calculatedSeconds = (currTimeObj.toSeconds() - dateObj.toSeconds());
		}
		else {
			calculatedSeconds = (dateObj.toSeconds() - currTimeObj.toSeconds());
		}

		return calculatedSeconds;
	}
};
