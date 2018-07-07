# AI-for-fruit-rage
This project is able to select the best one step in Fruit Rage Game. We use [Minimax Algorithm](https://en.wikipedia.org/wiki/Minimax) with [Alpha–beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) to solve this problem.

## Rules of Fruit Rage
The Fruit Rage is a two player game in which each player tries to maximize his/her share from a batch of fruits randomly placed in a box. The box is divided into cells and each cell is either empty or filled with one fruit of a specific type.

At the beginning of each game, all cells are filled with fruits. Players play in turn and can pick a cell of the box in their own turn and claim all fruit of the same type, in all cells that are connected to the selected cell through horizontal and vertical paths. For each selection or move the agent
is rewarded a numeric value which is the square of the number of fruits claimed in that move. Once an agent picks the fruits from the cells, their empty place will be filled with other fruits on top of them (which fall down due to gravity), if any. In this game, no fruit is added during game
play. Hence, players play until all fruits have been claimed.

The overall score of each player is the sum of rewards gained for every turn. The game will terminate when there is no fruit left in the box or when a player has run out of time.


## Getting Started

You need C++11 compiler because this project is done in C++11.

## Running the tests
The file ```input.txt``` is our input file and its format is:
```
1. First line: integer n, the width and height of the square board (0 < n < 27)

2. Second line: integer p, the number of fruit types (0 < p < 10)

3. Third line: strictly positive floating point number, your remaining time in seconds

4. Next n lines: the n x n board, with one board row per input file line, and n characters (plus endof-line marker) on each line. Each character can be either a digit from 0 to p-1, or a * to denote an empty cell. 
```

We have to output our result as ```output.txt``` whose format is:
```
1. First line: your selected move, represented as two characters: 
A letter from A to Z representing the column number (where A is the leftmost column, B is the next one to the right, etc), and
A number from 1 to 26 representing the row number (where 1 is the top row, 2 is the row below it, etc).

2. Next n lines: the n x n board just after your move and after gravity has been applied to make any fruits fall into holes created by your move taking away some fruits.
```

Just compile and run ```main.cpp```.