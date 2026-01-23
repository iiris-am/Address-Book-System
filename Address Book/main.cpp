//--------------------------------------------------------------------------------------------------------------------------
//  File name: Address Book.cpp
//  Version 1.0
// Author: Maelys Azevedo
//  Date: 11-03-2025
//  Program purpose: This is an address book program that allows to search contacts by name or by department. (CS2B Assignment #3)
//   Date               Programmer                Description
//  11/03/25          Maelys Azevedo         Initial implementation
 //--------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Name {
private:
	string first_name;
	string last_name;
public:
	static const string DEFAULT_FIRST_NAME;
	static const string DEFAULT_LAST_NAME;
public:
	Name();
	Name(string first_name, string last_name);
	~Name();
	
	bool operator==(const Name& other) const;
	friend ostream& operator<<(ostream& os, const Name& p_name);
};

const string Name::DEFAULT_FIRST_NAME = "Maelys";
const string Name::DEFAULT_LAST_NAME = "Azevedo";

Name::Name(): first_name(Name::DEFAULT_FIRST_NAME), last_name(Name::DEFAULT_LAST_NAME){}
Name::Name(string first_name, string last_name) : first_name(first_name), last_name(last_name) {}
Name::~Name(){}

bool Name::operator==(const Name& other) const {
	return (first_name == other.first_name && last_name == other.last_name);
}

ostream& operator<<(ostream& os, const Name& p_name) {
	os << (p_name.first_name + " " + p_name.last_name);
	return os;
}



class Contact {
private:
	Contact* next;
protected:
	Name name;
	string phone;
	string email;
	int location;
public:
	static const string DEFAULT_PHONE;
	static const string DEFAULT_EMAIL;
	static const int DEFAULT_LOCATION;
public:
	Contact();
	Contact(const string& first_name, const string& last_name, const string& phone, const string& email, int location);
	virtual ~Contact();

	Name get_name() const;
	void set_name(Name name);
	string get_phone() const;
	void set_phone(string phone);
	string get_email() const;
	void set_email(string email);
	int get_location() const;
	void set_location(int location);
	Contact* get_next() const;
	void set_next(Contact* next);

	virtual void ShowContact() const = 0;

};

const string Contact::DEFAULT_PHONE = "1-999-999-9999";
const string Contact::DEFAULT_EMAIL = "defaultemail@company.com";
const int Contact::DEFAULT_LOCATION = 0;

Contact::Contact() : name("", ""), phone(Contact::DEFAULT_PHONE), email(Contact::DEFAULT_EMAIL), location(Contact::DEFAULT_LOCATION), next(nullptr){}
Contact::Contact(const string& first_name, const string& last_name, const string& phone, const string& email, int location) : name(first_name, last_name), phone(phone), email(email), location(location), next(nullptr) {}
Contact::~Contact() { cout << name << " has gone home..." << endl; }

Name Contact::get_name() const { return name; }
void Contact::set_name(Name name) { this->name = name; }
string Contact::get_phone() const { return phone; }
void Contact::set_phone(string phone) { this->phone = phone; }
string Contact::get_email() const { return email; }
void Contact::set_email(string email) { this->email = email; }
int Contact::get_location() const { return location; }
void Contact::set_location(int location) { this->location = location; }
Contact* Contact::get_next() const { return next; }
void Contact::set_next(Contact* next) { this->next = next; }



class EmployeeContact : public Contact {
private:
	string title;
	string department;
public:
	static const string DEFAULT_TITLE;
	static const string DEFAULT_DEPARTMENT;
public:
	EmployeeContact();
	EmployeeContact(const string& first, const string& last, const string& phone, const string& email, int location, const string& title, const string& department);
	virtual ~EmployeeContact();

	string get_title() const;
	void set_title(string title);
	string get_department() const;
	void set_department(string department);

	virtual void ShowContact() const;
};

const string EmployeeContact::DEFAULT_TITLE = "No Role";
const string EmployeeContact::DEFAULT_DEPARTMENT = "No Department";

EmployeeContact::EmployeeContact(): Contact(), title(EmployeeContact::DEFAULT_TITLE), department(EmployeeContact::DEFAULT_DEPARTMENT) {}
EmployeeContact::EmployeeContact(const string& first, const string& last, const string& phone, const string& email, int location, const string& title, const string& department) : Contact(first, last, phone, email, location), title(title), department(department) {}
EmployeeContact::~EmployeeContact(){}

string EmployeeContact::get_title() const { return title; }
void EmployeeContact::set_title(string title) { this->title = title; }
string EmployeeContact::get_department() const { return department; }
void EmployeeContact::set_department(string department) { this->department = department; }

