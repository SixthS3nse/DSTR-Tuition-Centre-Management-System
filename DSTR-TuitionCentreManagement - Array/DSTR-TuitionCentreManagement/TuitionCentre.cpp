#include "General.h"

TuitionCentre::TuitionCentre() {};

TuitionCentre::TuitionCentre(string code, string name, string address, string password) {

	this->code = code;
	this->name = name;
	this->address = address;
	this->password = password;
	this->next = NULL;
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
	struct TuitionCentre* result = NULL;

	if (this == NULL) return &result;
	if (index - 1 < 0 || index-1 >= 3) return &result;

	result = &node[index-1];

	return &result;
}

struct TuitionCentre** TuitionCentre::searchByCode(string code) {
	struct TuitionCentre* node = this;
	struct TuitionCentre* result = NULL;

	if (node == NULL) return &result;

	int count = 0;
	while (count < 3) {
		if (node[count].code == code) {
			result = &node[count];
			return &result;
		}

		count++;
	}

	return &result;
}

bool TuitionCentre::passwordComparison(string pw) {
	return this->password == pw;
}

void TuitionCentre::displayTuitionCentres(int indexStart, bool withAddress) {
	system("CLS");

	struct TuitionCentre* node = this;

	if (node == NULL) return;

	while (indexStart - 1 < 3) {
		if (withAddress) {
			node[indexStart - 1].printCodeNameAddress(indexStart);
		}
		else {
			node[indexStart - 1].printCodeName(indexStart);
		}

		indexStart++;
	}


}

//Free up memory
void TuitionCentre::deleteTuitionCentreList()
{
	if (this == NULL) return;

	TuitionCentre* node = this;

	delete[3] node;
}

//External Functions (Not in Struct)
void DisplayAllTuitionCentres() {
	system("CLS");

	struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
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
	int count = 0;

	while ((inData >> code >> name >> address >> password) && count < 3) {

		struct TuitionCentre inpTuitionCentre = TuitionCentre(code, name, address, password);

		node[count] = inpTuitionCentre;
		count++;
	}
}
