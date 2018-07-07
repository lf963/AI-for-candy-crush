#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "homework11ab.h"
using namespace std;

void OutputResult(pair<int,int> &firstStep, int boardSize, vector<string> &board){
	ofstream myOutput;
	myOutput.open ("output.txt",ios::trunc);
	set<pair<int,int>> sameArea = getArea(firstStep.first,firstStep.second,boardSize,board);
	vector<string> afterGravityBoard = gravity(sameArea,boardSize,board);
	myOutput << char(firstStep.second+'A') << firstStep.first+1;
	cout << char(firstStep.second+'A') << firstStep.first+1 << endl;
	for(auto row : afterGravityBoard){
		myOutput << endl << row;
		cout << row << endl;
	}
}

int main(){
	clock_t tStart = clock();
	string line;
	int boardSize,fruitSize;
	float timeRemaining;
	vector<string> board;	//n*n board
	ifstream myfile("input.txt");
	if (myfile.is_open())
	{
		getline(myfile,line);	//first read: algorithm
		boardSize = stoi(line);
		
		getline(myfile,line);
		fruitSize = stoi(line);
		
		getline(myfile,line);
		timeRemaining = stof(line);
		
		
		while(getline(myfile,line)){
			board.push_back(line);
		}
		myfile.close();
		int boardArea = boardSize*boardSize;
		

		
		int score = 0, maxDepth; //if I choose firstStep, I can get how much score
		if(boardSize<=4 || (boardSize==5 && fruitSize==2) || (fruitSize==1)){
			maxDepth = boardArea;
		}
		else if(boardSize==5 && (fruitSize==4 || fruitSize==3)){
			maxDepth = 10;
		}
		else if(boardSize==5 && fruitSize==5){
			maxDepth=9;
		}
		else if(boardSize==5 && fruitSize>=6)
			maxDepth=8;
		else if(boardSize>=6 && boardSize<=10 && fruitSize<=4 && fruitSize>=2)
			maxDepth=7;
		else if((boardSize>=6 && boardSize<=10 && fruitSize<=6 && fruitSize>=5)\
		       || (boardSize>=11 && boardSize<=15 && fruitSize<=3 && fruitSize>=2))
			maxDepth=6;
		else if((boardSize>=6 && boardSize<=10 && fruitSize>=7)\
			   ||(boardSize>=11 && boardSize<=15 && fruitSize<=6 && fruitSize>=4)\
			   ||(boardSize>=15 && boardSize<=20 && fruitSize<=5 && fruitSize>=2)\
			   ||(boardSize>=21 && fruitSize==2)){
			maxDepth=5;
		}
		else if((boardSize>=11 && boardSize<=15 && fruitSize>=7)\
			   ||(boardSize>=15 && boardSize<=20 &&fruitSize>=6))
			maxDepth=4;
		else
			maxDepth=3;

		pair<int,int> firstStep = AlphaBeta(tStart,timeRemaining,maxDepth,score,boardSize,board);
		
		
		OutputResult(firstStep,boardSize,board);
	}

	else
		cout << "Unable to open file" << endl;; 
	
	return 0;
}

