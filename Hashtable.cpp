#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

struct Student {
  char firstName[20];
  char lastName[20];
  int id;
  float gpa;
  bool operator == (const Student& o){
    return o.id == this->id && strcmp(o.firstName, this->firstName) == 0 && strcmp(o.lastName, this->lastName) == 0;
  }
};

struct Node {
  Node* next;
  Student* student;
};

using namespace std;

void strupper(char* str);
void addStudent(Node**&, int&, int&);
void printStudent(Node**, int);
void deleteStudent(Node**&, int, int&);
void generateRandom(Node**&, vector<char*>*, vector<char*>*, int&, int&);
int addChain(Node**&, int, Student*);
void rehash(Node**&, int&);
int getHash(char*, int);
bool readNames(vector<char*>*, char*, int);

int main()
{
  Node** hashTable = NULL;
  int size = 100;
  int numStudents = 0;
  hashTable = new Node*[size];
  srand(time(NULL));
  for (int i = 0; i < size; i++){
    hashTable[i] = NULL;
  }
  vector<char*>* firstNames = new vector<char*>();
  vector<char*>* lastNames = new vector<char*>();
  char* fileName = new char();
  strcpy(fileName, "firstnames.txt");
  if (!readNames(firstNames, fileName, 2000)){
    return 1;
  }
  strcpy(fileName, "lastnames.txt");
  if (!readNames(lastNames, fileName, 1000)){
    return 1;
  }
  bool running = true;
  while (running == true){
    char input[80];
    cout<<"Do you want to add a student, print out the students, delete a student, generate random students, or quit?"<<endl;
    cin.getline(input, sizeof(input));
    strupper(input);
    if (strcmp(input, "ADD") == 0){
      addStudent(hashTable, size, numStudents);
    }
    else if (strcmp(input, "PRINT") == 0){
      printStudent(hashTable, size);
    }
    else if (strcmp(input, "DELETE") == 0){
      deleteStudent(hashTable, size, numStudents);
    }
    else if (strcmp(input, "RANDOM") == 0){
      generateRandom(hashTable, firstNames, lastNames, numStudents, size);
    }
    else if (strcmp(input, "QUIT") == 0){
      running = false;
    }
    else{
      cout<<"That's an invalid command"<<endl;
    }
  }
  delete[] hashTable;
  return 0;
}

void strupper(char* str){
  int len = strlen(str);
  for (int i = 0; i < len; i++){
    str[i] = touppper(str[i]);
  }
}

void addStudent(Node**& hashTable, int& size, int& numStudents){
  Student* newStudent = new Student();
  cout<<"Enter the student's first name"<<endl;
  cin.getline(newStudent->firstName, 20);
  cout<<"Enter the student's last name"<<endl;
  cin.getline(newStudent->lastName, 20);
  cout<<"Enter the student's ID"<<endl;
  cin>>newStudent->id;
  cin.clear();
  cin.ignore(999, '\n');
  cout<<"Enter the student's GPA"<<endl;
  cin>>newStudent->gpa;
  cin.clear();
  cin.ignore(999, '\n');
  int hash = (getHash(newStudent->firstName, size)+getHash(newStudent->lastName, size)*3+newStudent->id)%size;
  int ret = addChain(hashTable, hash, newStudent);
  if (ret == -1){
    cout<<"Duplicate student found"<<endl;
    return;
  }
  numStudents++;
  if (ret > 3 || numStudents > size/2){
    rehash(hashTable, size);
  }
}