void EmployeeContact::ShowContact() const {
	cout << left << setw(18) << name << "\t" << setw(25) << title << setw(20) << department << "Room: " << setw(6) << location << " " << setw(16) << phone << " " << email << endl;
}



class ContractorContact: public Contact {
private:
	string company;
	int months_duration;
public:
	static const string DEFAULT_COMPANY;
	static const int DEFAULT_MONTHS_DURATION;
public:
	ContractorContact();
	ContractorContact(const string& first, const string& last, const string& phone, const string& email, int location, const string& company, int months_duration);	
	virtual ~ContractorContact();

	string get_company() const;
	void set_company(string company);
	int get_months_duration() const;
	void set_months_duration(int months_duration);

	virtual void ShowContact() const;
};

const string ContractorContact::DEFAULT_COMPANY = "No Company";
const int ContractorContact::DEFAULT_MONTHS_DURATION = 0;

ContractorContact::ContractorContact() : Contact(), company(ContractorContact::DEFAULT_COMPANY), months_duration(ContractorContact::DEFAULT_MONTHS_DURATION) {}
ContractorContact::ContractorContact(const string& first, const string& last, const string& phone, const string& email, int location, const string& company, int months) : Contact(first, last, phone, email, location), company(company), months_duration(months) {}
ContractorContact::~ContractorContact() {}

string ContractorContact::get_company() const { return company; }
void ContractorContact::set_company(string company) { this->company = company; }
int ContractorContact::get_months_duration() const { return months_duration; }
void ContractorContact::set_months_duration(int months_duration) { this->months_duration = months_duration; }

void ContractorContact::ShowContact() const {
	cout << left << setw(18) << name << "\t" << setw(25) << (to_string(months_duration) + " months (contractor)") << setw(20) << company << "Room " << setw(6) << location << " " << setw(16) << phone << " " << email << endl;
}



class ContactList {
private:
	Contact* head;
public:
	ContactList();
	~ContactList();
private:
	Contact* FindContact(const Name& search_name) const;
	void Insert(Contact* new_contact);
public:
	void Init();
	void ShowAllContacts() const;
	void SearchByName(const Name& search_name) const;
	void SearchByDepartment(string target_department) const;
};

ContactList::ContactList() { head = nullptr; }
ContactList::~ContactList() {
	Contact* p_contact = head;
	while (p_contact != nullptr) {
		Contact* next = p_contact->get_next();
		delete p_contact;      
		p_contact = next;
	}
}

Contact* ContactList::FindContact(const Name& search_name) const {
	Contact* p_contact = head;

	while (p_contact != nullptr) {
		if (p_contact->get_name() == search_name){
			return p_contact;
		}
		p_contact = p_contact->get_next();
	}

	return nullptr;
}

void ContactList::Insert(Contact* p_new_contact) {
	p_new_contact->set_next(head);
	head = p_new_contact;
}

void ContactList::Init() { 

	Insert(new EmployeeContact("David", "Summer", "1-408-790-1682", "davids@tpcommuniations", 23, "Software Engineer", "Engineering"));

	Insert(new EmployeeContact("Jennifer", "Hans", "1-408-790-2381", "jenniferh@tpcommuniations", 17, "HR Representative", "Human Resources"));

	Insert(new ContractorContact("Cindy", "Morgan", "1-408-790-3953", "cindym@tpcommuniations", 43, "Other Company", 12));
	
	Insert(new EmployeeContact("Aljona", "Reyno", "1-408-790-4821", "aljonar@tpcommuniations", 1, "Mechanical Engineer", "Engineering"));

	Insert(new EmployeeContact("Gillian", "Mojica", "1-408-790-5932", "gillianm@tpcommuniations", 2, "Application Engineer", "Engineering"));

	Insert(new EmployeeContact("Alyssa", "Morgia", "1-408-790-6634", "alyssam@tpcommuniations", 3, "Manager", "Finance"));

	Insert(new EmployeeContact("Melody", "Lopez", "1-408-790-7135", "melodyl@tpcommuniations", 4, "Product Support Engineer", "Customer Support"));

	Insert(new EmployeeContact("Neil", "Kaci", "1-408-790-8291", "neilk@tpcommuniations", 5, "Test Technician", "Engineering"));

	Insert(new EmployeeContact("Katherine", "Lin", "1-408-790-9322", "katherinel@tpcommuniations", 6, "Business Analyst", "Finance"));

	Insert(new EmployeeContact("Achille", "Dannemard", "1-408-790-1933", "achilled@tpcommuniations", 7, "Admin Assistant", "Human Resources"));

	Insert(new EmployeeContact("Adam", "Couhert", "1-408-790-4829", "adamc@tpcommuniations", 8, "Manufacturing Engineer", "Manufacturer"));

	Insert(new EmployeeContact("Ryan", "Evans", "1-408-790-4012", "ryane@tpcommuniations", 9, "Hardware Engineer", "Engineering"));
	
	Insert(new EmployeeContact("Sheryl", "Lee Ralph", "1-408-790-2389", "sheryllr@tpcommuniations", 27, "IT Technical Support", "IT"));

	Insert(new EmployeeContact("Michelle", "Yeoh", "1-408-790-5402", "michelley@tpcommuniations", 55, "Director", "Marketing"));

	Insert(new EmployeeContact("Rachel", "Keen", "1-408-790-1139", "rachelk@tpcommuniations", 29, "Marketing Analyst", "Marketing"));

	Insert(new ContractorContact("Jennifer", "Coolidge", "1-408-790-7783", "jenniferc@tpcommuniations", 60, "Yet Another Company", 18));

	Insert(new ContractorContact("Mila", "Kunis", "1-408-790-6628", "milak@tpcommuniations", 33, "Random Company", 6));

}

