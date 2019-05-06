#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void bubble_sort(vector<int> &vec1);
void select_sort(vector<int> &vec1);
void insert_sort(vector<int> &vec1);
void merge_sort(vector<int> &vec1, int left, int right);
void merge(vector<int> &vec, int left, int mid, int right);

int main() {
	int size;
	ofstream myfile;
	myfile.open("Vector Numbers.txt");

	cout << "What is the size of your vector?" << endl;
	cin >> size;

	vector<int> vec1 (size);
	
	int x = 0;
	while (x != size) {
		vec1[x] = rand();
		x++;
	}

	int ans;
	cout << "Enter 1 for Bubble Sort, 2 for Selection Sort, 3 for Insertion Sort, and 4 for Merge Sort" << endl;
	cin >> ans;
	if (ans == 1) {
		bubble_sort(vec1);
	}
	else if (ans == 2) {
		select_sort(vec1);
	}
	else if (ans == 3) {
		insert_sort(vec1);
	}
	else if (ans == 4) { 
		merge_sort(vec1, 0, vec1.size()); }

	cout << "Sort Complete" << endl;
	vector<int>::iterator it1 = vec1.begin();
	while (it1 != vec1.end()) {
		myfile << *it1 << endl;
		it1++;
	}
	cout << "Print Complete" << endl;
	getchar();
	getchar();
	return 0;
}

void bubble_sort(vector<int> &vec1) {
	int temp = 0;
	int y = vec1.size();
	for (int x = 1; x < y; x++) {
		for (int z = 0; z < y - x; z++) {
			if (vec1[z] > vec1[z + 1]){
				temp = vec1[z];
				vec1[z] = vec1[z + 1];
				vec1[z + 1] = temp;
			}
		}
	}
	return;
}

void select_sort(vector<int> &vec1) {
	
	int pos = 0;
	int temp = 0;
	int y = vec1.size();
	for (int x = 0; x < y - 1; x++) {
		int min = vec1[x];
		for (int z = x + 1; z < y; z++) {
			if (vec1[z] < min) {
				min = vec1[z];
				pos = z;
			}
		}
		if (vec1[x] != vec1[pos]) {
			temp = vec1[x];
			vec1[x] = vec1[pos];
			vec1[pos] = temp;
		}
	}
	return;
}
void insert_sort(vector<int> &vec1) {
	int temp, y;
	for (int x = 0; x < vec1.size(); x++) {
		y = x;
		while (y > 0 && vec1[y] < vec1[y - 1]) {
			temp = vec1[y];
			vec1[y] = vec1[y - 1];
			vec1[y - 1] = temp;
			y--;
		}
	}
	return;
}
void merge_sort(vector<int> &vec, int left, int right) {
	if (right - left <= 1) return;
	int mid = (left+ right) / 2;
	merge_sort(vec, left, mid);
	merge_sort(vec, mid, right);
	merge(vec, left, mid, right);
}

void merge(vector<int> &vec, int left, int mid, int right) {
	vector<int> temp;
	int ogleft = left;
	int ogright = right;
	int ogmid = mid;

	while (left < ogmid || mid < right) {
		if (left == ogmid) {
			temp.push_back(vec[mid]);
			mid++;
		}
		else if (mid == right) {
			temp.push_back(vec[left]);
			left++;
		}
		else if (vec[left] < vec[mid]) {
			temp.push_back(vec[left]);
			left++;
		}
		else if (vec[mid] <= vec[left]) {
			temp.push_back(vec[mid]);
			mid++;
		}
	}
	for (int x = ogleft; x < ogright; x++) {
		vec[x] = temp[x - ogleft];
	}
}