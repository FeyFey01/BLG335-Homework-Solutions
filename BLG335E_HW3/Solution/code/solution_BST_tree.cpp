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

/////////////////// BST-Tree ///////////////////
class BST_tree{
	private:
		Node* root;
		void find_best_seller_recursive(Node* node);

	public:	
        publisher* best_seller[3];	

		stack<string> tree_deep_stack; // i didnt use this

        Node* get_root();
		Node* BST_insert(Node* root, Node* ptr);
		void insertValue(vector<string>);

        void find_best_seller(); 
        void preorder(Node* node, int depth);
		void performRandomizedSearches(int num_searches, const string& filename); // performs asked amount of randomized searches from a given csv file
		publisher* searchByName(const string& name); 

        BST_tree();
		~BST_tree();
};

/////////////////// External Functions ///////////////////
void print_best_sellers(int year, publisher* temp_publisher[3]){
    cout.precision(5);
    cout<< "End of the "+to_string(year)+" Year"<<endl;
    cout<< "Best seller in North America: "+temp_publisher[0]->name+" - "<<temp_publisher[0]->na_sales<<" million"<<endl;
    cout<< "Best seller in Europe: "+temp_publisher[1]->name+" - "<<temp_publisher[1]->eu_sales<<" million"<<endl;
    cout<< "Best seller rest of the World: "+temp_publisher[2]->name+" - "<<temp_publisher[2]->others_sales<<" million"<<endl;
}

// returns a vector of publisher names
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

    // Read each line from the file
    while (getline(file, line)) { // repeat for every line
        vector<string> row;
        string value;
        size_t pos = 0;

        while ((pos = line.find(',')) != string::npos) {
            value = line.substr(0, pos);
            row.push_back(value); // push the value until the first comma
            line.erase(0, pos + 1); // erase the extracted value and its comma from the line
        }
        row.push_back(line); // push the last column with no comma at the end for this row

        publisher_names.push_back(row[3]);  // Push the publisher into the vector
    }

    file.close();
    return publisher_names;
}

BST_tree generate_BST_tree_from_csv(string file_name){
    
    BST_tree temp_BSTtree;

    ifstream file(file_name);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file: " << file_name << endl;
        return temp_BSTtree;
    }

    getline(file, line);

	int decade = 0; // decade offset
	long long total_insertion_time = 0LL;  // to accumulate the insertion time in microseconds

    while (getline(file, line)) {
        string value;
        size_t pos = 0;
		vector<string> row;

        while ((pos = line.find(',')) != string::npos) {
            value = line.substr(0, pos);
            row.push_back(value);
            line.erase(0, pos + 1);
        }
        row.push_back(line);

        // After the year read has passed the current decade, calculate the cumulative sales
		if (stoi(row[2]) > (1990+decade)){
			temp_BSTtree.find_best_seller();
			print_best_sellers(1990+decade, temp_BSTtree.best_seller);
			decade += 10;
		}

		high_resolution_clock::time_point start = high_resolution_clock::now(); // Start time for insertion
		temp_BSTtree.insertValue(row); // Insert into BST
		high_resolution_clock::time_point end = high_resolution_clock::now(); // End time for insertion

		// Add the duration of this insertion to the total insertion time
		total_insertion_time += duration_cast<microseconds>(end - start).count();
    }

	temp_BSTtree.find_best_seller();
	print_best_sellers(1990+decade, temp_BSTtree.best_seller); // Print the last decade too
	
	cout << "Time taken to insert all data into BST: " << total_insertion_time << " µs" << endl;

    file.close();
    return temp_BSTtree;
}

BST_tree generate_BST_tree_from_csv_ordered(string file_name){
      
    BST_tree temp_BSTtree;
    vector<vector<string>> publishers;  // To hold rows of data

    ifstream file(file_name);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file: " << file_name << endl;
        return temp_BSTtree;
    }

    getline(file, line);
	long long total_insertion_time = 0LL;  // To accumulate the insertion time in microseconds
    // Read and parse each line again
    while (getline(file, line)) {
        string value;
        size_t pos = 0;
		vector<string> row;

        while ((pos = line.find(',')) != string::npos) {
            value = line.substr(0, pos);
            row.push_back(value);
            line.erase(0, pos + 1);
        }
        row.push_back(line);
        publishers.push_back(row);
    }
    file.close();

    sort(publishers.begin(), publishers.end(), [](const vector<string>& a, const vector<string>& b) {
        return a[0] < b[0];  // Compare the first element of the inner vectors
    });

    for (auto& row : publishers) { // iterate inside the sorted vector
        row[3] = row[0]; // my insert value uses the index 3 for data insertion so im moving the name into 3rd index

        high_resolution_clock::time_point start = high_resolution_clock::now(); // Start time for insertion
		temp_BSTtree.insertValue(row); // Insert into BST
		high_resolution_clock::time_point end = high_resolution_clock::now(); // End time for insertion

		// Add the duration of this insertion to the total insertion time
		total_insertion_time += duration_cast<microseconds>(end - start).count();
    }

    cout << "Time taken to insert all data into BST: " << total_insertion_time << " µs" << endl;
    return temp_BSTtree;
}


////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char* argv[]) {

    string fname = argv[1];
    BST_tree BSTtree = generate_BST_tree_from_csv(fname); // read + insert + search/print best seller
    // BST_tree BSTtree_ordered = generate_BST_tree_from_csv_ordered(fname); // create ordered tree

    // Perform 50 random searches
	BSTtree.performRandomizedSearches(50, fname);
    // BSTtree_ordered.performRandomizedSearches(50, fname);

    BSTtree.preorder(BSTtree.get_root(), 0); // preorder printing here
    // BSTtree_ordered.preorder(BSTtree_ordered.get_root(), 0);            
    return EXIT_SUCCESS;
}

