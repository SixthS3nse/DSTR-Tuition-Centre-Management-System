#include "General.h"

Tuition::Tuition() {};

Tuition::Tuition(int id, int tutor_id, int hour, string date) {

	this->id = id;
	this->tutor_id = tutor_id;
	this->hour = hour;
	this->date = date;
	this->next = NULL;
}

bool Tuition::printFile(int size) {

	bool success = false;

	struct Tuition* node = this;

	if (size == 0) {
		return success;
	}

	ofstream outData;
	outData.open("Tuition.txt");

	int count = 0;

	while (count < size) {
		outData << node[count].id << "\t" << node[count].tutor_id << "\t" << node[count].hour << "\t" << node[count].date << endl;
		count++;
	}

	success = true;

	return success;

}

int Tuition::getId() {
	return this->id;
}

//get info
string Tuition::getInfo() {
	string result = to_string(this->id) + "\t\t" + this->date;
	return result;
}

//retrieve by id
struct Tuition** Tuition::retrieveById(int id, int size) {
	struct Tuition* node = this;
	struct Tuition* result = NULL;

	if (node == NULL || size == 0) return &result;

	int count = 0;
	while (count < size) {
		if (node[count].getId() == id) {
			result = &node[count];
			return &result;
		}
		else {
			count++;
		}
	}

	return &result;
}


//External Functions (Not in Struct)
class TuitionDArray** RetrieveTuitions() {
	TuitionDArray* tuitionArr = new TuitionDArray(1);

	ifstream inData;
	inData.open("Tuition.txt");

	int id, tutor_id, hour;
	string str_id, str_tutor_id, str_hour, date;

	int count = 0;

	while (inData >> str_id >> str_tutor_id >> str_hour >> date) {

		id = stoi(str_id);
		tutor_id = stoi(str_tutor_id);
		hour = stoi(str_hour);

		struct Tuition input = Tuition(id, tutor_id, hour, date);

		if (count >= tuitionArr->size) {
			//increase array size
			tuitionArr->increaseSize(1);

			TuitionDArray* newArray = new TuitionDArray(*tuitionArr);
			tuitionArr->~TuitionDArray();
			tuitionArr = newArray;
		}

		//input tutor element into array
		tuitionArr->data[count] = input;

		count++;

	}

	return &tuitionArr;

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
	TutorDArray* tutorArr = *RetrieveTutorByTuitionCentre(getTuitionCentreCode());
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
		return;
	}


	//availability check
	struct Tutor** tutorPtr = tutorList->retrieveById(tutor_id, tutorArr->size);

	if (*tutorPtr == NULL) {
		tutorArr->~TutorDArray();
		system("CLS");
		cout << "Tutor not found / terminated!" << endl;
		return;
	}

	tutor_id = (*tutorPtr)->getId();

	//free up tutorList
	tutorArr->~TutorDArray();

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
	StudentDArray* studArr = *RetrieveStudents();
	struct Student* studentList = studArr->data;

	if (studentList == NULL) {
		system("CLS");
		cout << "Error in retriving student." << endl << endl;
		return;
	}

	//-request students-
	string str_student_id;
	int student_id = -1;

	StudentDArray* selectedStudents = new StudentDArray(0);

	studentList->displayStudents(studArr->size);

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
		struct Student** studentPtr = studentList->retrieveById(student_id, studArr->size);
		struct Student* newStud = *studentPtr;

		if (*studentPtr == NULL) {
			cout << "Invalid Input!" << endl << endl;
			continue;
		}

		//check if has been added
		if (selectedStudents->size > 0) {
			if (selectedStudents->data->retrieveById(student_id, selectedStudents->size) == NULL) {
				cout << "Student was already added!" << endl << endl;
				continue;
			}
		}

		//Increase size of selectedStudents
		selectedStudents->increaseSize(1);

		StudentDArray* newArray = new StudentDArray(*selectedStudents);
		selectedStudents->~StudentDArray();
		selectedStudents = newArray;

		selectedStudents->AddStudentToLast(newStud);

	} 


	//-check any student added-
	if (selectedStudents->size < 1) {
		system("CLS");
		cout << "No student added!" << endl;
		return;
	}

	//retrieve tuition list
	TuitionDArray* tuitionArr = *RetrieveTuitions();

	//get id
	int id = tuitionArr->generateId();

	//get today date
	string now = date("/", NULL, NULL, NULL);

	//create new struct
	struct Tuition* newTuition = new Tuition(id, tutor_id, hour, now);

	system("CLS");

	//Increase size of tuitionList
	tuitionArr->increaseSize(1);

	TuitionDArray* newArray = new TuitionDArray(*tuitionArr);
	tuitionArr->~TuitionDArray();
	tuitionArr = newArray;

	//add to list
	tuitionArr->AddTuitiontToLast(newTuition);

	//write to file
	if (tuitionArr->data->printFile(tuitionArr->size)) {
		cout << "Tuition is added!" << endl;
	}
	else {
		cout << "Error adding new tuition!" << endl << endl;
		return;
	}

	//retrieve rating list
	RatingDArray* ratingArr = *RetrieveRatings();

	//create rating permission for students
	int count = 0;
	struct Student* selectedStudentList = studArr->data;

	while (count < selectedStudents->size) {

		struct Rating* toAdd = new Rating(id, tutor_id, selectedStudentList[count].getId(), 0);

		//Increase size of ratinglist
		ratingArr->increaseSize(1);

		RatingDArray* newArray = new RatingDArray(*ratingArr);
		ratingArr->~RatingDArray();
		ratingArr = newArray;

		ratingArr->AddRatingToLast(toAdd);

		count++;
		//delete toAdd;
	}

	if (ratingArr->data->printFile(ratingArr->size)) {
		cout << "Rating access given!" << endl << endl;
	}
	else {
		cout << "Error adding giving rating access to student!" << endl << endl;
		return;
	}

	//free memory space
	tuitionArr->~TuitionDArray();
	studArr->~StudentDArray();
	selectedStudents->~StudentDArray();
	ratingArr->~RatingDArray();
}


