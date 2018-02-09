// Final Project Milestone 1
// Data.h
// Version 1.0
// Date  Oct 31/2017
// Author Eunbi Lee (Abby)
// Description
// Aid Management Application
// Get date data from user
// and check validation and store data into object
// and display data
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef SICT_DATE_H
#define SICT_DATE_H

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
namespace sict {
	int const min_year = 2000;
	int const max_year = 2030;
	class Date {
		int yr;		//year 2000-2030
		int mth;	//month 1-12
		int dy;		//depend on month
		int comparator;  //value of date for compare
		int errSt;		// error state
		int mdays(int, int)const;		//calculate days in a month
		void errCode(int errorCode);	//set error state
	public:
		Date();
		Date(int, int, int);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
	
	std::ostream& operator<<(std::ostream& , const Date&);	//helper function for write
	std::istream& operator>>(std::istream& , Date&);		//helper function for read
}
#endif
