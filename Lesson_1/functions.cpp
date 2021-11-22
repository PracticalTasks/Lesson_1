#include"header.h"

std::ostream& operator<<(std::ostream& out, Person& person)
{
	out <<std::setw(18)<<person.surName << std::setw(18) << person.firstName;
	if (person.middleName)
		out << std::setw(18) << *person.middleName;
	else
		out << std::setw(18)<<' ';
	return out;
}

bool operator<(const Person& person1, const Person& person2)
{
	return std::tie(person1.surName, person1.firstName, person1.middleName) <
		std::tie(person2.surName, person2.firstName, person2.middleName);
}

bool operator==(const Person& person1, const Person& person2)
{
	return std::tie(person1.surName, person1.firstName, person1.middleName) ==
		std::tie(person2.surName, person2.firstName, person2.middleName);
}

std::ostream& operator<<(std::ostream& out, PhoneNumber number)
{
	out <<std::setw(10)<<'+'<< number.countryCode << '(' << number.cityCode << ')' <<
		number.number;
	if (number.additionalNumber)
		out << ' ' << *number.additionalNumber << std::endl;
	else
		out << std::endl;
	return out;
}

bool operator<(const PhoneNumber& number1, const PhoneNumber& number2)
{
	return std::tie(number1.countryCode, number1.countryCode, number1.number, number1.additionalNumber) <
		std::tie(number2.countryCode, number2.countryCode, number2.number, number2.additionalNumber);
}

bool operator==(const PhoneNumber& number1, const PhoneNumber& number2)
{
	return std::tie(number1.countryCode, number1.countryCode, number1.number, number1.additionalNumber) ==
		std::tie(number2.countryCode, number2.countryCode, number2.number, number2.additionalNumber);
}

void PhoneNumber::clean()
{
	countryCode = 0;
	cityCode = 0;
	number = "";
	additionalNumber = std::nullopt;
}

int charToInt(std::string& str)
{
	int factor{ 1 };
	for (int i{}; i < str.size() - 1; ++i)
		factor *= 10;

	int val{ 0 };
	for(int i{};i<str.size();++i)
	{
		val += static_cast<int>(str[i] - '0') * factor;
		factor /= 10;
	}
	return val;
}

PhoneBook::PhoneBook(std::ifstream& file)
{	
	std::string str;
	Person person;
	PhoneNumber number;
	while (!file.eof())
	{
		file >> str;
		if (str[0] == '-')
			continue;

		person.surName = str;
		file >> person.firstName;
		file >> str;
		if (str[0] != '-')
			person.middleName = str;
		else
			person.middleName = std::nullopt;
		
		file >> str;
		number.countryCode = charToInt(str);
		file >> str;
		number.cityCode = charToInt(str);
		file >> str;
		number.number = str;
		file >> str;
		if (str[0] != '-')
			number.additionalNumber = charToInt(str);
		else
			number.additionalNumber = std::nullopt;
			
			

		std::pair pair1(person, number);
		vect.push_back(pair1);
	}
}

std::ostream& operator<<(std::ostream& out, PhoneBook& phoneBook)
{
	for (auto& [person, number] : phoneBook.vect)
	{
		out << person << number;
	}

	return out;
}

void PhoneBook::SortByName()
{
	std::sort(vect.begin(), vect.end(), [](std::pair<Person, PhoneNumber> pair1, std::pair<Person, PhoneNumber> pair2)
		{	return std::tie(pair1.first.surName, pair1.first.firstName, pair1.first.middleName) <
				std::tie(pair2.first.surName, pair2.first.firstName, pair2.first.middleName);});	
}

void PhoneBook::SortByPhone()
{
	std::sort(vect.begin(), vect.end(), [](std::pair<Person, PhoneNumber> pair1, std::pair<Person, PhoneNumber> pair2)
		{	return std::tie(pair1.second.countryCode, pair1.second.countryCode, pair1.second.number,pair1.second.additionalNumber) <
		std::tie(pair2.second.countryCode, pair2.second.countryCode, pair2.second.number, pair2.second.additionalNumber); });
}

std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(std::string name)
{
	int count{};
	PhoneNumber number;
	for (auto& [surname, phoneNumber] : vect)
	{
		if (surname.surName == name)
		{
			++count;
			number = phoneNumber;
		}
			
	}

	if (count == 1)
		return std::tie("", number);
	else if (count > 1)
	{
		number.clean();
		return std::tie("found more than 1", number);
	}	
	else
	{
		number.clean();
		return std::tie("not found", number);
	}
		
}

void PhoneBook::ChangePhoneNumber(Person personFind, PhoneNumber number)
{
	for (auto& [person, phoneNumber] : vect)
	{
		if (std::tie(person.surName,person.firstName,person.middleName) == 
			std::tie(personFind.surName,personFind.firstName,personFind.middleName))
		{
			phoneNumber = number;
		}
	}
}
