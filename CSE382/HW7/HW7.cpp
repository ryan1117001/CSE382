//Prim's Algorithm - Minimum Spanning Tree
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
class e_node { //stands for edge node
public:
	int nb;//the neighbor of a currently considered node
	int weight; //weight of the edge to the above neighbor
	e_node() { nb = 0; weight = 0; }//constructor
};

class h_node {
public:
	int checked; //whether node is checked;
	vector<e_node> edge;
	h_node() { vector<e_node> edge; checked = 0; }
};

vector<vector<e_node>> prim_method(vector<h_node> &graph);

int main() {
	ifstream in("text2.txt");
	int n, e; //n: num of nodes ; e: num of edges
	in >> n >> e;
	vector<h_node> graph(n);
	e_node e1;
	h_node h1;
	int n1, n2, w;
	for (int i = 0; i < e; i++) {
		in >> n1 >> n2 >> w; //n1 = where it comes from
		//n2 = where it is currently
		//w = how much it costs

		//it is bidirectional
		e1.nb = n2;
		e1.weight = w;
		graph[n1].edge.push_back(e1);
		e1.nb = n1;		
		graph[n2].edge.push_back(e1);
	}

	vector<vector<e_node>> min_graph = prim_method(graph);

	for (int x = 0; x < min_graph.size(); x++) {
		cout << "From node " << x << ", it can go to" << endl;
		for (int y = 0; y < min_graph[x].size(); y++) {
			cout << "	" << min_graph[x][y].nb << " at the cost of " << min_graph[x][y].weight << endl;
		}
	}

	getchar();
	getchar();
	return 0;
}

vector<vector<e_node>> prim_method(vector<h_node> &graph) {
	vector<vector<e_node>> min_graph(graph.size());
	//search for the smallest edge
	int cost = 9999;
	int f_node = -1;
	int b_node = -1;
	for (int x = 0; x < graph.size(); x++) {
		for (int y = 0; y < graph[x].edge.size(); y++) {
			if (graph[x].checked != 1 && graph[x].edge[y].weight < cost) {
				cost = graph[x].edge[y].weight;
				f_node = x;
				b_node = graph[x].edge[y].nb;
			}
		}
	}
	//initialized nodes to begin actual checking of neighbors
	graph[f_node].checked = 1;
	graph[b_node].checked = 1;
	e_node e2;
	e2.nb = f_node; 
	e2.weight = cost;
	min_graph[b_node].push_back(e2);
	e2.nb = b_node;
	min_graph[f_node].push_back(e2);
	

	//vector of all the checked nodes
	vector<int> checked_node;
	checked_node.push_back(f_node);
	checked_node.push_back(b_node);

	int counter = 2; //starts at two because edge first edge is found

	while (counter != graph.size()) {
		cost = 9999; //cost min of neighbors in checked node
		for (int a = 0; a < checked_node.size(); a++) {
			for (int b = 0; b < graph[checked_node[a]].edge.size(); b++) {
				if (graph[graph[checked_node[a]].edge[b].nb].checked != 1 && graph[checked_node[a]].edge[b].weight < cost) {
					f_node = graph[checked_node[a]].edge[b].nb;
					b_node = checked_node[a];
					cost = graph[checked_node[a]].edge[b].weight;
				}
			}
		}
		if (counter != graph.size() && cost == 9999) { //if this happens the graph has become cylic and cannot continue
			cout << "The graph is cyclic and cannot continue" << endl;
			vector<vector<e_node>> vec2;
			return vec2;
		}

		graph[f_node].checked = 1;
		e2.nb = f_node;
		e2.weight = cost;
		min_graph[b_node].push_back(e2);
		e2.nb = b_node;
		min_graph[f_node].push_back(e2);
		checked_node.push_back(f_node);
		counter++;
	}

	return min_graph;
}