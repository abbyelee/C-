// Final Project Milestone 2
// Version 1.0
// Date	 : December 4, 2017
// Author	Eunbi Lee
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#include <iostream>
#include <string.h>
#include "ErrorMessage.h"
#define _CRT_SECURE_NO_WARNINGS

namespace sict{

	//hold error msg or set empty state
	ErrorMessage::ErrorMessage(const char* errorMessage) {
		
		if(errorMessage !=nullptr) {
			
			errstr = new char[strlen(errorMessage) + 1];
			strncpy(errstr, errorMessage, strlen(errorMessage));	//copy err message
			errstr[strlen(errorMessage)] = '\0';
		}
		else{
			errstr = nullptr;  //safe empty state
		}
	}

	//deallocate dynamic memory allocated by the current object
	ErrorMessage::~ErrorMessage() {
		
		delete errstr;
		errstr = nullptr;
		
	}

	//clear current object, and set safe empty state
	void ErrorMessage::clear() {
		
		errstr = nullptr;
	}

	//return true, if the current object is safe empy state
	bool ErrorMessage::isClear() const {
		
		bool empty = errstr==nullptr; //safe empty state- true
		return empty;
	}

	//store copied message
	void ErrorMessage::message(const char* str) {
		
		if (str != nullptr) {	//errmsge is not empty
		
			delete errstr;    //deallocate			
			int len = strlen(str);
			errstr = new char[len + 1];
			strncpy(errstr, str, len);
			errstr[len] = '\0';
		}
		else {
			errstr = nullptr;
		}
		
	}

	//return address of error msg
	const char* ErrorMessage::message()const {
		return errstr;
	}

	// helper operator//if a message exists
	std::ostream& operator<<(std::ostream& os, const ErrorMessage& s) { 
		if (!s.isClear())	// err state is not clear
		{
			os << s.message();
		}
		return os;
	}
}
