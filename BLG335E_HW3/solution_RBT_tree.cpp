#include <iostream> 
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

/////////////////// Player ///////////////////
class publisher
{
public:
	string name;
	float na_sales;
	float eu_sales;
	float others_sales;
};

/////////////////// Node ///////////////////
class Node{
	public:
		publisher key;
		int color; // "Red"=1 or "Black"=0
		Node *parent, *left, *right;
	
		Node(publisher);
		~Node();
		int get_color();
        void set_color(int);
};

/////////////////// RB-Tree ///////////////////
class RB_tree{
	private:
		Node* root;
	public:	
        publisher* best_seller[3];	
		stack<string> tree_deep_stack;

        Node* get_root();

		Node* RB_insert(Node* root, Node* ptr);
        void insertValue(vector<string>);
		void RB_left_rotate(Node*);
		void RB_right_rotate(Node*);
		void RB_insert_fixup(Node*);
        void preorder();
        void find_best_seller(); 

        RB_tree();
		~RB_tree();
};

void print_best_sellers(int year, publisher* temp_publisher[3]){
    cout.precision(5);
    cout<< "End of the "+to_string(year)+" Year"<<endl;
    cout<< "Best seller in North America: "+temp_publisher[0]->name+" - "<<temp_publisher[0]->na_sales<<" million"<<endl;
    cout<< "Best seller in Europe: "+temp_publisher[1]->name+" - "<<temp_publisher[1]->eu_sales<<" million"<<endl;
    cout<< "Best seller rest of the World: "+temp_publisher[2]->name+" - "<<temp_publisher[2]->others_sales<<" million"<<endl;
}

RB_tree generate_RBT_tree_from_csv(string file_name){
	RB_tree temp_RBtree;
    
    // Fill this function.

    return temp_RBtree;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char* argv[]){

	string fname = argv[1];	
    RB_tree RBtree = generate_RBT_tree_from_csv(fname);

    // Fill this function.

	return EXIT_SUCCESS;
}


/////////////////// Node ///////////////////

Node::Node(publisher key){
	this->key = key;
    this->color = 1; // "RED";
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

/////////////////// RB-Tree ///////////////////
Node* RB_tree::get_root(){

    // Fill this function.

    return this->root;
}

Node* RB_tree::RB_insert(Node* root, Node* ptr){

    // Fill this function.

	return root;
}

void RB_tree::insertValue(vector<string> n) {
    
    // Fill this function.

}
void RB_tree::RB_left_rotate(Node *ptr){

    // Fill this function.

}

void RB_tree::RB_right_rotate(Node *ptr){

    // Fill this function.

}

void RB_tree::RB_insert_fixup(Node *ptr) {

    // Fill this function.
    
}

void RB_tree::preorder(){

    // Fill this function.
    
}

void RB_tree::find_best_seller(){

    // Fill this function.
    
}

RB_tree::RB_tree(){
	this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

RB_tree::~RB_tree(){
}
