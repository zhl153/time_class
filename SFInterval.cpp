#include"SFInterval.h"
#include<sstream>
#include<cstring>
//#pragma warning(disable:4996)
using namespace SoftwareFoundations;

SFInterval::SFInterval() :years(0), months(0), days(0), hours(0), minutes(0), seconds(0) {};
SFInterval::SFInterval(int year, int month, int day, int hour, int minute, int second) :years(year), months(month), days(day), hours(hour), minutes(minute), seconds(second) {};
SFInterval::operator const char*()const {
	std::stringstream stream;
	stream << years << " years, " << months << " months, " << days << " days, " << hours << " hours, " << minutes << " minutes and " << seconds << " seconds";
	std::string a=stream.str();
	static char* aa = new char[a.length() + 2];
	strcpy(aa,a.c_str());
//	std::cout << aa << std::endl;
	return aa;
}

SFInterval SFInterval::operator+(const SFInterval& other) {
	SFInterval re(years + other.years, months + other.months, days + other.days, hours + other.hours, minutes + other.minutes, seconds + other.seconds);
	int md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (re.seconds >= 60)re.minutes++, re.seconds -= 60;
	else if (re.seconds < 0)re.minutes--, re.seconds += 60;
	if (re.minutes >= 60)re.hours++, re.minutes -= 60;
	else if (re.minutes < 0)re.hours--, re.minutes += 60;
	if (re.hours >= 24||(re.hours>0&&re.days<0))re.days++, re.hours -= 24;
	else if ((re.hours < 0&&re.days>0)||re.hours<=-24)re.days--, re.hours += 24;
	if (re.months >= 12)re.years++, re.months -= 12;
	else if (re.months <=-12)re.years--, re.months += 12;
	if (re.days > md[re.months])re.days -= md[re.months], re.months++;
	else if (re.days < -md[re.months])re.days += md[re.months], re.months--;
	if (re.months >= 12)re.years++, re.months -= 12;
	else if (re.months <=-12)re.years--, re.months += 12;
	return re;
}
