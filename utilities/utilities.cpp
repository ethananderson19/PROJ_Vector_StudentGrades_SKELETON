#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, 
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}
/***
 * Clears allStudentData, Opens file, For each line; parses name, midterm1,midterm2 and an
 * optional finalgrade (if present in file)from that line. Puts this info into a studentData struct,
 * adds this struct to allstudentData vector.
 * NOTE:
 * Ignore empty lines
 * Non empty lines will contain 4 or 5 values to be parsed.
 * the default param separator_char is defined in the header file declaration of readFile ONLY, it is not in the readFile definition.
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds the student data info after it has been read from file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int readFile(std::string &file, std::vector<KP::studentData> &allstudentData, char char_to_search_for) {
	allstudentData.clear();

	std::string line;
	std::string token;
	KP::studentData myStudentData;
	stringstream ss;
	fstream myInputfile;

	myInputfile.open(file.c_str(), ios::in);

	if (!myInputfile.is_open()){
		return KP::COULD_NOT_OPEN_FILE;
	}

	while (std::getline(myInputfile,line)) {
		ss.clear();

		ss.str(line);

		myStudentData.clear();
		//get the name
		std::getline(ss, myStudentData.name, char_to_search_for);
		//get the midterm 1
		std::getline(ss, token, char_to_search_for);
		myStudentData.midterm1=stringToInt(token.c_str());
		//get the midterm 2
		std::getline(ss, token, char_to_search_for);
		myStudentData.midterm2=stringToInt(token.c_str());

		allstudentData.push_back(myStudentData);
	}
	myInputfile.close();
	return KP::SUCCESS;

}



/***
 * Iterates over all students in vector, and averages midterm1 and midterm2 to get the finalgrade
 * @param allstudentData
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData){

	if (allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}
	for(long unsigned int a = 1; a < allstudentData.size(); a++){
		allstudentData[a].finalgrade = (allstudentData[a].midterm1+allstudentData[a].midterm2)/2;
	}
	return KP::SUCCESS;

	}
//void extractFailingStudents(double failgrade = FAILGRADE);

/***
 * Opens file, serializes data from allstudentData to file, closes file
 * the default param seperator_char is defined in the header file ONLY
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         COULD_NOT_OPEN_FILE
 *         SUCCESS
 */

int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char char_to_search_for){
	ofstream myOutfile;
	if(allstudentData.empty()){
			return KP::VECTOR_CONTAINS_NO_STUDENTS;
		}
	myOutfile.open(file, ios::out);

	if (!myOutfile.is_open()){
		return KP::COULD_NOT_OPEN_FILE;
	}

	for(long unsigned int a = 0 ; a < allstudentData.size();a++){
		myOutfile << allstudentData[a].name << " " << allstudentData[a].midterm1 << " " << allstudentData[a].midterm2 << " " << allstudentData[a].finalgrade << "\n";



	}
	myOutfile.close();
	return KP::SUCCESS;


}


/***
 *
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param st - how to sort the vector
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
bool compareName (KP:: studentData& x, KP:: studentData& y) {
	return x.name < y.name;
}
// Used to sort the students from highest to lowest final grade
bool compareFinal (KP:: studentData& x, KP:: studentData& y){
	return x.finalgrade > y.finalgrade;
}
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st){
	KP::SORT_TYPE name = KP::NAME;
	KP::SORT_TYPE finalgrade = KP::FINAL_GRADE;

	//checks for an empty student data vector
	if (allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;;
	}

	if (st == name){
		sort(allstudentData.begin(), allstudentData.end(), compareName);

	}

	if (st == finalgrade){
		sort(allstudentData.begin(), allstudentData.end(), compareFinal);

	}
	return KP::SUCCESS;



}
//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, very fragile

