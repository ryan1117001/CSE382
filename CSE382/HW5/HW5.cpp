//HW5
//Dijkstra's Shortest Path Algorithm
//Floyd-Warshall's all-pair algorithm

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
class e_node { //stands for edge node
public:
	int nb;//the neighbor of a currently considered node
	int weight; //weight of the edge to the above neighbor
	e_node() {}//constructor
};
class rt_node { //rt stands for routing table
public:
	int cost;  //cost to a node
	int from;  //the from node to this node
	int checked;
	rt_node() { from = -1;  cost = 9999;  checked = 0; }
};
class matrix_node { //one matrix to hold to and cost
public:
	int cost; //9999 to represent max
	int to; //-1 to represent that currently is no path
	matrix_node() { cost = 9999; to = -1; } 
};

void dijkstra(vector<vector<e_node>> &graph, vector<rt_node> &rt, int &start);
void fw_setup(vector<vector<e_node>> &graph, vector<vector<matrix_node>> &matrix);
void fw(vector<vector<matrix_node>> &matrix);
void print_table(vector<rt_node> &rt, int &start);
void print_matrix(vector<vector<matrix_node>> &d_matrix);

int main() {

	ifstream in("text1.txt");
	int n, e; //n: num of nodes ; e: num of edges
	in >> n >> e;
	vector<e_node> ve;
	vector<vector<e_node> > graph(n, ve);
	e_node e1;
	int n1, n2, w;
	for (int i = 0; i < e; i++) {
		in >> n1 >> n2 >> w; //n1 = where it comes from, n2 = where it is currently, w = how much it costs
		e1.nb = n2;
		e1.weight = w;
		graph[n1].push_back(e1);
	}
	in.close();
	//vector<rt_node> rt(n); //rt stands for routing table
	int start = 0;

	//dijkstra algorithm
	for (start; start < n; start++) {
		vector<rt_node> rt(n); //rt stands for routing table
		//intialize the starting point
		rt[start].from = start;
		rt[start].cost = 0;
		dijkstra(graph, rt, start);
		print_table(rt, start);
		cout << endl;
	}
	//creation of matrix for fw algorithm
	vector<vector<matrix_node>> matrix(n, vector<matrix_node>(n));
	
	fw_setup(graph, matrix);
	fw(matrix);
	print_matrix(matrix);

	getchar();
	getchar();
	return 0;
}

void dijkstra(vector<vector<e_node>> &graph, vector<rt_node> &rt, int &start) {
	int current = start; //initialize where to begin
	for (int y = 0; y < rt.size(); y++) { //since it goes node by node, a for loop is usable
		int size = graph[current].size(); //number of neighbors
		for (int x = 0; x < size; x++) {//check the neighbors weight 
			int neighbor = graph[current][x].nb;
			int weight = graph[current][x].weight;
			if (rt[current].cost + weight < rt[neighbor].cost) { //if less than what is in the routing table
				rt[neighbor].cost = rt[current].cost + weight;   //it will update the table
				rt[neighbor].from = current;
			}
		}
		rt[current].checked = 1; //current node is checked off
		vector<rt_node>::iterator it1 = rt.begin();
		int min = 9999; //since 9999 is max, it will find the min
		while (it1 != rt.end()) {
			if (it1->checked == 0 && it1->cost < min) {
				min = it1->cost; //updates the min
				current = it1 - rt.begin(); //updates the current node
			}
			it1++;
		}
	}
}
void fw_setup(vector<vector<e_node>> &graph, vector<vector<matrix_node>> &matrix) {
	for (int x = 0; x < graph.size(); x++) { //two for loops to create initial matrix
		matrix[x][x].cost = 0; //for the pair (x,x), we know cost is 0 and to is itself
		matrix[x][x].to = x; 
		for (int y = 0; y < graph[x].size(); y++) {
			matrix[x][graph[x][y].nb].cost = graph[x][y].weight; //cost = weight
			matrix[x][graph[x][y].nb].to = graph[x][y].nb; //to = neighbor
		}
	}
}
void fw(vector<vector<matrix_node>> &matrix) { //floyd Warshall's All Pair Algorithm
	for (int k = 0; k < matrix.size(); k++) { //represents intermeditary node
		for (int i = 0; i < matrix[k].size(); i++) { //represents node coming from
			for (int j = 0; j < matrix[k].size(); j++) { //represents node going to
				if (matrix[i][k].cost + matrix[k][j].cost < matrix[i][j].cost) { //compares if new path is less costly
					matrix[i][j].cost = matrix[i][k].cost + matrix[k][j].cost; //update cost and to
					matrix[i][j].to = k;
				}
			}
		}
	}
}

void print_table(vector<rt_node> &rt, int &start) { //Print out routing table
	for (int i = 0; i < rt.size(); i++) {
		cout << "Cost from " << start << " to " << i << " is: " << rt[i].cost << "  from node is " << rt[i].from << endl;
	}
}

void print_matrix(vector<vector<matrix_node>> &matrix) { //Print entire matrix
	for (int a = 0; a < matrix.size(); a++) {
		cout << endl;
		for (int b = 0; b < matrix[a].size(); b++) {
			cout << "Cost from " << a << " to " << b << " is " << matrix[a][b].cost <<
				". It will go through node " << matrix[a][b].to << endl;
		}
	}
}