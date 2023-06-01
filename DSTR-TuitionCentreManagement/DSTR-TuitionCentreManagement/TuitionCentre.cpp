#include "General.h"

TuitionCentre::TuitionCentre() {};

TuitionCentre::TuitionCentre(string code, string name, string address, string password) {

	this->code = code;
	this->name = name;
	this->address = address;
	this->password = password;
	this->next = NULL;
}

void TuitionCentre::printFile() {

	struct TuitionCentre* node = this;

	if (node == NULL) {
		return;
	}

	ofstream outData;
	outData.open("TuitionCentre.txt");

	while (node != NULL) {
		outData << node->code << "\t" << node->name << "\t" << node->address << "\t" << node->password << endl;
		node = node->next;
	}

}

void TuitionCentre::printCodeName(int index) {
	cout << index << ". \t" << this->code << "\t" << this->name << endl;

}

void TuitionCentre::printCodeNameAddress(int index) {
	cout << index << ". \t" << this->code << "\t" << this->name << "\t" << this->address << endl;

}

string TuitionCentre::getCodeName() {
	string codename = this->name + " (" + this->code + ")";
	return codename;
}

string TuitionCentre::getInfo() {
	return this->name + "(" + this->code + ") - " + this->address ;
}

struct TuitionCentre** TuitionCentre::searchByIndex(int index) {
	struct TuitionCentre* node = this;
	struct TuitionCentre** result = NULL;

	if (this == NULL) return result;

	while (index > 1) {
		node = node->next;
		index--;
	}

	result = &node;

	return result;
}

struct TuitionCentre** TuitionCentre::searchByCode(string code) {
	struct TuitionCentre* node = this;
	struct TuitionCentre** result = NULL;

	if (node == NULL) return result;

	while (node != NULL) {
		if (node->code == code) {
			result = &node;
			return result;
		}
		else {
			node = node->next;
		}
	}

	return result;
}

bool TuitionCentre::passwordComparison(string pw) {
	return this->password == pw;
}

void TuitionCentre::displayTuitionCentres(int indexStart, bool withAddress) {
	system("CLS");

	struct TuitionCentre* node = this;

	if (node == NULL) return;

	while (node != NULL) {
		if (withAddress) {
			node->printCodeNameAddress(indexStart);
		}
		else {
			node->printCodeName(indexStart);
		}
		node = node->next;
		indexStart++;
	}
}

//Free up memory
void TuitionCentre::deleteTuitionCentreList()
{
	if (this == NULL) return;

	TuitionCentre* current = this;
	TuitionCentre* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

//External Functions (Not in Struct)
void DisplayAllTuitionCentres() {
	system("CLS");

	struct TuitionCentre* tuitionCentreList = NULL;
	RetrieveTuitionCentres(&tuitionCentreList);

	if (tuitionCentreList == NULL) return;

	cout << "All Tuition Centre:" << endl;
	tuitionCentreList->displayTuitionCentres(1, true);

	cout << endl;

	//free up memory
	tuitionCentreList->deleteTuitionCentreList();

}

void RetrieveTuitionCentres(struct TuitionCentre** head) {
	ifstream inData;
	inData.open("TuitionCentre.txt");

	struct TuitionCentre* node = *head;

	string code, name, address, password;

	while (inData >> code >> name >> address >> password) {

		struct TuitionCentre* inpTuitionCentre = new TuitionCentre(code, name, address, password);

		if (*head == NULL) {
			*head = inpTuitionCentre;
			node = *head;
		}
		else {
			node->next = inpTuitionCentre;
			node = node->next;

		}
	}
}
