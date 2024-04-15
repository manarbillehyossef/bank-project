#include "Account.h"
#include "Transaction.h"

//defult constructor
Account::Account(){
	this->m_persons = nullptr;
	this->m_transactionList = nullptr;
	this->m_totalPersons = 0;
	this->m_accountNumber = 0;
	this->m_numberOfTransaction = 0;
}

//---------------------------------------------------------------------------------------------------------------------------------
//constructors
Account::Account(Person** persons, int count, double balance) {
	this->m_numberOfTransaction = 0;
	this->m_transactionList = NULL;
	this->m_accountNumber = 0;
	this->m_balance = balance;
	this->m_totalPersons = count;
	for (int i = 0; i < count; i++) this->m_accountNumber += persons[i]->GetId();

	this->m_persons = new Person * [this->m_totalPersons];
	for (int j = 0; j < this->m_totalPersons; j++) {
		this->m_persons[j] = new Person(*persons[j]);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
	Account::Account(const Person & person, double balance) : m_persons(new Person * [1]) {          // Storing a copy of the Person object directly
		this->m_numberOfTransaction = 0;
		this->m_transactionList = nullptr;
		this->m_accountNumber = person.GetId();
		this->m_balance = balance;
		this->m_totalPersons = 1;
		this->m_persons[0] = new Person(person);
	}
//------------------------------------------------------------------------------------------------------------------------------------
	Account::Account(const Account& other) {//copy constructor

		this->m_accountNumber = other.m_accountNumber;
		this->m_balance = other.m_balance;
		this->m_numberOfTransaction = other.m_numberOfTransaction;
		this->m_totalPersons = other.m_totalPersons;
		if (this->m_totalPersons) this->m_persons = new Person * [this->m_totalPersons];
		for (int i = 0; i < this->m_totalPersons; i++) {//copy the person
			this->m_persons[i] = new Person(*other.m_persons[i]);
		}
		//copy the transaction
		if (this->m_numberOfTransaction) this->m_transactionList = new Transaction * [this->m_numberOfTransaction];
		for (int j = 0; j < this->m_numberOfTransaction; j++) {
			this->m_transactionList[j] = new Transaction(*other.m_transactionList[j]);
		}
	}
//---------------------------------------------------------------------------------------------------------------------------------------
//destructor
Account::~Account() {
	clearPersons();
	clearTransactions();

}
//---------------------------------------------------------------------------------------------------------------------------------------
//setter functions
void Account::SetPersons(Person** persons, int count)
{
	//delet the persons if there is any
	delete[] this->m_persons;
	this->m_totalPersons = count;//allocate memory and copy
	this->m_persons = new Person * [this->m_totalPersons];
	for (int i = 0; i < this->m_totalPersons; i++) {
		this->m_persons[i] = new Person(*persons[i]);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Account::SetAccountNumber(int number)
{
	this->m_accountNumber = number;
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Account::SetBalance(double balance)
{
	this->m_balance = balance;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void Account::SetTransactions(Transaction * *newTransaction, int count)
{
	
	clearTransactions();
	// Update the number of transactions
	this->m_numberOfTransaction = count;
	// Allocate memory for the new transaction list
	this->m_transactionList = new Transaction * [count];

	// Copy transaction objects from the newTransaction array
	for (int i = 0; i < count; ++i) {
		this->m_transactionList[i] = new Transaction(*newTransaction[i]);
	}

	
}

//---------------------------------------------------------------------------------------------------------------------------------------
Transaction**Account:: GetTransactions()
{
	return this->m_transactionList;
}
//---------------------------------------------------------------------------------------------------------------------------------------
int	Account::GetNumOfTransactions() {
	return this->m_numberOfTransaction;
}
//---------------------------------------------------------------------------------------------------------------------------------------
Person** Account::GetPersons() const
{
	return this->m_persons;
}
//---------------------------------------------------------------------------------------------------------------------------------------
int	Account::GetTotalPersons()const
{
	return this->m_totalPersons;
}
//----------------------------------------------------------------------------------------------------------------------------------------
int	Account::GetAccountNumber() const
{
	return this->m_accountNumber;
}
//----------------------------------------------------------------------------------------------------------------------------------------
double Account::GetBalance() const
{
	return this->m_balance;
}
//----------------------------------------------------------------------------------------------------------------------------------------
//member methods


void Account::Withdraw(double amount, const char* date)
{
	if (amount <= 0 || amount > m_balance) return; // Ensure amount is valid and sufficient balance
	// Update the account balance
	this->SetBalance(this->m_balance-amount);
	// Create a new withdrawal transaction
	Transaction newTransaction(this, this, -amount, date);

	// Allocate memory for the updated transaction list
	Transaction** updatedTransactions = new Transaction * [m_numberOfTransaction + 1];

	// Copy existing transactions to the updated transaction list
	for (int i = 0; i < m_numberOfTransaction; ++i) {
		updatedTransactions[i] = m_transactionList[i];
	}

	// Add the new transaction to the end of the updated transaction list
	updatedTransactions[m_numberOfTransaction] = new Transaction(newTransaction);

	// Set the updated transaction list
	SetTransactions(updatedTransactions, m_numberOfTransaction + 1);

	// Update the transaction count
	++m_numberOfTransaction;
}



//----------------------------------------------------------------------------------------------------------------------------------------
void Account::Deposit(double amount, const char* date) {
	if (amount <= 0 || amount > m_balance) return; // Ensure amount is valid and sufficient balance
	// Update the account balance
	m_balance += amount;
	// Create a new withdrawal transaction
	Transaction newTransaction(this, this, amount, date);

	// Allocate memory for the updated transaction list
	Transaction** updatedTransactions = new Transaction * [m_numberOfTransaction + 1];

	// Copy existing transactions to the updated transaction list
	for (int i = 0; i < m_numberOfTransaction; ++i) {
		updatedTransactions[i] = m_transactionList[i];
	}

	// Add the new transaction to the end of the updated transaction list
	updatedTransactions[m_numberOfTransaction] = new Transaction(newTransaction);

	// Set the updated transaction list
	SetTransactions(updatedTransactions, m_numberOfTransaction + 1);

	// Update the transaction count
	
}
//----------------------------------------------------------------------------------------------------------------------------------------
void Account::AddPerson(const Person& newPerson, double	amount)
{
	//chek if the person already exist in the array
	for (int i = 0; i < m_totalPersons; ++i) {
		if (m_persons[i]->GetId() == newPerson.GetId())return;//person already exist do nothing
	}
	m_balance += amount;
	m_totalPersons++;
	//create a new array with space for additional person
	Person** tmp = new Person * [m_totalPersons];
	//copy existing person to the new array
	for (int i = 0; i < m_totalPersons - 1; i++)
	{
		tmp[i] = m_persons[i];
	}
	//pointing to the new person
	tmp[m_totalPersons - 1] = new Person(newPerson);
	delete[] m_persons;
	m_persons = tmp;
}
//--------------------------------------------------------------------------------------------------------------------------------------
void Account::DeletePerson(const Person& oldPerson)
{
	int indextoremove = -1;
	for (int i = 0; i < m_totalPersons; ++i) {
		if (m_persons[i]->GetId() == oldPerson.GetId()) {
			indextoremove = i;
			break;
		}
	}
	if (indextoremove != -1) {
		delete m_persons[indextoremove];
		m_persons[indextoremove] = nullptr;

		// Copy the last person into the removed person's slot if needed
		if (indextoremove != m_totalPersons - 1) {
			m_persons[indextoremove] = m_persons[m_totalPersons - 1];
			m_persons[m_totalPersons - 1] = nullptr; // Set the last slot to nullptr
		}
		--m_totalPersons;
	}

	// If this was the last person, set m_persons to nullptr
	if (m_totalPersons == 0) {
		delete[] m_persons;
		m_persons = nullptr;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Account::AddTransaction(const Transaction& newTransaction)
{ 
	
	double amount = newTransaction.GetAmount();
	// If it's the same account, it is a withdrawal or deposit
	if (newTransaction.GetSource() == newTransaction.GetDes()) {
		if (amount < 0) {//its withdraw {
			Withdraw(amount, newTransaction.GetDate());
		}
		else// its deposit
			Deposit(amount, newTransaction.GetDate());
	}
	// If it is a transaction between two different accounts
	if (newTransaction.GetSource() != newTransaction.GetDes()) {
		// Update the balances due to the transaction
		newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - amount);
		newTransaction.GetDes()->SetBalance(newTransaction.GetDes()->GetBalance() + amount);

		

		// Copy existing transactions to new lists for both source and destination accounts
		Transaction** oldTransactionsSrc = newTransaction.GetSource()->GetTransactions();
		Transaction** oldTransactionsDes = newTransaction.GetDes()->GetTransactions();
		int numTransactionsSrc = newTransaction.GetSource()->GetNumOfTransactions();
		int numTransactionsDes = newTransaction.GetDes()->GetNumOfTransactions();
		++numTransactionsDes;
		++numTransactionsSrc;
		Transaction** newTransactionsSrc = new Transaction * [numTransactionsSrc + 1];
		Transaction** newTransactionsDes = new Transaction * [numTransactionsDes + 1];
		
		if (newTransactionsSrc == nullptr || newTransactionsDes == nullptr) {
			// Memory allocation failed
			// Handle error (e.g., throw an exception)
			delete[] newTransactionsSrc;
			delete[] newTransactionsDes;
			return;
		}

		// Copy existing transactions to the new lists for both source and destination accounts
		for (int i = 0; i < numTransactionsSrc-1; ++i) {
			newTransactionsSrc[i] = oldTransactionsSrc[i];
		}
		for (int i = 0; i < numTransactionsDes-1; ++i) {
			newTransactionsDes[i] = oldTransactionsDes[i];
		}

		// Add the new transaction to the end of the lists for both source and destination accounts
		newTransactionsSrc[numTransactionsSrc-1] = new Transaction(newTransaction);
		newTransactionsDes[numTransactionsDes-1] = new Transaction(newTransaction);

		newTransaction.GetSource()->SetTransactions(newTransactionsSrc, numTransactionsSrc );
		newTransaction.GetDes()->SetTransactions(newTransactionsDes, numTransactionsDes );
	
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------	
void Account::clearTransactions()
{
	
	
		for (int i= 0; i < this->m_numberOfTransaction; i++) {
			delete this->m_transactionList[i];
		}
		delete[] this->m_transactionList;
	}

//---------------------------------------------------------------------------------------------------------------------------------------
void Account::clearPersons() {

	// Clears all the Persons associated with an Account.
	for (int i = 0; i < this->m_totalPersons; i++)
		delete[] this->m_persons;
	this->m_totalPersons = 0;
}
