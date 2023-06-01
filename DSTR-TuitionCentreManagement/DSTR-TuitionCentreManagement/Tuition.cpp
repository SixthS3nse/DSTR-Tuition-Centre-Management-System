#include "General.h"

Tuition::Tuition() {};

Tuition::Tuition(int id, int tutor_id, int hour, string date) {

	this->id = id;
	this->tutor_id = tutor_id;
	this->hour = hour;
	this->date = date;
	this->next = NULL;
}

bool Tuition::printFile() {

	struct Tuition* node = this;

	if (node == NULL) {
		return false;
	}

	ofstream outData;
	outData.open("Tuition.txt");

	while (node != NULL) {
		outData << node->id << "\t" << node->tutor_id << "\t" << node->hour << "\t" << node->date << endl;
		node = node->next;
	}

	return true;

}

//generate id based on last record
int Tuition::generateId() {
	int current = 1;

	struct Tuition* node = this;

	if (this == NULL) return current;

	while (node != NULL) {

		if (node->id > current) {
			current = node->id;
		}

		node = node->next;
	}

	return current + 1;
}

//get info
string Tuition::getInfo() {
	string result = to_string(this->id) + "\t\t" + this->date;
	return result;
}

//retrieve by id
struct Tuition** Tuition::retrieveById(int id) {
	struct Tuition* node = this;
	struct Tuition** result = NULL;

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

//Free up memory
void Tuition::deleteTuitionList()
{
	if (this == NULL) return;

	Tuition* current = this;
	Tuition* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

//External Functions (Not in Struct)
void RetrieveTuitions(struct Tuition** head) {
	ifstream inData;
	inData.open("Tuition.txt");

	struct Tuition* node = *head;

	int id, tutor_id, hour;
	string str_id, str_tutor_id, str_hour, date;

	while (inData >> str_id >> str_tutor_id >> str_hour >> date) {

		id = stoi(str_id);
		tutor_id = stoi(str_tutor_id);
		hour = stoi(str_hour);

		struct Tuition* input = new Tuition(id, tutor_id, hour, date);

		if (*head == NULL) {
			*head = input;
			node = *head;
		}
		else {
			node->next = input;
			node = node->next;

		}
	}
}

void AddTuition() {

	//tuition centre check
	if (getTuitionCentreCode() == "") {
		setRole("");
		Login();
		return;
	}

	//select tutors
	//-retrieve tutors-
	struct Tutor* tutorList = NULL;
	RetrieveTutors(&tutorList);
	FilterTutorByTermination(&tutorList, false);
	FilterTutorByTuitionCentre(&tutorList, getTuitionCentreCode());

	string str_tutor_id;
	int tutor_id = -1;

	tutorList->displayTutors(true);

	cout << "Enter a tutor ID to edit: ";
	cin >> str_tutor_id;

	try {
		tutor_id = stoi(str_tutor_id);
	}
	catch (exception) {
		tutorList->deleteTutorList();
		system("CLS");
		cout << "Invalid Input" << endl << endl;
		return;
	}


	//availability check
	struct Tutor** tutorPtr = tutorList->retrieveById(tutor_id);

	if (*tutorPtr == NULL) {
		tutorList->deleteTutorList();
		system("CLS");
		cout << "Tutor not found / terminated!" << endl;
		return;
	}

	tutor_id = (*tutorPtr)->getId();

	//free up tutorList
	tutorList->deleteTutorList();

	//request hours
	string str_hour;
	int hour = -1;

	cout << "Enter number of hours of tuition: ";
	cin >> str_hour;

	try {
		hour = stoi(str_hour);
	}
	catch (exception) {
		system("CLS");
		cout << "Invalid Input!" << endl << endl;
		return;
	}

	//get students
	//-retrieve students-
	struct Student* studentList = NULL;
	RetrieveStudents(&studentList);

	if (studentList == NULL) {
		system("CLS");
		cout << "Error in retriving student." << endl << endl;
		return;
	}

	//-request students-
	string str_student_id;
	int student_id = -1;
	struct Student* selectedStudents = NULL;

	studentList->displayStudents();

	while (student_id != 0){
		cout << "Enter a student ID to add or 0 to stop adding: ";
		cin >> str_student_id;

		try {
			student_id = stoi(str_student_id);
		}
		catch (exception) {
			cout << "Invalid Input!" << endl << endl;
			continue;
		}

		if (student_id == 0) continue;

		//-retrival-
		struct Student** studentPtr = studentList->retrieveById(student_id);

		if (*studentPtr == NULL) {
			cout << "Invalid Input!" << endl << endl;
			continue;
		}

		struct Student *toAdd = *studentPtr;
		RemoveStudentFromList(&studentList, student_id);
		toAdd->next = NULL;
		AddStudentToLast(&selectedStudents, toAdd);

	} 

	//-check any student added-
	if (selectedStudents == NULL) {
		system("CLS");
		cout << "No student added!" << endl;
		return;
	}

	//retrieve tuition list
	struct Tuition* tuitionList = NULL;
	RetrieveTuitions(&tuitionList);

	//get id
	int id = tuitionList->generateId();

	//get today date
	string now = date("/", NULL, NULL, NULL);

	//create new struct
	struct Tuition* newTuition = new Tuition(id, tutor_id, hour, now);

	//add to list
	AddTuitionToLast(&tuitionList, newTuition);

	system("CLS");

	//write to file
	if (tuitionList->printFile()) {
		cout << "Tuition is added!" << endl;
	}
	else {
		cout << "Error adding new tuition!" << endl << endl;
		return;
	}

	//retrieve rating list
	struct Rating* ratingList = NULL;
	RetrieveRatings(&ratingList);

	//create rating permission for students
	while (selectedStudents != NULL) {

		struct Rating *toAdd = new Rating(id, tutor_id, selectedStudents->getId(), 0);
		AddRatingToLast(&ratingList, toAdd);

		selectedStudents = selectedStudents->next;
	}

	if (ratingList->printFile()) {
		cout << "Rating access given!" << endl << endl;
	}
	else {
		cout << "Error adding giving rating access to student!" << endl << endl;
		return;
	}

	//free memory space
	tuitionList->deleteTuitionList();
	studentList->deleteStudentList();
}

void AddTuitionToLast(struct Tuition** head, struct Tuition* newTuition) {
	struct Tuition* node = *head;

	if (node == NULL) {
		*head = newTuition;
	}
	else {
		while (node->next != NULL) {
			node = node->next;
		}

		node->next = newTuition;
	}

}

