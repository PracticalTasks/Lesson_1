#pragma once
#include<iostream>
#include<string>
#include<optional>
#include<tuple>
#include<vector>
#include<fstream>
#include<iomanip>
#include<algorithm>

//Task 1
struct Person
{
	std::string surName;
	std::string firstName;
	std::optional<std::string> middleName;

	friend std::ostream& operator<<(std::ostream& out, Person& person);
	friend bool operator<(const Person& person1, const Person& person2);
	friend bool operator==(const Person& person1, const Person& person2);
};

//Task 2
struct PhoneNumber
{
	int countryCode;
	int cityCode;
	std::string number;
	std::optional<int> additionalNumber;

	friend std::ostream& operator<<(std::ostream& out, PhoneNumber number);
	friend bool operator<(const PhoneNumber& number1, const PhoneNumber& number2);
	friend bool operator==(const PhoneNumber& number1, const PhoneNumber& number2);
	void clean();
};

//Task 3
class PhoneBook
{
public:
	std::vector<std::pair<Person, PhoneNumber> > vect;
	PhoneBook(std::ifstream& file);
	friend std::ostream& operator<<(std::ostream& out, PhoneBook& phoneBook);
	void SortByName();
	void SortByPhone();
	std::tuple<std::string, PhoneNumber> GetPhoneNumber(std::string name);
	void ChangePhoneNumber(Person person, PhoneNumber number);
};