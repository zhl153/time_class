#pragma once
namespace SoftwareFoundations {
	class SFInterval {
	public:
		int years;
		int months;
		int days;
		int hours;
		int minutes;
		int seconds;
		SFInterval();
		SFInterval(int year, int month, int day, int hour, int minute, int second);
		operator const char*()const; // Returns the interval of the form "Y years, M months, D days, H hours, M minutes and S seconds"
									 // Ex. 5 years, 3 months, 2 days, 6 hours, 7 minutes and 10 seconds
		SFInterval operator+(const SFInterval & other);
	};
}