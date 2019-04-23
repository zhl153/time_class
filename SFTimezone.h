#pragma once
#include<string>
namespace SoftwareFoundations {
	class SFTimezone {
	public:
		char* tz;
		SFTimezone(const char* aTimezoneAbbrev); //GMT, EST, CST, PST
		SFTimezone();
		SFTimezone(const SFTimezone &aTimezone);
		SFTimezone(std::string & aTimezone);
		~SFTimezone();
		operator const char*(); // Returns the 3 letter abbreviation of the timezone object
		operator std::string();
	};
}