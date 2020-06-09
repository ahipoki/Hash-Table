#include <iostream>
#include <cstring>

using namespace std;

void strupper(char* str);

int main()
{
  bool running = true;
  while (running == true){
    char input[80];
    cout<<"Do you want to add a student, print out the students, delete a student, or quit?"<<endl;
    cin.getline(input, sizeof(input));
    strupper(input);
    
  }
}

void strupper(char* str){
  int len = strlen(str);
  for (int i = 0; i < len; i++){
    str[i] = touppper(str[i]);
  }
}
