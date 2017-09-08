#include <bits/stdc++.h>

using namespace std;


/*
  Posições a serem iguais:
    if(a.mat[0][0] == a.mat[0][1] && a.mat[0][1] == a.mat[0][2])
    else if(a.mat[1][0] == a.mat[1][1] && a.mat[1][1] == a.mat[1][2])
    else if(a.mat[2][0] == a.mat[2][1] && a.mat[2][1] == a.mat[2][2])
    else if(a.mat[0][0] == a.mat[1][1] && a.mat[1][1] == a.mat[2][2]) 
    else if(a.mat[0][2] == a.mat[1][1] && a.mat[1][1] == a.mat[2][0]) 
    else if(a.mat[0][0] == a.mat[1][0] && a.mat[1][0] == a.mat[2][0]) 
    else if(a.mat[0][1] == a.mat[1][1] && a.mat[1][1] == a.mat[2][1]) 
    else if(a.mat[0][2] == a.mat[1][2] && a.mat[1][2] == a.mat[2][2]) 

*/

typedef struct matrix{
  int mat[3][3];
  int winner;
  vector<int> son;
}matrix;

vector<matrix> tictactoe;
vector<int> pos;

int checkWinner(matrix a){
  if(a.mat[0][0] == a.mat[0][1] && a.mat[0][1] == a.mat[0][2])
    return a.mat[0][0];     
  else if(a.mat[1][0] == a.mat[1][1] && a.mat[1][1] == a.mat[1][2])
    return a.mat[1][0];  
  else if(a.mat[2][0] == a.mat[2][1] && a.mat[2][1] == a.mat[2][2])
    return a.mat[2][0];  
  else if(a.mat[0][0] == a.mat[1][1] && a.mat[1][1] == a.mat[2][2]) 
    return a.mat[0][0]; 
  else if(a.mat[0][2] == a.mat[1][1] && a.mat[1][1] == a.mat[2][0]) 
    return a.mat[0][2];  
  else if(a.mat[0][0] == a.mat[1][0] && a.mat[1][0] == a.mat[2][0]) 
    return a.mat[0][0];  
  else if(a.mat[0][1] == a.mat[1][1] && a.mat[1][1] == a.mat[2][1]) 
    return a.mat[0][1];  
  else if(a.mat[0][2] == a.mat[1][2] && a.mat[1][2] == a.mat[2][2]) 
    return a.mat[0][2];
  return 0;
}

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
    tictactoe[index.first].winner = checkWinner(tictactoe[index.first]);
    if(tictactoe[index.first].winner)
      continue;
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
    tictactoe[index.first].son = son;
  }
}

void printMatrix(matrix a){
  for(int j = 0; j < 3; j++){
    for(int k = 0; k < 3; k++){
      printf("%d ", a.mat[j][k]);
    }
    cout<< endl;
  }  
}

bool foundPlay;
int indexNextPlay;

void searchNextPlay(int index, int value, int root, int father, int otherPlayer) {
  //cout << tictactoe[index].son.size() <<  endl; 


  if(foundPlay)
    return;

  if(tictactoe[index].winner == value){
    foundPlay = true;
    cout << "got here" << endl;
    return;
  }
     
  bool gotSon = false;
  for(int i = 0; i < tictactoe[index].son.size(); i++){
    gotSon = true;
    int nextIndex = tictactoe[index].son[i];
    cout << nextIndex << endl;
    if(!foundPlay)
    searchNextPlay(nextIndex, value, root, index, otherPlayer);
  }
  if(!gotSon){
    if(tictactoe[index].winner != otherPlayer)
      cout << "draw\n";
      foundPlay = true;
  }

  if( root == father and foundPlay){
    cout << "got here in index " << index << endl;
    if(indexNextPlay == -1)
      indexNextPlay = index;
    return;
  } 
}

int minmax(){
  // defined that player will be max and machine min
  // 1 is max and -1 is min
  
  int player = 1;
  int index = 0;
  bool stillHasPlays = true;
  while(stillHasPlays){
    foundPlay = false;
    if(player == 1){
      indexNextPlay=-1;
      searchNextPlay(index, player, index, -1, player*(-1));
      cout << " Proximo indice  "<<indexNextPlay << endl;
      if(indexNextPlay == -1){
        searchNextPlay(index, 2, index, -1, player*(-1));
      }
      index = indexNextPlay;
    } else{
      indexNextPlay=-1;
      searchNextPlay(index, player, index, -1, player*(-1));
      if(indexNextPlay == -1){
        searchNextPlay(index, 2, index, -1, player*(-1));
      }
      index = indexNextPlay;
    }
    
    stillHasPlays = true;

    player*=(-1);
  }

}

int main(){
  matrix initial;
  memset(initial.mat, 0 , sizeof(initial.mat));
  initial.winner = 0;
  tictactoe.push_back(initial);
  bfs();
  minmax();
  return 0;
}
