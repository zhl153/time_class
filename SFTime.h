#pragma once

#include<string>
namespace SoftwareFoundations {
	class SFDateTime;
	class SFInterval;
	class SFTime {
		int h;
		int mi;
		int s;
	public:
		int newday;
		SFTime();                             //default to now(HH:MM:SS) 
		SFTime(const char *aTimeString);      //must parse the given string of the form "HH:MM:SS"
		SFTime(int anHour, int aMinutes, int aSeconds); //build time from individual parts
		SFTime(const SFTime &aCopy);
		SFTime(const SFDateTime &aCopy);
		SFTime(std::string& aTimeString);
		SFTime& adjustByMinutes(int n); //--to + / -N minutes from the given time
		SFTime& adjustByHours(int n); //--to + / -N hours from the given time. 11:15pm + 2hours is 1 : 15a(rolls over)
		SFInterval operator-(const SFTime &other) const; //determine interval between two times...
		SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...
		int   getHour()const;
		int   getMinutes()const;
		int   getSeconds()const;

		SFTime& startOfDay(); //change time to(00:00 : 00)
		SFTime& endOfDay();   //change time to(23:59 : 59)

		std::string toTimeString();  //Returns string of the form HH:MM:SS

		bool operator>(const SFTime aTime)const;
		bool operator<(const SFTime aTime)const;
		bool operator==(const SFTime aTime)const;
		bool operator>=(const SFTime aTime)const;
		bool operator<=(const SFTime aTime)const;
		bool operator!=(const SFTime aTime)const;								 //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==

	};
}