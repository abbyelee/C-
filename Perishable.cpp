// Final Project Milestone 5
// Perishable.cpp
// Version 1.0
// Date  Dec 22/2017
// Author Eunbi Lee (Abby)
// Description
//
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include "Perishable.h"

using namespace std;

namespace sict {
	Perishable::Perishable():NonPerishable('P') {
		Date();	//set current obj safe empty state
	}

	fstream& Perishable::store(std::fstream& file, bool newLine) const {
		
		NonPerishable::store(file,newLine);
		file << ','<< pdate << endl;
		if (newLine == true) {
			 //file << '\n';
			
		}
		
		return file;
	}
	fstream& Perishable::load(std::fstream& file) {
		
		NonPerishable::load(file);
		file.ignore();//reading comma
		file >> pdate;
		//pdate.read;
		return file;
	}
	ostream& Perishable::write(std::ostream& os, bool linear) const {

		NonPerishable::write(os, linear);
		if (linear == true) {
			if (isEmpty()) { //no err
				os << pdate;
			
			}
		}

		else {	// not linear	
			if (isEmpty()) { //no err
				os << "Expiry date: " << pdate;
			}
		}
		return os;
	}
	istream& Perishable::read(std::istream& is) {
		
		NonPerishable::read(is);
		cout << "Expiry date (YYYY/MM/DD): ";		
		pdate.read(is);
		if (pdate.bad()) {
			
			if (pdate.errCode() == 1) {
				(*this).message("Invalid Date Entry");
			}
			else if (pdate.errCode() == 2) {
				(*this).message("Invalid Year in Date Entry");
			}
			else if (pdate.errCode() == 3) {
				(*this).message("Invalid Year in Date Entry");
			}
			else if (pdate.errCode() == 4) {
				(*this).message("Invalid Month in Date Entry");
			}
			else if (pdate.errCode() == 5) {
				(*this).message("Invalid Day in Date Entry");
			}
			is.istream::setstate(std::ios::failbit);
			
		}

	//	is.istream::setstate(std::ios::failbit);
		
		return is;
	}

	const Date& Perishable::expiry() const {

		return pdate;
	}

	Product* CreatePerishable() {
		Product* p = nullptr;
		p = new Perishable();
		return p;

	}
}
