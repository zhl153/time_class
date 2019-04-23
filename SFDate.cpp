#include"SFDate.h"
#include"SFDateTime.h"
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
#include<ctime>
#include<iostream>
#include<sstream>
#include <iomanip>
#include<map>
#include<string>
using namespace SoftwareFoundations;

SFDate::SFDate() {
	time_t timer = time(NULL);
	struct tm *info;
	info = gmtime(&timer);
	y = 1900 + info->tm_year;
	m = 1 + info->tm_mon;
	d = info->tm_mday;
};
SFDate::SFDate(const char *aDateTimeString) {
	std::string a(aDateTimeString);
	if (a.find("/") != std::string::npos) {
		m = std::stoi(a.substr(0, 2));
		d = std::stoi(a.substr(a.find_first_of("/")+1, 2));
		y = std::stoi(a.substr(a.find_last_of("/")+1, 4));
	}
	/*if (isdigit(a[0])) {
		char* sep;
		sep = strtok(a, "/");
		m = atoi(sep);
		sep = strtok(NULL, "/");
		d = atoi(sep);
		sep = strtok(NULL, "/");
		y = atoi(sep);
	}*/
	else {
		std::map<std::string,int> monthabb;
		monthabb["Jan"] = 1; monthabb["Feb"] = 2; monthabb["Mar"] =3 ; monthabb["Apr"] =4 ; monthabb["May"] = 5; monthabb["Jun"] = 6;
		monthabb["Jul"] = 7; monthabb["Aug"] = 8; monthabb["Sep"] = 9; monthabb["Oct"] = 10; monthabb["Nov"] =11 ; monthabb["Dec"] = 12;
		std::string tmp(a);
		if (monthabb.find(tmp.substr(0, 3)) != monthabb.end()) {
			m = monthabb[tmp.substr(0, 3)];
		}
		else {
			m = 1;
			std::cout << "invalid input" << std::endl;
		}
		d = std::stoi(a.substr(a.find(" ")+1, 2));
		y = std::stoi(a.substr(a.find(",") + 2, 4));
	}	
}
SFDate::SFDate(std::string& a) {
	if (a.find("/") != std::string::npos) {
		m = std::stoi(a.substr(0, 2));
		d = std::stoi(a.substr(a.find_first_of("/") + 1, 2));
		y = std::stoi(a.substr(a.find_last_of("/") + 1, 4));
	}
	else {
		std::map<std::string, int> monthabb;
		monthabb["Jan"] = 1; monthabb["Feb"] = 2; monthabb["Mar"] = 3; monthabb["Apr"] = 4; monthabb["May"] = 5; monthabb["Jun"] = 6;
		monthabb["Jul"] = 7; monthabb["Aug"] = 8; monthabb["Sep"] = 9; monthabb["Oct"] = 10; monthabb["Nov"] = 11; monthabb["Dec"] = 12;
		std::string tmp(a);
		if (monthabb.find(tmp.substr(0, 3)) != monthabb.end()) {
			m = monthabb[tmp.substr(0, 3)];
		}
		else {
			m = 1;
			std::cout << "invalid input" << std::endl;
		}
		d = std::stoi(a.substr(a.find(" ") + 1, 2));
		y = std::stoi(a.substr(a.find(",") + 2, 4));
	}
}
SFDate::SFDate(int month, int day, int year) {
	m = month;
	d = day;
	y = year;
}
SFDate::SFDate(const SFDate &aCopy) {
	m = aCopy.m;
	y = aCopy.y;
	d = aCopy.d;
}
SFDate::SFDate(const SFDateTime &aCopy) {
	m = aCopy.day.getMonth();
	y = aCopy.day.getYear();
	d = aCopy.day.getDay();
}

SFDate& SFDate:: operator++() {
	this->adjustByDays(1);
	return *this;
}
SFDate SFDate::operator++(int k) {
	SFDate tmp(*this);
	this->adjustByDays(1);
	return tmp;
}
SFDate& SFDate::operator --() {
	this->adjustByDays(-1);
	return *this;
}
SFDate SFDate::operator--(int k) {
	SFDate tmp(*this);
	this->adjustByDays(-1);
	return tmp;
}

SFInterval SFDate::operator-(const SFDate &other) const {
	SFInterval re;
	int md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))md[1] += 1;
	if (*this >= other) {
		int dd = d;
		int mm = m;
		int yy = y;
		if (dd < other.d) {
			dd += md[m - 2];
			mm -= 1;
			if (mm < 1)yy--, mm += 12;
		}
		re.days = dd - other.d;
		if (mm < other.m) {
			mm += 12;
			yy--;
		}
		re.months = mm - other.m;
		re.years = yy - other.y;
	}
	else {
		re = other - *this;
		re.years = -re.years;
		re.months = -re.months;
		re.days = -re.days;
	}
	return re;
}
SFInterval SFDate::operator-(const SFDateTime &other) const {
	SFInterval re;
	int md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))md[1] += 1;
	int dd = d;
	int mm = m;
	int yy = y;
	if (dd < other.day.getDay()) {
		dd += md[m - 2];
		mm -= 1;
		if (mm < 1)yy--, mm += 12;
	}
	re.days = dd - other.day.getDay();
	if (mm < other.day.getMonth()) {
		mm += 12;
		yy--;
	}
	re.months = mm - other.day.getMonth();
	re.years = yy - other.day.getYear();
	return re;
}

