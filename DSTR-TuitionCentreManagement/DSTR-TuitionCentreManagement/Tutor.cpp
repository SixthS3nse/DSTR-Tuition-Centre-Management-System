#include "General.h"

Tutor::Tutor() {}

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


bool Tutor::printFile() {

	bool success = false;

	struct Tutor* node = this;

	if (node == NULL) {
		return success;
	}

	ofstream outData;
	outData.open("Tutors.txt");

	while (node != NULL) {
		outData << node->id << "\t" << node->firstname << "\t" << node->lastname << "\t" << node->gender << "\t" << node->phone << "\t" << node->address
			<< "\t" << node->date_Joined << "\t" << node->date_Terminated << "\t" << node->subject_Code << "\t" << node->tuition_Centre_code << "\t" << node->rating << endl;
		node = node->next;
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

void Tutor::displayTutors(bool isBrief) {
	system("CLS");

	struct Tutor* node = this;

	if (this == NULL) return;

	if (isBrief) {
		cout << "ID" << "\t" << "Name" << endl;
	}
	else {
		cout << "ID" << "\t" << "Name" << "\t\t\t" << "Subject" << "\t" << "Tuition Centre" << "\t" << "Rating" << endl;
	}

	while (node != NULL) {

		//check termination status don't print if terminated
		if (node->isTerminated()) {
			node = node->next;
			continue;
		}

		if (isBrief) {
			node->printTutorBrief();
		}
		else {
			node->printTutorFull();
		}

		node = node->next;
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

void Tutor::previousTutor(struct Tutor** tutorList) {
	struct Tutor* tutor = this->prev;

	if (tutor == NULL) {
		//head to last tutor
		struct Tutor* node = *tutorList;

		while (node->next != NULL) {
			node = node->next;
		}

		tutor = node;
	}

	struct TuitionCentre* tuitionCentreList = NULL;
	RetrieveTuitionCentres(&tuitionCentreList);
	struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutor->getTuitionCentre());
	struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

	struct Subject* subjectList = NULL;
	RetrieveSubjects(&subjectList);
	struct Subject** subjectPtr = subjectList->searchByCode(tutor->getSubject());
	struct Subject* subjectNode = *subjectPtr;

	tutor->viewTutor(tuitionCentreNode, subjectNode);

	//Free memory
	tuitionCentreList->deleteTuitionCentreList();
	subjectList->deleteSubjectList();

	TutorNavigationMenu(tutorList, tutor);

}

void Tutor::nextTutor(struct Tutor** tutorList) {
	struct Tutor* tutor = this->next;

	if (tutor == NULL) {
		//head to first tutor
		struct Tutor* node = *tutorList;
		tutor = node;
	}

	struct TuitionCentre* tuitionCentreList = NULL;
	RetrieveTuitionCentres(&tuitionCentreList);
	struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutor->tuition_Centre_code);
	struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

	struct Subject* subjectList = NULL;
	RetrieveSubjects(&subjectList);
	struct Subject** subjectPtr = subjectList->searchByCode(tutor->subject_Code);
	struct Subject* subjectNode = *subjectPtr;

	tutor->viewTutor(tuitionCentreNode, subjectNode);

	//Free memory
	tuitionCentreList->deleteTuitionCentreList();
	subjectList->deleteSubjectList();

	TutorNavigationMenu(tutorList, tutor);

}

//retrieval
struct Tutor** Tutor::retrieveById(int id) {
	struct Tutor* node = this;
	struct Tutor** result = NULL;

	if (node == NULL) return result;

	while (node != NULL) {
		if (node->searchById(id)) {
			result = &node;
			return result;
		}
		else {
			node = node->next;
		}
	}

	return result;
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
bool Tutor::sortById() {
	return (this->id > this->next->id);
}

bool Tutor::sortByRating() {
	return (this->rating > this->next->rating);
}

bool Tutor::sortByHourlyPayRate(struct Subject** head) {
	bool result = false;

	float current_rate = 0, next_rate = 0;

	struct Subject** current_subject = (*head)->searchByCode(this->subject_Code);
	current_rate = current_subject == NULL ? 0 : (*current_subject)->hourly_pay_rate;

	struct Subject** next_subject = (*head)->searchByCode(this->next->subject_Code);
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

//get id
int Tutor::generateId() {
	int current = 1;

	struct Tutor* node = this;

	if (this == NULL) return current;

	while (node != NULL) {

		if (node->id > current) {
			current = node->id;
		}

		node = node->next;
	}

	return current + 1;
}

//Free up memory
void Tutor::deleteTutorList()
{
	if (this == NULL) return;

	Tutor* current = this;
	Tutor* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

//External functions
void DisplayAllTutors() {

	struct Tutor* tutorList = NULL;
	RetrieveTutors(&tutorList);
	FilterTutorByTermination(&tutorList, false);

	//Display Tutor
	tutorList->displayTutors(false);
	TutorListMenu(&tutorList);

}

void RetrieveTutors(struct Tutor** head) {
	ifstream inData;
	inData.open("Tutors.txt");

	struct Tutor* node = *head;
	struct Tutor* prev_node = NULL;

	int id;
	string str_id, firstname, lastname, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, str_rating;
	char gender;


	while (inData >> str_id >> firstname >> lastname >> gender >> phone >> address >> date_Joined >> date_Terminated >> subject_Code >> tuition_Centre_Code >> str_rating) {

		id = stoi(str_id);

		//Calculatate rating
		//-Retrieve-
		struct Rating* ratingList = NULL;
		RetrieveRatings(&ratingList);

		float rating = 0;

		if (ratingList != NULL) {
			//-Calculate-
			rating = CalculateRatings(&ratingList, id);
		}

		struct Tutor* input = new Tutor(id, firstname, lastname, gender, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, rating);


		if (*head == NULL) {
			*head = input;
			node = *head;
		}
		else {
			node->next = input;
			node->prev = prev_node;
			prev_node = node;
			node = node->next;

		}

	}

}

void SearchTutorById(struct Tutor** head) {

	if (*head == NULL) return;

	struct Tutor* node = *head;

	string input;
	int id = -1;

	cout << "Enter Tutor ID: ";
	cin >> input;

	try {
		id = stoi(input);
	}
	catch (exception) {
		cout << "Invalid Input!" << endl;
		node->displayTutors(false);
		return;
	}

	while (node != NULL) {
		if (node->searchById(id)) {
			node->printTutorFull();
			return;
		}

		node = node->next;
	}
}

void SearchTutorByRating(struct Tutor** head) {

	if (*head == NULL) return;

	struct Tutor* node = *head;

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
		node->displayTutors(false);
		return;
	}

	while (node != NULL) {
		if (node->searchByRating(min, max)) {
			node->printTutorFull();
		}

		node = node->next;
	}
}

void SearchTutorByTuitionCentre(struct Tutor** head) {

	if (*head == NULL) return;

	struct Tutor* node = *head;

	string input;
	int option = -1;

	//Display tuition centres
	struct TuitionCentre* tc_node = NULL;
	RetrieveTuitionCentres(&tc_node);

	if (tc_node == NULL) {
		tc_node->deleteTuitionCentreList();
		node->displayTutors(false);
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
		node->displayTutors(false);
		return;
	}

	if (*tc_ptr == NULL) {
		tc_node->deleteTuitionCentreList();
		node->displayTutors(false);
		return;
	}

	string tc_code = (*tc_ptr)->code;
	tc_node->deleteTuitionCentreList();

	while (node != NULL) {
		if (node->searchByTuitionCentre(tc_code)) {
			node->printTutorFull();
		}

		node = node->next;
	}

}

void SearchTutorBySubject(struct Tutor** head) {

	if (*head == NULL) return;

	struct Tutor* node = *head;

	string input;
	int option = -1;

	//Display subjects
	struct Subject* sub_node = NULL;
	RetrieveSubjects(&sub_node);

	if (sub_node == NULL) {
		sub_node->deleteSubjectList();
		node->displayTutors(false);
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
		node->displayTutors(false);
		return;
	}

	if (*sub_ptr == NULL) {
		sub_node->deleteSubjectList();
		node->displayTutors(false);
		return;
	}

	string sub_code = (*sub_ptr)->code;
	sub_node->deleteSubjectList();

	while (node != NULL) {
		if (node->searchBySubject(sub_code)) {
			node->printTutorFull();
		}

		node = node->next;
	}

}


void SortTutorById(struct Tutor** head) {
	if (*head == NULL) return;

	bool pass = false;

	while (!pass) {

		pass = true;
		struct Tutor* current_node = *head;
		struct Tutor* next_node = current_node->next;
		struct Tutor temp_node;

		while (next_node != NULL) {

			if (current_node->sortById()) {
				pass = false;
				temp_node = *current_node;
				*current_node = *next_node;
				*next_node = temp_node;

				next_node->next = current_node->next;
				current_node->next = next_node;

				current_node->prev = next_node->prev;
				next_node->prev = current_node;
			}

			current_node = current_node->next;
			next_node = current_node->next;
		}
	}

	(*head)->displayTutors(false);

}

void SortTutorByRating(struct Tutor** head) {
	if (*head == NULL) return;

	struct Tutor* node = *head;

	bool pass = false;

	while (!pass) {

		pass = true;
		struct Tutor* current_node = *head;
		struct Tutor* next_node = current_node->next;
		struct Tutor temp_node;

		while (next_node != NULL) {

			if (current_node->sortByRating()) {
				pass = false;
				temp_node = *current_node;
				*current_node = *next_node;
				*next_node = temp_node;

				next_node->next = current_node->next;
				current_node->next = next_node;

				current_node->prev = next_node->prev;
				next_node->prev = current_node;
			}

			current_node = current_node->next;
			next_node = current_node->next;
		}
	}

	(*head)->displayTutors(false);

}

void SortTutorByHourlyPayRate(struct Tutor** head) {
	if (*head == NULL) return;

	struct Tutor* node = *head;

	//retrieve subjects
	struct Subject* subjectList = NULL;
	RetrieveSubjects(&subjectList);

	if (subjectList == NULL) {
		subjectList->deleteSubjectList();
		node->displayTutors(false);
		return;
	}

	bool pass = false;

	while (!pass) {

		pass = true;
		struct Tutor* current_node = *head;
		struct Tutor* next_node = current_node->next;
		struct Tutor temp_node;

		while (next_node != NULL) {

			if (current_node->sortByHourlyPayRate(&subjectList)) {
				pass = false;
				temp_node = *current_node;
				*current_node = *next_node;
				*next_node = temp_node;

				next_node->next = current_node->next;
				current_node->next = next_node;

				current_node->prev = next_node->prev;
				next_node->prev = current_node;
			}

			current_node = current_node->next;
			next_node = current_node->next;
		}
	}

	//delete subject list
	subjectList->deleteSubjectList();

	(*head)->displayTutors(false);

}


void AddTutor() {

	struct Tutor* tutorList = NULL;
	RetrieveTutors(&tutorList);

	if (tutorList == NULL) {
		tutorList->deleteTutorList();
		return;
	}

	//count active tutors
	int count = GetTutorSize(&tutorList, true);

	if (count >= 10) {
		cout << "Maximum number of tutors has reached!" << endl;
		tutorList->deleteTutorList();
		return;
	}

	//free memory
	tutorList->deleteTutorList();


	//retrieve tuition centres
	string tuition_centre_code = "";
	struct TuitionCentre* tuitionCentreList = NULL;
	RetrieveTuitionCentres(&tuitionCentreList);

	if (tuitionCentreList == NULL) {
		tuitionCentreList->deleteTuitionCentreList();
		return;
	}

	//retrieve subjects
	string subject_code = "";
	struct Subject* subjectList = NULL;
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

	//re-retrieve tutor list
	tutorList = NULL;
	RetrieveTutors(&tutorList);

	//get id
	int id = tutorList->generateId();

	//create new struct
	struct Tutor* newTutor = new Tutor(id, firstname, lastname, gender, phone, address, date_joined, no_termination_date, subject_code, tuition_centre_code, 0.0f);

	//add to list
	AddTutorToLast(&tutorList, newTutor);

	system("CLS");

	//write to file
	if (tutorList->printFile()) {
		newTutor->printTutorBrief();
		cout << "Tutor is added!" << endl << endl;
	}
	else {
		cout << "Error adding new tutor!" << endl << endl;
	}

	//free memory space
	tutorList->deleteTutorList();

}

void AddTutorToLast(struct Tutor** head, struct Tutor* newTutor) {
	struct Tutor* node = *head;

	if (node == NULL) {
		*head = newTutor;
	}
	else {
		while (node->next != NULL) {
			node = node->next;
		}

		node->next = newTutor;
	}

}


void EditTutor() {
	struct Tutor* tutorList = NULL;
	RetrieveTutors(&tutorList);

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
		TutorManagementMenu();
		return;
	}


	//availability check
	struct Tutor** tutorPtr = tutorList->retrieveById(tutor_id);

	if (*tutorPtr == NULL) {
		tutorList->deleteTutorList();
		system("CLS");
		cout << "Tutor not found!" << endl;
		return;
	}
	struct Tutor* tutorNode = *tutorPtr;

	//termination check
	if (tutorNode->isTerminated()) {
		tutorList->deleteTutorList();
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
		tutorList->deleteTutorList();
		cout << "Invalid Input!" << endl;
		return;
	}

	//flush cin
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	string newData;

	switch (option) {
	default:
	case 0:
		tutorList->deleteTutorList();
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

	if (tutorList->printFile()) {
		tutorNode->printTutorFull();
		cout << "Tutor's information updated!" << endl << endl;;
	}
	else {
		cout << "Error in updating tutor's information" << endl << endl;;
	}

	//free memory
	tutorList->deleteTutorList();

}

void TerminateTutor() {
	struct Tutor* tutorList = NULL;
	RetrieveTutors(&tutorList);

	string str_tutor_id;
	int tutor_id = -1;

	tutorList->displayTutors(true);

	cout << "Enter a tutor ID to terminate: ";
	cin >> str_tutor_id;

	try {
		tutor_id = stoi(str_tutor_id);
	}
	catch (exception) {
		tutorList->deleteTutorList();
		system("CLS");
		cout << "Invalid Input" << endl << endl;
		TutorManagementMenu();
		return;
	}


	//availability check
	struct Tutor** tutorPtr = tutorList->retrieveById(tutor_id);

	if (*tutorPtr == NULL) {
		tutorList->deleteTutorList();
		system("CLS");
		cout << "Tutor not found!" << endl;
		return;
	}
	struct Tutor* tutorNode = *tutorPtr;

	//termination check
	if (tutorNode->isTerminated()) {
		tutorList->deleteTutorList();
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
		tutorList->deleteTutorList();
		cout << "Invalid Input!" << endl;
		return;
	}

	string newData;

	switch (option) {
	case 2:
	default:
		system("CLS");
		cout << "Tutor was not terminated!" << endl << endl;
		tutorList->deleteTutorList();
		return;
	case 1:
		tutorNode->terminateTutor();
		break;
	}

	//save to file
	system("CLS");

	if (tutorList->printFile()) {
		tutorNode->printTutorFull();
		cout << "Tutor's has been terminated!" << endl << endl;;
	}
	else {
		cout << "Error in terminating tutor." << endl << endl;;
	}

	//free memory
	tutorList->deleteTutorList();
}

void FilterTutorByTermination(struct Tutor** head, bool isTerminated) {
	struct Tutor* toDelete = *head;
	struct Tutor* prev_node = NULL;
	struct Tutor* next_node = NULL;

	if (*head == NULL) return;

	while (toDelete != NULL) {
		if (toDelete->isTerminated() == isTerminated) {
			prev_node = toDelete;
			toDelete = toDelete->next;
			continue;
		}

		//delete current node
		next_node = toDelete->next;

		if (next_node != NULL) {
			next_node->prev = prev_node;
		}

		if (prev_node != NULL) {
			prev_node->next = next_node;
		}
		else {
			*head = next_node;
		}

		free(toDelete);
		toDelete = next_node;
	}
}

void FilterTutorByTuitionCentre(struct Tutor** head, string tuitionCentreCode) {
	struct Tutor* toDelete = *head;
	struct Tutor* prev_node = NULL;
	struct Tutor* next_node = NULL;

	if (*head == NULL) return;

	while (toDelete != NULL) {
		if (toDelete->getTuitionCentre() == tuitionCentreCode) {
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
		free(toDelete);
		toDelete = next_node;
	}
}

int GetTutorSize(struct Tutor** head, bool terminationCondition) {
	int count = 0;
	struct Tutor* node = *head;

	while (node != NULL) {

		if (terminationCondition) {
			if (!node->isTerminated()) count++;
		}
		else {
			count++;
		}

		node = node->next;
	}

	return count;
}

void ViewTutor(struct Tutor** head) {
	if (*head == NULL) return;

	struct Tutor* tutor = *head;

	struct TuitionCentre* tuitionCentreList = NULL;
	RetrieveTuitionCentres(&tuitionCentreList);
	struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutor->getTuitionCentre());
	struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

	struct Subject* subjectList = NULL;
	RetrieveSubjects(&subjectList);
	struct Subject** subjectPtr = subjectList->searchByCode(tutor->getSubject());
	struct Subject* subjectNode = *subjectPtr;

	tutor->viewTutor(tuitionCentreNode, subjectNode);

	//Free memory
	tuitionCentreList->deleteTuitionCentreList();
	subjectList->deleteSubjectList();

	TutorNavigationMenu(head, tutor);
}