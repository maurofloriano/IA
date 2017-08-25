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
  while(!bfsQueue.empty()){

  }
}

int main(){
  return 0;
}
