#include "General.h"


Tutor::Tutor(int id, string firstname, string lastname, char gender, string phone, string address, string date_Joined, string date_Terminated, string subject_Code, string tuition_Centre_code, float rating) {
	this->id = id;
	this->firstname = firstname;
	this->lastname = lastname;
	this->gender = gender;
	this->phone = phone;
	this->address = address;
	this->date_Joined = date_Joined;
	this->date_Terminated = date_Terminated;
	this->subject_Code = subject_Code;
	this->tuition_Centre_code = tuition_Centre_code;
	this->rating = rating;
	this->next = NULL;
	this->prev = NULL;
}

Tutor::Tutor() {}


bool Tutor::printFile(int size) {

	bool success = false;

	struct Tutor* node = this;

	if (size == 0) {
		return success;
	}

	ofstream outData;
	outData.open("Tutors.txt");
	int count = 0;

	while (count < size) {
		outData << node[count].id << "\t" << node[count].firstname << "\t" << node[count].lastname << "\t" << node[count].gender << "\t" << node[count].phone << "\t" << node[count].address
			<< "\t" << node[count].date_Joined << "\t" << node[count].date_Terminated << "\t" << node[count].subject_Code << "\t" << node[count].tuition_Centre_code << "\t" << node[count].rating << endl;
		
		count++;
	}

	success = true;

	return success;
}

int Tutor::getId() {
	return this->id;
}

string Tutor::getSubject() {
	return this->subject_Code;
}

string Tutor::getTuitionCentre() {
	return this->tuition_Centre_code;
}

string Tutor::getFullName() {
	return this->firstname + " " + this->lastname;
}

float Tutor::getRating() {
	return this->rating;
}

string Tutor::getTerminationDate() {
	return this->date_Terminated;
}

void Tutor::printTutorFull() {
	cout << this->id << "\t" << this->firstname << " " << this->lastname << "\t\t" << this->subject_Code << "\t" << this->tuition_Centre_code << "\t\t" << this->rating << endl;
}

void Tutor::printTutorBrief() {
	cout << this->id << "\t" << this->firstname << " " << this->lastname << endl;

}

void Tutor::displayTutors(bool isBrief, int size) {
	system("CLS");

	struct Tutor* node = this;
	int count = 0;

	if (size == 0) return;

	if (isBrief) {
		cout << "ID" << "\t" << "Name" << endl;
	}
	else {
		cout << "ID" << "\t" << "Name" << "\t\t\t" << "Subject" << "\t" << "Tuition Centre" << "\t" << "Rating" << endl;
	}

	while (count < size) {

		//check termination status don't print if terminated
		if (node[count].isTerminated()) {
			count++;
			continue;
		}

		if (isBrief) {
			node[count].printTutorBrief();
		}
		else {
			node[count].printTutorFull();
		}

		count++;
	}

	cout << endl;
}


//view specific tutor all info
void Tutor::viewTutor(struct TuitionCentre* tuitionCentre, struct Subject* subject) {
	system("CLS");
	cout << "Tutor Information" << endl << endl;;
	cout << "ID: " << this->id << endl;
	cout << "Full Name: " << this->id << endl;
	cout << "Subject: " << subject->getInfo() << endl;
	cout << "Tuition Centre: " << tuitionCentre->getInfo() << endl;
	cout << "Address: " << this->address << endl;
	cout << "Contact: " << this->phone << endl;
	cout << "Overall Rating: " << this->rating << endl << endl;;
}

void TutorDArray::previousTutor(int current) {

	if (size == 0) return;

	TutorDArray* tutorDArrayPtr = this;

	struct Tutor* tutor = NULL;
	int prev = current - 1;

	if (prev < 0) {
		//head to first tutor
		prev = size - 1;
	}

	tutor = &data[prev];

	struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
	RetrieveTuitionCentres(&tuitionCentreList);
	struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutor->getTuitionCentre());
	struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);
	struct Subject** subjectPtr = subjectList->searchByCode(tutor->getSubject());
	struct Subject* subjectNode = *subjectPtr;

	tutor->viewTutor(tuitionCentreNode, subjectNode);

	//Free memory
	tuitionCentreList->deleteTuitionCentreList();
	subjectList->deleteSubjectList();

	TutorNavigationMenu(&tutorDArrayPtr, prev);

}

