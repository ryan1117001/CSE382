#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

class cell {
public:
	int id;
	int wall;
	int visited;
	int from;
	cell() { visited = 0; from = -1; }
};

void DFS(vector<cell> &maze, int n, int start, int end);
void BFS(vector<cell> &maze, int n, int start, int end);
int checkright(vector<cell> &maze, int top);
int checkleft(vector<cell> &maze, int top);
int checktop(vector<cell> &maze, int top);
int checkbottom(vector<cell> &maze, int top);
void moveright(vector<cell> &maze, stack<int> &dfsstack, int top);
void moveleft(vector<cell> &maze, stack<int> &dfsstack, int top);
void movetop(vector<cell> &maze, stack<int> &dfsstack, int top, int n);
void movebottom(vector<cell> &maze, stack<int> &dfsstack, int top, int n);
void moveright(vector<cell> &maze, queue<int> &dfsstack, int top);
void moveleft(vector<cell> &maze, queue<int> &dfsstack, int top);
void movetop(vector<cell> &maze, queue<int> &dfsstack, int top, int n);
void movebottom(vector<cell> &maze, queue<int> &dfsstack, int top, int n);
void print_sol(vector<cell> &maze, int start, int end);
//void print_maze(vector<cell> &maze, int n);
//void set_left(vector<string> &p_maze, int x);
//void set_top(vector<string> &p_maze, int x, int y);
//void set_bot(vector<string> &p_maze, int x, int y);
//void set_right(vector<string> &p_maze, int x);

int main() {
	int n;
	cout << "What is the length of a side of this maze?" << endl;

	cin >> n;
	vector<cell> maze(n*n);
	ifstream in("maze1.txt");
	for (int i = 0; i < n*n; i++) {
		maze[i].id = i;
		in >> maze[i].wall;
	}
	ofstream mazevalues;
	mazevalues.open("Maze Values.txt");

	for (int i = 0; i < n*n; i++) { mazevalues << maze[i].id << " " << maze[i].wall << endl; } //prints out values of maze to txt file

	DFS(maze, n, 0, n*n - 1);
	for (int i = 0; i < n*n; i++) { //reset for BFS
		maze[i].visited = 0;
		maze[i].from = -1;
	}
	//print_maze(maze, n);

	BFS(maze, n, 0, n*n - 1);

	//print_maze(maze, n);

	getchar();
	getchar();
	return 0;
}

void DFS(vector<cell> &maze, int n, int start, int end) {
	stack<int> dfsstack;
	dfsstack.push(start);
	do {
		int topwall = 0;
		int bottomwall = 0;
		int leftwall = 0;
		int rightwall = 0;

		leftwall = checkleft(maze, dfsstack.top());
		rightwall = checkright(maze, dfsstack.top());
		topwall = checktop(maze, dfsstack.top());
		bottomwall = checkbottom(maze, dfsstack.top());
		
		int temp = dfsstack.top();
		dfsstack.pop();
		if (rightwall == 0) { moveright(maze, dfsstack, temp); }
		if (leftwall == 0) { moveleft(maze, dfsstack, temp); }
		if (topwall == 0) { movetop(maze, dfsstack, temp, n); }
		if (bottomwall == 0) { movebottom(maze, dfsstack, temp, n); }
	} while (dfsstack.top() != end);
	print_sol(maze, start, end);
}
void BFS(vector<cell> &maze, int n, int start, int end) {
	queue<int> bfsstack;
	bfsstack.push(start);
	do {
		int topwall = 0;
		int bottomwall = 0;
		int leftwall = 0;
		int rightwall = 0;

		leftwall = checkleft(maze, bfsstack.front());
		rightwall = checkright(maze, bfsstack.front());
		topwall = checktop(maze, bfsstack.front());
		bottomwall = checkbottom(maze, bfsstack.front());

		int temp = bfsstack.front();
		bfsstack.pop();
		if (rightwall == 0) { moveright(maze, bfsstack, temp); }
		if (leftwall == 0) { moveleft(maze, bfsstack, temp); }
		if (topwall == 0) { movetop(maze, bfsstack, temp, n); }
		if (bottomwall == 0) { movebottom(maze, bfsstack, temp, n); }
	} while (bfsstack.front() != end);
	print_sol(maze, start, end);
}
//if there is a wall, then it wall return 1
int checkright(vector<cell> &maze, int top) { //check if right wall is present
	if ((maze[top].wall % 4) >= 2) return 1;
	else return 0;
}

int checkleft(vector<cell> &maze, int top) { //check if left wall is present
	if ((maze[top].wall % 16) >= 8) return 1;
	else return 0;
}

int checktop(vector<cell> &maze, int top) { //check top wall is present
	if ((maze[top].wall % 2) == 1) return 1;
	else return 0;
}

int checkbottom(vector<cell> &maze, int top) { //check bottom wall is present
	if ((maze[top].wall % 8) >= 4) return 1;
	else return 0;
}

