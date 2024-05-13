#pragma once

#include <iostream>
#include <string>
using namespace std;

class activ {
protected:
	string content;
	int number;
public:
	activ(string Content = "", int Number = 0) : content(Content), number(Number) {}

	string getContent() { return content; }
	int getNumber() { return number; }
};
class kronos {
protected:
	//string timeString;
	int month, date, year, hour, min;

public:
	kronos(struct tm* localTime) {

		date = localTime->tm_mday;
		month = localTime->tm_mon + 1; // tm_mon is 0-indexed, so add 1
		year = localTime->tm_year + 1900; // tm_year is years since 1900
		hour = localTime->tm_hour;
		min = localTime->tm_min;
		/*time_t now = time(0);
		char buffer[30] = {};

	timeString = ctime_s(buffer, 30, &now);
	timeString = buffer;*/

	}
	kronos(int Year = 0, int Month = 0, int Date = 0) : year(Year), month(Month), date(Date) {

	}
	int getDate() { return date; }
	int getMonth() { return month; }
	int getYear() { return year; }
	//void displayTime() const {
	//	std::cout << "Current date and time: " << timeString;
	//}
};