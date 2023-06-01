#include "General.h"

Subject::Subject() {};

Subject::Subject(string code, string name, float hourly_pay_rate) {
	this->code = code;
	this->name = name;
	this->hourly_pay_rate = hourly_pay_rate;
	this->next = NULL;
}

void Subject::printCodeName(int index) {
	cout << index << ". \t" << this->code << "\t" << this->name << endl;
}

void Subject::printCodeNamePay(int index) {
	cout << index << ". \t" << this->code << "\t" << this->name << "\t" << this->hourly_pay_rate << endl;
}


void Subject::displaySubjects(int indexStart, bool withPayRate) {
	system("CLS");

	struct Subject* node = this;

	if (this == NULL) return;

	while (indexStart - 1 < 5) {
		if (withPayRate) {
			node[indexStart - 1].printCodeNamePay(indexStart);
		}
		else {
			node[indexStart - 1].printCodeName(indexStart);
		}

		indexStart++;
	}

}

string Subject::getInfo() {
	return (this->name + "(" + this->code + ")");
}

struct Subject** Subject::searchByIndex(int index) {
	struct Subject* node = this;
	struct Subject* result = NULL;

	if (this == NULL) return &result;
	if (index - 1 < 0 || index - 1 >= 5) return &result;

	result = &node[index - 1];

	return &result;
}

struct Subject** Subject::searchByCode(string code) {
	struct Subject* node = this;
	struct Subject* result = NULL;

	if (node == NULL) return &result;

	int count = 0;
	while (count < 5) {
		if (node[count].code == code) {
			result = &node[count];
			return &result;
		}

		count++;
	}

	return &result;
}

//Free up memory
void Subject::deleteSubjectList()
{
	if (this == NULL) return;

	Subject* node = this;

	delete[5] node;
}

//External functions
void DisplayAllSubjects() {
	system("CLS");

	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);

	if (subjectList == NULL) return;

	cout << "All Subjects:" << endl;
	subjectList->displaySubjects(1, true);

	cout << endl;

	//free up memory
	subjectList->deleteSubjectList();

}

void RetrieveSubjects(struct Subject** head) {
	ifstream inData;
	inData.open("Subject.txt");

	struct Subject* node = *head;

	string code, name, str_hourly_pay_rate;
	int count = 0;

	while ((inData >> code >> name >> str_hourly_pay_rate) && count < 5) {

		float hourly_pay_rate = stof(str_hourly_pay_rate);

		struct Subject inpSubject = Subject(code, name, hourly_pay_rate);

		node[count] = inpSubject;
		count++;

	}
}
