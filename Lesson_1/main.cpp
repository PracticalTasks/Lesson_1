#include"header.h"

using namespace std;

int main()
{
	//Task 1
	cout << "Task 1\n";
	Person person;
	Person person2;
	person.firstName = "Donald";
	person.surName = "McDonald";
	person.middleName = "Albertovich";
	cout << person << endl;
	person2.firstName = "Jack";
	person2.surName = "Black";
	cout << person2<<endl;
	cout << boolalpha<<(person < person2)<<endl;

	//Task 2
	cout << "\nTask 2\n";
	PhoneNumber number;
	number.countryCode = 7;
	number.cityCode = 911;
	number.number = "1234567";
	number.additionalNumber = 12;
	cout << number;

	//Task 3
	cout << "\nTask3\n";
	ifstream file("PhoneBook.txt");
	if (!file)
	{
		std::cout << "File is not found\n";
		return 0;
	}
		
	PhoneBook book(file);
	cout << "----------Sort by phone----------" << endl;
	book.SortByPhone();
	cout << book;

	cout << "----------Sort by name----------" << endl;
	book.SortByName();
	cout << book;

	cout << "----------Get phone number----------" << endl;
	auto printPhoneNumber = [&book](const string & surname)
	{
		cout << surname << '\t';
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			cout << get<1>(answer);
		else if (get<0>(answer) == "found more than 1")
			cout << get<0>(answer);
		else
			cout << get<0>(answer);
	};
	printPhoneNumber("Mironova");
	printPhoneNumber("Solovev");

	cout << "\n----------Change phone number----------" << endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;


}