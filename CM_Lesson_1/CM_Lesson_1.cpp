#include <iostream>
#include <tuple>
#include <optional>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// 1
// Создайте структуру Person с 3 полями: фамилия, имя, отчество.Поле отчество должно быть опционального типа, 
// т.к.не у всех людей есть отчество.Перегрузите оператор вывода данных для этой структуры.
// Также перегрузите операторы < и == (используйте tie).

struct Person
{
	string lastName;
	string name;
	string middleName;
	friend ostream& operator << (ostream& out, const Person& person);
	friend bool operator <(const Person& person1, const Person& person2);
	friend bool operator ==(const Person& person1, const Person& person2);
};

ostream& operator << (ostream& out, const Person& person)
{
	out << setw(11) << person.lastName << " " << setw(10) << person.name << " " << setw(14) << person.middleName;
	return out;
}

bool operator <(const Person& person1, const Person& person2)
{
	return tie(person1.lastName, person1.name, person1.middleName) < tie(person2.lastName, person2.name, person2.middleName);
}

bool operator ==(const Person& person1, const Person& person2)
{
	return !(person1 < person2) && !(person2 < person1);
}



void task_1()
{
	Person person1 = { "Ivanov", "Ivan", "Ivanovich" };
	Person person2 = { "Petrov", "Petr", "Petrovich" };
	Person person3 = { "Vasilyev", "Vasiliy", "Vasilyevich" };
	Person person4 = { "Ivanov", "Ivan", "Ivanovich" };

	cout << person1 << endl;
	cout << person2 << endl;
	cout << person3 << endl;
	cout << boolalpha << (person3 < person2) << endl;
	cout << boolalpha << (person3 == person2) << endl;
	cout << boolalpha << (person1 == person4) << endl;

}

// 2
// Создайте структуру PhoneNumber с 4 полями:
// ·         код страны(целое число)
// ·         код города(целое число)
// ·         номер(строка)
// ·         добавочный номер(целое число, опциональный тип)
// Для этой структуры перегрузите оператор вывода.
// Необходимо, чтобы номер телефона выводился в формате : +7(911)1234567 12, 
// где 7 – это номер страны, 911 – номер города, 1234567 – номер, 12 – добавочный номер.
// Если добавочного номера нет, то его выводить не надо.

struct PhoneNumber
{
	int countryCode;
	int townCode;
	string number;
	optional<int> additionalNumber;
	friend ostream& operator << (ostream& out, const PhoneNumber& pn);
};

ostream& operator << (ostream& out, const PhoneNumber& pn)
{
	out << "+" << pn.countryCode << "(" << pn.townCode << ")" << pn.number;

	if (pn.additionalNumber.has_value())
		out << " "  << pn.additionalNumber.value();
	return out;
}

bool operator <(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
	return tie(pn1.countryCode, pn1.townCode, pn1.number, pn1.additionalNumber) < tie(pn2.countryCode, pn2.townCode, pn2.number, pn2.additionalNumber);
}

void task_2()
{
	PhoneNumber pn1 = { 7, 495, "1234567", 24 };
	PhoneNumber pn2 = { 7, 499, "2223344"};
	cout << pn1 << endl;
	cout << pn2 << endl;
}

// 3
// Создайте класс PhoneBook, который будет в контейнере хранить пары : Человек – Номер телефона.
// Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.
// В теле конструктора происходит считывание данных из файла и заполнение контейнера.
// Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.
// 
// В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей 
// в алфавитном порядке.Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена будут одинаковы, 
// то сортировка производится по отчествам.Используйте алгоритмическую функцию sort.
// 
// Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов.
// Используйте алгоритмическую функцию sort.
// 
// Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber.
// Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке.
// Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», если было найдено 
// больше одного человека, то в строке должно быть «found more than 1».Для прохода по элементам контейнера используйте алгоритмическую функцию for_each.
// 
// Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, если находит заданного человека в контейнере, 
// то меняет его номер телефона на новый, иначе ничего не делает.Используйте алгоритмическую функцию find_if.
//





