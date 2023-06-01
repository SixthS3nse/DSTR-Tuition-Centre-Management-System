#ifndef GENERAL_H
#define GENERAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>

using namespace std;


const string no_termination_date = "00/00/0000";

//---begin::All main method headers---
void Login();
string getRole();
void setRole(string);
string getTuitionCentreCode();
void setTuitionCentreCode(string);
int getStudentId();
void setStudentId(int);
string date(string, int, int, int);
tm todayStruct();

//Tutor
void DisplayAllTutors();

void SearchTutorById(class TutorDArray**);
void SearchTutorByRating(class TutorDArray**);
void SearchTutorByTuitionCentre(class TutorDArray**);
void SearchTutorBySubject(class TutorDArray**);

void SortTutorById(class TutorDArray**);
void SortTutorByRating(class TutorDArray**);
void SortTutorByHourlyPayRate(class TutorDArray**);

class TutorDArray** RetrieveTutors();
class TutorDArray** RetrieveTutorByTermination(bool);
class TutorDArray** RetrieveTutorByTuitionCentre(string);

//void AddTutorToLast(struct Tutor**, struct Tutor*);
void AddTutor();
void EditTutor();
void TerminateTutor();
void ViewTutor(TutorDArray**);

int GetTutorSize(struct Tutor**, bool, int);

//Students
class StudentDArray** RetrieveStudents();

//Menu
void DisplayHRMenu();
void DisplayStudentMenu();
void DisplayAdminMenu();
void TutorManagementMenu();
void TutorListMenu(class TutorDArray**);
void SearchMenu(class TutorDArray**);
void SortMenu(class TutorDArray**);
void TutorNavigationMenu(class TutorDArray**, int);

//Subjects
void RetrieveSubjects(struct Subject**);
//void DisplaySubjects(struct Subject**, int, bool);
//void DeleteSubjectList(struct Subject**);
void DisplayAllSubjects();


//Tuition Centre
void RetrieveTuitionCentres(struct TuitionCentre**);
//void DisplayTuitionCentres(struct TuitionCentre**, int, bool);
//void DeleteTuitionCentreList(struct TuitionCentre**);
void DisplayAllTuitionCentres();

//Rating
float CalculateRatings(struct Rating**, int, int);
class RatingDArray** RetrieveRatings();
void GiveRating();

//Tuition
class TuitionDArray** RetrieveTuitions();
void AddTuition();


//---end::All main method headers---

//---begin::All data structs---
struct Tutor {

private:
	int id;
	string firstname;
	string lastname;
	char gender;
	string date_Joined;
	string date_Terminated;
	string subject_Code;
	string tuition_Centre_code;
	float rating;

public:
	string phone;
	string address;
	struct Tutor* next;
	struct Tutor* prev;

	//Tutor Constructor: id, firstname, lastname, gender, phone, address, date_Joined, date_Terminated, subject_Code, tuition_Centre_Code, rating
	struct Tutor(int id, string, string, char, string, string, string, string, string, string, float);
	struct Tutor();

	//Functions
	void terminateTutor();
	void viewTutor(struct TuitionCentre*, struct Subject*);

	bool printFile(int);
	void printTutorFull();
	void printTutorBrief();

	void displayTutors(bool, int);


	int getId();
	string getTuitionCentre();
	string getFullName();
	float getRating();
	string getTerminationDate();

	bool searchById(int);
	bool searchByRating(int, int);
	bool searchByTuitionCentre(string);
	bool searchBySubject(string);

	bool sortById(struct Tutor**);
	bool sortByRating(struct Tutor**);
	bool sortByHourlyPayRate(struct Subject**, struct Tutor**);

	bool isTerminated();
	string getSubject();

	struct Tutor** retrieveById(int, int);

};

struct Student {

private:
	int id;

public:
	string firstname;
	string lastname;
	string username;
	string password;
	string contact;


	struct Student* next;

	//Student Constructor: id, firstname, lastname, username, password, contact
	struct Student(int, string, string, string, string, string);
	struct Student();

	//Functions
	//void addStudent(struct Student**, struct Student*);
	void printInfo();

	void displayStudents(int);

	struct Student** searchByUsername(string, int);

	struct Student** retrieveById(int, int);

	bool passwordComparison(string);
	string getFullName();
	int getId();
};

struct Subject {

public:
	string code;
	string name;
	float hourly_pay_rate;

	struct Subject* next;

	//Subject Constructor: code, name, hourly_pay_rate
	struct Subject(string, string, float);
	struct Subject();

	//Functions
	void displaySubjects(int, bool);
	void deleteSubjectList();

	void printCodeName(int);
	void printCodeNamePay(int);

	struct Subject** searchByIndex(int);
	struct Subject** searchByCode(string);
	string getInfo();

};

struct TuitionCentre {

public:
	string code;
	string name;
	string address;
	string password;

	struct TuitionCentre* next;

