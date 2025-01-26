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

/////////////////// BST-Tree ///////////////////
class BST_tree{
	private:
		Node* root;
	public:	
        publisher* best_seller[3];	
		stack<string> tree_deep_stack;

        Node* get_root();

		Node* BST_insert(Node* root, Node* ptr);
		void insertValue(vector<string>);
        void find_best_seller(); 

        BST_tree();
		~BST_tree();
};

void print_best_sellers(int year, publisher* temp_publisher[3]){
    cout.precision(5);
    cout<< "End of the "+to_string(year)+" Year"<<endl;
    cout<< "Best seller in North America: "+temp_publisher[0]->name+" - "<<temp_publisher[0]->na_sales<<" million"<<endl;
    cout<< "Best seller in Europe: "+temp_publisher[1]->name+" - "<<temp_publisher[1]->eu_sales<<" million"<<endl;
    cout<< "Best seller rest of the World: "+temp_publisher[2]->name+" - "<<temp_publisher[2]->others_sales<<" million"<<endl;
}

BST_tree generate_BST_tree_from_csv(string file_name){
    
    BST_tree temp_BSTtree;

    // Fill this function.

    return temp_BSTtree;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char* argv[]){

	string fname = argv[1];	
    BST_tree BSTtree = generate_BST_tree_from_csv(fname);

    // Fill this function.

	return EXIT_SUCCESS;
}


/////////////////// Node ///////////////////

Node::Node(publisher key){
	this->key = key;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}


Node* BST_tree::get_root(){

    // Fill this function.

    return this->root;
}

Node* BST_tree::BST_insert(Node* root, Node* ptr){

    // Fill this function.

	return root;
}


void BST_tree::insertValue(vector<string> n) {

    // Fill this function.
}

void BST_tree::find_best_seller(){

    // Fill this function.

}


BST_tree::BST_tree(){
	this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

BST_tree::~BST_tree(){
}
