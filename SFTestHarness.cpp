//
//  SFTestHarness.cpp
//  ECE180-Assignment3
//
//  Created by rick gessner on 2/12/18.
//
//#define _CRT_SECURE_NO_WARNINGS
#include "SFTestHarness.hpp"
#include"SFDate.h"
#include"SFTime.h"
#include"SFDateTime.h"
#include<string>
#include<iostream>
using SoftwareFoundations::SFTestHarness;

int SFTestHarness::runDateTests() {
	std::string aDate1 = "02/15/2018";
	std::string aDate2 = "02/17/2018";
	std::string re1(dateDifferenceTest(aDate1, aDate2));
	std::string r1("0 years, 0 months, 2 days, 0 hours, 0 minutes and 0 seconds");
//	std::cout << re1 << '\n' << r1 << '\n';
	if (r1.compare(re1))std::cout << "dateDifferenceTest" << std::endl;

	aDate1 = "02/15/2018";
	std::string re2 = adjustDateByWeeksTest(aDate1, 1);
	std::string r2("02/22/2018"); //std::cout << re2 << '\n' << r2 << '\n';
	if (r2.compare(re2))std::cout << "adjustDateByWeeksTest" << std::endl;

	aDate1 = "03/15/2018";
	std::string re3 = setMonthDateTest(aDate1, 5);
	std::string r3("05/15/2018"); //std::cout << re3 << '\n' << r3 << '\n';
	if (r3.compare(re3))std::cout << "setMonthDateTest" << std::endl;

	aDate1 = "02/15/2018";
	int r4=getDayOfWeekDateTest(aDate1)-4;
	if (r4)std::cout << "getDayOfWeekDateTest"<<std::endl;

	aDate1 = "03/15/2018";
	std::string re5=endOfMonthDateTest(aDate1);
	std::string r5("03/31/2018");// std::cout << re5 << '\n' << r5 << '\n';
	if (r5.compare(re5))std::cout << "endOfMonthDateTest" << std::endl;

  return r1.compare(re1)+ r2.compare(re2)+ r3.compare(re3)+r4+ r5.compare(re5);
}

int SFTestHarness::runTimeTests() {

	std::string aTime1 = "09:05:15";
	std::string aTime2 = "09:05:22";
	std::string re1=timeDifferenceTest(aTime1, aTime2);
	std::string r1("0 years, 0 months, 0 days, 0 hours, 0 minutes and 7 seconds");
	//std::cout << re1 << '\n';
	if (r1.compare(re1))std::cout << "timeDifferenceTest" << std::endl;

	aTime1 = "09:15:15";
	std::string re2=adjustTimeByMinutesTest(aTime1, 5);
	std::string r2("09:20:15"); //std::cout << re2 << '\n' << r2 << '\n';
	if (r2.compare(re2))std::cout << "adjustTimeByMinutesTest" << std::endl;

	aTime1 = "09:25:15";
	int r3 = getMinutesTimeTest(aTime1) - 25;
	if (r3)std::cout << "getMinutesTimeTest" << std::endl; 
	SFTime now;
	//std::cout << now.toTimeString() << '\n';
  return r1.compare(re1)+r2.compare(re2)+r3;
}

int SFTestHarness::runDateTimeTests() {

	std::string aDateTime1 = "02/15/2018 09:35:15";
	std::string  aTimeZone1 = "PST";
	std::string   aDateTime2 = "02/15/2018 11:35:15";
	std::string   aTimeZone2 = "EST";
	std::string re1 = dataTimeDifferenceTest(aDateTime1, aTimeZone1, aDateTime2, aTimeZone2); 
	std::string r1("0 years, 0 months, 0 days, 1 hours, 0 minutes and 0 seconds");
	if (r1.compare(re1))std::cout << "dataTimeDifferenceTest" << std::endl;
	
	aDateTime1 = "02/15/2018 09:45:15";
	std::string re2 = dataTimeToStringTest(aDateTime1, "PST");
	std::string r2("Feb 15, 2018 09:45:15 PST");
	if (r2.compare(re2))std::cout << "dataTimeToStringTest" << std::endl;


	bool a=greaterThanDateTimeTest("02/15/2018 09:05:15", "PST", "02/15/2018 11:05:15", "EST");
	if (!a)std::cout << "greaterThanDateTimeTest" << std::endl;

  return r1.compare(re1)+r2.compare(re2)+(!a);
}

int SFTestHarness::runIntervalTests() {
	SFDateTime a1("02/12/2018 09:05:15");
	SFDate d1("Febuary 10, 2018");
	int er=0;
	if((a1 - d1).days!=-2){er++;std::cout << "IntervalTests" << std::endl;}
	SFTime t1("08:55:15");
	if((a1-t1).minutes!=-10){er++;std::cout << "IntervalTests" << std::endl;}
  return er;
}

int SFTestHarness::runTimezoneTests() {
	std::string aDateTime1 = "02/15/2018 09:55:15";
	std::string re3 = timezoneConversionDateTimeTest(aDateTime1, "PST");
	std::string r3("Feb 15, 2018 01:55:15 PST");
	if (r3.compare(re3))std::cout << " timezoneConversionDateTimeTest" << std::endl;
  return int(r3.compare(re3));
}

/*
 * Return string representation of interval between two dates
 * Ex. aDate1 = "02/15/2018"
 *     aDate2 = "02/17/2018"
 * Returns : "0 years, 0 months, 2 days, 0 hours, 0 minutes and 0 seconds"
 */
