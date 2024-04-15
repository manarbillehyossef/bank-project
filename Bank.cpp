#include "Bank.h"

//defult constructor
Bank::Bank() :m_name(nullptr), m_account(nullptr), m_bankCode(0), m_numbeOfAccounts(0), m_totalBalance(0){}
//---------------------------------------------------------------------------------------------------------------------------------------
Bank::Bank(const char* name, int code) :m_name(nullptr), m_account(nullptr), m_bankCode(code), m_numbeOfAccounts(0), m_totalBalance(0)
{

SetBankName(name);
}

//---------------------------------------------------------------------------------------------------------------------------------------
//destructor
Bank::~Bank()
{
	if (m_name != nullptr) delete[] m_name;
	if (m_account != nullptr) {
		for (int i = 0; i < m_numbeOfAccounts; ++i) {
			delete m_account[i];
		}
		delete[] m_account;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------
//seters
void Bank::SetBankName(const char* name)
{
	//free previosly allocated memory
	delete[] m_name;
	//safety check for newname
	if (name != nullptr) {
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
	else { m_name = nullptr; }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Bank::SetAccount(Account** account, int numbeOfAccounts)
{
	//valid inputs
	if (account == nullptr || numbeOfAccounts <= 0)return;
	//delete existing account and deallocate memory
	for (int i = 0; i < this->m_numbeOfAccounts; ++i) {
		DeleteAccount(*this->m_account[i]);
	}
	delete[]m_account;
	m_account = nullptr;
	//allocate memory for the account array
	this->m_account = new Account * [numbeOfAccounts];
	//copy acount pointer
	for (int i = 0; i < numbeOfAccounts; ++i) {
		this->m_account[i] = account[i];
	}
	this->m_numbeOfAccounts = numbeOfAccounts;
}
//-------------------------------------------------------------------------------------------------------------------------------------
//seters
void Bank::SetTotal(double total) {
	m_totalBalance = total;
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Bank::SetCode(int code) {
	m_bankCode = code;
}
//--------------------------------------------------------------------------------------------------------------------------------------
const char* Bank::GetBankName() const {
	return m_name;
}
//--------------------------------------------------------------------------------------------------------------------------------------
Account** Bank::GetAccounts() const {
	return m_account;
}
//---------------------------------------------------------------------------------------------------------------------------------------
int	Bank::GetNumberOfAccounts() const {
	return m_numbeOfAccounts;
}
//--------------------------------------------------------------------------------------------------------------------------------------
double	Bank::GetTotal() const {
	return m_totalBalance;
}
//--------------------------------------------------------------------------------------------------------------------------------------
int	Bank::GetCode() const {
	return m_bankCode;
}
//--------------------------------------------------------------------------------------------------------------------------------------
//member methods
void Bank::AddAccount(const Account& account) {
	
	
	if (m_account != nullptr) {
		// Check if the account already exists in the array
		for (int i = 0; i < m_numbeOfAccounts; ++i) {
			if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
				// Account already exists, do nothing
				return;
			}
		}
	}

	// Allocate memory for the new account array
	Account** temp = new Account * [m_numbeOfAccounts + 1];
	if (temp == nullptr) {
		// Memory allocation failed
		// Handle error (e.g., throw an exception)
		return;
	}

	// Copy existing accounts to the new array
	for (int i = 0; i < m_numbeOfAccounts; ++i) {
		temp[i] = m_account[i];
	}

	// Add the new account to the array
	temp[m_numbeOfAccounts] = new Account(account);

	// Delete the old array
	delete[] m_account;

	// Assign the new array to m_account
	m_account = temp;

	// Increment the number of accounts
	++m_numbeOfAccounts;

	// Update the total balance
	m_totalBalance += account.GetBalance();
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Bank::AddAccount(const Person& per, double amount) {
	//create an account for the person with specified initial amount
	Account* newaccount = new Account(per, amount);
	//Add the new account to the bank
	AddAccount(*newaccount);
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Bank::AddPerson(const Person& newPerson, const Account& account, double amount)
{
	// Flag to track if the account exists in the bank's accounts
	bool accountExist = false;
	int existingaccountindex = -1;
	// Check if the account exists in the bank's accounts
	for (int i = 0; i < m_numbeOfAccounts; ++i) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			accountExist = true;
			existingaccountindex = i;
			break;
		}
	}
	// If the account exists
	if (accountExist) {
		// Ensure that the m_account[existingaccountindex] is not null
		if (existingaccountindex != -1 && m_account[existingaccountindex]) {
			// Check if the person already exists
			bool personExistForAccount = false;
			for (int j = 0; j < m_account[existingaccountindex]->GetTotalPersons(); ++j) {
				// Compare the ID of the new person with the ID of the persons of the account
				if (m_account[existingaccountindex]->GetPersons()[j]->GetId() == newPerson.GetId()) {
					personExistForAccount = true;
					break;
				}
			}
			// If the person doesn't exist for the account, add them
			if (!personExistForAccount) {
				m_account[existingaccountindex]->AddPerson(newPerson, amount);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------
void Bank::DeleteAccount(const Account& account)
{ // Find the index of the account in the array
	int accountIndex = -1;
	for (int i = 0; i < m_numbeOfAccounts; ++i) {
		if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
			accountIndex = i;
			break;
		}
	}
	if (accountIndex == -1) {
		return;
	}
	// If the account exists
	if (accountIndex != -1) {
		// Delete the account from the array
		delete m_account[accountIndex];
		// Shift the elements after the deleted account to fill the gap
		for (int i = accountIndex; i < m_numbeOfAccounts - 1; ++i) {
			m_account[i] = m_account[i + 1];
		}
		// Decrement the number of accounts
		--m_numbeOfAccounts;
		// If it was the last account, clean up the array
		if (m_numbeOfAccounts == 0) {
			delete[] m_account;
			m_account = nullptr;
		}
	}
}
	
//--------------------------------------------------------------------------------------------------------------------------------------
void Bank::DeletePerson(const Person& p) {
	// Iterate through all accounts
	for (int i = 0; i < m_numbeOfAccounts; ++i) {
		// Check if the person exists in the current account
		bool personFound = false;
		for (int j = 0; j < m_account[i]->GetTotalPersons(); ++j) {
			if (m_account[i]->GetPersons()[j]->GetId() == p.GetId()) {
				// Person found in the current account
				personFound = true;
				// Delete the person from the account manually
				delete m_account[i]->GetPersons()[j];
				// Shift the remaining persons to fill the gap
				for (int k = j; k < m_account[i]->GetTotalPersons() - 1; ++k) {
					m_account[i]->GetPersons()[k] = m_account[i]->GetPersons()[k + 1];
				}
				// Decrement the total number of persons in the account
				m_totalBalance -= m_account[i]->GetBalance();
				// No need to continue searching for the person in the current account
				break;
			}
		}
		// If the person was found and deleted from the account
		if (personFound) {
			// If there are no persons left in the account, delete the account
			if (m_account[i]->GetTotalPersons() == 0) {
				// Delete the account
				delete m_account[i];
				// Shift the remaining accounts to fill the gap
				for (int k = i; k < m_numbeOfAccounts - 1; ++k) {
					m_account[k] = m_account[k + 1];
				}
				// Decrement the number of accounts
				--m_numbeOfAccounts;
				// If it was the last account, clean up the array
				if (m_numbeOfAccounts == 0) {
					delete[] m_account;
					m_account = nullptr;
					return;
					// No need to continue searching for the person in other accounts
				}
			}
			
			
		}
	}
}
