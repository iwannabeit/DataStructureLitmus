#include <iostream>

using namespace std;

class Queue{
public:
  int *data;
  int capacity;
  int rear, front;
  int count;

public:
  Queue(int capacity) : capacity(capacity){
    data = new int[capacity];
    front = rear = count = 0;
  }

  ~Queue(){
    delete[] data;
  }

  bool isEmpty(){
    return front == rear;
  }

  bool isFull(){
    return (rear + 1) % capacity == front;
  }

  void push(int val){
    if(isFull()){
      cout << "포화 상태" << endl;
    }
    else{
      rear = (rear + 1) % capacity;
      data[rear] = val;
      count++;
    }
  }

  int pop(){
    if(isEmpty()){
      cout << "비어 있음" <<endl;
      return 0;
    }
    else{
      front = (front + 1) % capacity;
      count--;
      return data[front];
    }
  }

  int getFront(){
    if(isEmpty()){
      cout << "비어 있음" <<endl;
      return 0;
    }
    else{
      return data[(front+1) % capacity];
    }
  }

  int size(){
    return count;
  }
  
};

class CircleQueue{
public:
  int N,K,D;
  int *life;

public:
  CircleQueue(int N, int K, int D) : N(N), K(K), D(D){
    life = new int[N];
  }

  void circle(){
    Queue q(N+1);

    for(int i=1; i<=N; i++){
      q.push(i);
      life[i-1] = D;
    }

    while(!q.isEmpty()){
      if(q.size() > 1){ //7
        for(int i=0; i< K-1; i++){ //k번째 전에는 앞에 값 다시 넣어주기
          int f = q.pop();
          q.push(f);
        }

        if(life[q.getFront()-1] <= 1){ //목숨이 1보다 작으면 pop
          cout << q.getFront() << ",";
          q.pop();
        }
        else{ //1보다 크면
          life[q.getFront()-1]--;
        }
      }
      else{
        cout << q.getFront();
        q.pop();
      }
    }
  }

};


int main(){

  int N, K, D;

  cin >> N >> K >> D;
  CircleQueue circle(N, K, D);

  cout << "<";

  circle.circle();

  cout << ">\n";

  return 0;
}