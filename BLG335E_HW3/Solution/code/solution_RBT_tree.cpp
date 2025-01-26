#include <iostream> 
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <string>
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
class publisher{
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
        void preorder_helper(Node* node, int depth);
        void find_best_seller_helper(Node* node);

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
        publisher* searchByName(const string& name);
        void performRandomizedSearches(int num_searches, const string& filename);
        RB_tree();
		~RB_tree();
};

/////////////////// External Functions ///////////////////
void print_best_sellers(int year, publisher* temp_publisher[3]){
    cout.precision(5);
    cout<< "End of the "+to_string(year)+" Year"<<endl;
    cout<< "Best seller in North America: "+temp_publisher[0]->name+" - "<<temp_publisher[0]->na_sales<<" million"<<endl;
    cout<< "Best seller in Europe: "+temp_publisher[1]->name+" - "<<temp_publisher[1]->eu_sales<<" million"<<endl;
    cout<< "Best seller rest of the World: "+temp_publisher[2]->name+" - "<<temp_publisher[2]->others_sales<<" million"<<endl;
}

RB_tree generate_RBT_tree_from_csv(string file_name){
	
    RB_tree temp_RBtree;

    ifstream file(file_name);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file: " << file_name << endl;
        return temp_RBtree;
    }

    // Skip the header line
    getline(file, line);

    int decade = 0; // decade offset
    long long total_insertion_time = 0LL;  // To accumulate the insertion time in microseconds

    while (getline(file, line)) {
        string value;
        size_t pos = 0;
        vector<string> row;

        while ((pos = line.find(',')) != string::npos) {
            value = line.substr(0, pos);
            row.push_back(value);
            line.erase(0, pos + 1);
        }
        row.push_back(line); // read kast row too

        if (stoi(row[2]) > (1990 + decade)) {
            temp_RBtree.find_best_seller();
            print_best_sellers(1990 + decade, temp_RBtree.best_seller);
            decade += 10;
        }

        high_resolution_clock::time_point start = high_resolution_clock::now();  // Start time for insertion
        temp_RBtree.insertValue(row);
        high_resolution_clock::time_point end = high_resolution_clock::now();  // End time for insertion

        // Add the duration of this insertion 
        total_insertion_time += duration_cast<microseconds>(end - start).count();
    }

    temp_RBtree.find_best_seller();
    print_best_sellers(1990 + decade, temp_RBtree.best_seller);

    cout << "Time taken to insert all data into RB Tree: " << total_insertion_time << " µs" << endl;

    file.close();

    return temp_RBtree;
}

RB_tree generate_RB_tree_from_csv_ordered(string file_name){
      
    RB_tree temp_RBTtree;
    vector<vector<string>> publishers;  // to hold rows of data

    ifstream file(file_name);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file: " << file_name << endl;
        return temp_RBTtree;
    }

    getline(file, line);  // skip header line
	long long total_insertion_time = 0LL;  // to track time taken for insertions
    // Read data line by line
    while (getline(file, line)) {
        string value;
        size_t pos = 0;
		vector<string> row;

        while ((pos = line.find(',')) != string::npos) {
            value = line.substr(0, pos);
            row.push_back(value);
            line.erase(0, pos + 1);
        }
        row.push_back(line);  // last value
        publishers.push_back(row);
    }
    file.close();

    sort(publishers.begin(), publishers.end(), [](const vector<string>& a, const vector<string>& b) {
        return a[0] < b[0];  // Sort by first column
    });

    for (auto& row : publishers) {
        row[3] = row[0];  // Set value in 3rd column to first column value

        high_resolution_clock::time_point start = high_resolution_clock::now(); // start timer
		temp_RBTtree.insertValue(row); // insert into tree
		high_resolution_clock::time_point end = high_resolution_clock::now(); // stop timer

		// add insertion time
		total_insertion_time += duration_cast<microseconds>(end - start).count();
    }

    cout << "Time taken to insert all data into BST: " << total_insertion_time << " µs" << endl;
    return temp_RBTtree;
}

