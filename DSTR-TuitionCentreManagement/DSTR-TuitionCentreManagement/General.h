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
void RetrieveTutors(struct Tutor**);
void DisplayAllTutors();

void SearchTutorById(struct Tutor**);
void SearchTutorByRating(struct Tutor**);
void SearchTutorByTuitionCentre(struct Tutor**);
void SearchTutorBySubject(struct Tutor**);

void SortTutorById(struct Tutor**);
void SortTutorByRating(struct Tutor**);
void SortTutorByHourlyPayRate(struct Tutor**);

void AddTutorToLast(struct Tutor**, struct Tutor*);
void AddTutor();
void EditTutor();
void TerminateTutor();
void ViewTutor(struct Tutor**);


void FilterTutorByTermination(struct Tutor**, bool);
void FilterTutorByTuitionCentre(struct Tutor**, string);

int GetTutorSize(struct Tutor**, bool);

//Students
void RetrieveStudents(struct Student**);
void AddStudentToLast(struct Student**, struct Student*);
void RemoveStudentFromList(struct Student**, int);

//Menu
void DisplayHRMenu();
void DisplayStudentMenu();
void DisplayAdminMenu();
void TutorManagementMenu();
void TutorListMenu(struct Tutor**);
void SearchMenu(struct Tutor**);
void SortMenu(struct Tutor**);
void TutorNavigationMenu(struct Tutor**, struct Tutor*);

//Subjects
void RetrieveSubjects(struct Subject**);
void DisplayAllSubjects();


//Tuition Centre
void RetrieveTuitionCentres(struct TuitionCentre**);
void DisplayAllTuitionCentres();

//Rating
float CalculateRatings(struct Rating** , int);
void RetrieveRatings(struct Rating**);
void AddRatingToLast(struct Rating**, struct Rating*);
void GiveRating();
void FilterRating(struct Rating**);

//Tuition
void RetrieveTuitions(struct Tuition**);
void AddTuition();
void AddTuitionToLast(struct Tuition**, struct Tuition*);


//---end::All main method headers---

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
	void nextTutor(struct Tutor**);
	void previousTutor(struct Tutor**);

	bool printFile();
	void printTutorFull();
	void printTutorBrief();

	void displayTutors(bool);
	void deleteTutorList();


	int getId();
	string getTuitionCentre();
	string getFullName();
	float getRating();
	string getTerminationDate();

	bool searchById(int);
	bool searchByRating(int, int);
	bool searchByTuitionCentre(string);
	bool searchBySubject(string);

	bool sortById();
	bool sortByRating();
	bool sortByHourlyPayRate(struct Subject**);

	bool isTerminated();
	int generateId();
	string getSubject();

	struct Tutor** retrieveById(int);

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
	void printFile();
	void printInfo();

	void displayStudents();
	void deleteStudentList();

	struct Student** searchByUsername(string);

	struct Student** retrieveById(int);

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
	void addSubject(struct Subject** head, struct Subject* newSubject);

	void displaySubjects(int, bool);
	void deleteSubjectList();

	void printFile();
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

	//Functions
	void displayTuitionCentres(int, bool);
	void deleteTuitionCentreList();

	void printCodeName(int);
	void printCodeNameAddress(int);
	void printFile();

	struct TuitionCentre** searchByIndex(int);

	bool passwordComparison(string);

	string getCodeName();
	string getInfo();

	struct TuitionCentre** searchByCode (string);

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
	bool printFile();

	void deleteTuitionList();

	int generateId();
	string getInfo();

	struct Tuition** retrieveById(int);


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
	void displayRatings();
	void deleteRatingList();

	void printInfo(struct Tuition*, struct Tutor*, struct Subject*);
	bool printFile();
	bool editRating(int);

	struct Rating** retrieveByTuitionId(int);

};


#endif