#include "General.h"

string hrPass = "hr12345";

void loginAsHr();
void loginAsAdmin();
void loginAsStudent();

void Login() {

	string input;
	int option = -1;

	try {
		cout << "Pick a role to login or press \"0\" to exit system." << endl;
		cout << "0. \tSystem exit" << endl;
		cout << "1. \tHR" << endl;
		cout << "2. \tAdmin" << endl;
		cout << "3. \tStudent" << endl << endl;

		cout << "Enter your choice: ";

		cin >> input;

		cout << endl;

		option = stoi(input);
	}
	catch (exception) {
		Login();
	}

	if (option == -1) {
		Login();
	}

	switch (option) {
	default:
	case 0: exit(0);
		break;
	case 1:
		loginAsHr();
		break;
	case 2:
		loginAsAdmin();
		break;
	case 3:
		loginAsStudent();
		break;
	}
}

void loginAsHr() {
	system("CLS");

	string password;
	cout << "Enter the HR's password: ";
	cin >> password;

	if (password == "0") {
		Login();
	}
	else {
		if (password == hrPass) {
			cout << "Welcome back HR!" << endl;
			setRole("HR");
			system("CLS");
			DisplayHRMenu();
		}
		else {
			cout << "Incorrect HR password!" << endl;
			loginAsHr();
		}
	}
}

void loginAsStudent() {
	system("CLS");

	string username, password;
	cout << "Enter the your username: ";
	cin >> username;

	cout << "Enter your password: ";
	cin >> password;

	//Retrieve students
	StudentDArray* studentArr = *RetrieveStudents();
	struct Student* studentList = studentArr->data;

	//Find student based on username
	struct Student** studentPtr = studentList->searchByUsername(username, studentArr->size);

	if (*studentPtr != NULL) {
		struct Student* student = *studentPtr;
		if (student->passwordComparison(password)) {
			setRole("Student");
			setStudentId(student->getId());
			system("CLS");
			cout << "Welcome back " << student->getFullName() << " !" << endl;;

			//free up memory space
			studentArr->~StudentDArray();

			DisplayStudentMenu();
			return;
		}
		else {
			cout << "Invalid username or password!" << endl;
		}
	}
	else {
		cout << "Invalid username or password!" << endl;
	}

	Login();

}

void loginAsAdmin() {
	system("CLS");

	string strTuitionCentre, password;

	//Retrieve tuition centres
	struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
	RetrieveTuitionCentres(&tuitionCentreList);

	tuitionCentreList->displayTuitionCentres(1, false);

	cout << "Enter the index: ";
	cin >> strTuitionCentre;

	cout << "Enter the password: ";
	cin >> password;

	int idxTuitionCentre = 0;

	try {
		idxTuitionCentre = stoi(strTuitionCentre);
	}
	catch (exception) {
		loginAsAdmin();
		return;
	}

	if (idxTuitionCentre > 0) {
		//Find tuition centre based on index
		struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByIndex(idxTuitionCentre);

		if (*tuitionCentrePtr != NULL) {
			struct TuitionCentre* tuitionCentre = *tuitionCentrePtr;

			if (tuitionCentre->passwordComparison(password)) {
				setRole("Admin");
				setTuitionCentreCode(tuitionCentre->code);
				system("CLS");
				cout << "Welcome back Admin - " << tuitionCentre->getCodeName() << " !" << endl;

				//free up memory space
				tuitionCentreList->deleteTuitionCentreList();

				//Display admin menu
				DisplayAdminMenu();

				return;
			}
			else {
				cout << "Invalid centre or password!" << endl;
			}
		}
		else {
			cout << "Invalid centre or password!" << endl;
		}

		//free up memory space
		tuitionCentreList->deleteTuitionCentreList();
		Login();
	}
}
