//HW3 Due: 11:59pm, September 29 (Thursday)
//Implement the following class and design proper tests in main program.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class max_heap {
public:
	vector<int> heap;//Let's use 0 as the first index for the heap
	void add(int v);//add a new value v to the heap
	void remove(int v); //remove the first element with value v
	void sort();//sort the vector;  you need to implement it using the 
				//heap sort algorithm described in class
	void print(); //print all elements of 
	void check_up(int parent, int child); //checks to see if value needs to go upward
	void check_l_and_r(int parent, int l_child, int r_child); //checks only left and right child
	void check_l_and_r(int parent, int l_child, int r_child, int n_parent, int x); //check left and right child but before it moves on 
																				   //it checks if the node needs to move up;	
};

	void max_heap::add(int v) {
		if (heap.size() == 0) { //starting at 0, so empty vector, pushes and return
			heap.push_back(v);
			return;
		}
		heap.push_back(v); //pushes new value in
		int child = heap.size() - 1;
		int parent = (child - 1) / 2;

		//added values only need to see if they have to go up
		check_up(parent, child); 
	}

	void max_heap::remove(int r) {
		int last_v = heap.size() - 1;
		int temp = 0;
		vector<int>::iterator it1;

		it1 = find(heap.begin(), heap.end(), r);
		if (it1 == heap.end()) {
			cout << "value does not exist" << endl;
			return;
		}
		int index = it1 - heap.begin();
		
		temp = heap[index];
		heap[index] = heap[last_v];
		heap[last_v] = temp;

		heap.pop_back(); //gets rid of the last value in vector
		
		int size = heap.size();
		int parent = index;
		int n_parent = (parent - 1) / 2;
		int l_child = (2 * parent) + 1;
		int r_child = (2 * parent) + 2;
		if (parent == size) return; //if the one you want to remove is the last one
		temp = 0;
		//restoration of heap
		//a vector element is now out of order. 
		//In remove, if it needs to go up, it will only go up
		//if it goes down it will only go down
		if (heap[parent] >= heap[n_parent] && parent !=0) {  //when first swapped, checks if it needs to go up. Also makes sure it doesn't go up higher
			check_up(n_parent, parent);
			return;
		}
		//time to check the children
		if (l_child >= size) { //check if the left child is out of the vector. If left is out, right is always out
			return;
		}
		else if (r_child >= size) { //check if the right is out of heap size. 
			//if it made it past the previous if statement, then left child exists
			if (heap[l_child] > heap[parent]) { //may need to swap the left child with parent
				temp = heap[parent];
				heap[parent] = heap[l_child];
				heap[l_child] = temp;
			}
				return;
		}
		else { //if it reaches here, both left and right children exist and are within the vector
			check_l_and_r(parent, l_child, r_child); //goes and checks left and right
		}
	}

	void max_heap::sort() { //sort the value of the heap
		int last_v = heap.size() - 1; //the last value of the vector
		//it acts as the end boundary of the vector
		int temp = 0;
		if (heap.empty()) return;
		while (last_v != 0) {
			//Will always start at zero
			int parent = 0;
			int n_parent = (parent - 1) / 2;
			int l_child = (2 * parent) + 1;
			int r_child = (2 * parent) + 2;

			//swap first with last
			if (heap[0] >= heap[last_v]) {
				temp = heap[last_v];
				heap[last_v] = heap[0];
				heap[0] = temp;
			}

			//restoration of heap
			//checks left and right but before it moves on, it checks upward as well
			if (l_child < last_v && r_child < last_v) {
				check_l_and_r(parent, l_child, r_child, n_parent, last_v);
			}
			last_v--;
		}
		return;
	}

	void max_heap::check_up(int parent, int child) { //checks the parent and child and sees 
		//if child is greater than parent
		while (heap[parent] < heap[child]) {
			int temp = 0; //swap
			temp = heap[parent];
			heap[parent] = heap[child];
			heap[child] = temp;

			//child becomes the parent and parent is redefined
			//this is to see if it needs to keep moving up
			child = parent; 
			parent = (parent - 1) / 2;
		}
	}

	void max_heap::check_l_and_r(int parent, int l_child, int r_child) {
		int temp = 0;
		int size = heap.size();
		while (heap[parent] < heap[l_child] || heap[parent] < heap[r_child]) {
			if (heap[l_child] >= heap[r_child]) { //if left child is greater swaps and keeps going downward
				temp = heap[parent];
				heap[parent] = heap[l_child];
				heap[l_child] = temp;

				parent = l_child; //parent is now left because we are going downwards
				l_child = (2 * parent) + 1;
				r_child = (2 * parent) + 2;
				if (l_child >= size || r_child >= size) return; //if it is out of bounds
			}
			else if (heap[r_child] > heap[l_child]) { //if right child is greater swaps and keeps going downward
				temp = heap[parent]; //swaps right child downward
				heap[parent] = heap[r_child];
				heap[r_child] = temp;

				parent = r_child; //parent is now right because we're going downwards
				l_child = (2 * parent) + 1;
				r_child = (2 * parent) + 2;
				if (l_child >= size || r_child >= size) return; //if it is out of bounds
			}
		}
	}
	void max_heap::check_l_and_r(int parent, int l_child, int r_child, int n_parent, int x) {
		int temp = 0;
		int size = heap.size();
		while (l_child < x && r_child < x) {
			if (heap[l_child] >= heap[r_child]) { //if left child is greater swaps and keeps going downward
				temp = heap[parent];
				heap[parent] = heap[l_child];
				heap[l_child] = temp;

				parent = l_child; //the parent is now left child, because we are going downwards
				l_child = (2 * parent) + 1;
				r_child = (2 * parent) + 2;
				if (l_child >= size || r_child >= size) return; //Because it already swapped before it checked left and right already in heap
				int l_parent = (parent - 1) / 2; //checks to see if we need to go upwards
				check_up(l_parent, parent); //special case where it needs to move up
			}
			else if (heap[r_child] > heap[l_child]) { //if right child is greater swaps and keeps going downward
				temp = heap[parent];
				heap[parent] = heap[r_child];
				heap[r_child] = temp;

				parent = r_child; //right child is now parent, as we are going downwards
				l_child = (2 * parent) + 1;
				r_child = (2 * parent) + 2;
				if (l_child >= size || r_child >= size) return; //Because it already swapped before it checked left and right already in heap
				int r_parent = (parent - 1) / 2;
				check_up(r_parent, parent); //special case where the swap needs to go up
			}
		}
	}

	void max_heap::print() { //simply print out the values using a iterator
		if (heap.empty()) return;
		vector<int>::iterator it1 = heap.begin();
		while (it1 != heap.end()) {
			cout << *it1 << " ";
			it1++;
		}
		cout << endl;

	};

	int main() {
		max_heap n_heap;

		////If you want to create a custom vector
		//int ans = -1;
		//while (ans != 0) {
		//	cout << "What do you want to do?" << endl;
		//	cout << "Press 0 to sort and print, press 1 to add a value into heap, 2 to remove the first element with the desired value" << endl;
		//	cout << endl;
		//	cin >> ans;
		//	switch (ans) {
		//	case 0: {
		//		
		//		n_heap.sort();
		//		n_heap.print();
		//		cout << "Heap is sorted and Printed" << endl;
		//		
		//		getchar();
		//		getchar();
		//		return 0;
		//	}
		//	case 1: {
		//		int v = 0;
		//		cout << "What value are you adding?" << endl;
		//		cin >> v;
		//		n_heap.add(v);
		//		cout << "Value added" << endl;
		//		cout << endl;
		//		break;
		//	}
		//	case 2: {
		//		int r = 0;

		//		cout << "What value are you removing?" << endl;
		//		cin >> r;
		//		n_heap.remove(r);
		//		cout << "Value removed" << endl;
		//		cout << endl;
		//		break;
		//	}
		//	}
		//}
		//
		//Example Values
		n_heap.add(2435);
		n_heap.add(221);
		n_heap.add(645);
		n_heap.add(723);
		n_heap.add(763);
		n_heap.add(752);
		n_heap.add(1);
		n_heap.add(34);
		n_heap.add(34);
		n_heap.add(2623);
		n_heap.add(23145);
		n_heap.add(324);
		n_heap.print();
		
		n_heap.remove(2623);
		n_heap.print();

		n_heap.sort();
		n_heap.print();

		getchar();
		getchar();
		return 0;
	}