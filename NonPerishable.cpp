// Final Project Milestone 4
// NonPerishable.cpp
// Version 1.0
// Date  Dec 20/2017
// Author Eunbi Lee (Abby)
// Description
//
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "NonPerishable.h"

using namespace std;
namespace sict {

	//store product name
	void NonPerishable::name(const char* newName) {
		productName = nullptr;
		if (newName != nullptr) {	//store name in class
			productName = new char[max_name_length + 1];
			strncpy(productName, newName, max_name_length);
			productName[max_name_length] = '\0';
		}
		
	}

	//return product name
	const char* NonPerishable::name() const {

		return productName; //if no name return nullptr
	}

	//calculate price with tax
	double NonPerishable::cost() const {
		double price = 0.0;
		if (taxable == true) {	//if tax yes, calculate cost
			price = priceBeforeTax * (tax_rate + 1);
		}
		else
			price = priceBeforeTax;	// no tax, return before tax price
		return price; //after tax
	}

	//store error state in ErrorMessage object
	void NonPerishable::message(const char* err) {
		errtemp.message(err);
	}

	//ErrorMessage object is clear
	bool NonPerishable::isClear() const {
		
		bool errClear = errtemp.isClear();
		return errClear; //return true clear error message
	}

	//
	NonPerishable::NonPerishable(char pType) {
		//initialize product type
		type[0] = pType;
		type[1] = '\0';
		if (type[0] == 'p' || type[0] == 'P') { //Create Perishable type object
		//set current object to Perichable empty state
			CreateProduct();

		}
		else {	//set empty state  //N type object
			CreateProduct();

		}
	}

	//constructor with seven argument
	NonPerishable::NonPerishable(const char* g_sku, const char* g_pName, const char* g_unit, int g_quantityH, bool g_taxable, double g_priceBeforeTax, int g_quantityN) {
		if (g_sku != nullptr) {	//copy sku
			strncpy(sku, g_sku, max_sku_length);
			sku[max_sku_length] = '\0';
		}
		else {
			g_sku = '\0';
		}
		name(g_pName);	//copy product name

		if (g_unit != nullptr) {	//copy unit
			strncpy(unit, g_unit, max_unit_length);
			sku[max_unit_length] = '\0';
		}
		
		//copy other value
		quantityH = g_quantityH;	
		taxable = g_taxable;
		priceBeforeTax = g_priceBeforeTax;
		quantityN = g_quantityN;

	}

	//destructor
	NonPerishable::~NonPerishable() {

		delete[] productName;
		productName = nullptr;

	}

	//coopy constructor
	NonPerishable::NonPerishable(const NonPerishable& src) {
		
		(*this).productName = nullptr;	//delete data
		*this = src;	//copy using assignment operator
	}

	//copy assignment operator
	NonPerishable& NonPerishable::operator=(const NonPerishable& src) {
		if (this != &src) {

			strncpy(sku, src.sku, max_sku_length);	//copy sku
			sku[max_sku_length] = '\0';

			strncpy(unit, src.unit, max_unit_length);	//copy unit
			sku[max_unit_length] = '\0';

			quantityH = src.quantityH;
			taxable = src.taxable;
			priceBeforeTax = src.priceBeforeTax;
			quantityN = src.quantityN;

			const char* str;			
			str = src.errtemp.message();	//str point err msg
			errtemp.message(str);			//store err msg into current object 

			if (src.productName != nullptr) {		//copy product name

				name(src.productName);
			}
			else
				productName = nullptr;
							
		}

		return *this;
	}

	//store data into file
	std::fstream& NonPerishable::store(std::fstream& file, bool newLine) const {
		
		int a = taxable == true ? 1 : 0;		//convert true = int 1, false = int 1
				
		if (type[0] == 'N') {	//store NonPerishable product into file 
			file << type << "," << sku << "," << productName << "," << priceBeforeTax << "," << quantityH << "," << a << "," << unit << "," << quantityN << endl;
			
		}
		else if (type[0] == 'P') {	//store Perishable product  into file
			file << type << "," << sku << "," << productName << "," << priceBeforeTax << "," << a << "," << quantityH << "," << unit << "," << quantityN;
		}		
		
		return file;
	}

	//get data from file
	std::fstream& NonPerishable::load(std::fstream& file) {
		
		char nameTmp[max_name_length+1];	
	
		if (file.is_open()) {
									
				file.get(sku,max_sku_length+1,',');	//get sku				
				file.ignore();//reading a comma
				file.get(nameTmp,max_name_length+1, ','); //get product name
				file.ignore();//reading a comma
				file >> priceBeforeTax;	//get price before tax

				if (type[0] == 'P') {	//if P type object, get data following order
					file.ignore();//reading a comma
					file >> taxable;
					file.ignore();//reading a comma
					file >> quantityH;
				}
				else if (type[0] == 'N') {	//if N type object, get data following order
					file.ignore();//reading a comma
					file >> quantityH;
					file.ignore();//reading a comma
					file >> taxable;
				}
				file.ignore();//reading a comma
				file.get(unit, max_unit_length + 1, ',');		
				file.ignore();
				file >> quantityN;

				name(nameTmp);	//store name into current object
		
			}
		
		return file;
	}

