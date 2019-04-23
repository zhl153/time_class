#include"SFDateTime.h"
#include<sstream>
#include<map>
#include<cstring>
#include<string>
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
using namespace SoftwareFoundations;

SFDateTime::SFDateTime(SFTimezone *aTimezone) :day(), time(), timezone(*aTimezone) {
}
SFDateTime::SFDateTime(const SFDateTime &aCopy) : day(SFDate(aCopy)), time(SFTime(aCopy)), timezone((SFTimezone)aCopy) {
}
SFDateTime::SFDateTime(int aMonth, int aDay, int aYear, int anHour, int aMinutes, int aSeconds, SFTimezone *aTimezone) : day(aMonth, aDay, aYear), time(anHour, aMinutes, aSeconds), timezone(*aTimezone) {
}
SFDateTime::SFDateTime(const char* aString, SFTimezone *aTimezone ) {
	std::string tmp(aString);
	std::string tmp1 = tmp.substr(0, tmp.find_last_of(" "));
	std::string tmp2 = tmp.substr(tmp.find_last_of(" ")+1);
	day=(tmp1);
	time = tmp2;
/*	char* aa = new char[strlen(aString) + 1]; 
	strcpy(aa, aString);
	char* sep; char*sap;
	sep = strtok(aa, " ");sap=strtok(NULL, " ");
	day = sep;	
	time = sap;//MARK*/
	if (aTimezone) {
		timezone = *aTimezone;
	}
}
SFDateTime::SFDateTime(const SFDate &aDate, const SFTime &aTime, SFTimezone *aTimezone ) : day(aDate), time(aTime), timezone(*aTimezone) {
}
SFDateTime::SFDateTime(std::string& aDateTime, std::string& aTimezone) :timezone(aTimezone.c_str()){
	std::string tmp1 = aDateTime.substr(0, aDateTime.find_last_of(" "));
	std::string tmp2 = aDateTime.substr(aDateTime.find_last_of(" ") + 1);
	day = tmp1;
	time = tmp2;
}


SFInterval SFDateTime::operator-(const SFDateTime &other) const {
	SFDateTime another(other);	//std::cout << "another: "<<another.toDateTimeString()<<'\n';
	another.setTimezone(const_cast<SFTimezone&>(timezone));//MARK
	SFInterval re1, re2, re;
	//std::cout << "another: "<<another.toDateTimeString()<<'\n';
	re1 = another.time- time;
	re2 =  another.day-day ;
//	std::cout <<  re2.operator const char *() << '\n';
	re = re1 + re2;
	return re;
}
SFInterval SFDateTime::operator-(const SFDate &other)const {
	SFInterval re;
	re = other-day ;
	return re;
}
SFInterval SFDateTime::operator-(const SFTime &other)const {
	SFInterval re;
	re = other-time;
	return re;
}


SFTimezone&  SFDateTime::getTimezone() {
	return timezone;
}

SFDateTime&  SFDateTime::setTimezone(SFTimezone &aTimezone) {
	char* currenttz = nullptr;
	if (timezone) {
		currenttz = new char[4];
		strcpy(currenttz, timezone);
//		delete[] timezone.tz;
//		timezone.tz=nullptr;
	}
	if (aTimezone.tz) {
		timezone.tz = new char[4];
		strcpy(timezone.tz, aTimezone.tz);
	}
	if ((currenttz) && (timezone) && (strcmp(currenttz, timezone))) {
		std::map<std::string, int> zone;
		zone["GMT"] = 0; zone["EST"] = -5; zone["CST"] = -6; zone["PST"] = -8;
		//		int newtime = zone[timezone] - zone[currenttz] + time.getHour();
	//	std::cout << timezone.tz << currenttz << zone[timezone.tz]<<zone["EST"]<<std::endl;
		

		time.adjustByHours(zone[timezone.tz] - zone[currenttz]);
		day.adjustByDays(time.newday);
	}
	//change timezone
//	delete[] currenttz; currenttz = nullptr;
	return *this;
}

SFDateTime::operator const char*() {
	std::stringstream stream;
	stream << day.getMonth() << " " << day.getDay() << ", " << day.getYear() << " " << time.toTimeString() << " " << timezone;
	return stream.str().c_str();
}
SFDateTime::operator SFDate() {
	return SFDate(day.getMonth(), day.getDay(), day.getYear());
}
SFDateTime::operator SFTime() {
	return SFTime(time.getHour(), time.getMinutes(), time.getSeconds());
}
SFDateTime::operator SFTimezone() const{
	return timezone;
}


