#include <iostream>
#include <set>
#include <vector>
#include <utility>

using namespace std;
int MAX_Value(clock_t &,float,int,vector<string>,pair<int,int>,int,int,pair<int,int> &,int);

/*cooperate with function getArea*/
void getAreaDFS(int x, int y, int boardSize,vector<string> board,set<pair<int,int>> &sameArea){
	sameArea.insert(make_pair(x,y));
	char fruit = board[x][y];
	if(x+1 < boardSize && board[x+1][y] == fruit && sameArea.find(make_pair(x+1,y)) == sameArea.end())
		getAreaDFS(x+1,y,boardSize,board,sameArea);
	
	if(x-1 >= 0 && board[x-1][y] == fruit && sameArea.find(make_pair(x-1,y)) == sameArea.end())
		getAreaDFS(x-1,y,boardSize,board,sameArea);
	
	if(y+1 < boardSize && board[x][y+1] == fruit && sameArea.find(make_pair(x,y+1)) == sameArea.end())
		getAreaDFS(x,y+1,boardSize,board,sameArea);
	
	if(y-1 >= 0 && board[x][y-1] == fruit && sameArea.find(make_pair(x,y-1)) == sameArea.end())
		getAreaDFS(x,y-1,boardSize,board,sameArea);
}

/*cooperate with function getAreaDFS*/
set<pair<int,int>> getArea(int x, int y, int boardSize,vector<string> board){
	set<pair<int,int>> sameArea;
	getAreaDFS(x,y,boardSize,board,sameArea);
	return sameArea;
}

vector<string> gravity(set<pair<int,int>> sameArea,int boardSize,vector<string> board){
	//let all fruits in sameArea become *
	for(auto pos : sameArea)
		board[pos.first][pos.second] = '*';
	
	// apply gravity, LeetCode 283. Move Zeroes 
	for(int col=0; col<boardSize; col++){
		int i,j;
		for(i=j=boardSize-1; j>=0; j--){
			if(board[j][col] != '*'){
				board[i][col] = board[j][col];
				i--;
			}
		}
		for(;i>=0;i--)
			board[i][col] = '*';
	}
	return board;
}

bool isTerminal(int boardSize, vector<string> board){
	for(int col=0; col<boardSize; col++){
		if(board[boardSize-1][col] != '*')
			return false;
	}
	return true;
}

int MIN_Value(clock_t &tStart,float timeRemaining,int boardSize,vector<string> board,\
	          pair<int,int> boundary, int score, int level,pair<int,int> &goodChoice,\
	           int maxDepth){
	
	clock_t curTimeStamp = clock();
	float curTime = double(curTimeStamp-tStart)/CLOCKS_PER_SEC;
	if(curTime > 0.9*timeRemaining || level >= maxDepth || isTerminal(boardSize,board)){
		return score;
	}

	int v = boundary.second;	//set boundary infinity
	set<pair<int,int>> visited;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if(board[i][j] != '*' && visited.find(make_pair(i,j)) == visited.end()){
				set<pair<int,int>> sameArea = getArea(i,j,boardSize,board);

				int localScore = pow(sameArea.size(),2);

				score -= localScore;
				
				visited.insert(sameArea.begin(),sameArea.end());
				
				vector<string> afterGravityBoard = gravity(sameArea,boardSize,board);
				

				v = min(v,MAX_Value(tStart,timeRemaining,boardSize,afterGravityBoard,\
					boundary,score,level+1,goodChoice,maxDepth));
				
				if(v <= boundary.first){
					return v;
				}
				boundary.second = min(boundary.second,v);
				score += localScore;
			}
			
		}
	}
	return v;
}

int MAX_Value(clock_t &tStart,float timeRemaining, int boardSize,vector<string> board,\
	          pair<int,int> boundary, int score, int level,pair<int,int> &goodChoice,\
	           int maxDepth){
	
	clock_t curTimeStamp = clock();
	float curTime = double(curTimeStamp-tStart)/CLOCKS_PER_SEC;
	if(curTime > 0.9*timeRemaining || level >= maxDepth || isTerminal(boardSize,board)){
		return score;
	}

	int v = boundary.first;	//set boundary -infinity
	set<pair<int,int>> visited;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if(board[i][j] != '*' && visited.find(make_pair(i,j)) == visited.end()){
				set<pair<int,int>> sameArea = getArea(i,j,boardSize,board);

				int localScore = pow(sameArea.size(),2);

				score += localScore;
				visited.insert(sameArea.begin(),sameArea.end());
				

				vector<string> afterGravityBoard = gravity(sameArea,boardSize,board);
				
				int result = MIN_Value(tStart,timeRemaining,boardSize,afterGravityBoard,\
					boundary,score,level+1,goodChoice,maxDepth);
				if(result > v){
					v = result;
					goodChoice = make_pair(i,j);
				}
				
				if(v >= boundary.second){
					return v;
				}
				
				boundary.first = max(boundary.first,v);
				score -= localScore;
			}
		}
	}
	return v;
	
}

pair<int,int> AlphaBeta(clock_t &tStart, float timeRemaining,int maxDepth, int &score, int boardSize, vector<string> board){
	
	pair<int,int> goodChoice(-1,-1);
	pair<int,int> boundary(-pow(boardSize,4)-1,pow(boardSize,4)+1);
	int initialScore = 0, curLevel = 1;
	score = MAX_Value(tStart,timeRemaining,boardSize,board,\
		              boundary,initialScore,curLevel,goodChoice,maxDepth);
	
	return goodChoice;
}

