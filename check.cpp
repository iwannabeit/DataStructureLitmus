#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <stdexcept>

using namespace std;

class Stack {
  char* array;
  int capacity;
  int top;

  public:
  Stack(int capacity) : capacity(capacity), top(-1){
    array = new char[capacity];
  }

  ~Stack(){
    delete[] array; // 동적할당 메모리 해제
  }

  void push(char item){
    if(top + 1 == capacity){
      char* newArray = new char[capacity * 2];
      memcpy(newArray, array, capacity);
      delete[] array;
      array = newArray;
      capacity *= 2;
    }
    array[++top] = item;
  }

  char pop(){
    if(isEmpty()){
      throw out_of_range("pop : Stack underflow");
    }
    return array[top--];
  }

  bool isEmpty() const{
    return top == -1;
  }

  char peek() const{
    if(isEmpty()){
      throw out_of_range("스택 비어있음");
    }
    return array[top];
  }

  void clear(){
    top = -1;
  }
};

class BracketCheck{
  Stack stack;

public:
  BracketCheck(int capacity): stack(capacity) {}

  void checkMatching(string str){
    Stack stack(100);
    int line_cnt = 0;
    int bracket_cnt = 0;
    bool quote = false;
    bool single_annot = false;
    bool multi_annot = false;

    

    for(int i=0; i<str.length(); i++){
      char c = str[i];
      //따옴표 처리
      if(c == '\"' && !single_annot && !multi_annot){
        if(!quote){
          quote = true;
        } else{
          quote = false;
        }
      }
      //주석처리
      if(c == '/' && !quote && !single_annot && !multi_annot){
        if(str[i+1] == '/'){
          single_annot = true;
        }
        else if(str[i+1] == '*'){
          if(!multi_annot){
            multi_annot = true;
          }
        }
      }
      // 별표 주석이 먼저 나오면
      if(c == '*' && multi_annot){
        if(str[i+1] == '/'){
          if(multi_annot)
            multi_annot = false;
        }
      }

      if((c == '(' || str[i] == '[' || c == '{') && !quote && !single_annot && !multi_annot){
        stack.push(str[i]);
        // cout << "디버깅중 : "<< stack.peek() << endl;
      }
      else if((c == ')' || c == ']' || c=='}') && !quote && !single_annot && !multi_annot){
        if(c == ')'){
          if(!stack.isEmpty()){
            if(stack.peek() == '('){
              stack.pop();
              bracket_cnt++;
            }
            else{
              line_cnt++;
              break;
            }
          }
          else{
            stack.push(c);
          }
        }
        else if(c == ']'){
          if(!stack.isEmpty()){
            if(stack.peek() == '['){
              stack.pop();
              bracket_cnt++;
            }
            else {
              line_cnt++;
              break;
            }
            
          }
          else{
            stack.push(c);
          }
        }
        else if(c == '}'){
          if(!stack.isEmpty()){
            if(stack.peek() == '{'){
              stack.pop();
              bracket_cnt++;
            }
            else{
              line_cnt++;
              break;
            }
          }
          else{
            stack.push(c);
          }
        }
      }
      //개행문자 처리
      if(c == '\n'){
        line_cnt++;
        single_annot = false;
      }
    }

    if(!stack.isEmpty()){
      cout << "Error, Line_count : " << line_cnt << ", bracket_count : " << bracket_cnt << endl;
      return;
    }
    else{
      cout << "OK, Line_count : " << line_cnt << ", bracket_count : " << bracket_cnt << endl;
      return;
    }

  }
};

int main() {
    std::string Str,temp;
    while(true){
        std::getline(std::cin,temp);
        if(temp=="EOF") break;
        Str.append(temp);
        Str.append("\n");
        std::cin.clear();
    }
    
    BracketCheck checker(100);
    checker.checkMatching(Str);
  
  return 0;
}