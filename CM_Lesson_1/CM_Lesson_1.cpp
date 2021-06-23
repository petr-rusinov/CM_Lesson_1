#include <iostream>
#include <tuple>
#include <optional>

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
	out << person.lastName << " " << person.name << " " << person.middleName;
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



int main()
{
	task_1();
	task_2();
}