void TutorDArray::nextTutor(int current) {
	if (size == 0) return;

	TutorDArray* tutorDArrayPtr = this;

	struct Tutor* tutor = NULL;
	int next = current + 1;


	if (next >= size) {
		//head to first tutor
		next = 0;
	}

	tutor = &data[next];

	struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
	RetrieveTuitionCentres(&tuitionCentreList);
	struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutor->getTuitionCentre());
	struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);
	struct Subject** subjectPtr = subjectList->searchByCode(tutor->getSubject());
	struct Subject* subjectNode = *subjectPtr;

	tutor->viewTutor(tuitionCentreNode, subjectNode);

	//Free memory
	tuitionCentreList->deleteTuitionCentreList();
	subjectList->deleteSubjectList();

	TutorNavigationMenu(&tutorDArrayPtr, next);

}

//retrieval
struct Tutor** Tutor::retrieveById(int id, int size) {
	struct Tutor* node = this;
	struct Tutor* result = NULL;

	if (node == NULL || size == 0) return &result;

	int count = 0;
	while (count < size) {
		if (node[count].searchById(id)) {
			result = &node[count];
			return &result;
		}
		else {
			count++;
		}
	}

	return &result;
}

//searches
bool Tutor::searchById(int id) {
	return (this->id == id);
}

bool Tutor::searchByRating(int min, int max) {
	return (this->rating >= min && this->rating <= max);
}

bool Tutor::searchByTuitionCentre(string code) {
	return (this->tuition_Centre_code == code);
}

bool Tutor::searchBySubject(string code) {
	return (this->subject_Code == code);
}

//sorting
bool Tutor::sortById(struct Tutor** nextNodePtr) {
	return (this->id > (*nextNodePtr)->id);
}

bool Tutor::sortByRating(struct Tutor** nextNodePtr) {
	return (this->rating > (*nextNodePtr)->rating);
}

bool Tutor::sortByHourlyPayRate(struct Subject** head, struct Tutor** nextNodePtr) {
	bool result = false;

	float current_rate = 0, next_rate = 0;

	struct Subject** current_subject = (*head)->searchByCode(this->subject_Code);
	current_rate = current_subject == NULL ? 0 : (*current_subject)->hourly_pay_rate;

	struct Tutor* nextNode = *nextNodePtr;
	struct Subject** next_subject = (*head)->searchByCode(nextNode->subject_Code);
	next_rate = next_subject == NULL ? 0 : (*next_subject)->hourly_pay_rate;

	//compare hourly pay rate
	result = current_rate > next_rate;

	return result;
}

bool Tutor::isTerminated() {
	bool result = this->date_Terminated != no_termination_date;
	return result;
}

//terminate
void Tutor::terminateTutor() {
	this->date_Terminated = date("/", NULL, NULL, NULL);
}

//External functions
void DisplayAllTutors() {

	TutorDArray* tutorArr = *RetrieveTutorByTermination(false);
	struct Tutor* tutorList = tutorArr->data;

	//Display Tutor
	tutorList->displayTutors(false, tutorArr->size);
	TutorListMenu(&tutorArr);

}

void SearchTutorById(TutorDArray** tutorDArrayPtr) {

	if (*tutorDArrayPtr == NULL) return;

	TutorDArray* tutorArr = *tutorDArrayPtr;

	if (tutorArr->size == 0) return;

	struct Tutor* node = tutorArr->data;

	string input;
	int id = -1;

	cout << "Enter Tutor ID: ";
	cin >> input;

	try {
		id = stoi(input);
	}
	catch (exception) {
		cout << "Invalid Input!" << endl;
		node->displayTutors(false, tutorArr->size);
		return;
	}

	int count = 0;

	while (count < tutorArr->size) {
		if (node[count].searchById(id)) {
			node[count].printTutorFull();
			return;
		}

		count++;
	}
}