std::string SFTestHarness::dateDifferenceTest(std::string aDate1, std::string aDate2) {
	SFDate date1(aDate1);
	SFDate date2(aDate2);
//	std::cout << (date2 - date1) << std::endl;
  return (date2 - date1).operator const char *();
}

/*
 * Return string representation of date with weeks adjusted
 * Ex. aDate = "02/15/2018"
 *     aWeeks = 1
 * Returns : "02/22/2018"
 */
std::string SFTestHarness::adjustDateByWeeksTest(std::string aDate, int aWeeks) {
	SFDate date(aDate.c_str());	
  return date.adjustByWeeks(aWeeks).toDateString();
}

/*
 * Return string representation of date with month changed
 * Ex. aDate = "02/15/2018"
 *     aMonth = 5
 * Returns : "05/15/2018"
 */
std::string SFTestHarness::setMonthDateTest(std::string aDate, int aMonth) {
	SFDate date(aDate.c_str());
  return date.setMonth(aMonth).toDateString();
}

/*
 * Return integer representation of the day of the week for the given date
 * Ex. aDate = "02/15/2018"
 * Returns : 4
 */
int SFTestHarness::getDayOfWeekDateTest(std::string aDate) {
	SFDate date(aDate.c_str());
  return date.getDayOfweek();
}

/*
 * Return string representation of date at the end of month of the given date
 * Ex. aDate = "03/15/2018"
 * Returns : "03/31/2018"
 */
std::string SFTestHarness::endOfMonthDateTest(std::string aDate) {
	SFDate date(aDate.c_str());
  return date.endOfMonth().toDateString();
}

/*
 * Return string representation of interval between two times
 * Ex. aTime1 = "09:05:15"
 *     aTime2 = "09:05:22"
 * Returns : "0 years, 0 months, 0 days, 0 hours, 0 minutes and 7 seconds"
 */
std::string SFTestHarness::timeDifferenceTest(std::string aTime1, std::string aTime2) {
	SFTime time1(aTime1);
	SFTime time2(aTime2);
//	std::cout << (time2 - time1).operator const char *() << std::endl;
  return (time2-time1).operator const char *();
}

/*
 * Return string representation of interval between two times
 * Ex. aTime1 = "09:05:15"
 *     aMinutes = 5
 * Returns : "09:10:15"
 */
std::string SFTestHarness::adjustTimeByMinutesTest(std::string aTime1, int aMinutes) {
	SFTime time(aTime1.c_str());
  return time.adjustByMinutes(aMinutes).toTimeString();
}

/*
 * Return minutes from the given time
 * Ex. aTime = "09:05:15"
 * Returns : 5
 */
int SFTestHarness::getMinutesTimeTest(std::string aTime) {
	SFTime time(aTime.c_str());
  return time.getMinutes();
}

/*
 * Return string representation of interval between two times
 * Ex. aDateTime1 = "02/15/2018 09:05:15"
 *     aTimeZone1 = "PST"
 *     aDateTime2 = "02/15/2018 11:05:15"
 *     aTimeZone2 = "EST"
 * Returns : "0 years, 0 months, 0 days, 1 hours, 0 minutes and 0 seconds"
 */
std::string SFTestHarness::dataTimeDifferenceTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2) {//std::cout << "HERE"<<'\n';
//SFTimezone tz1(aTimezone1);
//SFTimezone tz2(aTimezone2.c_str());
	SFDateTime dt1(aDateTime1,aTimezone1); 
	SFDateTime dt2(aDateTime2,aTimezone2);
//	std::cout << dt1.toDateTimeString() << '\n' << dt2.toDateTimeString() << '\n';
	return (const char*)(dt2-dt1);
}

/*
 * Return string representation of given date-time
 * Ex. aDateTime = "02/15/2018 09:05:15"
 *     aTimeZone = "PST"
 * Returns : "Feb 15, 2018 09:05:15 PST"
 */
std::string SFTestHarness::dataTimeToStringTest(std::string aDateTime, std::string timezone) {
	SFTimezone tz1(timezone.c_str());
	SFDateTime dt(aDateTime.c_str(), &tz1);

  return dt.toDateTimeString();
}

/*
 * Return string representation of given GMT date-time converted to given timezone
 * Ex. aDateTime = "02/15/2018 09:05:15"
 *     aTimeZone = "PST"
 * Returns : "Feb 15, 2018 01:05:15 PST"
 */
std::string SFTestHarness::timezoneConversionDateTimeTest(std::string aDateTime, std::string timezone) {
	SFTimezone tz1("GMT");
	SFDateTime dt(aDateTime.c_str(), &tz1);
	SFTimezone tz(timezone.c_str());
	return dt.setTimezone(tz).toDateTimeString();
}

/*
 * Return true if aDateTime1 is stricty greater than aDateTime2
 * Ex. aDateTime1 = "02/15/2018 09:05:15"
 *     aTimeZone1 = "PST"
 *     aDateTime2 = "02/15/2018 11:05:15"
 *     aTimeZone2 = "EST"
 * Returns : true
 */
bool SFTestHarness::greaterThanDateTimeTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2) {
	SFTimezone tz1(aTimezone1.c_str());
	SFTimezone tz2(aTimezone2.c_str());	
	SFDateTime dt1(aDateTime1.c_str(), &tz1);
	SFDateTime dt2(aDateTime2.c_str(), &tz2);
	return dt1>dt2;
}

int SFTestHarness::runAllTests() {
  int theResult = runDateTests();
 theResult+=runTimeTests();
 theResult+=runDateTimeTests();
  theResult+=runIntervalTests();
  theResult+=runTimezoneTests();
  return theResult;
}