bool SFDateTime::operator>(const SFDateTime aDay) {
	SFDateTime another(aDay);
	another.setTimezone((timezone));//MARK //adjust timezone
	if (day > another.day)return true;
	else if (day < another.day)return false;
	else {
		if (time > another.time)return true;
		else return false;
	}
}
bool SFDateTime::operator<(const SFDateTime aDay) {
	SFDateTime another(aDay);
	another.setTimezone((timezone));//adjust timezone
	if (day < another.day)return true;
	else if (day > another.day)return false;
	else {
		if (time < another.time)return true;
		else return false;
	}
}
bool SFDateTime::operator==(const SFDateTime aDay) {
	return !((*this > aDay) || (*this < aDay));
}
bool SFDateTime::operator>=(const SFDateTime aDay) {
	return !(*this < aDay);
}
bool SFDateTime::operator<=(const SFDateTime aDay) {
	return !(*this > aDay);
}
bool SFDateTime::operator!=(const SFDateTime aDay) {
	return !(*this == aDay);
}

SFDateTime& SFDateTime::adjustByDays(int n) {
	day.adjustByDays(n);
	return *this;
}
SFDateTime& SFDateTime::adjustByWeeks(int n) {
	day.adjustByWeeks(n);
	return *this;
}
SFDateTime& SFDateTime::adjustByMonths(int n) {
	day.adjustByMonths(n);
	return *this;
}
SFDateTime& SFDateTime::adjustByYears(int n) {
	day.adjustByYears(n);
	return *this;
}
SFDateTime& SFDateTime::adjustByMinutes(int n) {
	time.adjustByMinutes(n);
	day.adjustByDays(time.newday);
	return *this;
}
SFDateTime& SFDateTime::adjustByHours(int n) {
	time.adjustByHours(n);
	day.adjustByDays(time.newday);
	return *this;
}
SFDateTime& SFDateTime::operator++() {
	SFDateTime tmp(*this);
	day++;
	return tmp;
}
SFDateTime SFDateTime::operator++(int k) {
	day++;
	return *this;
}
SFDateTime& SFDateTime::operator --() {
	SFDateTime tmp(*this);
	day--;
	return tmp;
}
SFDateTime SFDateTime::operator--(int k) {
	day--;
	return *this;
}
SFDateTime& SFDateTime::setDay(int aDay) {
	day.setDay(aDay);
	return *this;
}
SFDateTime& SFDateTime::setMonth(int aMonth) {
	day.setMonth(aMonth);
	return *this;
}
SFDateTime& SFDateTime::setYear(int aYear) {
	day.setYear(aYear);
	return*this;
}
int   SFDateTime::getDay()const {
	return day.getDay();
}
int   SFDateTime::getMonth()const {
	return day.getMonth();
}
int   SFDateTime::getYear()const {
	return day.getYear();
}
int   SFDateTime::getHour()const {
	return time.getHour();
}
int   SFDateTime::getMinutes()const {
	return time.getMinutes();
}
int   SFDateTime::getSeconds()const {
	return time.getSeconds();
}
int   SFDateTime::getDayOfYear() {
	return day.getDayOfYear();
}
int   SFDateTime::getDayOfweek() {
	return day.getDayOfweek();
}
int   SFDateTime::getWeekOfYear() {
	return day.getWeekOfYear();
}
int   SFDateTime::daysInMonth() {
	return day.daysInMonth();
}
SFDateTime& SFDateTime::startOfMonth() {
	day.startOfMonth();
	return *this;
}
SFDateTime& SFDateTime::endOfMonth() {
	 day.endOfMonth();
	return *this;
}
SFDateTime& SFDateTime::startOfYear() {
	day.startOfYear();
	return *this;
}
SFDateTime& SFDateTime::endOfYear() {
	day.endOfYear();
	return *this;
}
SFDateTime& SFDateTime::startOfDay() {
	time.startOfDay();
	return *this;
}
SFDateTime& SFDateTime::endOfDay() {
	time.endOfDay();
	return *this;
}

std::string SFDateTime::toDateString() {
	return day.toDateString();
}
std::string SFDateTime::toTimeString() {
	return time.toTimeString();
}

std::string SFDateTime::toDateTimeString() {
	std::map<int, std::string> monthabb;
	monthabb[1] = "Jan"; monthabb[2] = "Feb"; monthabb[3] = "Mar"; monthabb[4] = "Apr"; monthabb[5] = "May"; monthabb[6] = "June";
	monthabb[7] = "July"; monthabb[8] = "Aug"; monthabb[9] = "Sep"; monthabb[10] = "Oct"; monthabb[11] = "Nov"; monthabb[12] = "Dec";
	std::stringstream stream;
	stream << monthabb[day.getMonth()] << " " << day.getDay() << ", " << day.getYear() << " " << time.toTimeString() << " " << timezone;
	return stream.str();
}
