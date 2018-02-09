// Final Project Milestone 5
// Perishable.h
// Version 1.0
// Date	 : December 22, 2017
// Author	Eunbi Lee
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#pragma once
#ifndef SICT_PERISHBLAE_H
#define SICT_PERISHABLE_H
#include "NonPerishable.h"
#include "Date.h"
namespace sict {

	class Perishable : public NonPerishable{
		Date pdate;		//Datd objet
	public: 
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		const Date& expiry() const;//return  expiry date

	};

	Product* CreatePerishable(); //create a Perishable abject
}
#endif