void ContactList::ShowAllContacts() const {
	Contact* p_contact = head;

	while (p_contact != nullptr) {
		p_contact->ShowContact();
		p_contact = p_contact->get_next();
	}
}

void ContactList:: SearchByName(const Name& search_name) const {
	Contact* p_contact = FindContact(search_name);

	if (p_contact != nullptr) {
		p_contact->ShowContact();
	}
	else {
		cout << "ERROR: Could not find a contact with a matching name!" << endl;
	}
}

void ContactList::SearchByDepartment(string target_department) const {
	Contact* p_contact = head;
	bool found_any = false;

	while (p_contact != nullptr) {
		EmployeeContact* p_employee = dynamic_cast<EmployeeContact*>(p_contact);

		if (p_employee != nullptr && p_employee->get_department() == target_department) {
			p_employee->ShowContact();
			found_any = true;
		}
		
		p_contact = p_contact->get_next();
	}

	if (!found_any) {
		cout << "ERROR: No employees found in department: " << target_department << endl;
	}
}



class AddressBook {
private:
	string company_name;
	ContactList contact_list;
public:
	static const string DEFAULT_COMPANY_NAME;
public:
	AddressBook();
	AddressBook(string company_name);
	~AddressBook();

	void Init();
	void Run();
private:
	void Menu() const;
	int GetUserOption() const;
	void ShowAllContacts() const;
	void SearchByName() const;
	void SearchByDepartment() const;
	void Quit() const;
};

const string AddressBook::DEFAULT_COMPANY_NAME = "No Company Name";

AddressBook::AddressBook() : company_name(AddressBook::DEFAULT_COMPANY_NAME) {}
AddressBook::AddressBook(string company_name): company_name(company_name) {}
AddressBook::~AddressBook(){}

void AddressBook::Init() {
	contact_list.Init();
}

void AddressBook::Run() {
	int option;
	do {
		Menu();
		option = GetUserOption();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		switch (option) {
		case 1:
			ShowAllContacts();
			break;
		case 2:
			SearchByName();
			break;
		case 3:
			SearchByDepartment();
			break;
		case 4:
			Quit();
			break;
		default:
			cout << "Invalid option. Please select 1-4." << endl;
		}
		cout << endl;
	} while (option != 4);
}

void AddressBook::Menu() const {
	cout << company_name << " Address Book Menu" << endl;
	cout << "1. View all contacts\n2. Search by name\n3. Search by department\n4. Quit" << endl;
}

int AddressBook::GetUserOption() const {
	cout << "Select an option (1-4): ";
	int user_input = -1;
	cin >> user_input;

	return user_input;
}

void AddressBook::ShowAllContacts() const {
	contact_list.ShowAllContacts();
}


void AddressBook::SearchByName() const{
	string first;
	string last;

	cout << "Enter first name: ";
	cin >> first;
	cout << "Enter last name: ";
	cin >> last;

	Name search(first, last);
	contact_list.SearchByName(search);
}

void AddressBook::SearchByDepartment() const {
	string department;
	cout << "Enter a department: ";
	getline(cin, department);
	if (department.empty()) getline(cin, department);
	contact_list.SearchByDepartment(department);
}

void AddressBook::Quit() const {
	cout << "Thanks for using our AddressBook. See you again!" << endl;
}



int main() {
	AddressBook* p_book = new AddressBook("TP Communications");
	p_book->Init();
	p_book->Run();
	delete p_book;

	return -1;
}