#include <iostream>
using namespace std;

class Square{
private:
  int length;
  char** arr;

public:
  Square(int n): length(n){
    arr = new char*[length];
    for(int i=0; i<length; ++i){
      arr[i] = new char[length];
    }
  }  

  ~Square(){
    for(int i=0; i<length; ++i){
      delete[] arr[i];
    }
    delete[] arr;
  }

  void drawSquare(){
    for(int i=0; i<length; ++i){
      for(int j=0; j < length; ++j){
        arr[i][j] = '*';
      }
    }
  }

  void printSquare(){
    for(int i=0; i<length; ++i){
      for(int j=0; j<length; ++j){
        cout << arr[i][j];
      }
      cout << endl;
    }
  }
};

int main(){
  int n;
  cin >> n;

  Square square(n);
  square.drawSquare();
  square.printSquare();

  return 0;
}