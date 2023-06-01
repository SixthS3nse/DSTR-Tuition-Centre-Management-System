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
		struct TuitionCentre* tuitionCentreList = new TuitionCentre[3];
		RetrieveTuitionCentres(&tuitionCentreList);

		//Retrieve subjects
		struct Subject* subjectList = new Subject[5];
		RetrieveSubjects(&subjectList);

		//Retrieve tutors
		TutorDArray* tutorArr = *RetrieveTutors();
		struct Tutor* tutorList = tutorArr->data;

		//calculate number of active tutors
		int activeCount = GetTutorSize(&tutorArr->data, false, tutorArr->size);

		int count = 0;

		while (count < tutorArr->size) {

			struct TuitionCentre** tuitionCentrePtr = tuitionCentreList->searchByCode(tutorList[count].getTuitionCentre());
			struct TuitionCentre* tuitionCentreNode = *tuitionCentrePtr;

			struct Subject** subjectPtr = subjectList->searchByCode(tutorList[count].getSubject());
			struct Subject* subjectNode = *subjectPtr;

			outData << tutorList[count].getId() << "\t" << tutorList[count].getFullName() << "\t" << tutorList[count].phone << "\t" << tutorList[count].address
				<< "\t" << subjectNode->getInfo() << "\t" << tuitionCentreNode->getInfo() << "\t" << tutorList[count].getRating() << endl;

			count++;
		}
		
		cout << "================================================" << endl;
		outData << "Number of active tutors: " + activeCount;

		//free memory
		tuitionCentreList->deleteTuitionCentreList();
		tutorArr->~TutorDArray();
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
		TutorDArray* tutorArr = *RetrieveTutors();
		struct Tutor* tutorList = tutorArr->data;
		
		if (tutorArr->size < 1) return;


		TutorDArray* deletedArr = new TutorDArray(0);
		TutorDArray* saveArr = new TutorDArray(0);

		//Retrieve tuition
		TuitionDArray* tuitionArr = *RetrieveTuitions();

		//Retrieve rating
		RatingDArray* ratingArr = *RetrieveRatings();

		int count = 0;

		while (count < tutorArr->size) {

			if (tutorList[count].isTerminated() && tutorList[count].getTerminationDate() == toDelete) {

				//Increase size of deletedArr
				deletedArr->increaseSize(1);

				struct TutorDArray* newDeletedArray = new TutorDArray(*deletedArr);
				deletedArr->~TutorDArray();
				deletedArr = newDeletedArray;

				//add to deleted node
				deletedArr->AddTutorToLast(&tutorList[count]);

			}
			else {

				//Increase size of saveArr
				saveArr->increaseSize(1);

				struct TutorDArray* newSaveArray = new TutorDArray(*saveArr);
				saveArr->~TutorDArray();
				saveArr = newSaveArray;

				//add to save node
				saveArr->AddTutorToLast(&tutorList[count]);
			}
			
			count++;
			
		}

		cout << "================================================" << endl;
		
		saveArr->data->printFile(saveArr->size);

		//free memory
		//tutorArr->~TutorDArray();
		saveArr->~TutorDArray();


		//delete tuition of deleted tutor
		int count2 = 0;

		while (count2 < deletedArr->size) {

			TuitionDArray* saveTuitionArr = new TuitionDArray(0);
			int index = 0;

			while (index < tuitionArr->size) {
				if (tuitionArr->data[index].tutor_id != deletedArr->data[count].getId()) {

					//Increase size of saveTuitionArr
					saveTuitionArr->increaseSize(1);

					struct TuitionDArray* newSaveArray = new TuitionDArray(*saveTuitionArr);
					saveTuitionArr->~TuitionDArray();
					saveTuitionArr = newSaveArray;

					//add to save node
					saveTuitionArr->AddTuitiontToLast(&tuitionArr->data[count]);
					break;
				}

				index++;
			}

			tuitionArr = saveTuitionArr;
			count2++;

		}

		tuitionArr->data->printFile(tuitionArr->size);

		//free memory
		tuitionArr->~TuitionDArray();


		int count3 = 0;

		//delete rating of deleted tutor
		while (count3 < deletedArr->size) {

			RatingDArray* saveRatingArr = new RatingDArray(0);
			int index = 0;

			while (index < ratingArr->size) {
				if (ratingArr->data[index].tutor_id != deletedArr->data[count].getId()) {

					//Increase size of saveTuitionArr
					saveRatingArr->increaseSize(1);

					struct RatingDArray* newSaveArray = new RatingDArray(*saveRatingArr);
					saveRatingArr->~RatingDArray();
					saveRatingArr = newSaveArray;

					//add to save node
					saveRatingArr->AddRatingToLast(&ratingArr->data[count]);
					break;
				}

				index++;
			}

			ratingArr = saveRatingArr;
			count3++;

		}

		ratingArr->data->printFile(ratingArr->size);

		//free memory
		ratingArr->~RatingDArray();

	}
}