	//Tuition Constructor: code, name, address, password
	struct TuitionCentre(string, string, string, string);
	struct TuitionCentre();

	~TuitionCentre() {};

	//Functions
	void displayTuitionCentres(int, bool);
	void deleteTuitionCentreList();

	void printCodeName(int);
	void printCodeNameAddress(int);

	struct TuitionCentre** searchByIndex(int);

	bool passwordComparison(string);

	string getCodeName();
	string getInfo();

	struct TuitionCentre** searchByCode(string);

};

struct Tuition {
private:
	int id;

public:
	int tutor_id;
	int hour;
	string date;

	struct Tuition* next;

	// Tuition Constructor : id, tutor_Id, hour, date
	struct Tuition(int, int, int, string);
	struct Tuition();

	//Functions
	bool printFile(int);

	string getInfo();
	int getId();

	struct Tuition** retrieveById(int, int);


};

struct Rating {

	int tuition_id;
	int tutor_id;
	int student_id;
	int rating;

	struct Rating* next;

	// Rating Constructor : id, tutor_Id, student_id, rating
	struct Rating(int, int, int, int);
	struct Rating();

	//Functions
	void displayRatings(int);

	void printInfo(struct Tuition*, struct Tutor*, struct Subject*);
	bool printFile(int);
	bool editRating(int);

	struct Rating** retrieveByTuitionId(int, int);

};

//---end::All data structs---


//---begin::Dynamic array classes---

class TutorDArray {
public:
	int size = 0;
	struct Tutor* data = new Tutor[size];

	TutorDArray(int s) {
		size = s;
		data = new Tutor[size];
	}

	TutorDArray(TutorDArray& oldArray) {
		size = oldArray.size;
		data = new Tutor[size];

		for (int i = 0; i < size - 1; i++) {
			data[i] = oldArray.data[i];
		}
	}

	void increaseSize(int s) {
		size += s;
	}

	void decreaseSize(int s) {
		size -= s;
	}


	void AddTutorToLast(struct Tutor* newTutor) {
		data[size - 1] = *newTutor;
	}


	int generateId() {
		int current = 1;

		if (data == NULL) return current;

		int count = 0;
		while (count < size) {

			if (data[count].getId() > current) {
				current = data[count].getId();
			}

			count++;
		}

		return current + 1;
	}

	void previousTutor(int);

	void nextTutor(int);

	~TutorDArray() {
		delete[] data;
	}
};

class StudentDArray {
public:
	int size = 0;
	struct Student* data = new Student[size];

	StudentDArray(int s) {
		size = s;
		data = new Student[size];
	}

	StudentDArray(StudentDArray& oldArray) {
		size = oldArray.size;
		data = new Student[size];

		for (int i = 0; i < size - 1; i++) {
			data[i] = oldArray.data[i];
		}
	}

	void increaseSize(int s) {
		size += s;
	}

	void decreaseSize(int s) {
		size -= s;
	}


	void AddStudentToLast(struct Student* newStud) {
		data[size - 1] = *newStud;
	}


	int generateId() {
		int current = 1;

		if (data == NULL) return current;

		int count = 0;
		while (count < size) {

			if (data[count].getId() > current) {
				current = data[count].getId();
			}

			count++;
		}

		return current + 1;
	}

	~StudentDArray() {
		delete[] data;
	}
};

class TuitionDArray {
public:
	int size = 0;
	struct Tuition* data = new Tuition[size];

	TuitionDArray(int s) {
		size = s;
		data = new Tuition[size];
	}

	TuitionDArray(TuitionDArray& oldArray) {
		size = oldArray.size;
		data = new Tuition[size];

		for (int i = 0; i < size - 1; i++) {
			data[i] = oldArray.data[i];
		}
	}

	void increaseSize(int s) {
		size += s;
	}

	void decreaseSize(int s) {
		size -= s;
	}


	void AddTuitiontToLast(struct Tuition* newTuition) {
		data[size - 1] = *newTuition;
	}


	int generateId() {
		int current = 1;

		if (data == NULL) return current;

		int count = 0;
		while (count < size) {

			if (data[count].getId() > current) {
				current = data[count].getId();
			}

			count++;
		}

		return current + 1;
	}

	~TuitionDArray() {
		delete[] data;
	}
};

class RatingDArray {
public:
	int size = 0;
	struct Rating* data = new Rating[size];

	RatingDArray(int s) {
		size = s;
		data = new Rating[size];
	}

	RatingDArray(RatingDArray& oldArray) {
		size = oldArray.size;
		data = new Rating[size];

		for (int i = 0; i < size - 1; i++) {
			data[i] = oldArray.data[i];
		}
	}

	void increaseSize(int s) {
		size += s;
	}

	void decreaseSize(int s) {
		size -= s;
	}


	void AddRatingToLast(struct Rating* newRating) {
		data[size - 1] = *newRating;
	}

	~RatingDArray() {
		delete[] data;
	}
};



//---end::Dynamic array classes---

#endif