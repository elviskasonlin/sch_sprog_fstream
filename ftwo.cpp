//
// SPROG File Stream Sample
// ftwo.cpp
//
// Created by elviskason.lin on 17 July 2017
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// ---------- VAR Global Variables ----------
vector <string> subjects;
int totalStudents, totalSubj;

// ---------- CLASS Student ----------
class student {
  // VAR
  string name;
  vector <float> marks;
  float average;

public:
  // GETTER
  string getName(void) { return name; }
  float getMark(int index) { return marks[index]; }
  float getAverage(void) { return average;}

  // SETTER
  void setName(string input_name) { name = input_name; }
  void addMark(float input_mark) { marks.push_back(input_mark); }
  void editMark(float input_mark, unsigned int index) { marks[index] = input_mark; }
  void processAverage(void) {
    float sum = 0;
    for (int x = 0; x < (int)marks.size(); x++) { sum += getMark(x); }
    average = sum / marks.size();
  }
};

// ---------- FUNC MISC ----------

// ----- GET INPUT <unsigned short int> -----
unsigned short int getMenuChoice(string argcs) {
  unsigned short int choice;
  cout << argcs ; cin >> choice;
  return choice;
}

// ---------- FUNC Load File ----------

// REMEMBER TO ADD PROMPT TO ASK WHETHER USER WISHES TO LOAD NEW DATASET

void loadFile(vector <student> &data) {
  // Initial User Greetings
  cout << "\n ---------- \nFILE LOADING\n ---------- \n" << endl;

  // Get file name
  string fileName;
  cout << "\nEnter file name for input : ";
  cin >> fileName;
  cin.clear();
  cout << "***** Trying to find : \"" << fileName << "\"" << endl;

  // Initialise file stream
  ifstream fin;
  fin.open(fileName);

  // IF Statement to check whether file exists.
  if (fin.fail()) {
    cout << "***** ERROR. No such file or directory." << endl;
    cin.clear();
    // A small prompt to check whether user wish to try to load again.
    char choice;
    cout << "Do you wish to load another file? Y to Load." << endl << "Your choice : "; cin >> choice;
    if (choice == 'y' || choice == 'Y') { loadFile(data); } else { return; }

  } else {
    // Get variables for total number of Students & Subjects
    fin >> totalStudents >> totalSubj;
    fin.ignore();

    // Iteration construct to get subject names.
    for (int ia = 0; ia < totalSubj; ia++) {
      string temp; getline(fin, temp);
      subjects.push_back(temp);
    }
    fin.ignore();

    // Iteration construct to get marks for each student.
    for (int ib = 0; ib < totalStudents; ib++) {
      student buffer; // Create a temporary object called buffer that uses student construct.
      string name; float temp;

      // Get student name
      getline(fin, name);
      buffer.setName(name);

      // Get student marks
      for (int ic = 0; ic < totalSubj; ic++) {
        fin >> temp;
        buffer.addMark(temp); // Push back to internal vector.
      }

      buffer.processAverage(); // Processes the average for the person.
      data.push_back(buffer);
      fin.ignore();
    }

    cout << "***** File \"" << fileName << "\" loaded successfully!" << endl;
    cout << "Total number of students : " << data.size() << endl << endl;
  }
  fin.close();
}

// --------- FUNC Output File ----------

void outputFile(vector <student> &data) {
  
}

// --------- FUNC DISPLAY ----------

void displayMenu() {
  cout << "\n ---------- \nAVAILABLE FUNCTIONS\n ---------- \n" << endl;
  cout << "1. Load Student Data File\n2. Display Statistics ...\n3. DEBUG Display Raw Data\n0. EXIT PROGRAM\n";
}

void displayStats(vector <student> &data) {
  // Ask for type of data to show.
  // EXAMPLES
  // Number of Failures, Number of Passes, Number of Distinctions, Standard Deviation, Weighted Mean.
}

void debug_displayData(vector <student> &data) {
  cout << "\n ---------- \nDEBUG DISPLAY DATA\n ---------- \n" << endl;
  cout << "Total num of Students : " << totalStudents << " Total num of Subjects : " << totalSubj << endl;

  for (int i = 0; i < totalStudents; i++) {
    cout << data[i].getName() << " " << data[i].getAverage() << endl;
    for (int ib = 0; ib < totalSubj; ib++) {
      cout << subjects[ib] << " : " << data[i].getMark((unsigned int)ib) << "\t";
    }
    cout << endl;
  }
}

int main() {
  vector <student> data;
  unsigned short int menuChoice = 1;

  cout << endl << "DATA ANALYSIS PROGRAMME V1.0.0a" << endl << "Written by Py." << endl << "-------------------------------\n\n";

  while (menuChoice != 0) {
    displayMenu();
    menuChoice = getMenuChoice("Enter your choice : ");
    switch (menuChoice) {
      case 0 : cout << "/!\\ EXITING PROGRAM" << endl; break;
      case 1 : loadFile(data); break;
      case 2 : displayStats(data); break;
      case 3 : debug_displayData(data); break;
      default : break;
    }
  }

  return 0;
}