SFDate& SFDate::adjustByDays(int n) {
	int nd;
	if (n <= 28 && n >= -28) { nd = n; n = 0; }
	else if (n>28) {
		nd = 28;
		n -= nd;
	}
	else {
		nd = -28;
		n += 28;
	}
	d += nd;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
		if (d > 31) {
			m++;
			d = d - 31;
		}
		if (m > 12) {
			y++;
			m = m - 12;
		}
		if (d < 1) {
			m--;
			if (m == 2) {
				if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0)) d = d + 29;
				else d = d + 28;
			}
			else if (m == 0) {
				y -= 1;
				m += 12;
				d = d + 31;
			}
			else if (m == 7)d += 31;
			else d += 30;
		}
	}
	else if (m == 2) {
		if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0)) {
			if (d > 29) {
				m++;
				d = d - 29;
			}
		}
		else {
			if (d > 28) {
				m++;
				d = d - 28;
			}
		}
		if (d < 1) {
			m--;
			d += 31;
		}
	}
	else {
		if (d > 30) {
			m++;
			d = d - 30;
		}
		if (d < 1) {
			m--;
			d += 31;
		}
	}
	if (n != 0)adjustByDays(n);
	return *this;
}
SFDate& SFDate::adjustByWeeks(int n) {
	int wd = n * 7;
	this->adjustByDays(wd);
	return *this;
}
SFDate& SFDate::adjustByMonths(int n) {
	int nm;
	if (n <= 12 && n >= -12) {
		nm = n; n = 0;
	}
	else if (n > 12) { nm = 12; n -= 12; }
	else { nm = -12; n += 12; }
	int mm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))mm[1] += 1;
	m += nm;
	if (m > 12) {
		y++;
		m -= 12;
	}
	else if (m < 0) {
		y--;
		m += 12;
	}
	if (mm[m - 1] < d)m++, d = 1;
	if (m > 12) {
		y++;
		m -= 12;
	}
	if (n != 0)adjustByMonths(n);
	return *this;
}
SFDate& SFDate::adjustByYears(int n) {
	y += n;
	if ((!((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))) && m == 2 && d > 28)m++, d = 1;
	return *this;
}

SFDate& SFDate::setDay(int aDay) {
	if (aDay <= 0 || aDay > 31) {
		std::cout << "Invalid Input" << std::endl;
		return *this;
	}
	if ((m == 4 || m == 6 || m == 9 || m == 11) && (aDay > 30)) {
		std::cout << "Invalid Input" << std::endl;
		return *this;
	}
	if (m == 2) {
		if (((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))) {
			if (aDay > 29) {
				std::cout << "Invalid Input" << std::endl;
				return *this;
			}
		}
		else {
			if (aDay > 28) {
				std::cout << "Invalid Input" << std::endl;
				return *this;
			}
		}
	}
	d = aDay;
	return *this;
}
SFDate& SFDate::setMonth(int aMonth) {
	if (aMonth > 12 || aMonth < 1) {
		std::cout << "Invalid Input" << std::endl;
		return *this;
	}
	m = aMonth;
	int mm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))mm[1] += 1;
	if (d > mm[m - 1])d = 1, m++;
	if (m > 12)m = 1, y++;
	return *this;
}
SFDate& SFDate::setYear(int aYear) {
	y = aYear;
	return *this;
}

int   SFDate::getDay()const {
	return d;
}
int   SFDate::getMonth()const {
	return m;
}
int   SFDate::getYear()const {
	return y;
}

int   SFDate::getDayOfYear() {
	int mm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))mm[1] += 1;
	int doy = 0;
	for (int i = 0; i < m - 1; i++) {
		doy += mm[i];
	}
	doy += d;
	return doy;
}
int   SFDate::getDayOfweek() {
	int mm = m;
	int yy = y;
	if (mm == 1 || mm == 2) mm += 12, yy--;
	int W = (d + 2 * mm + 3 * (mm + 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400 + 1) % 7;
	return W;
}
int   SFDate::getWeekOfYear() {
	int doy = this->getDayOfYear();
	SFDate start(1, 1, y);
	int i = start.getDayOfweek();
	if (doy - 7 + i <= 0)return 1;
	else return (doy - 7 + i) / 7 + 2;
}
int   SFDate::daysInMonth() {
	int mm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y % 100 != 0 && y % 4 == 0) || (y % 400 == 0))mm[1] += 1;
	return mm[m - 1];
}

SFDate& SFDate::startOfMonth() {
	d = 1;
	return *this;
}
SFDate& SFDate::endOfMonth() {
	d = this->daysInMonth();
	return *this;
}
SFDate& SFDate::startOfYear() {
	d = 1;
	m = 1;
	return *this;
}
SFDate& SFDate::endOfYear() {
	d = 31;
	m = 12;
	return *this;
}

std::string SFDate::toDateString() {
	std::stringstream stream;
	stream << std::setfill('0')<<std::setw(2)<<m << "/" << std::setfill('0') << std::setw(2)<< d << "/" << std::setfill('0') << std::setw(4)<< y;
	return stream.str();
}

bool SFDate::operator>(const SFDate aDay)const {
	if (y > aDay.y)return true;
	else if (y < aDay.y)return false;
	else {
		if (m > aDay.m)return true;
		else if (m < aDay.m)return false;
		else {
			if (d > aDay.d)return true;
			else return false;
		}
	}
}
bool SFDate::operator<(const SFDate aDay)const {
	if (y < aDay.y)return true;
	else if (y > aDay.y)return false;
	else {
		if (m < aDay.m)return true;
		else if (m > aDay.m)return false;
		else {
			if (d < aDay.d)return true;
			else return false;
		}
	}
}
bool SFDate::operator==(const SFDate aDay)const {
	return (!(*this > aDay)) && (!(*this < aDay));
}
bool SFDate::operator>=(const SFDate aDay)const {
	return !(*this < aDay);
}
bool SFDate::operator<=(const SFDate aDay)const {
	return !(*this > aDay);
}
bool SFDate::operator!=(const SFDate aDay)const {
	return !(*this == aDay);
}
