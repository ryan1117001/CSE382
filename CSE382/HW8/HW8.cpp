/*HW 8: AVL tree.You program will take an input sequence of integers and create an AVL tree
by continuously invoking an add_node function.
In addition, you need to implement a remove_node function(to remove a node with a given value).
You are required to continue from the partial code that I provided below.


Part A(due Friday, November 18) : Implement the member functions for R - Rotate and L - Rotate,
including the corresponding height update for related nodes.
Part B(Due Wednesday, November 30) : implement remove function.


If you complete the part A, you should immediately move to Part B.

*/


//Partial code for HW8 by C-Y (Roger) Chen, Syracuse University

#include <iostream> //to use cout
#include <algorithm> //to use max function

using namespace std;

class node {
public:
	int value;
	int height;
	int child; //0: this node is a left child of its parent; 1: right child; -1 this node is the tree root
	node * parent;
	node * l_child;
	node * r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node * root;
	avl_tree() {
		root = nullptr; //initial creation creates root node nullptr
	}
	void add_node(int i);
	void in_order_traversal(node *p);
	node * height_adjustment(node *p, int &pattern);
	void L_Rotate(node *p, int &pattern); // You need to implement this.
	void R_Rotate(node *p, int &pattern); //You need to implement this.
	//void remove_node(int i); //You need to implement this.
};
void avl_tree::add_node(int i) {
	int pattern; //number represents L-L, R-R, L-R, or R-L
	node * p = new node(i); //newly created node
	node * action_node;
	if (root == nullptr) { root = p; p->child = -1; return; } //if avl tree is empty
	node  * p1 = root, *p2 = root; //p1 initially is root (to see if it goes left or right) 
	//then becomes new parent (using l_child or r_child of , p2 keeps track of parent
	while (p1 != nullptr) {
		p2 = p1;
		if (i < p1->value) { p->child = 0; p1 = p1->l_child; } //set up for left child
		else { //set up for right child
			p->child = 1;
			p1 = p1->r_child; //p1 is new parent using r_child
		}
	}
	//p1 = p;
	p->parent = p2; //p2 is parent of current node
	if (p->child == 0) { p2->l_child = p; } //current node becomes l_child of parent
	if (p->child == 1) { p2->r_child = p; } //current node becomes r_child of parent
	action_node = height_adjustment(p2, pattern);
	if (action_node != nullptr) {
		cout << "action_node's value =  " << action_node->value << "  Imbalance Pattern  = " << pattern << endl;

		switch (pattern) {
		case 0: R_Rotate(action_node, pattern); break; //L-L Pattern
		case 1: L_Rotate(action_node->l_child, pattern); R_Rotate(action_node, pattern); break; //L-R Pattern
		case 2: R_Rotate(action_node->r_child, pattern); L_Rotate(action_node, pattern); break; //R-L Pattern
		case 3: L_Rotate(action_node, pattern); break; // R-R Pattern
		}
		action_node = height_adjustment(action_node->parent, pattern);
	}

}
void avl_tree::in_order_traversal(node * p) { //to print out in order
	if (p == nullptr)  return;
	in_order_traversal(p->l_child); //left first, parent, then right is in order;
	cout << "value = " << p->value << " " << "height = " << p->height << endl;
	in_order_traversal(p->r_child);
	//right,parent,left is post fix
	//prefix parent, left, right is prefix
}