bool compareByName(pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) { return p1.first < p2.first; }
bool compareByPhone(pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) { return p1.second < p2.second; }
class PhoneBook
{
private:
	vector<pair<Person, PhoneNumber>> m_phoneBook;
	vector<string> splitStr(const string& str, char sep)
	{
		string substring = "";

		const size_t sz = str.size();
		size_t substrBeginPos = 0, substrEndPos = 0;
		size_t separatorLen = 0;

		vector<string> retVal;


		while (substrBeginPos < sz)
		{
			separatorLen = (substrBeginPos == 0) ? 0 : 1;
			substrEndPos = str.find(sep, substrBeginPos + separatorLen);
			substring = str.substr(substrBeginPos + separatorLen, substrEndPos - substrBeginPos - separatorLen);
			substrBeginPos = substrEndPos;
			retVal.push_back(substring);
		}

		return retVal;
	}
public:
	PhoneBook() {}
	PhoneBook(ifstream& ifs) 
	{
		Person p;
		PhoneNumber pn;
		char buf[500];
		vector<string> vec;
		string s = "";
		
		do
		{
			ifs.getline(buf, 500);
			s = string(buf);
			if (s != "")
			{
				vec = splitStr(s, ',');
				p.lastName = vec[0];
				p.name = vec[1];
				p.middleName = vec[2];
				pn.countryCode = stoi(vec[3]);
				pn.townCode = stoi(vec[4]);
				pn.number = vec[5];
				if (vec[6] != "")
					pn.additionalNumber = stoi(vec[6]);

				add(p, pn);
			}
		} while (ifs);
	}
	
	void sortByName()
	{
		sort(m_phoneBook.begin(), m_phoneBook.end(), compareByName);
	}
	void sortByPhone()
	{
		sort(m_phoneBook.begin(), m_phoneBook.end(), compareByPhone);
	}
	string getPhoneNumber(const string& lastName)
	{
		return "";
	}
	void changePhoneNumber(const Person& p, const PhoneNumber& pn)
	{

	}
	void add(const Person& p, const PhoneNumber& pn)
	{
		pair<const Person&, const PhoneNumber&> pp(p, pn);
		m_phoneBook.push_back(pp);
	}

	void print()
	{
		for (pair<Person, PhoneNumber> p : m_phoneBook)
		{
			cout << p.first << "\t" << p.second << endl;
		}
	}
};


void task_3()
{
	//Person person4 = { "Ivanov", "Ivan", "Ivanovich" };
	//Person person2 = { "Petrov", "Petr", "Petrovich" };
	//Person person1 = { "Vasilyev", "Vasiliy", "Vasilyevich" };
	//Person person3 = { "Ivanov", "Ivan", "Ivanovich" };
	//PhoneNumber pn1 = { 7, 495, "1234567", 24 };
	//PhoneNumber pn2 = { 7, 499, "2223344" };
	//PhoneNumber pn3 = { 7, 487, "2345566" };
	//PhoneNumber pn4 = { 7, 800, "5556600" };

	//PhoneBook pb;
	//pb.add(person1, pn1);
	//pb.add(person2, pn2);
	//pb.add(person3, pn3);
	//pb.add(person4, pn4);
	//pb.sortByName();
	//pb.print();
	//cout << "--------------------------" << endl;
	//pb.sortByPhone();
	//pb.print();
	ifstream file("Phonebook1.txt");
	PhoneBook pb(file);
	pb.print();
	cout << "------SortByPhone-------" << endl;
	pb.sortByPhone();
	pb.print();
	cout << "------SortByName-------" << endl;
	pb.sortByName();
	pb.print();

}




int main()
{
	//task_1();
	//task_2();
	task_3();
	//string s = "1,This,is,an,example,,";
	//vector<string> vec = splitStr(s, ',');

}
