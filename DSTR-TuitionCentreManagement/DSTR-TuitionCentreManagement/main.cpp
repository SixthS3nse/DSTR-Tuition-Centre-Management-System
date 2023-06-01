#include "General.h"

string role = "";
string tuitionCentreCode = "";
int student_id = -1;

int main() {

	Login();


}

string getRole() {
	return role;
}

void setRole(string r) {
	role = r;
}

string getTuitionCentreCode() {
	return tuitionCentreCode;
}

void setTuitionCentreCode(string code) {
	tuitionCentreCode = code;
}

int getStudentId() {
	return student_id;
}

void setStudentId(int id) {
	student_id = id;
}

string date(string delimiter, int d = NULL, int m = NULL, int y = NULL) {

	//get current datetime
	time_t t = time(NULL);

	//input into struct
	struct tm today;
	localtime_s(&today, &t);

	int day, month, year;

	year = (y == NULL) ? today.tm_year + 1900 : y;
	month = (m == NULL) ? today.tm_mon + 1 : m;
	day = (d == NULL) ? today.tm_mday : d;

	//put into format
	stringstream ss_day, ss_month;
	ss_day << setw(2) << setfill('0') << day;
	string result = ss_day.str();

	result += delimiter;
	
	ss_month << setw(2) << setfill('0') << month;
	result = result + ss_month.str();
	result += delimiter + to_string(year);

	return result;
}

tm todayStruct() {
	//get current datetime
	time_t t = time(NULL);

	//input into struct
	struct tm today;
	localtime_s(&today, &t);

	return today;
}

void GenerateReport() {
	struct tm now = todayStruct();

	if (now.tm_wday == 0 && now.tm_hour == 0 && now.tm_min == 0 && now.tm_sec == 0) {
		//Generate report
		string fileName = date("", NULL, NULL, NULL) + "- Weekly Report.txt";

		ofstream outData;
		outData.open(fileName);

		//Retrieve tuition centres
		struct TuitionCentre* tuitionCentreList = NULL;
		RetrieveTuitionCentres(&tuitionCentreList);

		//Retrieve subjects
		struct Subject* subjectList = NULL;
		RetrieveSubjects(&subjectList);

		//Retrieve tutors
		struct Tutor* tutorList = NULL;
		RetrieveTutors(&tutorList);

		//calculate number of active tutors
		int count = GetTutorSize(&tutorList, false);

		while (tutorList != NULL) {

			struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutorList->getTuitionCentre());
			struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

			struct Subject** subjectPtr = subjectList->searchByCode(tutorList->getSubject());
			struct Subject* subjectNode = *subjectPtr;

			outData << tutorList->getId() << "\t" << tutorList->getFullName() << "\t" << tutorList->phone << "\t" << tutorList->address
				<< "\t" << subjectNode->getInfo() << "\t" << tuitionCentreNode->getInfo() << "\t" << tutorList->getRating() << endl;

			tutorList = tutorList->next;
		}
		
		cout << "================================================" << endl;
		outData << "Number of active tutors: " + count;

		//free memory
		tuitionCentreList->deleteTuitionCentreList();
		tutorList->deleteTutorList();
		subjectList->deleteSubjectList();
	}
}

void DeleteTutor() {
	struct tm now = todayStruct();

	if (now.tm_wday == 0 && now.tm_hour == 0 && now.tm_min == 0 && now.tm_sec == 0) {

		struct tm dateToDelete = now;
		
		int monthToDelete = dateToDelete.tm_mon - 6;

		if (monthToDelete < 0) {
			monthToDelete += 11;
			dateToDelete.tm_year -= 1;
			dateToDelete.tm_mon = monthToDelete;
		}

		string toDelete = date("/", dateToDelete.tm_mday, dateToDelete.tm_mon + 1, dateToDelete.tm_year + 1990);


		//Retrieve tutors
		struct Tutor* tutorList = NULL;
		struct Tutor* tutor_prev_node = NULL;
		struct Tutor* tutor_next_node = NULL;
		RetrieveTutors(&tutorList);

		struct Tutor* deletedNodes = NULL;

		//Retrieve tuition
		struct Tuition* tuitionList = NULL;
		struct Tuition* tuition_prev_node = NULL;
		struct Tuition* tuition_next_node = NULL;
		RetrieveTuitions(&tuitionList);

		//Retrieve rating
		struct Rating* ratingList = NULL;
		struct Rating* rating_prev_node = NULL;
		struct Rating* rating_next_node = NULL;
		RetrieveRatings(&ratingList);


		while (tutorList != NULL) {

			if (tutorList->isTerminated() && tutorList->getTerminationDate() == toDelete) {
				//delete current node
				tutor_next_node = tutorList->next;

				if (tutor_prev_node != NULL) {
					tutor_prev_node->next = tutor_next_node;
				}

				//add to deleted node
				tutorList->next = NULL;
				AddTutorToLast(&deletedNodes, tutorList);

				tutorList = tutor_next_node;
				continue;
			}
			
			tutor_prev_node = tutorList;
			tutorList = tutorList->next;
			
		}

		cout << "================================================" << endl;
		
		tutorList->printFile();

		//free memory
		tutorList->deleteTutorList();

		//pointer of deleted tutors
		struct Tutor** deletedNodePtr = &deletedNodes;

		//delete tuition of deleted tutor
		while (tuitionList != NULL) {

			struct Tutor* deletedNode = *deletedNodePtr;

			while (deletedNode) {
				if (tuitionList->tutor_id == deletedNode->getId()) {
					//delete current node
					tuition_next_node = tuitionList->next;

					if (tuition_prev_node != NULL) {
						tuition_prev_node->next = tuition_next_node;
					}

					tuitionList = tuition_next_node;
					break;
				}

				deletedNode = deletedNode->next;

			}

			tuition_prev_node = tuitionList;
			tuitionList = tuitionList->next;

		}

		tuitionList->printFile();

		//free memory
		tuitionList->deleteTuitionList();


		//delete rating of deleted tutor
		while (ratingList != NULL) {

			struct Tutor* deletedNode = *deletedNodePtr;

			while (deletedNode != NULL) {
				if (ratingList->tutor_id == deletedNode->getId()) {
					//delete current node
					rating_next_node = ratingList->next;

					if (rating_prev_node != NULL) {
						rating_prev_node->next = rating_next_node;
					}

					ratingList = rating_next_node;
					break;;
				}

				deletedNode = deletedNode->next;
			}

			rating_prev_node = ratingList;
			ratingList = ratingList->next;
		}

		ratingList->printFile();

		//free memory
		ratingList->deleteRatingList();

	}
}