node * avl_tree::height_adjustment(node *p, int &pattern) { //p is parent of added node
	int pattern1, pattern2; //pattern1 at action node, pattern2 at child nodes
	node * p1; //child with the greater height
	int l_height, r_height, new_height;
	while (p != nullptr) {
		if (p->l_child == nullptr) l_height = 0; else l_height = p->l_child->height; //if action node is leaf node l_height = 0, else height is predetermined
		if (p->r_child == nullptr) r_height = 0; else r_height = p->r_child->height; //if action node is leaf node r_height = 0, else height is predetermined
		new_height = max(l_height, r_height) + 1; //new_height = height of child +1
		//the following statement has been revised
		if (new_height == p->height  && abs(l_height - r_height) <= 1) { return nullptr; } //when it is root, returns nullptr
		p->height = new_height; //new action node height
		if (abs(l_height - r_height) > 1) { //when there is discrepency between childs of action node 

			if (l_height > r_height) {
				pattern1 = 0; //L pattern
				p1 = p->l_child;
			}
			else {
				pattern1 = 1; //R pattern
				p1 = p->r_child;
			}

			if (p1->l_child == nullptr) l_height = 0; else l_height = p1->l_child->height; //checks to see if it is leaf node. If not height is changed
			if (p1->r_child == nullptr) r_height = 0; else r_height = p1->r_child->height;

			if (l_height > r_height) {
				pattern2 = 0; //L pattern
			}
			else {
				pattern2 = 1; //R pattern
			}
			if (pattern1 == 0 && pattern2 == 0) pattern = 0; //L-L pattern.  Need to invoke  R_Rotate
			if (pattern1 == 0 && pattern2 == 1) pattern = 1; //L-R pattern.  Need to invoke  L_Rotate and then R_Rotate
			if (pattern1 == 1 && pattern2 == 0) pattern = 2; //R-L pattern.  Need to invoke  R_Rotate and then L_Rotate
			if (pattern1 == 1 && pattern2 == 1) pattern = 3; //R-R pattern.  Need to invoke  L_Rotate
			return p;
		}
		p = p->parent; // changes as it checks upward (assuming there hasn't been a violation yet)
	} //p points to the action nodee
	  //the first node with height imbalance
	return nullptr;
}
void avl_tree::L_Rotate(node *p, int &pattern) { //p is action node
	node *temp = nullptr; //to hold node that needs to switch sides
	if (p == root) //change root if need be
		root = p->r_child;
	if (p->r_child->l_child != nullptr) { //need to do a inner rotation if this exists
		temp = p->r_child->l_child;
	}
	p->r_child->child = p->child; //changes child of r_child
	p->r_child->parent = p->parent; //connects r_child parent to current parent 
	//connection of parents when it is not root
	if (p->child != -1) {
		if (p->child == 0)
			p->parent->l_child = p->r_child; //connects new parent and child if p is l_child
		else
			p->parent->r_child = p->r_child; //connects new parent and child if p is r_child
	}
	p->r_child->l_child = p; //connects p as l_child

	p->child = 0; //changes p as l_child
	p->parent = p->r_child; //changes parent
	
	//change in height
	if (p->r_child->r_child != nullptr) p->height -= 2; 
	else { 
		p->height--;
		p->r_child->height++;
	}
	p->r_child = nullptr; //p no longer points to what is now parent
	if (temp != nullptr) { //if this is not null, then inner rotation is necessary
		p->r_child = temp;
		temp->parent = p;
		temp->child = 1;
	}
	
	return;
}

void avl_tree::R_Rotate(node *p, int &pattern) { //p is node that is used as pivot point
	node *temp = nullptr; //to hold node that needs to switch sides
	if (p == root) //change root if need be
		root = p->l_child;
	if (p->l_child->r_child != nullptr) { //need to do a inner rotation if this exists
		temp = p->l_child->r_child;
	}
	
	p->l_child->child = p->child; //changes child of l_child
	p->l_child->parent = p->parent; //connects l_child to current parent
	//connection of parents for one of two patterns for rotation when it is not root
	if (p->child != -1) {
		if (p->child == 0)
			p->parent->l_child = p->l_child; //connects new parent and child if p is l_child
		else
			p->parent->r_child = p->l_child; //connects new parent and child if p is r_child
	}
	p->l_child->r_child = p; //connects p as r_child

	p->child = 1; //changes p as r_child
	p->parent = p->l_child; //changes parent
	
	if (p->l_child->l_child != nullptr) p->height -= 2; //change in height
	else {
		p->height--;
		p->l_child->height++;
	}
	p->l_child = nullptr; //p no longer points to what is now parent
	if (temp != nullptr) { //uses temp to do inner rotation
		p->l_child = temp;
		temp->parent = p;
		temp->child = 0;
	}
	
	return;
}

int main() {
	avl_tree t1;
	t1.add_node(80);
	t1.add_node(65);
	t1.add_node(32);
	t1.add_node(25);
	t1.add_node(21);
	t1.add_node(150);
	t1.add_node(90);
	t1.add_node(50);
	t1.add_node(45);
	t1.add_node(70);
	t1.add_node(49);
	t1.add_node(130);
	t1.add_node(125);
	t1.in_order_traversal(t1.root);
	
	getchar();
	getchar();
	return 0;
}