/////////////////// Node ///////////////////
Node::Node(publisher key){
	this->key = key;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

/////////////////// BST-Tree ///////////////////
BST_tree::BST_tree(){
	this->root = NULL;
    this->best_seller[0] = NULL;
    this->best_seller[1] = NULL;
    this->best_seller[2] = NULL;
}

BST_tree::~BST_tree(){
}

/////////////////// BST-Tree Functions ///////////////////
Node* BST_tree::get_root(){

    // I didnt add anything else bc this is already working

    return this->root;
}

Node* BST_tree::BST_insert(Node* root, Node* ptr){

    // Base case: If the current root is null, return this as the root
    if (root == nullptr) {
        return ptr;
    }

    // Insert by name
    if (ptr->key.name < root->key.name) {
        root->left = BST_insert(root->left, ptr); // recursively add to left
    }
    else if (ptr->key.name > root->key.name) {
        root->right = BST_insert(root->right, ptr); // recursively add to right
    }
    else {
        // IF publisher already exists add to cumulative sales
        root->key.na_sales += ptr->key.na_sales;
        root->key.eu_sales += ptr->key.eu_sales;
        root->key.others_sales += ptr->key.others_sales;
    }

    return root;  // Return the root

}

void BST_tree::insertValue(vector<string> n) {

    // Parse input values
    publisher pub;
    pub.name = n[3];  // Publisher name
    pub.na_sales = stof(n[4]);   // Convert string to float
    pub.eu_sales = stof(n[5]);
    pub.others_sales = stof(n[6]);

    // Create a new node
    Node* newNode = new Node(pub);

    // insert the node into the tree
    root = BST_insert(root, newNode);

}

void BST_tree::find_best_seller(){

	Node* current = root;

    while (current != nullptr) {
        // If the current node has a left child, go to the leftmost node

        if (current->left != nullptr) { // Find the rightmost node in the left subtree
            
            Node* pre = current->left;
            while (pre->right != nullptr && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == nullptr) {
                pre->right = current;
                current = current->left; 
            }

            // Already visited the left subtree
            else {
                pre->right = nullptr;
                if (best_seller[0] == nullptr || current->key.na_sales > best_seller[0]->na_sales)
                    best_seller[0] = &current->key;
                if (best_seller[1] == nullptr || current->key.eu_sales > best_seller[1]->eu_sales)
                    best_seller[1] = &current->key;
                if (best_seller[2] == nullptr || current->key.others_sales > best_seller[2]->others_sales)
                    best_seller[2] = &current->key;

                current = current->right;
            }
        }
        // If there's no left child
        else { 
            
            if (best_seller[0] == nullptr || current->key.na_sales > best_seller[0]->na_sales)
                best_seller[0] = &current->key;
            if (best_seller[1] == nullptr || current->key.eu_sales > best_seller[1]->eu_sales)
                best_seller[1] = &current->key;
            if (best_seller[2] == nullptr || current->key.others_sales > best_seller[2]->others_sales)
                best_seller[2] = &current->key;

            current = current->right;
        }
    }
}

void BST_tree::preorder(Node* node, int depth) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < depth; ++i) {
        cout << "-"; // - for child nodes
    }

    // Print the publisher's name
    cout << node->key.name << endl;

    preorder(node->left, depth + 1); // recursively call leftside with more depth
    preorder(node->right, depth + 1); // call rightside
}

publisher* BST_tree::searchByName(const string& name) {
    Node* current = root;
    
    while (current != nullptr) {
        // Compare the publisher names
        if (name < current->key.name) {
            current = current->left; 
        }
        else if (name > current->key.name) {
            current = current->right; 
        }
        else {
            // return the publisher data
            return &current->key;
        }
    }
    
    // If not found, return nullptr
    return nullptr;
}

void BST_tree::performRandomizedSearches(int num_searches, const string& filename) {

    // Get the list of publisher names from the CSV
    vector<string> publisher_names = returnNameVector(filename);

    if (publisher_names.empty()) {
        return;
    }

    // Random number generator to select random publisher names
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, publisher_names.size() - 1);

    double total_search_time = 0;
    for (int i = 0; i < num_searches; ++i) {
        // Random publisher name from the list
        string random_search_key = publisher_names[dis(gen)];

        high_resolution_clock::time_point search_start = high_resolution_clock::now();
        publisher* found_pub = searchByName(random_search_key);
        high_resolution_clock::time_point search_end = high_resolution_clock::now();

        // Add the search time in nanoseconds 
        total_search_time += duration_cast<nanoseconds>(search_end - search_start).count();;
    }

    // Calculate the average search time in nanoseconds
    double average_search_time = total_search_time / num_searches;

    cout << fixed << setprecision(1);  // Set output to one decimal place
    cout << "Average time for " << num_searches << " random searches : " << average_search_time << " ns" << endl;
}

// I am not using this but this is also a method:
void BST_tree::find_best_seller_recursive(Node* node){
    if (node == nullptr) return;

    // Check and update best sellers for each region
    if (best_seller[0] == nullptr || node->key.na_sales > best_seller[0]->na_sales)
        best_seller[0] = &node->key;
    if (best_seller[1] == nullptr || node->key.eu_sales > best_seller[1]->eu_sales)
        best_seller[1] = &node->key;
    if (best_seller[2] == nullptr || node->key.others_sales > best_seller[2]->others_sales)
        best_seller[2] = &node->key;

    // Recursive traversal
    find_best_seller_recursive(node->left);
    find_best_seller_recursive(node->right);
}