void SearchTutorByRating(TutorDArray** tutorDArrayPtr) {

	if (*tutorDArrayPtr == NULL) return;

	TutorDArray *tutorDArray = *tutorDArrayPtr;

	if (tutorDArray->size == 0) return;

	struct Tutor* node = tutorDArray->data;

	string inp_min, inp_max;
	int min, max = -1;

	cout << "Enter Min. Rating (in whole number): ";
	cin >> inp_min;

	cout << "Enter Max. Rating (in whole number): ";
	cin >> inp_max;

	try {
		min = stoi(inp_min);
		max = stoi(inp_max);
	}
	catch (exception) {
		cout << "Invalid Input!" << endl;
		node->displayTutors(false,tutorDArray->size);
		return;
	}

	int count = 0;

	while (count < tutorDArray->size) {
		if (node[count].searchByRating(min, max)) {
			node[count].printTutorFull();
		}

		count++;
		
	}
}

void SearchTutorByTuitionCentre(TutorDArray** tutorDArrayPtr) {

	if (*tutorDArrayPtr == NULL) return;

	TutorDArray* tutorArr = *tutorDArrayPtr;

	if (tutorArr->size <= 1) return;

	struct Tutor* node = tutorArr->data;


	string input;
	int option = -1;

	//Display tuition centres
	struct TuitionCentre* tc_node = new TuitionCentre[3];
	RetrieveTuitionCentres(&tc_node);

	if (tc_node == NULL) {
		tc_node->deleteTuitionCentreList();
		node->displayTutors(false, tutorArr->size);
		return;
	}

	tc_node->displayTuitionCentres(1, false);

	cout << "Enter your option: ";
	cin >> input;

	struct TuitionCentre** tc_ptr = NULL;

	try {
		option = stoi(input);
		tc_ptr = tc_node->searchByIndex(option);
	}
	catch (exception) {
		tc_node->deleteTuitionCentreList();
		cout << "Invalid Input!" << endl;
		node->displayTutors(false, tutorArr->size);
		return;
	}

	if (*tc_ptr == NULL) {
		tc_node->deleteTuitionCentreList();
		node->displayTutors(false, tutorArr->size);
		return;
	}

	string tc_code = (*tc_ptr)->code;
	tc_node->deleteTuitionCentreList();

	int count = 0;

	while (count < tutorArr->size) {
		if (node[count].searchByTuitionCentre(tc_code)) {
			node[count].printTutorFull();
		}

		count++;
	}

}

void SearchTutorBySubject(TutorDArray** tutorDArrayPtr) {

	if (*tutorDArrayPtr == NULL) return;

	TutorDArray* tutorArr = *tutorDArrayPtr;

	if (tutorArr->size <= 1) return;

	struct Tutor* node = tutorArr->data;


	string input;
	int option = -1;

	//Display subjects
	struct Subject* sub_node = new Subject[5];
	RetrieveSubjects(&sub_node);

	if (sub_node == NULL) {
		sub_node->deleteSubjectList();
		node->displayTutors(false, tutorArr->size);
		return;
	}

	sub_node->displaySubjects(1, false);

	cout << "Enter your option: ";
	cin >> input;

	struct Subject** sub_ptr = NULL;

	try {
		option = stoi(input);
		sub_ptr = sub_node->searchByIndex(option);
	}
	catch (exception) {
		sub_node->deleteSubjectList();
		cout << "Invalid Input!" << endl;
		node->displayTutors(false, tutorArr->size);
		return;
	}

	if (*sub_ptr == NULL) {
		sub_node->deleteSubjectList();
		node->displayTutors(false, tutorArr->size);
		return;
	}

	string sub_code = (*sub_ptr)->code;
	sub_node->deleteSubjectList();
	int count = 0;

	while (count < tutorArr->size) {
		if (node[count].searchBySubject(sub_code)) {
			node[count].printTutorFull();
		}

		count++;
	}

}


