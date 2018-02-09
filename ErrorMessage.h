// Final Project Milestone 2
// ErrirNessage.h
// Version 1.0
// Date	 : December 4, 2017
// Author	Eunbi Lee
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#ifndef SICT_ERRORMESSAGE_H
#define SICT_ERRORMESSAGE_H

namespace sict {
	class ErrorMessage {
		char* errstr;

	public:
		explicit ErrorMessage(const char* errorMessage = nullptr);	//hold error msg or set empty state
		ErrorMessage(const ErrorMessage& em) = delete;	//deleted copy constructor - prevents copying
		ErrorMessage& operator=(const ErrorMessage& em) = delete;	//deleted assignment operator that prevents assignment
		virtual ~ErrorMessage();	//deallocate any memory
		void clear();	//clear any message stored by the current object and set empty state
		bool isClear() const;	//return true if current object is empty
		void message(const char* str);	//store, copy error message
		const char* message()const;	//return address of error message
		
	};
	std::ostream& operator<<(std::ostream&, const ErrorMessage&); // helper operator//if a message exists
	

}
#endif // SICT_ERRORMESSAGE_H
