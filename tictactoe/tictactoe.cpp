#include <bits/stdc++.h>

using namespace std;

typedef struct matrix{
  int mat[3][3];
  int winner;
}matrix;

vector<matrix> tictactoe;
vector<int> pos;

void bfs(){
  matrix actual;
  queue< pair< int,int > > bfsQueue; // postion of three and actual player;
  bfsQueue.push(make_pair(0,1));
  int player = 1;
  int lim = 1;
  while(!bfsQueue.empty()){
    pair< int, int > index;
    index = bfsQueue.front();
    bfsQueue.pop();
    player = index.second;
    actual = tictactoe[index.first];
    vector<int> son;
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        matrix next = actual;
        if(!next.mat[i][j]){
          next.mat[i][j] = player;
          tictactoe.push_back(next);
          son.push_back(tictactoe.size()-1);
          bfsQueue.push(make_pair(tictactoe.size()-1, player*(-1)));
        }
      }
    }

  }
}

int main(){
  matrix initial;
  memset(initial.mat, 0 , sizeof(initial.mat));
  initial.winner = 0;
  tictactoe.push_back(initial);
  bfs();
  for(int i = 0; i < tictactoe.size(); i++){
    for(int j = 0; j < 3; j++){
      for(int k = 0; k < 3; k++){
        printf("%d ", tictactoe[i].mat[j][k]);
      }
      cout<< endl;
    }
    cout << endl;
  }
  return 0;
}
