#pragma once
#include"SFDate.h"
#include"SFTime.h"
#include"SFTimezone.h"
namespace SoftwareFoundations {
	class SFDateTime {
	public:
		SFDate day;
		SFTime time;
		SFTimezone timezone;
		SFDateTime(SFTimezone *aTimezone = nullptr); //init a new datetime based on GMT, unless a valid timezone is provided		
		SFDateTime(const SFDateTime &aCopy); //copy construct
		SFDateTime(int aMonth, int aDay, int aYear, int anHour = 0, int aMinutes = 0, int aSeconds = 0, SFTimezone *aTimezone = nullptr);
		SFDateTime(const char* aString, SFTimezone *aTimezone = nullptr); //parse the given string of the form "MM/DD/YYYY HH:MM:SS"
		SFDateTime(const SFDate &aDate, const SFTime &aTime, SFTimezone *aTimezone = nullptr);
		SFDateTime(std::string& aDateTime, std::string& aTimezone);
		SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...
		SFInterval operator-(const SFDate &other)const;
		SFInterval operator-(const SFTime &other)const;

		SFDateTime& adjustByDays(int n);// --to add or subtract N days from the given date
		SFDateTime& adjustByWeeks(int n);// --to add or subtract N weeks from the given date
		SFDateTime& adjustByMonths(int n);// --to add or subtract N months from the given date
		SFDateTime& adjustByYears(int n);
		SFDateTime& adjustByMinutes(int n); //--to + / -N minutes from the given time
		SFDateTime& adjustByHours(int n);
		SFDateTime& operator++(); //advance by one day
		SFDateTime operator++(int k);
		SFDateTime& operator --(); //back up by one day...
		SFDateTime operator--(int k);
		SFDateTime& setDay(int aDay);     //set the current day of the given date object; aDay must be in valid range
		SFDateTime& setMonth(int aMonth);  //set the current month of the given date object aMonth must be in valid range
		SFDateTime& setYear(int aYear);
		int   getDay()const;   //if date is 12/15/2018, the day is the 15th
		int   getMonth()const; //if date is 12/15/2018, the month is 12 (dec)
		int   getYear()const;
		int   getHour()const;
		int   getMinutes()const;
		int   getSeconds()const;
		int   getDayOfYear(); //if date is 01/04/1961, the day of year is 4 (range is 1..365)
		int   getDayOfweek(); //range (0..6 -- 0==sunday) 
		int   getWeekOfYear();//if date is 01/10/2018, the week of year is 2 (range is 1..52)				
		int   daysInMonth();
		SFDateTime& startOfMonth(); //if date is 12/15/2018, return 12/01/2018 
		SFDateTime& endOfMonth();   //if date is 12/15/2018, return 12/31/2018
		SFDateTime& startOfYear();  //if date is 12/15/2018, return 01/01/2018 
		SFDateTime& endOfYear();
		SFDateTime& startOfDay(); //change time to(00:00 : 00)
		SFDateTime& endOfDay();
		SFTimezone&  getTimezone(); //retrieve timezone currently associated with this object
		SFDateTime&  setTimezone(SFTimezone &aTimezone); //change timezone		
		bool operator>(const SFDateTime aDay);
		bool operator<(const SFDateTime aDay);
		bool operator==(const SFDateTime aDay);
		bool operator>=(const SFDateTime aDay);
		bool operator<=(const SFDateTime aDay);
		bool operator!=(const SFDateTime aDay);
		operator const char*();
		operator SFDate();
		operator SFTime();
		operator SFTimezone()const;
		std::string toDateString();
		std::string toTimeString();
		std::string toDateTimeString();   //Jan 4, 1961 09:15:00 PST (always this format)
	};
}