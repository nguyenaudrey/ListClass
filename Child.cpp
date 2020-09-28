/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #3: Child
* Description: This is the cpp file for the Child class
*/

#include "Child.h"

// Default Constructor
Child::Child()
{
	firstname = "UNKNOWN FIRST";
	lastname = "UNKNOWN LAST";
	age = 0;
}

// Constructor
// Accepts 2 strings representing first name and last name 
// Accepts an int representing age
Child::Child(string fn, string ln, int age)
{
	firstname = fn;
	lastname = ln;
	this->age = age;
}

// Deconstructor
Child::~Child()
{
	firstname = "";
	lastname = "";
	age = 0;
}

bool Child::setData(string fn, string ln, int age)
{
	firstname = fn;
	lastname = ln;
	this->age = age;
	return true;
}

// Checks if less than 
bool Child::operator<(const Child& kid) const
{
	if (lastname < kid.lastname)
	{
		return true;
	}
	else if (lastname == kid.lastname) {
		if (firstname < kid.firstname)
		{
			return true;
		}
		else if (firstname == kid.firstname)
		{
			if (age < kid.age)
			{
				return true;
			}
		}
	}
	return false;
}

// Checks if greater than
bool Child::operator>(const Child& kid) const
{
	if (!(*this < kid) && !(*this == kid))
	{
		return true;
	}
	return false;
}

// Checks if less or equal to
bool Child::operator<=(const Child& kid) const
{
	if ((*this < kid) || (*this == kid))
	{
		return true;
	}
	return false;
}

// Checks if greater than or equal to
bool Child::operator>=(const Child& kid) const
{
	if ((*this > kid) || (*this == kid))
	{
		return true;
	}
	return false;
}

// Checks for equality
bool Child::operator==(const Child& kid) const
{
	if ((firstname == kid.firstname) && (lastname == kid.lastname) && (age == kid.age))
	{
		return true;
	}
	return false;
}

// Checks for inequality
bool Child::operator!=(const Child& kid) const
{
	return !(*this == kid);
}

// Assignment overload operator
Child& Child::operator = (const Child& kid)
{
	firstname = kid.firstname;
	lastname = kid.lastname;
	this->age = kid.age;
	return *this;
}

// Prints out the name and age of the child
ostream& operator<<(ostream& outStream, const Child& kid)
{
	outStream << kid.firstname << kid.lastname << kid.age;
	return outStream;
}

// Reads in the name and age of the child
istream& operator>>(istream& inStream, Child& kid)
{
	string fn;
	string ln;
	int age;
	inStream >> fn >> ln >> age;
	kid.setData(fn, ln, age);
	return inStream;
}