void SortTutorById(TutorDArray** tutorDArrayPtr) {
	if (*tutorDArrayPtr == NULL) return;

	TutorDArray* tutorArr = *tutorDArrayPtr;

	if (tutorArr->size <= 1) return;

	struct Tutor* node = tutorArr->data;

	bool pass = false;

	while (!pass) {

		pass = true;
		int count = 0;
		struct Tutor* current_node = &node[count];
		struct Tutor* next_node = &node[count + 1];
		struct Tutor temp_node;

		while (count + 1 < tutorArr->size) {

			current_node = &node[count];
			next_node = &node[count + 1];

			if (current_node->sortById(&next_node)) {
				pass = false;
				temp_node = *current_node;
				*current_node = *next_node;
				*next_node = temp_node;
			}

			count++;
		}
	}

	tutorArr->data->displayTutors(false, tutorArr->size);

}

void SortTutorByRating(TutorDArray** tutorDArrayPtr) {
	if (*tutorDArrayPtr == NULL) return;

	TutorDArray* tutorArr = *tutorDArrayPtr;

	if (tutorArr->size <= 1) return;

	struct Tutor* node = tutorArr->data;

	bool pass = false;

	while (!pass) {

		pass = true;
		int count = 0;
		struct Tutor* current_node = &node[count];
		struct Tutor* next_node = &node[count + 1];
		struct Tutor temp_node;

		while (count + 1 < tutorArr->size) {

			current_node = &node[count];
			next_node = &node[count + 1];

			if (current_node->sortByRating(&next_node)) {
				pass = false;
				temp_node = *current_node;
				*current_node = *next_node;
				*next_node = temp_node;
			}

			count++;
		}
	}

	tutorArr->data->displayTutors(false, tutorArr->size);

}

void SortTutorByHourlyPayRate(TutorDArray** tutorDArrayPtr) {
	if (*tutorDArrayPtr == NULL) return;

	TutorDArray* tutorArr = *tutorDArrayPtr;

	if (tutorArr->size <= 1) return;

	struct Tutor* node = tutorArr->data;

	//retrieve subjects
	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);

	if (subjectList == NULL) {
		subjectList->deleteSubjectList();
		node->displayTutors(false, tutorArr->size);
		return;
	}

	bool pass = false;

	while (!pass) {

		pass = true;
		int count = 0;
		struct Tutor* current_node = NULL;
		struct Tutor* next_node = NULL;
		struct Tutor temp_node;

		while (count + 1 < tutorArr->size) {
			current_node = &node[count];
			next_node = &node[count + 1];

			if (current_node->sortByHourlyPayRate(&subjectList, &next_node)) {
				pass = false;

				temp_node = *current_node;
				*current_node = *next_node;
				*next_node = temp_node;

			}

			count++;
		}
	}

	//delete subject list
	subjectList->deleteSubjectList();

	tutorArr->data->displayTutors(false, tutorArr->size);
}


