#include"SFTimezone.h"
#include<cstring>
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
using namespace SoftwareFoundations;

SFTimezone::SFTimezone() {
	tz = nullptr;
}
SFTimezone::SFTimezone(const char* aTimezoneAbbrev) {
//	if (tz)delete[] tz, tz = nullptr;
	if (aTimezoneAbbrev) {
		tz = new char[4];
		strcpy(tz, aTimezoneAbbrev);
	}
}
SFTimezone::SFTimezone(const SFTimezone &aTimezone) {
//	if (!tz)delete[] tz, tz = nullptr;
	if (aTimezone.tz != nullptr) {
			tz = new char[4];
			strcpy(tz, aTimezone.tz);		
	}
	else
		tz = nullptr;
}
SFTimezone::SFTimezone(std::string& aTimezone) {
//	if (!tz)delete[] tz, tz = nullptr;
	if (aTimezone.size()) {
		tz = new char[4];
		strcpy(tz, aTimezone.c_str());
	}
	else tz = nullptr;
}
SFTimezone::~SFTimezone() {
	/*if (!tz) {
		delete[] tz;
		tz = nullptr;
	}*/
}

SFTimezone::operator const char*() {
	if (!tz)return "";
	else return tz;
}
SFTimezone::operator std::string() {
	std::string re;
	if (!tz)return re;
	else {
		re = tz;
		return re;
	}
}
