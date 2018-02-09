// Final Project Milestone 4
// Version 1.0
// Date	 : December 20, 2017
// Author	Eunbi Lee
// NonPerishable.h
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#ifndef SICT_NONPERISHBLAE_H
#define SICT_NONPERISHABLE_H
#include "Product.h"
#include "ErrorMessage.h"
namespace sict {
	const int max_sku_length = 7; //not include null
	const int max_unit_length = 10; //not include null
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class NonPerishable : public Product {
		
		char type[2]; //identify type of object  N or P
		char sku[max_sku_length + 1];
		char* productName;
		char unit[max_unit_length + 1];
		int quantityH;
		int quantityN;
		double priceBeforeTax;
		bool taxable;
	
		ErrorMessage errtemp;	// hold err msg
		
	protected:
		void name(const char*);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		
		NonPerishable(char = 'N');
		NonPerishable(const char*, const char*, const char*, int = 0, bool = true, double = 0.0, int = 0);		
		~NonPerishable();
		NonPerishable(const NonPerishable&);//coopy constructor
		NonPerishable& operator=(const NonPerishable& source);//copy assignment operator
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;

	};
	//helper function
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
	Product* CreateProduct();
}
#endif