void AddTutor() {

	TutorDArray* tutorArr =	*RetrieveTutorByTermination(false);
	struct Tutor* tutorList = tutorArr->data;

	if (tutorList == NULL) {
		tutorArr->~TutorDArray();
		return;
	}

	if (tutorArr->size - 1 >= 10) {
		cout << "Maximum number of tutors has reached!" << endl;
		tutorArr->~TutorDArray();
		return;
	}

	tutorArr->~TutorDArray();

	//retrieve tuition centres
	string tuition_centre_code = "";
	struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
	RetrieveTuitionCentres(&tuitionCentreList);

	if (tuitionCentreList == NULL) {
		tuitionCentreList->deleteTuitionCentreList();
		return;
	}

	//retrieve subjects
	string subject_code = "";
	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);

	if (subjectList == NULL) {
		tuitionCentreList->deleteTuitionCentreList();
		subjectList->deleteSubjectList();
		return;
	}

	//select tuition centre & subject
	string str_input_tc, str_input_sub;
	int input_tc = -1, input_sub = -1;

	//-request tuition centre-
	tuitionCentreList->displayTuitionCentres(1, false);
	cout << "Enter the index: ";
	cin >> str_input_tc;

	//-process tuition centre-
	try {
		input_tc = stoi(str_input_tc);
	}
	catch (exception) {
		tuitionCentreList->deleteTuitionCentreList();
		subjectList->deleteSubjectList();
		system("CLS");
		cout << "Invalid Input!" << endl;
		return;
	}

	struct TuitionCentre** tuitionCentrePtr = NULL;

	if (input_tc > 0) {
		tuitionCentrePtr = tuitionCentreList->searchByIndex(input_tc);
	}

	//tuition centre retrieval check, if unavailable back to tutor management menu
	if (*tuitionCentrePtr == NULL) {
		tuitionCentreList->deleteTuitionCentreList();
		subjectList->deleteSubjectList();
		system("CLS");
		cout << "Invalid Input!" << endl;
		return;
	}

	tuition_centre_code = (*tuitionCentrePtr)->code;
	tuitionCentreList->deleteTuitionCentreList();

	//-request subject-
	subjectList->displaySubjects(1, false);
	cout << "Enter the index: ";
	cin >> str_input_sub;

	//-process subject-
	try {
		input_sub = stoi(str_input_sub);
	}
	catch (exception) {
		subjectList->deleteSubjectList();
		system("CLS");
		cout << "Invalid Input!" << endl;
		return;
	}

	struct Subject** subjectPtr = NULL;

	if (input_sub > 0) {
		subjectPtr = subjectList->searchByIndex(input_sub);
	}

	//-subject retrieval check, if unavailable back to tutor management menu-
	if (*subjectPtr == NULL) {
		subjectList->deleteSubjectList();
		system("CLS");
		cout << "Invalid Input!" << endl;
		return;
	}

	subject_code = (*subjectPtr)->code;
	subjectList->deleteSubjectList();

	string firstname, lastname, phone, address, date_joined, str_gender;
	char gender;
	date_joined = date("/", NULL, NULL, NULL);

	system("CLS");

	//request tutor's info
	cout << "Enter Tutor's First Name: ";
	cin >> firstname;

	cout << endl << "Enter Tutor's Last Name: ";
	cin >> lastname;

	cout << endl << "Enter Tutor's Phone: ";
	cin >> phone;

	//flush cin
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << endl << "Enter Tutor's Address: ";
	getline(cin, address);

	replace(address.begin(), address.end(), ' ', '_');

	//-gender request & process-
	cout << endl << "Select Tutor Gender" << endl;
	cout << "1. Male" << endl;
	cout << "2. Female" << endl << endl;
	cout << "Enter your option: ";
	cin >> str_gender;

	if (str_gender == "1") {
		gender = 'M';
	}
	else if (str_gender == "2") {
		gender = 'F';
	}
	else {
		system("CLS");
		cout << "Invalid Input!" << endl;
		return;
	}

	//re-retrieve
	tutorArr = *RetrieveTutors();
	tutorList = tutorArr->data;
	
	//get id
	int id = tutorArr->generateId();

	//create new struct
	struct Tutor* newTutor = new Tutor(id, firstname, lastname, gender, phone, address, date_joined, no_termination_date, subject_code, tuition_centre_code, 0.0f);

	//Increase size
	tutorArr->increaseSize(1);

	struct TutorDArray* newArray = new TutorDArray(*tutorArr);
	tutorArr->~TutorDArray();
	tutorArr = newArray;

	//add to list
	tutorArr->AddTutorToLast(newTutor);
	tutorList = tutorArr->data;

	system("CLS");

	//write to file
	if (tutorList->printFile(tutorArr->size)) {
		newTutor->printTutorBrief();
		cout << "Tutor is added!" << endl << endl;
	}
	else {
		cout << "Error adding new tutor!" << endl << endl;
	}

	//free memory space
	tutorArr->~TutorDArray();
	free(newTutor);
}


