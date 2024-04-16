#include <iostream>
using namespace std;
#include <cctype>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <limits>

class Stack {
  string* array;
  int capacity;
  int top;

  public:
  Stack(int capacity) : capacity(capacity), top(-1){
    array = new string[capacity];
  }

  ~Stack(){
    delete[] array; // 동적할당 메모리 해제
  }

  void push(string item){
    if(top + 1 == capacity){
      string* newArray = new string[capacity * 2];
      memcpy(newArray, array, capacity);
      delete[] array;
      array = newArray;
      capacity *= 2;
    }
    array[++top] = item;
  }

  string pop(){
    if(isEmpty()){
      throw out_of_range("pop : Stack underflow");
    }
    return array[top--];
  }

  bool isEmpty() const{
    return top == -1;
  }

  string peek() const{
    if(isEmpty()){
      throw out_of_range("스택 비어있음");
    }
    return array[top];
  }

  void clear(){
    top = -1;
  }
};

int priority(string op){
  if(op == "+" || op == "-") return 1;
  if(op == "*" || op == "/") return 2;
  return 0;
}

//중위표기 -> 후위표기
string infixToPostfix(const string &infix){
  string postfix;
  Stack stack(100);

  stringstream ss(infix);
  string c;

  while (!ss.eof()){
    ss >> c;

    if(c == "+" || c == "-" || c == "*" || c == "/"){ //isalpha -> 알파벳인지 확인하는 함수 , isdigit -> 숫자인지 확인하는 함수
      while(!stack.isEmpty() && priority(c) <= priority(stack.peek())){ //스택에 있는 값이 우선순위가 더 크면
        postfix += stack.pop() + " "; 
      }
      stack.push(c);

    } else if (c == "("){
      stack.push(c);
    } else if( c== ")"){
      while(!stack.isEmpty() && stack.peek() != "("){
        postfix += stack.pop()+ " ";
      }
      stack.pop();
    } else{ //숫자
      postfix += c + " ";
    }
  }
  //남아있는 것들 모두 pop
  while(!stack.isEmpty()){
    postfix += stack.pop()+" ";
  }

  return postfix;
}

void evaluatePostfix(const string& postfix){
  Stack stack(100);

  stringstream ss(postfix);
  string c;

  while(ss >> c){
    //연산자이면
    if(c == "+" || c == "-" || c == "*" || c == "/"){
      double val2 = stod(stack.pop());
      double val1 = stod(stack.pop());
      
      if(c == "+"){
        stack.push(to_string(val1 + val2));
      } else if(c == "-"){
        stack.push(to_string(val1 - val2));
      } else if(c == "*"){
        stack.push(to_string(val1 * val2));
      } else{
        if(val2 == 0){
          cout << "Error : zero division error" << endl;
          return;
        }
        stack.push(to_string(val1 / val2));
      }

    } else { //숫자면
      stack.push(c); //ASCII 코드 0이 '48'을 빼줌으로써 
    }
  }

  cout << fixed << setprecision(2) << stod(stack.pop()) << endl; //최종 결과
  
}

int main() {
    string infix;
    getline(cin, infix);

    string postfix = infixToPostfix(infix);

    evaluatePostfix(postfix);

    return 0;
}