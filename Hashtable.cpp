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
  bool running = true;
  while (running == true){
    char input[80];
    cout<<"Do you want to add a student, print out the students, delete a student, or quit?"<<endl;
    cin.getline(input, sizeof(input));
    strupper(input);
    if (strcmp(input, "ADD") == 0){
      
    }
    else if (strcmp(input, "PRINT") == 0){
      
    }
    else if (strcmp(input, 
  }
}

void strupper(char* str){
  int len = strlen(str);
  for (int i = 0; i < len; i++){
    str[i] = touppper(str[i]);
  }
}