void EditTutor() {
	TutorDArray* tutorArr = *RetrieveTutors();
	struct Tutor* tutorList = tutorArr->data;

	string str_tutor_id;
	int tutor_id = -1;

	tutorList->displayTutors(true, tutorArr->size);

	cout << "Enter a tutor ID to edit: ";
	cin >> str_tutor_id;

	try {
		tutor_id = stoi(str_tutor_id);
	}
	catch (exception) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Invalid Input" << endl << endl;
		TutorManagementMenu();
		return;
	}


	//availability check
	struct Tutor** tutorPtr = tutorList->retrieveById(tutor_id, tutorArr->size);

	if (*tutorPtr == NULL) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Tutor not found!" << endl;
		return;
	}
	struct Tutor* tutorNode = *tutorPtr;

	//termination check
	if (tutorNode->isTerminated()) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Tutor was already terminated!" << endl;
		return;
	}

	//edit field
	string input;
	int option = -1;

	try {
		cout << "Choose a sort-by option below:" << endl;
		cout << "0. Back" << endl;
		cout << "1. Address" << endl;
		cout << "2. Contact" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		tutorArr->~TutorDArray();
		cout << "Invalid Input!" << endl;
		return;
	}

	//flush cin
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	string newData;

	switch (option) {
	default:
	case 0:
		tutorArr->~TutorDArray();
		return;
	case 1:
		system("CLS");
		cout << "Enter Tutor's New Address: " << endl;
		getline(cin, newData);
		replace(newData.begin(), newData.end(), ' ', '_');
		tutorNode->address = newData;
		break;
	case 2:
		system("CLS");
		cout << "Enter Tutor's New Contact: " << endl;
		cin >> newData;
		tutorNode->phone = newData;
		break;
	}



	//save to file
	system("CLS");

	if (tutorList->printFile(tutorArr->size)) {
		tutorNode->printTutorFull();
		cout << "Tutor's information updated!" << endl << endl;;
	}
	else {
		cout << "Error in updating tutor's information" << endl << endl;;
	}

	//free memory
	tutorArr->~TutorDArray();

}

void TerminateTutor() {
	TutorDArray* tutorArr = *RetrieveTutors();
	struct Tutor* tutorList = tutorArr->data;

	string str_tutor_id;
	int tutor_id = -1;

	tutorList->displayTutors(true, tutorArr->size);

	cout << "Enter a tutor ID to terminate: ";
	cin >> str_tutor_id;

	try {
		tutor_id = stoi(str_tutor_id);
	}
	catch (exception) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Invalid Input" << endl << endl;
		TutorManagementMenu();
		return;
	}


	//availability check
	struct Tutor** tutorPtr = tutorList->retrieveById(tutor_id, tutorArr->size);

	if (*tutorPtr == NULL) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Tutor not found!" << endl;
		return;
	}
	struct Tutor* tutorNode = *tutorPtr;

	//termination check
	if (tutorNode->isTerminated()) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Tutor was already terminated!" << endl;
		return;
	}

	//edit field
	string input;
	int option = -1;

	try {
		cout << "Confirm to terminate tutor?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		tutorArr->~TutorDArray();
		cout << "Invalid Input!" << endl;
		return;
	}

	string newData;

	switch (option) {
	case 2:
	default:
		system("CLS");
		cout << "Tutor was not terminated!" << endl << endl;
		tutorArr->~TutorDArray();
		return;
	case 1:
		tutorNode->terminateTutor();
		break;
	}

	//save to file
	system("CLS");

	if (tutorList->printFile(tutorArr->size)) {
		tutorNode->printTutorFull();
		cout << "Tutor's has been terminated!" << endl << endl;;
	}
	else {
		cout << "Error in terminating tutor." << endl << endl;;
	}

	//free memory
	tutorArr->~TutorDArray();
}

class TutorDArray** RetrieveTutors() {

	TutorDArray* tutorArr = new TutorDArray(1);

	ifstream inData;
	inData.open("Tutors.txt");

	int id;
	string str_id, firstname, lastname, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, str_rating;
	char gender;

	int count = 0;

	while (inData >> str_id >> firstname >> lastname >> gender >> phone >> address >> date_Joined >> date_Terminated >> subject_Code >> tuition_Centre_Code >> str_rating) {

		id = stoi(str_id);


		//Calculatate rating
		//-Retrieve-
		RatingDArray* ratingArr = *RetrieveRatings();
		struct Rating* ratingList = ratingArr->data;

		float rating = 0;

		if (ratingList != NULL) {
			//-Calculate-
			rating = CalculateRatings(&ratingList, id, ratingArr->size);
		}

		struct Tutor input = Tutor(id, firstname, lastname, gender, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, rating);

		if (count >= tutorArr->size) {
			//increase array size
			tutorArr->increaseSize(1);

			struct TutorDArray* newArray = new TutorDArray(*tutorArr);
			tutorArr->~TutorDArray();
			tutorArr = newArray;
		}

		//input tutor element into array
		tutorArr->data[count] = input;

		count++;

	}

