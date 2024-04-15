#include "Transaction.h"
#include "Account.h"

Transaction::Transaction(Account* s, Account* d, double amount, const char* date) :
 m_date(nullptr) {
	//allocate memory for date and copy the provided string
	this->SetDate(date);
	this->SetSource(s);
	this->SetDes(d);
	this->SetAmount(amount);
}

//-----------------------------------------------------------------------------------------------------
Transaction::Transaction(const Transaction& other) ://copy constructor
	 m_date(nullptr)
{
	this->SetAmount(other.m_amount);
	this->SetDate(other.m_date);
	this->SetSource( other.m_source);
	this->SetDes(other.m_destination);
	
}



//-----------------------------------------------------------------------------------------------------
void Transaction::SetSource(Account* src) {
	if (src != nullptr) {
		this->m_source = src;
	}
}
//----------------------------------------------------------------------------------------------------
void Transaction::SetDes(Account* dst) {
	if (dst != nullptr) {
		this->m_destination = dst;
	}
}

//-----------------------------------------------------------------------------------------------------
void	Transaction::SetAmount(double amount) {
			this->m_amount = amount;
}
//-----------------------------------------------------------------------------------------------------
void	Transaction::SetDate(const char* date) {
	this->m_date = strdup(date);
}
//------------------------------------------------------------------------------------------------------
Account* Transaction::GetSource() const {
			return this->m_source;
		}
		
//------------------------------------------------------------------------------------------------------
Account* Transaction::GetDes() const {
	return this->m_destination;
}
//------------------------------------------------------------------------------------------------------
 double Transaction:: GetAmount ()const {
				return this->m_amount;
			}
//-------------------------------------------------------------------------------------------------------
 char* Transaction::GetDate() const {
	 return this->m_date;
 }
//-------------------------------------------------------------------------------------------------------
