#include "General.h"

void DisplayHRMenu() {

	//Role Check
	if (getRole() != "HR") {
		setRole("");
		setTuitionCentreCode("");
		Login();
		return;
	}

	string input;
	int option = -1;

	try {
		cout << "Choose an option below:" << endl;
		cout << "0. Logout" << endl;
		cout << "1. Tutor Management Menu" << endl;
		cout << "2. View Subject" << endl;
		cout << "3. View Tuition Centre" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		DisplayHRMenu();
	}

	if (option == -1) {
		DisplayHRMenu();
	}

	switch (option) {
	default:
	case 0: 
		setRole("");
		setTuitionCentreCode("");
		setStudentId(-1);
		Login();
		break;
	case 1:
		system("CLS");
		TutorManagementMenu();
		break;
	case 2: 
		DisplayAllSubjects();
		DisplayHRMenu();
		break;
	case 3: 
		DisplayAllTuitionCentres();
		DisplayHRMenu();
		break;
	}

}

void DisplayAdminMenu() {
	//Role Check
	if (getRole() != "Admin") {
		setRole("");
		setTuitionCentreCode("");
		Login();
		return;
	}

	string input;
	int option = -1;

	try {
		cout << "Choose an option below:" << endl;
		cout << "0. Logout" << endl;
		cout << "1. View Tutors" << endl;
		cout << "2. Add Tuition" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		DisplayAdminMenu();
	}

	if (option == -1) {
		DisplayAdminMenu();
	}

	switch (option) {
	default:
	case 0:
		setRole("");
		setTuitionCentreCode("");
		setStudentId(-1);
		Login();
		break;
	case 1: 
		DisplayAllTutors();
		break;
	case 2:
		AddTuition();
		DisplayAdminMenu();
		break;
	}
}

void DisplayStudentMenu() {
	//Role Check
	if (getRole() != "Student") {
		setRole("");
		setTuitionCentreCode("");
		setStudentId(-1);
		Login();
		return;
	}

	string input;
	int option = -1;

	try {
		cout << "Choose an option below:" << endl;
		cout << "0. Logout" << endl;
		cout << "1. View Tutors" << endl;
		cout << "2. Give Ratings" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		DisplayStudentMenu();
	}

	if (option == -1) {
		DisplayStudentMenu();
	}

	switch (option) {
	default:
	case 0:
		setRole("");
		setTuitionCentreCode("");
		setStudentId(-1);
		Login();
		break;
	case 1:
		DisplayAllTutors();
		break;
	case 2:
		GiveRating();
		break;
	}
}

void TutorManagementMenu() {
	string input;
	int option = -1;

	try {
		cout << "Choose an option below:" << endl;
		cout << "0. Back" << endl;
		cout << "1. Tutor List" << endl;
		cout << "2. Add Tutor" << endl;
		cout << "3. Edit Tutor" << endl;
		cout << "4. Terminate Tutor" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		TutorManagementMenu();
	}

	if (option == -1) {
		TutorManagementMenu();
	}

	switch (option) {
	default:
	case 0: getRole() == "HR" ? DisplayHRMenu() : Login();
		break;
	case 1: 
		DisplayAllTutors();
		break;
	case 2: 
		AddTutor();
		TutorManagementMenu();
		break;
	case 3:
		EditTutor();
		TutorManagementMenu();
		break;
	case 4:
		TerminateTutor();
		TutorManagementMenu();
		break;
	}
}

void TutorListMenu(struct Tutor** head) {
	string input;
	int option = -1;

	try {
		cout << "Choose an action below:" << endl;
		cout << "0. Back" << endl;
		cout << "1. Search Tutor" << endl;
		cout << "2. Sort Tutor" << endl;
		cout << "3. View Specific Tutor" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		TutorListMenu(head);
	}

	if (option == -1) {
		TutorListMenu(head);
	}

	switch (option) {
	default:
	case 0: 
		(*head)->deleteTutorList();
		if (getRole() == "HR") {
			system("CLS");
			TutorManagementMenu();
		}
		else if (getRole() == "Admin") {
			system("CLS");
			DisplayAdminMenu();
		}
		else {
			system("CLS");
			DisplayStudentMenu();
		}
		break;
	case 1:
		SearchMenu(head);
		break;
	case 2: 
		SortMenu(head);
		break;
	case 3:
		ViewTutor(head);
		break;
	}
}

void SearchMenu(struct Tutor** head) {
	string input;
	int option = -1;

	try {
		cout << "Choose a search-by option below:" << endl;
		cout << "0. Back" << endl;
		cout << "1. ID" << endl;
		cout << "2. Rating" << endl;
		cout << "3. Tuition Centre" << endl;
		cout << "4. Subject" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		SearchMenu(head);
	}

	if (option == -1) {
		SearchMenu(head);
	}

	switch (option) {
	default:
	case 0: 
		(*head)->displayTutors(false);
		TutorListMenu(head);
		break;
	case 1:
		SearchTutorById(head);
		TutorListMenu(head);
		break;
	case 2:
		SearchTutorByRating(head);
		TutorListMenu(head);
		break;
	case 3: 
		SearchTutorByTuitionCentre(head);
		TutorListMenu(head);
		break;
	case 4: 
		SearchTutorBySubject(head);
		TutorListMenu(head);
		break;
	}
}

void SortMenu(struct Tutor** head) {
	string input;
	int option = -1;

	try {
		cout << "Choose a sort-by option below:" << endl;
		cout << "0. Back" << endl;
		cout << "1. ID" << endl;
		cout << "2. Overall Rating" << endl;
		cout << "3. Hourly Pay Rate" << endl << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		SortMenu(head);
	}

	if (option == -1) {
		SortMenu(head);
	}

	switch (option) {
	default:
	case 0:
		(*head)->displayTutors(false);
		TutorListMenu(head);
		break;
	case 1:
		SortTutorById(head);
		TutorListMenu(head);
		break;
	case 2:
		SortTutorByRating(head);
		TutorListMenu(head);
		break;
	case 3:
		SortTutorByHourlyPayRate(head);
		TutorListMenu(head);
		break;
	}
}

void TutorNavigationMenu(struct Tutor** head, struct Tutor* current) {
	string input;
	int option = -1;

	try {
		cout << "Choose an option below:" << endl;
		cout << "0. Back" << endl;
		cout << "1. Previous Tutor" << endl;
		cout << "2. Next Tutor" << endl;
		cout << "Enter your option: ";

		cin >> input;
		option = stoi(input);

	}
	catch (exception) {
		TutorNavigationMenu(head, current);
	}

	if (option == -1) {
		TutorNavigationMenu(head, current);
	}

	switch (option) {
	default:
	case 0:
		(*head)->displayTutors(false);
		TutorListMenu(head);
		break;
	case 1:
		current->previousTutor(head);
		break;
	case 2:
		current->nextTutor(head);
		break;
	}
}