vector<string> returnNameVector(const string& filename) {
    vector<string> publisher_names;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return publisher_names;
    }

    // Skip the header line
    getline(file, line);

    // loop through file
    while (getline(file, line)) {
        vector<string> row;
        string value;
        size_t pos = 0;

        // split line by commas
        while ((pos = line.find(',')) != string::npos) {
            value = line.substr(0, pos);
            row.push_back(value);
            line.erase(0, pos + 1);
        }
        row.push_back(line);  // last column

        // Assuming name is in the 3rd column
        publisher_names.push_back(row[3]);  // Push name to vector
    }

    file.close();
    return publisher_names;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char* argv[]){

    string fname = argv[1];

    // Generate the Red-Black tree from the CSV file
    RB_tree RBtree = generate_RBT_tree_from_csv(fname);
    // RB_tree RBtree_ordered = generate_RB_tree_from_csv_ordered(fname);

    RBtree.performRandomizedSearches(50, fname);
    // RBtree_ordered.performRandomizedSearches(50, fname);

    RBtree.preorder();
    // RBtree_ordered.preorder();
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
RB_tree::RB_tree(){
	this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

RB_tree::~RB_tree(){
}

/////////////////// RB-Tree Functions ///////////////////
Node* RB_tree::get_root(){

    // Fill this function.

    return this->root;
}

Node* RB_tree::RB_insert(Node* root, Node* ptr){
    // cout << "Inserting: " << ptr->key.name << endl;

    if (root == nullptr) {
        // cout << "Root is null, inserting here." << endl;
        return ptr;
    }

    if (ptr->key.name < root->key.name) {
        // cout << "Going left from " << root->key.name << endl;
        root->left = RB_insert(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->key.name > root->key.name) {
        // cout << "Going right from " << root->key.name << endl;
        root->right = RB_insert(root->right, ptr);
        root->right->parent = root;
    } else {
        // cout << "Publisher already exists, updating sales." << endl;
        root->key.na_sales += ptr->key.na_sales;
        root->key.eu_sales += ptr->key.eu_sales;
        root->key.others_sales += ptr->key.others_sales;
        return root;
    }

    // cout << "Returning root after insertion: " << root->key.name << endl;
    return root;
}

void RB_tree::insertValue(vector<string> n) {
    if (n.size() < 7) {  // Check for enough data
        // cout << "Error: Insufficient data in row" << endl;
        return;
    }

    publisher pub;
    pub.name = n[3];  // Publisher name
    pub.na_sales = stof(n[4]);   // Convert to float
    pub.eu_sales = stof(n[5]);
    pub.others_sales = stof(n[6]);

    // Create new node
    Node* newNode = new Node(pub);

    // Insert into Red-Black tree
    // cout << "Inserting: " << n[3] << " with sales: " << n[4] << ", " << n[5] << ", " << n[6] << endl;
    root = RB_insert(root, newNode);  // Update root
    // preorder();

    // Fix tree violations
    RB_insert_fixup(newNode);
}

void RB_tree::RB_left_rotate(Node *ptr){

    Node* rightChild = ptr->right;
    ptr->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = ptr;
    }

    rightChild->parent = ptr->parent;

    if (ptr->parent == nullptr) {
        root = rightChild;
    } else if (ptr == ptr->parent->left) {
        ptr->parent->left = rightChild;
    } else {
        ptr->parent->right = rightChild;
    }

    rightChild->left = ptr;
    ptr->parent = rightChild;

}

void RB_tree::RB_right_rotate(Node *ptr){

    Node* leftChild = ptr->left;
    ptr->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = ptr;
    }

    leftChild->parent = ptr->parent;

    if (ptr->parent == nullptr) {
        root = leftChild;
    } else if (ptr == ptr->parent->right) {
        ptr->parent->right = leftChild;
    } else {
        ptr->parent->left = leftChild;
    }

    leftChild->right = ptr;
    ptr->parent = leftChild;

}

void RB_tree::RB_insert_fixup(Node* ptr) {
    while (ptr != root && ptr->parent != nullptr && ptr->parent->color == 1) {
        if (ptr->parent == ptr->parent->parent->left) {
            Node* uncle = ptr->parent->parent->right;
            if (uncle != nullptr && uncle->color == 1) {
                // Case 1: Uncle is red
                ptr->parent->color = 0;
                uncle->color = 0;
                ptr->parent->parent->color = 1;
                ptr = ptr->parent->parent;
            } else {
                // Case 2 and 3: Uncle is black
                if (ptr == ptr->parent->right) {
                    ptr = ptr->parent;
                    this->RB_left_rotate(ptr);  // Rotate left
                }
                // Case 4: Uncle is black and ptr is left child
                ptr->parent->color = 0;
                ptr->parent->parent->color = 1;
                this->RB_right_rotate(ptr->parent->parent);  // Rotate right
            }
        } else {
            // Symmetric case (when parent is right child)
            Node* uncle = ptr->parent->parent->left;
            if (uncle != nullptr && uncle->color == 1) {
                ptr->parent->color = 0;
                uncle->color = 0;
                ptr->parent->parent->color = 1;
                ptr = ptr->parent->parent;
            } else {
                if (ptr == ptr->parent->left) {
                    ptr = ptr->parent;
                    this->RB_right_rotate(ptr);  // Rotate right
                }
                ptr->parent->color = 0;
                ptr->parent->parent->color = 1;
                this->RB_left_rotate(ptr->parent->parent);  // Rotate left
            }
        }
    }
    root->color = 0;  // Root must be black
}

void RB_tree::preorder() {
    // Helper for printing nodes with indentation
    preorder_helper(root, 0);
}

void RB_tree::find_best_seller() {
    // Initialize best sellers as nullptr
    best_seller[0] = nullptr;  // North America
    best_seller[1] = nullptr;  // Europe
    best_seller[2] = nullptr;  // Other regions

    // Start traversal from root
    find_best_seller_helper(root);
}
publisher* RB_tree::searchByName(const string& name) {
    Node* current = root;
    
    while (current != nullptr) {
        // Compare the publisher names
        if (name < current->key.name) {
            current = current->left;  // Go left if the name is smaller
        }
        else if (name > current->key.name) {
            current = current->right;  // Go right if the name is bigger
        }
        else {
            // Publisher found, return the publisher data
            return &current->key;
        }
    }
    
    // If not found, return nullptr
    return nullptr;
}

void RB_tree::performRandomizedSearches(int num_searches, const string& filename) {

    // Get the list of publisher names from the CSV
    vector<string> publisher_names = returnNameVector(filename);

    if (publisher_names.empty()) {
        cout << "No publisher names available for searching." << endl;
        return;
    }

    // Random number generator to pick random publisher names
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, publisher_names.size() - 1);

    // Variable to calculate total search time
    double total_search_time = 0;  // Changed to double to store fractional time

    for (int i = 0; i < num_searches; ++i) {

        // Pick a random publisher name from the list
        string random_search_key = publisher_names[dis(gen)];

        high_resolution_clock::time_point search_start = high_resolution_clock::now();
        publisher* found_pub = searchByName(random_search_key);
        high_resolution_clock::time_point search_end = high_resolution_clock::now();

        // Add the search time in nanoseconds to the total
        total_search_time += duration_cast<nanoseconds>(search_end - search_start).count();
    }

    // Calculate and print the average search time in nanoseconds
    double average_search_time = total_search_time / num_searches;

    cout << fixed << setprecision(1);  // Set the output precision to one decimal place
    cout << "Average time for " << num_searches << " random searches : " << average_search_time << " ns" << endl;
}

