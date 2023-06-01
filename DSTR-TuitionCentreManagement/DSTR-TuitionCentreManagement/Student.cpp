#include "General.h"

Student::Student() {};

Student::Student(int id, string firstname, string lastname, string username, string password, string contact) {
	this->id = id;
	this->firstname = firstname;
	this->lastname = lastname;
	this->username = username;
	this->password = password;
	this->contact = contact;
	this->next = NULL;
}

void Student::displayStudents() {
	//struct Student* node = *head;

	if (this == NULL) return;

	struct Student* node = this;

	while (node != NULL) {
		node->printInfo();
		node = node->next;
	}
}

void Student::printFile() {

	struct Student* node = this;

	if (node == NULL) {
		return;
	}

	ofstream outData;
	outData.open("Students.txt");

	while (node != NULL) {
		outData << node->id << "\t" << node->firstname << "\t" << node->lastname << "\t" << node->username << "\t" << node->password << "\t" << node->contact << endl;
		node = node->next;
	}

}

void Student::printInfo() {
	cout << this->id << "\t" << this->firstname << " " << this->lastname << " (" << this->username << ")" << endl;

}

struct Student** Student::searchByUsername(string username) {
	struct Student* node = this;
	struct Student** result = NULL;

	if (node == NULL) return result;

	while (node != NULL) {
		if (node->username == username) {
			result = &node;
			return result;
		}
		else {
			node = node->next;
		}
	}

	return result;
}

struct Student** Student::retrieveById(int id) {
	struct Student* node = this;
	struct Student** result = NULL;

	if (node == NULL) return result;

	while (node != NULL) {
		if (node->id == id) {
			result = &node;
			return result;
		}
		else {
			node = node->next;
		}
	}

	return result;
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

void Student::deleteStudentList() {

	if (this == NULL) {
		return;
	}

	Student* current = this;
	Student* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

//External Functions (Not in Struct)
//void AddStudent(struct Student** head, struct Student* newStudent) {
//	struct Student* node = *head;
//
//	if (*head == NULL) {
//		*head = newStudent;
//	}
//	else {
//		while (node->next != NULL) {
//			node = node->next;
//		}
//
//		node->next = newStudent;
//	}
//}
//
void RetrieveStudents(struct Student** head) {
	ifstream inData;
	inData.open("Students.txt");

	struct Student* node = *head;

	int id;
	string strid, firstname, lastname, username, contact, password;

	while (inData >> strid >> firstname >> lastname >> username >> password >> contact) {
		id = stoi(strid);
		struct Student* inpStudent = new Student(id, firstname, lastname, username, password, contact);

		if (*head == NULL) {
			*head = inpStudent;
			node = *head;
		}
		else {
			node->next = inpStudent;
			node = node->next;

		}

	}

}

void AddStudentToLast(struct Student** head, struct Student* newStudent) {
	struct Student* node = *head;

	if (node == NULL) {
		*head = newStudent;
	}
	else {
		while (node->next != NULL) {
			node = node->next;
		}

		node->next = newStudent;
	}

}

//remove not delete node
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



