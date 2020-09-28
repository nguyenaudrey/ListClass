/*
* Student: Audrey Nguyen
* Professor: Robert Dimpsey
* Assignment #3: Child
* Description: This is the h file for the Child class
*/

#ifndef CHILD_H
#define CHILD_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Child
{
public:
	// Default Constructor
	Child();

	// Constructor which accepts parameters
	Child(string fn, string ln, int age);

	// Deconstructor
	~Child();

	// Sets the data
	bool setData(string fn, string ln, int age);

	// Checks if less than 
	bool operator<(const Child& kid) const;

	// Checks if greater than
	bool operator>(const Child& kid) const;

	// Checks if greater than or equal to
	bool operator>=(const Child& kid) const;

	// Checks if less than or equal to
	bool operator<=(const Child& kid) const;

	// Checks for equality
	bool operator==(const Child& kid) const;

	// Checks for inequality
	bool operator!=(const Child& kid) const;

	// Assignment overload operator
	Child& operator = (const Child&);

	// Prints out the child
	friend ostream& operator<<(ostream& outStream, const Child& kid);

	//Reads in a child
	friend istream& operator>>(istream& inStream, Child& kid);

private:
	string firstname;
	string lastname;
	int age;
};

#endif