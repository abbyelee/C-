// Final Project Milestone 1
//
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

#include <iostream>
#include "Date.h"
using namespace std;
namespace sict {

	// number of days in month mon_ and year year_
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	/*default constructor/safe empty state*/
	Date::Date() {  
		yr = 0;
		mth = 0;
		dy = 0;
		comparator = 0; 
		errCode(NO_ERROR);
	}

	/*constructor with three arguments, check validation, set comparator, set error code*/
	Date::Date(int getY, int getM, int getD) {
		//check validation
		bool valid = getY <= 2030 && getY >= 2000
			&& getM >= 1 && getM <= 12
			&& getD >= 1 && getD <= mdays(getM, getY);

		if (valid) {  //if valid data, store data in object
			yr = getY;
			mth = getM;
			dy = getD;
			errCode(NO_ERROR);//set error code
			//calculate the comparator 
			comparator = getY*372 + getM* 13 + getD;
		}
		else {
			if ((getY < 2000 || getY >2030) && (getM < 1 || getM >12) && (getD <1 || getD>mdays(getM, getY))) {//any data are not valid
				Date();		//set safe empty state
			}
			else if (getY < 2000 || getY > 2030) {		//year error
				(*this) = Date();
				errCode(YEAR_ERROR);
			}
			else if (getM < 1 || getM >12) {		//month error
				(*this) = Date();
				errCode(MON_ERROR);
			}
			else if (getD < 1 || getD > mdays(getM, getY)) {  //day error
				(*this) = Date();
				errCode(DAY_ERROR);
			}
		}
	}

	/*two objets are not empty and two dates are same, return true*/
	bool Date::operator==(const Date& rhs) const {	
		bool valid = (*this).yr != 0 && rhs.yr != 0 && (*this).mth != 0 && rhs.mth != 0 && (*this).dy != 0 && rhs.dy != 0 && (*this).comparator == rhs.comparator;
		return valid;
	}

	/*two objets are not empty and two dates are not same, return true*/
	bool Date::operator!=(const Date& rhs) const {
		bool valid = (*this).yr != 0 && rhs.yr != 0 && (*this).mth != 0 && rhs.mth != 0 && (*this).dy != 0 && rhs.dy != 0 && (*this).comparator != rhs.comparator;
		return valid;
	}

	/*two objets are not empty and current date is less than right hand side data, return true*/
	bool Date::operator<(const Date& rhs) const {
		bool valid = (*this).yr != 0 && rhs.yr != 0 && (*this).mth != 0 && rhs.mth != 0 && (*this).dy != 0 && rhs.dy != 0 && (*this).comparator < rhs.comparator;
		return valid;
	}

	/*two objets are not empty and current date is greater than right hand side data, return true*/
	bool Date::operator>(const Date& rhs) const {
		bool valid = (*this).yr != 0 && rhs.yr != 0 && (*this).mth != 0 && rhs.mth != 0 && (*this).dy != 0 && rhs.dy != 0 && (*this).comparator > rhs.comparator;
		return valid;
	}

	/*two objets are not empty and current date is less than and equal right hand side data, return true*/
	bool Date::operator<=(const Date& rhs) const {
		bool valid = (*this).yr != 0 && rhs.yr != 0 && (*this).mth != 0 && rhs.mth != 0 && (*this).dy != 0 && rhs.dy != 0 && (*this).comparator <= rhs.comparator;
		return valid;
	}

	/*two objets are not empty and current date is greater than and equal right hand side data, return true*/
	bool Date::operator>=(const Date& rhs) const {
		bool valid = (*this).yr != 0 && rhs.yr != 0 && (*this).mth != 0 && rhs.mth != 0 && (*this).dy != 0 && rhs.dy != 0 && (*this).comparator >= rhs.comparator;
		return valid;
	}

	/*return int value of error state*/
	int Date::errCode() const {
		return errSt; // Error code value 0,1,2,3,4
	}

	/* if error, return true*/
	bool Date::bad() const {        
		bool valid = errSt!=NO_ERROR;
		return valid;
	}

	/*set error state*/
	void Date::errCode(int errorCode) {		
		errSt = errorCode;
	}
	/*read data from user*/
	istream& Date::read(istream& istr) {
		char a, b;
		int y, m, d;
		istr >> y >> a >> m >> b >> d;  // get data from user
		
		if (istr.fail() == true) {		//if fail in any point 

			errCode(CIN_FAILED);		//change value of error state to CIN_FAILED
		}
		else {
			Date tmp(y, m, d);			// store in temperay object and check validation, set comparator, error code
			(*this) = tmp;				// and store data in current object
		}
		return istr;				//return reference of this object
	}

	/*display data from object*/
	ostream& Date::write(ostream& ostr) const {
				
		ostr << yr << '/';		// display data with date form
		cout.setf(ios::fixed);
		cout.width(2);
		cout.fill('0'); 
		ostr << mth << '/';
		cout.setf(ios::fixed);
		cout.width(2);
		cout.fill('0'); 
		ostr<< dy;

		return ostr;		// return reference of formed object
	}

	/* helper function to display data, make own overloading operator <<*/
	ostream& operator<<(ostream& ostr, const Date& rhs) {
		
		rhs.write(ostr);
		return ostr;

	}
	/* helper function to read data, make own overloading operator >>*/
	istream& operator>>(istream& istr, Date& rhs) {
		rhs.read(istr);
		return istr;
 	}
}
