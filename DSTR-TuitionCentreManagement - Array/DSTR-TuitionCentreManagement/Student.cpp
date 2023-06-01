#include "General.h"

Student::Student() {}

Student::Student(int id, string firstname, string lastname, string username, string password, string contact) {
	this->id = id;
	this->firstname = firstname;
	this->lastname = lastname;
	this->username = username;
	this->password = password;
	this->contact = contact;
	this->next = NULL;
}


void Student::displayStudents(int size) {

	if (size == 0) return;

	struct Student* node = this;
	int count = 0;

	while (count != size) {
		node[count].printInfo();
		count++;
	}

	cout << endl;
}


void Student::printInfo() {
	cout << this->id << "\t" << this->firstname << " " << this->lastname << " (" << this->username << ")" << endl;

}

struct Student** Student::searchByUsername(string username, int size) {
	struct Student* node = this;
	struct Student* result = NULL;

	if (node == NULL || size == 0) return &result;

	int count = 0;

	while (count < size) {
		if (node[count].username == username) {
			result = &node[count];
			return &result;
		}

		count++;
	}

	return &result;
}

struct Student** Student::retrieveById(int id, int size) {
	struct Student* node = this;
	struct Student* result = NULL;

	if (node == NULL || size == 0) return &result;

	int count = 0;

	while (count < size) {
		if (node[count].id == id) {
			result = &node[count];
			return &result;
		}

		count++;
	}
	return &result;
}

bool Student::passwordComparison(string pw) {
	return password == pw;
}

string Student::getFullName() {
	string fullName = this->firstname + " " + this->lastname;
	return fullName;
}

int Student::getId() {
	return this->id;
}

//External Functions (Not in Struct)
class StudentDArray** RetrieveStudents() {
	StudentDArray* studArr = new StudentDArray(1);

	ifstream inData;
	inData.open("Students.txt");

	int id;
	string strid, firstname, lastname, username, contact, password;
	int count = 0;

	while (inData >> strid >> firstname >> lastname >> username >> password >> contact) {
		id = stoi(strid);

		struct Student inpStudent = Student(id, firstname, lastname, username, password, contact);

		if (count >= studArr->size) {
			studArr->increaseSize(1);
			struct StudentDArray* newArray = new StudentDArray(*studArr);
			studArr->~StudentDArray();
			studArr = newArray;
		}
	
		studArr->data[count] = inpStudent;

		count++;

	}

	return &studArr;
}

//remove not delete node [dynamic]
void RemoveStudentFromList(struct Student** head, int id) {
	struct Student* toDelete = *head;
	struct Student* prev_node = NULL;
	struct Student* next_node = NULL;

	if (*head == NULL) return;

	while (toDelete != NULL) {
		if (toDelete->getId() != id) {
			prev_node = toDelete;
			toDelete = toDelete->next;
			continue;
		}

		//delete current node
		next_node = toDelete->next;
		if (prev_node != NULL) {
			prev_node->next = next_node;
		}
		else {
			*head = next_node;
		}
		toDelete = next_node;
	}
}



