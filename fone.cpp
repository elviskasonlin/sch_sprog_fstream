//
// File Stream SPROG 
// fone.cpp
//
// Created by elviskason.lin on 10 July 2017
//

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

// ---------- CLASS Student ----------
class student {
  // Private variables
  string name;
  vector <string> subjects;
  vector <float> mark;

public:
  // Set Functions
  void setName(string nameIn) { name = nameIn; }
  void addMark(float value) { mark.push_back(value); }
  void editMark(float value, unsigned int index) { mark[index] = value; }
  void addSubject(string subjectName) { subjects.push_back(subjectName); }
  void editSubject(string subjectName, unsigned int index) { subjects[index] = subjectName; }

  // Get Functions
  string getName() { return name; }
  float getMark(unsigned int index) { return mark[index]; }
  string getSubject(unsigned int index) { return subjects[index]; };

};

// ---------- OPERATION INPUT ----------

/*
  # How input works.

  50 5 (total number of students [totalNum], total number of subjects [totalSubj])
  Mathematics
  Principles of Marketing
  Literature
  Visual Arts
  Geography
  80 50 75 63 25
  90 30 27 65 62
  90 85 87 78 82
  50 70 70 68 76
  .
  .
  .
  50th student.

 */
void loadFile(vector <student> &dt) {
  student tmp;

  // Get name of file to load.
  string fileName;
  cout << "Enter file name for input : ";
  cin >> fileName;

  // Load file.
  ifstream fin;
  fin.open(fileName);

  if (fin.fail()) {
    // IF statement to check whether the file can be opened.
    cout << "/!\\ ERROR. FILE NOT FOUND." << endl;
    cin.clear();
    loadFile(dt);
  } else {
    // ELSE statement should the file be present, continue with getting the data.
    // Get the total number of students specified in the first line.
    int totalNum, totalSubj;
    fin >> totalNum >> totalSubj;

    // Iteration construct to get subject names.
    for (int ia = 0; ia < (int)totalSubj; ia++) {
      string temp; getline(fin, temp);
      tmp.addSubject(temp);
    }

    // Iteration construct to get repeated input
    for (int ia = 0; ia < totalNum; ia++) {
      // Get values for subjects for each student.
      for (int ib = 0; ib < totalSubj; ib++) {
        float temp; fin >> temp;
        tmp.addMark(temp);
      }
    }
  }
  fin.close();
}

int main() {
  // MAIN STORAGE
  vector <student> data;

  // INPUT OPERATION
  loadFile(data);

  return 0;
}
