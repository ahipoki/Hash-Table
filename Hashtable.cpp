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

void printStudent(Node** hashTable, int size){
  bool students = false;
  for (int i = 0; i < size; i++){
    if (hashTable[i] == NULL){
      continue;
    }
    Node* n = hashTable[i];
    students = true;
    do{
      cout<<endl;
      cout<<"Student: "<<n->student->firstName<<" "<<n->student->lastName<<endl;
      cout<<"ID: "<<n->student->id<<endl;
      cout<<"GPA: "<<n->student->id<<endl;
      n = n->next;
    } while (n != NULL);
  }
  if (!students){
    cout<<"Student list is currently empty"<<endl;
    cout<<endl;
  }
}

void deleteStudent(Node**& hashTable, int size, int& numStudents){
  Student* removeStudent = new Student();
  cout<<"Enter student's first name"<<endl;
  cin.getline(removeStudent->firstName, 20);
  cin.clear();
  cin.ignore(999, '\n');
  cout<<"Enter student's last name"<<endl;
  cin.getline(removeStudent->lastName, 20);
  cin.clear();
  cin.ignore(999, '\n');
  cout<<"Enter student's ID"<<endl;
  cin>>removeStudent->id;
  cin.clear();
  cin.ignore(999, '\n');
  int hash = (getHash(removeStudent->firstName, size)+getHash(removeStudent->lastName, size)*3+removeStudent->id)%size;
  Node* n = hashTable[hash];
  Node* prev = NULL;
  if (hashTable[hash] != NULL){
    do{
      if (*(n->student) == *removeStudent){
        if (prev == NULL){
          hashTable[hash] = n->next;
          delete n;
        }
        else{
          prev->next = n->next;
          delete n;
        }
        numStudents--;
        return;
      }
      prev = n;
      n = n->next;
    } while (n != NULL);
  }
  cout<<"That student could not be found"<<endl;
  return;
}

void generateRandom(Node**& hashTable, vector<char*>* firstNames, vector<char*>* lastNames, int& numStudents, int& size){
  cout<<"Enter the amount of students you want to generate"<<endl;
  int numToGenerate;
  cin>>numToGenerate;
  cin.ignore(999, '\n');
  if (numToGenerate <= 0){
    cout<<"You cannot generate negative students"<<endl;
    return;
  }
  if (numToGenerate > 1000){
    cout<<"You cannot generate that many students! It will now set it to 100"<<endl;
    numToGenerate = 100;
  }
  for (int i = 0; i < numToGenerate; i++){
    Student* newStudent = new Student();
    int random = rand()%2000;
    strcpy(newStudent->firstName, firstNames->at(random));
    random = rand()%1000;
    strcpy(s->lastName, lastNames->at(random)); 
    newStudent->id = numStudents++;
    newStudent->gpa = float(rand()%350+100)/100;
    int hash = (getHash(newStudent->firstName, size) + getHash(newStudent->lastName, size)*3 + newStudent->id)%size;
    int chainlength = addChain(hashTable, hash, newStudent);
    if (chainlength > 3 || numStudents > size/2){
      rehash(hashTable, size);
    }
  }
}

int addChain(Node**& hashTable, int h, Student* s){
  if (hashTable[h] == NULL){
    hashTable[h] = new Node();
    hashTable[h]->student = s;
    return 0;
  }
  int chainLength = 0;
  Node* link = hashTable[h];
  while (link->next != NULL){
    if (*(link->student) == *s){
      return -1;
    }
    link = link->next;
    chainLength++;
  }
  if (*(link->student) == *s){
      return -1;
  }
  link->next = new Node();
  link->next->student = s;
  return chainLength;
}

void rehash(Node**& hashTable, int& size){
  Node** tempHash = new Node*[size*2];
  for (int i = 0; i < size*2; i++){
    tempHash[i] = NULL;
  }
  for (int i = 0; i < size; i++){
    if (hashTable[i] == NULL){
      continue;
    }
    Node* n = hashTable[i];
    do{
      Student* s = n->student;
      int hash = (getHash(s->firstName, size*2) + getHash(s->lastName, size*2)*3 + s->id)%(size*2);
      addChain(tempHash, hash, s);
      n=n->next;
    } while (n != NULL);
  }
  delete[] hashTable;
  hashTable = tempHash;
  size *= 2;
}

int getHash(char* s, int size){
  int hash = 3;
  for (int i = 0; i < strlen(s); i++){
    hash *= 71993;
    hash += int(s[i]);
    hash %= size;
  }
  hash *= 71993;
  hash %= size;
  return hash;
}

bool readNames(vector<char*>* names, char* firstName, int n){
  ifstream fileStream(firstName);
  if (!fileStream.is_open()){
    cout<<"Couldn't read from file"<<endl;
    return false;
  }
  for (int i = 0; i < n; i++){
    char name[80];
    fileStream.getline(name, sizeof(name));
    if (n == 1000){
      name[strlen(name)-1] = '\0';
    }
    names->push_back(name);
  }
  return true;
}