	return &tutorArr;

}

class TutorDArray** RetrieveTutorByTermination(bool isTerminated) {

	TutorDArray* tutorArr = new TutorDArray(1);

	ifstream inData;
	inData.open("Tutors.txt");

	int id;
	string str_id, firstname, lastname, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, str_rating;
	char gender;

	int count = 0;

	while (inData >> str_id >> firstname >> lastname >> gender >> phone >> address >> date_Joined >> date_Terminated >> subject_Code >> tuition_Centre_Code >> str_rating) {

		if (isTerminated) {
			if (date_Terminated == no_termination_date) continue;
		}
		else {
			if (date_Terminated != no_termination_date) continue;
		}
		
		id = stoi(str_id);

		//Calculatate rating
		//-Retrieve-
		RatingDArray* ratingArr = *RetrieveRatings();
		struct Rating* ratingList = ratingArr->data;

		float rating = 0;

		if (ratingList != NULL) {
			//-Calculate-
			rating = CalculateRatings(&ratingList, id, ratingArr->size);
		}

		struct Tutor input = Tutor(id, firstname, lastname, gender, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, rating);

		if (count >= tutorArr->size) {
			//increase array size
			tutorArr->increaseSize(1);

			struct TutorDArray* newArray = new TutorDArray(*tutorArr);
			tutorArr->~TutorDArray();
			tutorArr = newArray;
		}

		//input tutor element into array
		tutorArr->data[count] = input;

		count++;

	}

	return &tutorArr;
}

class TutorDArray** RetrieveTutorByTuitionCentre(string tuitionCentreCode) {

	TutorDArray* tutorArr = new TutorDArray(1);

	ifstream inData;
	inData.open("Tutors.txt");

	int id;
	string str_id, firstname, lastname, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, str_rating;
	char gender;

	int count = 0;

	while (inData >> str_id >> firstname >> lastname >> gender >> phone >> address >> date_Joined >> date_Terminated >> subject_Code >> tuition_Centre_Code >> str_rating) {

		if (tuitionCentreCode != tuition_Centre_Code || date_Terminated != no_termination_date) continue;


		id = stoi(str_id);

		//Calculatate rating
		//-Retrieve-
		RatingDArray* ratingArr = *RetrieveRatings();
		struct Rating* ratingList = ratingArr->data;

		float rating = 0;

		if (ratingList != NULL) {
			//-Calculate-
			rating = CalculateRatings(&ratingList, id, ratingArr->size);
		}

		struct Tutor input = Tutor(id, firstname, lastname, gender, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, rating);

		if (count >= tutorArr->size) {
			//increase array size
			tutorArr->increaseSize(1);

			struct TutorDArray* newArray = new TutorDArray(*tutorArr);
			tutorArr->~TutorDArray();
			tutorArr = newArray;
		}

		//input tutor element into array
		tutorArr->data[count] = input;

		count++;

	}
	return &tutorArr;

}

int GetTutorSize(struct Tutor** head, bool terminationCondition, int size) {
	int count = 0;
	int index = 0;
	struct Tutor* node = *head;

	while (index < size) {

		if (terminationCondition) {
			if (!node[index].isTerminated()) count++;
		}
		else {
			count++;
		}

		index++;
	}

	return count;
}


void ViewTutor(TutorDArray** tutorDArrayPtr) {
	if (tutorDArrayPtr == NULL) return;

	TutorDArray* tutorDArray = *tutorDArrayPtr;

	if (tutorDArray->size == 0) return;

	struct Tutor* tutor = tutorDArray->data;

	struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
	RetrieveTuitionCentres(&tuitionCentreList);
	struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutor[0].getTuitionCentre());
	struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);
	struct Subject** subjectPtr = subjectList->searchByCode(tutor[0].getSubject());
	struct Subject* subjectNode = *subjectPtr;

	tutor[0].viewTutor(tuitionCentreNode, subjectNode);

	//Free memory
	tuitionCentreList->deleteTuitionCentreList();
	subjectList->deleteSubjectList();

	TutorNavigationMenu(tutorDArrayPtr, 0);
}