	//display data
	std::ostream& NonPerishable::write(std::ostream& os, bool linear) const {
		if (linear == true) {
			if (!isEmpty()) {  //if error state
				os << errtemp;	//display err msg
			}
			else {	//if empty err state, linear
				
				os << setw(max_sku_length) << left <<setfill(' ')<< sku << "|";
				os << setw(20)<<left<< setfill(' ') << productName << "|";			
				os << setw(7) << setprecision(2)<< right<<fixed << setfill(' ') << total_cost() << "|";				
				os << setw(4) << right << setfill(' ') << quantityH << "|";			
				os << setw(10) << left << setfill(' ') << unit << "|";			
				os << setw(4) << right << setfill(' ') << quantityN << "|";
			
			}
		}
	
		else {		//display line by line
			
			os << "Sku: ";
			os << sku << endl;
			os << "Name: ";
			os << productName << endl;
			os << "Price: ";
			os.setf(ios::fixed);
			os.precision(2);
			os << priceBeforeTax << endl;
			
			if (taxable == true) {	//tax is applied
				os << "Price after tax: ";
				os.precision(2);
				os.setf(ios::fixed);
				os << total_cost() << endl;	//calculate tax
			}
			else {	// tax is not applied
				os << "Price after tax: N/A" << endl;
			}

			os << "Quantity On Hand: ";
			os << quantityH << " " << unit <<endl;
			os << "Quantity Needed: ";
			os << quantityN;
			if (type[0] == 'P') {
				os << endl;
			}			
		}

		return os;
	}

	//get data from client
	std::istream& NonPerishable::read(std::istream& is) {

		char taxchar[2];
		char name[76] ;

		NonPerishable t;	//temporary object

		//get data from client
		cout << " Sku: ";
		is >> t.sku;
		cout << " Name: ";
		is >> name;
		t.name(name);
		cout << " Unit: ";
		is >> t.unit;
		cout << " Taxed? (y/n): ";
		is >> taxchar;

		if (taxchar[0] == 'y' || taxchar[0] == 'Y' || taxchar[0] == 'n' || taxchar[0] == 'N') { //if valid data Y,y,N,n ask next question
			cout << " Price: ";
			is >> t.priceBeforeTax;
			if (t.priceBeforeTax > 0) {				//if valid data, get next data
				cout << "Quantity On hand: ";
				is >> t.quantityH;
				if (t.quantityH > 0) {
					cout << "Quantity Needed: ";
					is >> t.quantityN;
					if (t.quantityN > 0) {		//all input valid
						
						*this = t;	//copy temporary object to current object
					}
					else {
						t.message("Invalid Quantity Needed Entry");	// store error message into temp object 
						is.istream::setstate(std::ios::failbit);	//return fail bit and stop getting data and break out 
					}
				}
				else {
					t.message("Invalid Quantity Entry");
					is.istream::setstate(std::ios::failbit);
				}
			}
			else {
				t.message("Invalid Price Entry");
				is.istream::setstate(std::ios::failbit);
			}
		}
		else {
			t.message("Only (Y)es or (N)o are acceptable");
			
			is.istream::setstate(std::ios::failbit);
		}

		if (taxchar[0] == 'y'||taxchar[0] == 'Y' )		//convert int value to bool
		{
			t.taxable = true;
		}
		else if (taxchar[0] == 'N' || taxchar[0] == 'n' )
		{
			t.taxable = false;
		}

		*this = t;	//copy temporary object to current object
		return is;
	}

	//same sku
	bool NonPerishable::operator==(const char* g_sku) const {
		bool sameSku = strcmp(sku, g_sku) == 0;
		return sameSku;
	}

	//calculate total cost of quantity on hand
	double NonPerishable::total_cost() const {
		double total = quantityH * cost();
		return total;
	}

	// update quantity on hand
	void NonPerishable::quantity(int u) {
		
		quantityH = quantityH + u;
	}

	//return true no error state 
	bool NonPerishable::isEmpty() const {
		//bool noError = errmsg == nullptr; 
		bool noError = errtemp.isClear();
		return noError;
	}

	//return quantity needed
	int NonPerishable::qtyNeeded() const {
		
		return quantityN;
	}

	//return quantity on hand
	int NonPerishable::quantity() const {
		
		return quantityH;
	}

	//greater than sku
	bool NonPerishable::operator>(const char* rhc) const {
		
		bool greater = strcmp(sku, rhc) == 0;
		return greater;
	}
	
	// add quantity
	int NonPerishable::operator+=(int u) {

		if (u > 0) {
			quantityH = quantity() + u;
		}
		else
			quantityH = quantity();
		return quantityH;
	}

	//compare name
	bool NonPerishable::operator>(const Product& rhc) const {
		bool greaterName = strcmp(productName, rhc.name()) > 0;// >0 greater
		return greaterName;
	}

	//////////////////helper function/////////////////////

	std::ostream& operator<<(std::ostream&os, const Product& p) {

		if (p.name() != nullptr) {
			p.write(os, true);
		}
		else {
			p.write(os, false);
		}
		return os;
	}
	std::istream& operator>>(std::istream&is, Product& p) {
		p.read(is);
		return is;
	}

	//add total cost and received double value
	double operator+=(double& d, const Product& p) {
		d = p.total_cost() + d;
		return d;
	}

	//create Nonperishable object
	Product* CreateProduct() {
		
		Product* p = nullptr;
		p = new NonPerishable('\0', '\0', '\0', 0, true, 0.0, 0);
		return p;

	}
}