void moveright(vector<cell> &maze, stack<int> &dfsstack, int top) { //put next value into stack
	if (maze[top + 1].visited == 1) return;
	maze[top + 1].visited = 1;
	maze[top + 1].from = top;
	dfsstack.push(top + 1);
}

void moveleft(vector<cell> &maze, stack<int> &dfsstack, int top) { //put next value into stack
	if (maze[top - 1].visited == 1) return;
	maze[top - 1].visited = 1;
	maze[top - 1].from = top;
	dfsstack.push(top - 1);
}

void movetop(vector<cell> &maze, stack<int> &dfsstack, int top, int n) { //put next value into stack
	if (maze[top - n].visited == 1) return;
	maze[top - n].visited = 1;
	maze[top - n].from = top;
	dfsstack.push(top - n);
}

void movebottom(vector<cell> &maze, stack<int> &dfsstack, int top, int n) { //put next value into stack
	if (maze[top + n].visited == 1) return;
	maze[top + n].visited = 1;
	maze[top + n].from = top;
	dfsstack.push(top + n);
}

void moveright(vector<cell> &maze, queue<int> &bfsstack, int top) { //put next value into queue
	if (maze[top + 1].visited == 1) return;
	maze[top + 1].visited = 1;
	maze[top + 1].from = top;
	bfsstack.push(top + 1);
}

void moveleft(vector<cell> &maze, queue<int> &bfsstack, int top) { //put next value into queue
	if (maze[top - 1].visited == 1) return;
	maze[top - 1].visited = 1;
	maze[top - 1].from = top;
	bfsstack.push(top - 1);
}

void movetop(vector<cell> &maze, queue<int> &bfsstack, int top, int n) { //put next value into queue
	if (maze[top - n].visited == 1) return;
	maze[top - n].visited = 1;
	maze[top - n].from = top;
	bfsstack.push(top - n);
}

void movebottom(vector<cell> &maze, queue<int> &bfsstack, int top, int n) { //put next value into queue
	if (maze[top + n].visited == 1) return;
	maze[top + n].visited = 1;
	maze[top + n].from = top;
	bfsstack.push(top + n);
}

void print_sol(vector<cell> &maze, int start, int end) { //print out solution using stack
	stack<int> solution;

	int x = end;
	while (x != start) {
		solution.push(x);
		x = maze[x].from;
	}
	solution.push(x);
	cout << "The solution from start to end is" << endl;
	while (!solution.empty()) {
		cout << solution.top() + 1;
		if (solution.top() == end) break;
		solution.pop();
		cout << " -> ";
	}
	cout << endl;
}

//void print_maze(vector<cell> &maze, int n) { //bonus question - code does not work, so all of it is commented out
//	vector<string> p_maze ((((2 * n) + 1)*((2 * n) + 1)), " ");
//	ofstream maze_sol;
//	maze_sol.open("Maze_solution.txt");
//	for (int i=0; i < ((2 * n) + 1)*((2 * n) + 1); i++) {
//		if (i < (2 * n + 1)) p_maze[i] = "-"; //top border
//		if (i > (2 * n + 1) - (2 * n + 1)) p_maze[i] = "-"; //bottom border
//		if (i > 2*n && ((i-(2*n))%(2*n+1)) == 0) p_maze[i] = "|"; //right border
//		if (i % (2 * n + 1) == 0) p_maze[i] = "|"; //left border
//	}
//	int x = (2 * n) + 2; //to start where needed
//	int y = (2 * n) + 1;
//	int start = 0;
//	while (start < n*n) {
//		
//		int topwall = 0;
//		int bottomwall = 0;
//		int leftwall = 0;
//		int rightwall = 0;
//
//		leftwall = checkleft(maze, start);
//		rightwall = checkright(maze, start);
//		topwall = checktop(maze, start);
//		bottomwall = checkbottom(maze, start);
//
//		if (rightwall == 1) set_right(p_maze, x);
//		if (leftwall == 1) set_left(p_maze, x);
//		if (topwall == 1) set_top(p_maze, x, y);
//		if (bottomwall == 1) set_bot(p_maze, x, y);
//
//		start++;
//		if ((x % ((2 * n)) == 0) && x < (((2 * n) + 1)*((2 * n) + 1))) x += 63;
//		else x += 2;
//	}
//	for (int i = 0; i < ((2 * n) + 1)*((2 * n) + 1); i++) {
//		maze_sol << p_maze[i];
//		if ((i > 0) && i % ((2 * n) + 1) == 0) maze_sol << endl;
//	}
//}
//
//void set_top(vector<string> &p_maze, int x, int y) { //sets top border
//	p_maze[x - y] = "-";
//}
//void set_bot(vector<string> &p_maze, int x, int y) { //sets bottom border
//	p_maze[x + y] = "-";
//}
//void set_right(vector<string> &p_maze, int x) { //sets right border
//	p_maze[x + 1] = "|";
//}
//void set_left(vector<string> &p_maze, int x) { //set left border
//	p_maze[x - 1] = "|";
//}