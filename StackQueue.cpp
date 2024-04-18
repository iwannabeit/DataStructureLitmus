#include <iostream>

using namespace std;

class DataStructure{
protected:
  int* array;
  int capacity;
  int ptr;

protected:
  void increaseCapacity(){
    int newCapacity = capacity * 2;
    int* newArray = new int[newCapacity];

    for(int i=0; i<capacity; i++){
      newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
  }

  void decreaseCapacity(){
    int newCapacity = capacity/2 + 1;
    int* newArray = new int[newCapacity];

    for(int i=0; i<newCapacity; i++){
      newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
  }

public:
  explicit DataStructure(int capacity): capacity(capacity){
    array = new int[capacity];
  }

  ~DataStructure(){
    delete[] array;
  }

  virtual void printElements() const{
    throw runtime_error("Not implemented");
  }

  virtual bool isEmpty() const{
    throw runtime_error("Not implemented");
  }

  virtual bool isFull() const{
    throw runtime_error("Not implemented");
  }

  virtual void add(int item){
    throw runtime_error("Not implemented");
  }

  virtual int remove(){
    throw runtime_error("Not implemented");
  }

  virtual int size(){
    throw runtime_error("Not implemented");
  }
};

class Stack : public DataStructure{
public:
  Stack(int capacity) : DataStructure(capacity) {
    DataStructure::ptr = -1;
  }
  ~Stack(){
    DataStructure::ptr = -1;
  }

  void printElements() const override {
    for (int i = ptr; i >= 0; --i) {
      cout << array[i] << " ";
    }
    cout << endl;
  }

 bool isEmpty() const override {
    return ptr == -1;
  }

  bool isFull() const override {
    return ptr == capacity - 1;
  }

  void add(int item) override {
    if (isFull()) {
      increaseCapacity();
    }
    array[++ptr] = item;
  }

  int remove() override {
    if (isEmpty()) {
      throw runtime_error("Stack is empty");
    }
    return array[ptr--];
  }

  int size() override {
    return ptr + 1;
  }
};

class Queue : public DataStructure{
public:
  Queue(int capacity) : DataStructure(capacity) {
    DataStructure::ptr = -1;
  }

  ~Queue(){
    DataStructure::ptr = -1;
  }

  void printElements() const override {
    for (int i = 0; i <= ptr; i++) {
      cout << array[i] << " ";
    }
    cout << endl;
  }

  bool isEmpty() const override {
    return ptr == -1;
  }

  bool isFull() const override {
    return ptr == capacity -1;
  }

  void add(int item) override {
    if (isFull()) {
      increaseCapacity();
    }
    ptr++;
    array[ptr] = item;
  }

  int remove() override {
    if (isEmpty()) {
      throw runtime_error("Queue is empty");
    }
    int item = array[0];
    for(int i=1; i<=ptr; i++){
      array[i-1] = array[i];
    }
    ptr--;
    return item;
  }

  int size() override {
    return ptr + 1;
  }

};

// int main(){
//   Stack st(10);
//   Queue q(10);

//   st.add(1);
//   st.add(2);
//   st.add(3);
//   st.add(4);
//   st.add(5);
//   st.add(6);

//   st.printElements();

//   st.add(9);


//   st.printElements();

//   st.remove();

//   st.printElements();

//   cout << st.size() << endl;

//   return 0;
// }