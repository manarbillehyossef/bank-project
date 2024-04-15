#include "Person.h"

//constructors
Person::Person() :m_name(NULL), m_id(0) {} //default constructor

//--------------------------------------------------------------------
//parameterized constructor
Person::Person(const char* name, int id) :m_name(NULL) {

		this->SetName(name);
		this->SetId(id);
}
//---------------------------------------------------------------------
Person::Person(const Person& other)//copy constructor
{
	this->m_name = NULL;
	this->SetName(other.m_name);
	this->SetId(other.m_id);
	
}
//-----------------------------------------------------------------------
//destructor
Person::~Person() {
	//free dynamically alocated memory
	if (this->m_name != nullptr)
		delete[] m_name;
}
//------------------------------------------------------------------------
void Person::SetName(const char* newName)
{//free previosly allocated memory

	if (newName != nullptr) {
		this->m_name = new char[strlen(newName) + 1];
		strcpy(this->m_name, newName);
	}

}
//-------------------------------------------------------------------------

void Person::SetId(int newId)
{
	this->m_id = newId;
}
//--------------------------------------------------------------------------
char* Person:: GetName() const {
	return this->m_name;
}
//--------------------------------------------------------------------------
int Person::GetId() const
{
	return this->m_id;
}
