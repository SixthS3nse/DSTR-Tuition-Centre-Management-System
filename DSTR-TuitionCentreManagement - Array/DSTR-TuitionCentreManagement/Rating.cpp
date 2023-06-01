#include "General.h"

Rating::Rating() {};

Rating::Rating(int tuition_Id, int tutor_Id, int student_Id, int rating) {
	this->tuition_id = tuition_Id;
	this->tutor_id = tutor_Id;
	this->student_id = student_Id;
	this->rating = rating;
	this->next = NULL;
}

bool Rating::printFile(int size) {
	bool success = false;

	struct Rating* node = this;

	if (size == 0) {
		return success;
	}

	ofstream outData;
	outData.open("Ratings.txt");

	int count = 0;

	while (count < size) {
		outData << node[count].tuition_id << "\t" << node[count].tutor_id << "\t" << node[count].student_id << "\t" << node[count].rating << endl;
		count++;
	}
	success = true;
	return success;
}

bool Rating::editRating(int rate) {
	this->rating = rate;

	bool result = false;
	struct Rating* modifiedRating = this;

	RatingDArray* ratingArr = *RetrieveRatings();
	struct Rating* ratingList = ratingArr->data;
	
	int count = 0;

	while (count < ratingArr->size) {
		if (ratingList[count].tuition_id == modifiedRating->tuition_id && ratingList[count].tutor_id == modifiedRating->tutor_id && ratingList[count].student_id == modifiedRating->student_id) {
			ratingArr->data[count].rating = modifiedRating->rating;
			break;
		}

		count++;
	}

	result = ratingArr->data->printFile(ratingArr->size);

	ratingArr->~RatingDArray();

	return result;
}

void Rating::displayRatings(int size) {

	if (size == 0) return;

	struct Rating* node = this;

	//retrieve tuitions
	TuitionDArray* tuitionArr = *RetrieveTuitions();
	struct Tuition* tuitionList = tuitionArr->data;

	//retrieve tutors
	TutorDArray* tutorArr = *RetrieveTutorByTermination(false);
	struct Tutor* tutorList = tutorArr->data;

	//retrieve subjects
	struct Subject* subjectList = new Subject[5];
	RetrieveSubjects(&subjectList);

	int count = 0;

	while (count < size) {

		if (node[count].rating != 0 || node[count].student_id != getStudentId()) {
			count++;
			continue;
		}

		struct Tuition** tuitionPtr = tuitionList->retrieveById(node[count].tuition_id, tuitionArr->size);
		struct Tuition* tuitionNode = *tuitionPtr;

		struct Tutor** tutorPtr = tutorList->retrieveById(node[count].tutor_id, tutorArr->size);
		struct Tutor* tutorNode = *tutorPtr;

		string subject_code = tutorNode->getSubject();
		struct Subject** subjectPtr = subjectList->searchByCode(subject_code);
		struct Subject* subjectNode = *subjectPtr;

		node->printInfo(tuitionNode, tutorNode, subjectNode);
		count++;
	}

	//free memory
	tuitionArr->~TuitionDArray();
	tutorArr->~TutorDArray();
	subjectList->deleteSubjectList();
}

void Rating::printInfo(struct Tuition* tuition, struct Tutor* tutor, struct Subject* subject) {
	cout << tuition->getInfo() << "\t" << tutor->getFullName() << "\t" << subject->getInfo() << endl;
}

//retrieve by id
struct Rating** Rating::retrieveByTuitionId(int id, int size) {
	struct Rating* node = this;
	struct Rating* result = NULL;

	if (node == NULL || size == 0) return &result;
	int count = 0;

	while (count < size) {
		if (node[count].tuition_id == id && node[count].student_id == getStudentId()) {
			result = &node[count];
			return &result;
		}
		
		count++;
	}

	return &result;
}


//External function
float CalculateRatings(struct Rating** head, int tutor_Id, int size) {

	float result = 0;

	if (size == 0 || *head == NULL) return result;

	struct Rating* node = *head;

	int total = 0, count = 0, index = 0;

	while (index < size) {

		if (node[index].rating == 0) {
			index++;
			continue;
		}

		if (node[index].tutor_id == tutor_Id) {
			total = total + node[index].rating;
			count++;
		}

		index++;
	}

	result = count != 0? total / count : 0;

	return result;
}

class RatingDArray** RetrieveRatings() {
	RatingDArray* ratingArr = new RatingDArray(1);

	ifstream inData;
	inData.open("Ratings.txt");

	int tuition_id, tutor_id, student_id, rating;
	string str_tuition_id, str_tutor_id, str_student_id, str_rating;
	int count = 0;

	while (inData >> str_tuition_id >> str_tutor_id >> str_student_id >> str_rating) {

		tuition_id = stoi(str_tuition_id);
		tutor_id = stoi(str_tutor_id);
		student_id = stoi(str_student_id);
		rating = stoi(str_rating);

		struct Rating input = Rating(tuition_id, tutor_id, student_id, rating);
		

		if (count >= ratingArr->size) {
			//increase array size
			ratingArr->increaseSize(1);

			RatingDArray* newArray = new RatingDArray(*ratingArr);
			ratingArr->~RatingDArray();
			ratingArr = newArray;
		}

		//input tutor element into array
		ratingArr->data[count] = input;

		count++;

	}

	return &ratingArr;

}



void GiveRating() {
	system("CLS");

	//Retrieve rating list;
	RatingDArray* ratingArr = *RetrieveRatings();

	if (ratingArr->size < 1) {
		DisplayStudentMenu();
		return;
	}

	cout << "Tuition_ID" << "\t" << "Date" << "\t\t" << "Tutor" << "\t\t" << "Subject" << endl;;
	//FilterRating(&ratingList);
	ratingArr->data->displayRatings(ratingArr->size);

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
		ratingArr->~RatingDArray();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	if (tuition_id == 0) {
		system("CLS");
		ratingArr->~RatingDArray();
		DisplayStudentMenu();
	}

	if (tuition_id < 0) {
		system("CLS");
		ratingArr->~RatingDArray();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	//retrieve rating record based on tuition id
	struct Rating** ratingPtr = ratingArr->data->retrieveByTuitionId(tuition_id, ratingArr->size);

	if (*ratingPtr == NULL) {
		system("CLS");
		ratingArr->~RatingDArray();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	//rated check
	struct Rating* ratingNode = *ratingPtr;

	if (ratingNode->rating != 0) {
		system("CLS");
		ratingArr->~RatingDArray();
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
		ratingArr->~RatingDArray();
		cout << "Invalid Input!" << endl << endl;
		DisplayStudentMenu();
		return;
	}

	if (rating < 1 || rating > 5) {
		system("CLS");
		ratingArr->~RatingDArray();
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
	ratingArr->~RatingDArray();
	GiveRating();

}

//for student only
//void FilterRating(struct Rating** head) {
//
//	struct Rating* toDelete = *head;
//	struct Rating* prev_node = NULL;
//	struct Rating* next_node = NULL;
//
//	if (*head == NULL) return;
//
//	while (toDelete != NULL) {
//		if (toDelete->student_id == getStudentId()) {
//			prev_node = toDelete;
//			toDelete = toDelete->next;
//			continue;
//		}
//
//		//delete current node
//		next_node = toDelete->next;
//		if (prev_node != NULL) {
//			prev_node->next = next_node;
//		}
//		else {
//			*head = next_node;
//		}
//		free(toDelete);
//		toDelete = next_node;
//	}
//}