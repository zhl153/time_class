#include"SFTime.h"
#include"SFDateTime.h"
#include<ctime>
#include<sstream>
#include<iostream>
#include <iomanip>
#include<cstring>
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
using namespace SoftwareFoundations;

SFTime::SFTime() {
	newday = 0;
	time_t timer = time(NULL);
	struct tm *info;
	info = gmtime(&timer);
	h = info->tm_hour;
	mi = info->tm_min;
	s = info->tm_sec;
}
SFTime::SFTime(const char *aTimeString) {
	std::string atimestring(aTimeString);
	if (!isdigit(atimestring[0])) {
		std::cout << "invalid input " << aTimeString << std::endl;
		h = s = mi = 0;
	}
	else {
		h = std::stoi(atimestring.substr(0, 2));
		mi = std::stoi(atimestring.substr(atimestring.find_first_of(":") + 1, 2));
		s = std::stoi(atimestring.substr(atimestring.find_last_of(":") + 1, 2));
	}
	newday = 0;
}
SFTime::SFTime(int anHour, int aMinutes, int aSeconds) :h(anHour), mi(aMinutes), s(aSeconds), newday(0) {};
SFTime::SFTime(const SFTime &aCopy) : h(aCopy.h), mi(aCopy.mi), s(aCopy.s), newday(0) {
}
SFTime::SFTime(const SFDateTime &aCopy) : h(aCopy.time.getHour()), mi(aCopy.time.getMinutes()), s(aCopy.time.getSeconds()), newday(0) {
}
SFTime::SFTime(std::string& aTimeString) {
	if (!isdigit(aTimeString[0])) {
		std::cout << "invalid input " << aTimeString << std::endl;
		h = s = mi = 0;
	}
	else {
		h = std::stoi(aTimeString.substr(0, 2));
		mi = std::stoi(aTimeString.substr(aTimeString.find_first_of(":") + 1, 2));
		s = std::stoi(aTimeString.substr(aTimeString.find_last_of(":") + 1, 2));
	}
	newday=0;
}

SFTime& SFTime::adjustByMinutes(int n) {
	int nm;
	if (n <= 60 && n >= -60) {
		nm = n; n = 0;
	}
	else if (n > 60) { nm = 60; n -= 60; }
	else { nm = -60; n += 60; }
	mi += nm;
	if (mi >= 60) {
		h++;
		mi -= 60;
		if (h > 23) h -= 24, newday--;
	}
	if (mi < 0) {
		h--;
		mi += 60;
		if (h < 0)h += 24, newday++;
	}
	if (n != 0)this->adjustByMinutes(n);
	return *this;
}
SFTime& SFTime::adjustByHours(int n) {
	int nh = n % 24;
	h += nh;
	if (h >= 24)h -= 24, newday++;
	if (h < 0)h += 24, newday--;
	return *this;
}

int   SFTime::getHour() const {
	return h;
}
int   SFTime::getMinutes()const {
	return mi;
}
int   SFTime::getSeconds()const {
	return s;
}

SFTime& SFTime::startOfDay() {
	h = mi = s = 0;
	return *this;
}
SFTime& SFTime::endOfDay() {
	h = 23;
	mi = s = 59;
	return *this;
}

std::string SFTime::toTimeString() {
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(2) << h << ":" << std::setfill('0') << std::setw(2) << mi << ":" << std::setfill('0') << std::setw(2) << s;
	return stream.str();
}

bool SFTime::operator>(const SFTime aTime)const {
	if (h > aTime.h)return true;
	else if (h < aTime.h)return false;
	else {
		if (mi > aTime.mi)return true;
		else if (mi < aTime.mi)return false;
		else {
			if (s > aTime.s)return true;
			else return false;
		}
	}
}
bool SFTime::operator<(const SFTime aTime)const {
	if (h < aTime.h)return true;
	else if (h > aTime.h)return false;
	else {
		if (mi < aTime.mi)return true;
		else if (mi > aTime.mi)return false;
		else {
			if (s < aTime.s)return true;
			else return false;
		}
	}
}
bool SFTime::operator==(const SFTime aTime)const {
	return !((*this > aTime) || (*this < aTime));
}
bool SFTime::operator>=(const SFTime aTime) const{
	return !(*this < aTime);
}
bool SFTime::operator<=(const SFTime aTime)const {
	return !(*this > aTime);
}
bool SFTime::operator!=(const SFTime aTime) const{
	return !(*this == aTime);
}

SFInterval SFTime::operator-(const SFTime &other) const {
	SFInterval re;
	if (*this >= other) {
		int ss = s;
		int mimi = mi;
		int hh = h;
		if (ss < other.s)ss += 60, mimi--;
		re.seconds = ss - other.s;
		if (mimi < other.mi)mimi += 60, hh--;
		re.minutes = mimi - other.mi;
		re.hours = hh - other.h;
	}
	else {
		re = other - *this;
		re.hours = -re.hours;
		re.minutes = -re.minutes;
		re.seconds = -re.seconds;
	}
	return re;
}
SFInterval SFTime::operator-(const SFDateTime &other) const {
	SFInterval re;
	int ss = s;
	int mimi = mi;
	int hh = h;
	if (ss < other.time.getSeconds())ss += 60, mimi--;
	re.seconds = ss - other.time.getSeconds();
	if (mimi < other.time.getMinutes())mimi += 60, hh--;
	re.minutes = mimi - other.time.getMinutes();
	re.hours = hh - other.time.getHour();
	return re;
}
