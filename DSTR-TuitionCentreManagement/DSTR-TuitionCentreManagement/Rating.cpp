#include "General.h"

Rating::Rating() {};

Rating::Rating(int tuition_Id, int tutor_Id, int student_Id, int rating) {
	this->tuition_id = tuition_Id;
	this->tutor_id = tutor_Id;
	this->student_id = student_Id;
	this->rating = rating;
	this->next = NULL;
}

bool Rating::printFile() {

	struct Rating* node = this;

	if (node == NULL) {
		return false;
	}

	ofstream outData;
	outData.open("Ratings.txt");

	while (node != NULL) {
		outData << node->tuition_id << "\t" << node->tutor_id << "\t" << node->student_id << "\t" << node->rating << endl;
		node = node->next;
	}

	return true;
}

bool Rating::editRating(int rate) {
	this->rating = rate;

	bool result = false;
	struct Rating* modifiedRating = this;

	struct Rating* ratingList = NULL;
	RetrieveRatings(&ratingList);
	struct Rating** head = &ratingList;

	while (ratingList != NULL) {
		if (ratingList->tuition_id == modifiedRating->tuition_id && ratingList->tutor_id == modifiedRating->tutor_id && ratingList->student_id == modifiedRating->student_id) {
			ratingList->rating = modifiedRating->rating;
			break;
		}

		ratingList = ratingList->next;
	}

	result = (*head)->printFile();

	ratingList->deleteRatingList();

	return result;
}

void Rating::displayRatings() {

	if (this == NULL) return;

	struct Rating* node = this;

	//retrieve tuitions
	struct Tuition* tuitionList = NULL;
	RetrieveTuitions(&tuitionList);

	//retrieve tutors
	struct Tutor* tutorList = NULL;
	RetrieveTutors(&tutorList);

	//retrieve tutors
	struct Subject* subjectList = NULL;
	RetrieveSubjects(&subjectList);

	while (node != NULL) {

		if (node->rating != 0) {
			node = node->next;
			continue;
		}

		struct Tuition** tuitionPtr = tuitionList->retrieveById(node->tuition_id);
		struct Tuition* tuitionNode = *tuitionPtr;

		struct Tutor** tutorPtr = tutorList->retrieveById(node->tutor_id);
		struct Tutor* tutorNode = *tutorPtr;

		string subject_code = tutorNode->getSubject();
		struct Subject** subjectPtr = subjectList->searchByCode(subject_code);
		struct Subject* subjectNode = *subjectPtr;

		node->printInfo(tuitionNode, tutorNode, subjectNode);
		node = node->next;
	}

	//free memory
	tuitionList->deleteTuitionList();
	tutorList->deleteTutorList();
	subjectList->deleteSubjectList();
}

void Rating::printInfo(struct Tuition* tuition, struct Tutor* tutor, struct Subject* subject) {
	cout << tuition->getInfo() << "\t" << tutor->getFullName() << "\t" << subject->getInfo() << endl;
}

//retrieve by id
struct Rating** Rating::retrieveByTuitionId(int id) {
	struct Rating* node = this;
	struct Rating** result = NULL;

	if (node == NULL) return result;

	while (node != NULL) {
		if (node->tuition_id == id) {
			result = &node;
			return result;
		}
		else {
			node = node->next;
		}
	}

	return result;
}

//free memory
void Rating::deleteRatingList() {

	if (this == NULL) {
		return;
	}

	Rating* current = this;
	Rating* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

//External function
float CalculateRatings(struct Rating** head, int tutor_Id) {

	float result = 0;

	if (*head == NULL) return result;

	struct Rating* node = *head;

	int total = 0, count = 0;

	while (node != NULL) {

		if (node->rating == 0) {
			node = node->next;
			continue;
		}

		if (node->tutor_id == tutor_Id) {
			total = total + node->rating;
			count++;
		}

		node = node->next;
	}

	result = count != 0? total / count : 0;

	return result;
}

void RetrieveRatings(struct Rating** head) {
	ifstream inData;
	inData.open("Ratings.txt");

	struct Rating* node = *head;

	int tuition_id, tutor_id, student_id, rating;
	string str_tuition_id, str_tutor_id, str_student_id, str_rating;

	while (inData >> str_tuition_id >> str_tutor_id >> str_student_id >> str_rating) {

		tuition_id = stoi(str_tuition_id);
		tutor_id = stoi(str_tutor_id);
		student_id = stoi(str_student_id);
		rating = stoi(str_rating);

		struct Rating* input = new Rating(tuition_id, tutor_id, student_id, rating);

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

void AddRatingToLast(struct Rating** head, struct Rating* newRating) {
	struct Rating* node = *head;

	if (node == NULL) {
		*head = newRating;
	}
	else {
		while (node->next != NULL) {
			node = node->next;
		}

		node->next = newRating;
	}

}

void GiveRating() {
	system("CLS");

	//Retrieve rating list;
	struct Rating* ratingList = NULL;
	RetrieveRatings(&ratingList);

	if (ratingList == NULL) {
		DisplayStudentMenu();
		return;
	}

	cout << "Tuition_ID" << "\t" << "Date" << "\t\t" << "Tutor" << "\t\t" << "Subject" << endl;;
	FilterRating(&ratingList);
	ratingList->displayRatings();

	string str_tuition_id, str_rating;
	int tuition_id = -1, rating = 0;

	cout << endl;
	cout << "Enter the tuition ID to give rating or 0 to exit: ";
	cin >> str_tuition_id;

	try {
		tuition_id = stoi(str_tuition_id);
	}
	catch (exception) {
		system("CLS");
		ratingList->deleteRatingList();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	if (tuition_id == 0) {
		system("CLS");
		ratingList->deleteRatingList();
		DisplayStudentMenu();
	}

	if (tuition_id < 0) {
		system("CLS");
		ratingList->deleteRatingList();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	//retrieve rating record based on tuition id
	struct Rating** ratingPtr = ratingList->retrieveByTuitionId(tuition_id);

	if (*ratingPtr == NULL) {
		system("CLS");
		ratingList->deleteRatingList();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	//rated check
	struct Rating* ratingNode = *ratingPtr;

	if (ratingNode->rating != 0) {
		system("CLS");
		ratingList->deleteRatingList();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	//request rating
	cout << endl;
	cout << "Rating Scale: 1 (lowest) to 5 (highest)" << endl;
	cout << "Whole number only - eg. 4" << endl << endl;
	cout << "Enter your rating: ";
	cin >> str_rating;

	try {
		rating = stoi(str_rating);
	}
	catch (exception) {
		system("CLS");
		ratingList->deleteRatingList();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	if (rating < 1 || rating > 5) {
		system("CLS");
		ratingList->deleteRatingList();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	system("CLS");

	if (ratingNode->editRating(rating)) {
		cout << "Rated!" << endl;
	}
	else {
		cout << "Fail to rate, please try again later!" << endl;
	}

	//Free memory;
	ratingList->deleteRatingList();
	GiveRating();

}

//for student only
void FilterRating(struct Rating** head) {

	struct Rating* toDelete = *head;
	struct Rating* prev_node = NULL;
	struct Rating* next_node = NULL;

	if (*head == NULL) return;

	while (toDelete != NULL) {
		if (toDelete->student_id == getStudentId()) {
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