/////////////////// RB-Tree Helper Functions ///////////////////
void RB_tree::find_best_seller_helper(Node* node) {
    if (node == nullptr) {
        return; // Base case: stop if node is nullptr
    }

    // Compare and update best sellers for each region
    if (best_seller[0] == nullptr || node->key.na_sales > best_seller[0]->na_sales) {
        best_seller[0] = &node->key;
    }
    if (best_seller[1] == nullptr || node->key.eu_sales > best_seller[1]->eu_sales) {
        best_seller[1] = &node->key;
    }
    if (best_seller[2] == nullptr || node->key.others_sales > best_seller[2]->others_sales) {
        best_seller[2] = &node->key;
    }

    // Recursively visit the left and right children
    find_best_seller_helper(node->left);
    find_best_seller_helper(node->right);
}

void RB_tree::preorder_helper(Node* node, int depth) {
    if (node == nullptr) {
        return; // Base case: stop if node is nullptr
    }

    // Print the indentation for current node based on its depth
    for (int i = 0; i < depth; ++i) {
        cout << "-"; // Indentation for child nodes
    }

    // Print the node information (publisher's name and color)
    cout << "(" << (node->color == 1 ? "RED" : "BLACK") << ") " << node->key.name << endl;

    // Recursively call the function for the left and right children, increasing the depth
    preorder_helper(node->left, depth + 1);
    preorder_helper(node->right, depth + 1);
}
