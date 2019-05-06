//Dijkstra's algorithm by Roger Chen, Syracuse University
//Implemented with min-Heap
//Time Complexity O(N + E log N)
//The goal is to get from 0 to 5 with the least amount of cost
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
	int h_pos; //the postion in heap for this node
	rt_node() { from = -1;  cost = 9999;  checked = 0; }
};

class h_node { //stands for head_node
public:
	int id;
	int cost;
	h_node() { id = -1; cost = 9999; }
	h_node(int i, int j) { id = i; cost = j; }
	bool operator<(h_node h) { return (cost < h.cost); }
};

void set_up(vector<rt_node> &rt, vector<h_node> & heap, int &start); //Insert the souce node to heap and update rt and heap accordingly
void heap_adjust_up(vector<rt_node> &rt, vector<h_node> & heap, int &n);
void heap_adjust_down(vector<rt_node> & rt, vector<h_node> & heap);
void heap_op(vector<vector<e_node>> & graph, vector<rt_node> & rt, vector<h_node> &heap);

int main() {

	ifstream in("text3.txt");
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
	vector<rt_node> rt(n); //rt stands for routing table
	vector<h_node> heap(n);
	int start = 0;
	set_up(rt, heap, start);
	heap_op(graph, rt, heap);

	for (int i = 0; i < n; i++) {

		cout << "cost from " << start << " to " << i << " is: " << rt[i].cost << "  from node is " << rt[i].from << endl;
	}
	getchar();
	getchar();
	return 0;
}


void set_up(vector<rt_node> &rt, vector<h_node> & heap, int &start) {

	rt[start].from = start;
	rt[start].cost = 0;
	for (size_t i = 0; i < heap.size(); i++) {
		heap[i].id = i;
		rt[i].h_pos = i;
	}
	heap[start].id = 0;
	heap[0].id = start;
	heap[0].cost = 0;
	rt[0].h_pos = start;
	rt[start].h_pos = 0;
}
void heap_adjust_up(vector<rt_node> &rt, vector<h_node> & heap, int &n) {
	int child = n;
	int parent = (child - 1) / 2;
	while (heap[child]<heap[parent]) {
		//swap
		h_node temp = heap[parent];
		heap[parent] = heap[child];
		heap[child] = temp;

		rt[heap[parent].id].h_pos = parent;
		rt[heap[child].id].h_pos = child;

		//child becomes the parent and parent is redefined
		//this is to see if it needs to keep moving up
		child = parent;
		parent = (parent - 1) / 2;
	}
}
void heap_adjust_down(vector<rt_node> & rt, vector<h_node> & heap) {
	h_node temp;
	int size = heap.size();
	int parent = 0;
	int l_child = (2 * parent) + 1;
	int r_child = (2 * parent) + 2;
	if (l_child >= size) { //check if the left child is out of the vector. If left is out, right is always out
		return;
	}
	if (r_child >= size) { //check if the right is out of heap size. 
						   //if it made it past the previous if statement, then left child exists
		if (heap[l_child] < heap[parent]) { //may need to swap the left child with parent
			temp = heap[parent];
			heap[parent] = heap[l_child];
			heap[l_child] = temp;
		}
		return;
	}
	else {
		while (heap[l_child] < heap[parent] || heap[r_child] < heap[parent]) {
			if (heap[l_child] < heap[r_child]) {
				temp = heap[parent];
				heap[parent] = heap[l_child];
				heap[l_child] = temp;
				//set routing table
				rt[heap[parent].id].h_pos = parent;
				rt[heap[l_child].id].h_pos = l_child;

				parent = l_child; //parent is now left because we are going downwards
				l_child = (2 * parent) + 1;
				r_child = (2 * parent) + 2;
				if (l_child >= size || r_child >= size) return; //if it is out of bounds
			}
			else if (heap[r_child] < heap[l_child]) {
				temp = heap[parent]; //swaps right child downward
				heap[parent] = heap[r_child];
				heap[r_child] = temp;
				//setting routing table
				rt[heap[parent].id].h_pos = parent;
				rt[heap[r_child].id].h_pos = r_child;

				parent = r_child; //parent is now right because we're going downwards
				l_child = (2 * parent) + 1;
				r_child = (2 * parent) + 2;
				if (l_child >= size || r_child >= size) return; //if it is out of bounds
			}
		}
	}
}
void heap_op(vector<vector<e_node>> & graph, vector<rt_node> & rt, vector<h_node> &heap) {
	while (heap.size() != 0) {
		h_node temp;
		int top_id = heap[0].id; //the top the heap

		//swap the h_node
		temp = heap[0];
		heap[0] = heap[heap.size() - 1];
		heap[heap.size() - 1] = temp;

		//set the id at routing table to be zero because it is swapped to top of the heap
		rt[heap[0].id].h_pos = 0;

		rt[heap[heap.size() -1].id].checked = 1; //point the top node as checked
		heap.pop_back(); //pop the back node
		heap_adjust_down(rt, heap); //adjust down
		
		for (int x = 0; x < graph[top_id].size(); x++) { //the graph of the top to check neighbors
			int neighbor = graph[top_id][x].nb; //neighbor of what was just popped
			int h_pos = rt[neighbor].h_pos; //heap position within the routing table
			int weight = graph[top_id][x].weight; //weight of the neighbor
			if (rt[top_id].cost + weight < rt[neighbor].cost) { //if the sum and the weight of the 
				//neighbor is greater that what is already in the routing table, changes the cost of the
				//value at the routing table
				rt[neighbor].cost = rt[top_id].cost + weight;
				rt[neighbor].from = top_id;
				heap[h_pos].cost = rt[top_id].cost + weight;
				heap_adjust_up(rt, heap, h_pos); //restores the heap
			}
		}
	}
}