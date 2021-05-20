#include <iostream>
#include<vector>
#include <bits/stdc++.h>
#include <sys/time.h>

using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
  int height;
};

int max(int a, int b){
    return (a>b)? a : b;
}

// height of tree
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

Node* New_Node(int key) {
  Node* node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *z = x->right;
  x->right = y;
  y->left = z;
  y->height = max(height(y->left),height(y->right)) + 1;
  x->height = max(height(x->left),height(x->right)) + 1;
  return x;
}

// Rotate left
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *z = y->left;
  y->left = x;
  x->right = z;
  x->height = max(height(x->left),height(x->right)) + 1;
  y->height = max(height(y->left),height(y->right)) + 1;
  return y;
}

int balance_factor(Node* N) {
  if (N == NULL) 
    return 0;
  return ( height(N->left) - height(N->right) );
}

Node* insertNode(Node* node, int key) {
  // insertion of new node at leaf
  if (node == NULL)
    return (New_Node(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node; //case: node with key already present --> no insertion

  // balancing of tree
  node->height = 1 + max( height(node->left),height(node->right) ); 
  int balanceFactor = balance_factor(node);
  if (balanceFactor > 1)
  {
    if (key < node->left->key){
      return rightRotate(node);
    } 
    else if (key > node->left->key){
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

// Node with minimum value
Node* node_MimumKey(Node* node) {
  Node* current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

// Search the tree
Node* Search_Tree(Node* root, int key){
    if (root == NULL)
        return root;
    if (key < root->key){
        root = root->left;
        Search_Tree (root, key);
    }
    else if(key > root->key){
        root = root->right;
        Search_Tree (root, key);
    }
    else 
        return root;
}


// Delete a node

Node* deleteNode(Node* root, int key) {
  
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) || (root->right == NULL))
    {
      Node* temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node *temp = node_MimumKey(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = balance_factor(root);
  if (balanceFactor > 1) {
    if (balance_factor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (balance_factor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

vector<double> search_time_estimator(vector<int> v, Node* root) //root is the initial node where iteration starts
{
    vector<int>::iterator it; //iterator for input list of integers for performing search in the AVl tree
    vector<double> search_time_list;
    struct timeval start, end;
    
    for(it = v.begin(); it != v.end(); ++it){
        
        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
    
        root = Search_Tree(root,*it); //cycles of insertions
        
        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        search_time_list.push_back(time_taken);
    }
    return search_time_list;
}

double insert_time_estimator(vector<int> v, Node* root) //root is the initial node where iteration starts
{
    vector<int>::iterator it; //iterator for input list of integers for performing insertions into the AVl tree
    //vector<double> insert_time_list;
    struct timeval start, end;
    double time_taken;
    gettimeofday(&start, NULL);
    ios_base::sync_with_stdio(false);
    
    for(it = v.begin(); it != v.end(); ++it){
        root = insertNode(root,*it); //cycles of insertions
    }
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    //insert_time_list.push_back(time_taken);
    return time_taken;
}

vector<double> delete_time_estimator(vector<int> v, Node* root) //root is the initial node where iteration starts
{
    vector<int>::iterator it; //iterator for input list of integers for performing deletionss into the AVl tree
    vector<double> delete_time_list;
    struct timeval start, end;
    
    for(it = v.begin(); it != v.end(); ++it){
        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
    
        root = deleteNode(root,*it); //cycles of insertions
        
        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        delete_time_list.push_back(time_taken);
    }
    return delete_time_list;
}

Node* Tree_Creator(vector<int> v, Node* root)
{
    vector<int>::iterator it;
    for(it = v.begin(); it != v.end(); ++it){
        root = insertNode(root, *it);
    }
    
    return root;
}

// Print the tree
void printTree(Node *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

int main() {

  vector<int> insertion_vector(1500000, 10);
  vector<int> deletion_vector(1000000, 5);
  vector<int> search_vector(1000000, 6);
  
  //vector<double> result_insert = insert_time_estimator(insertion_vector, NULL);
  
  vector<double>::iterator pt;
  
  
  vector<double> insertion_time;
  for(int i = 0; i < 100000; ++i){
      vector<int> sample_vector(i,0);
      insertion_time.push_back(insert_time_estimator(sample_vector, NULL));
  }
  
  for(int j = 0 ; j < 100000; ++j){
      cout << insertion_time[j] << "," ;
  }
  /*
  cout<< "THIS IS THE INSERT TIME VECTOR" << endl;
  for(pt = result_insert.begin(); pt != result_insert.end(); ++pt){
      cout << *pt << setprecision(6) << ", ";
  }
  
  Node* New_Tree_Node = Tree_Creator(insertion_vector, NULL);
    
  vector<double> result_delete = delete_time_estimator(deletion_vector, New_Tree_Node);
  */
  /*
  cout<< "THIS IS THE DELETE TIME VECTOR" << endl;
  for(pt = result_delete.begin(); pt != result_delete.end(); ++pt){
      cout << *pt << setprecision(6) << ", ";
  }
  */
  
  //printTree(result, "", true);
  return 0;
}



