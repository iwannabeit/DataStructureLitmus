#include <iostream>
#include <queue>
using namespace std;

class CircleQueue{
private:
  queue<int> q;
  int N,K,D;
  int *life;

public:
  CircleQueue(int N, int K, int D) : N(N), K(K), D(D){
    life = new int[N];
  }

  void push(int a){
    q.push(a);
  }

  void size(){
    cout << q.size() << endl;
  }

  void circle(){
    for(int i=1; i<=N; i++){
      q.push(i);
      life[i-1] = D;
    }

    while(!q.empty()){
      if(q.size() > 1){ //7
        for(int i=0; i< K-1; i++){ //k번째 전에는 앞에 값 다시 넣어주기
          q.push(q.front());
          q.pop();
        }

        if(life[q.front()-1] <= 1){ //목숨이 1보다 작으면 pop
          cout << q.front() << ",";
          q.pop();
        }
        else{ //1보다 크면
          life[q.front()-1]--;
          // cout << life[q.front()-1] << endl;
          // q.push(q.front());
          // q.pop();
        }
      }
      else{
        cout << q.front();
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

  cout << ">";

  return 0;
}