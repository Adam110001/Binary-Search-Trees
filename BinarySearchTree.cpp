#include "bst.h"

using namespace std;

// Creates an empty binary tree
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

// Creates a binary tree with an initial word to store
BinarySearchTree::BinarySearchTree(string word)
{
    insert(word);
}

Node *copy(Node* brench)
{
    Node *newBrench = new Node;
    if (brench) {
        newBrench -> data = brench->data;
        newBrench -> left = copy(brench->left);
        newBrench -> right = copy(brench -> right);
    }
    else return nullptr;
    return newBrench;
}

// Creates a binary tree by copying an existing tree
BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs)
{
    root = copy(rhs.root);
}

void destroyTreeHelper(Node** tree_node)
{
    string data;
    
    if(*tree_node == nullptr)
        return;
    else if (data <= (*tree_node) -> data) //Checks for smaller values
        (*tree_node) -> left = nullptr;
    else if (data > (*tree_node) -> data) //Checks for greater values
        (*tree_node) -> right = nullptr;
    else
        return;
}

// Destroys (cleans up) the tree
BinarySearchTree::~BinarySearchTree()
{
    destroyTreeHelper(&root);
}

void insertHelper(Node **tree, string data)
{
    if (*tree == nullptr) {
        *tree = new Node;
        (*tree) -> data = data;
        (*tree) -> left = nullptr;
        (*tree) -> right= nullptr;
    } else {
        if (data < (*tree) -> data)
            insertHelper(&(*tree) -> left, data);
        else if (data > (*tree) -> data)
            insertHelper(&(*tree) -> right, data);
        else
            return;
    }
}

// Adds a word to the tree
void BinarySearchTree::insert(string word)
{
    insertHelper(&root, word);
}

void removeHelper(Node **tree, string data)
{
    // Find the item
    bool occured = false;
    Node* previous = nullptr;
    Node* current = (*tree);
    if(current == nullptr)
        return;
    while(current != nullptr)
    {
        if(current->data==data)
        {
            occured = true;
            break;
        }
        else
        {
            previous = current;
            if(data > (current->data))
                current=current->right;
            else
                current=current->left;
        }
    }
    if(!occured)
    {
        return;
    }
    // CASE 1: Removing a node with a single child
    if((current->left==nullptr && current->right != nullptr) || (current->left != nullptr && current->right==nullptr))
    {
        // Data on right are present
        if(current->left==nullptr && current->right != nullptr)
        {
            // If predecessor's left tree equals Node tree
            if(previous->left==current)
            {
                // then predecessor's left tree becomes tree's right tree and delete tree
                previous->left=current->right;
                delete current;
                current=nullptr;
            }
            // If predecessor's right tree equals Node tree
            else
            {
                // then predecessor's right tree becomes tree's right tree and delete tree
                previous->right=current->right;
                delete current;
                current=nullptr;
            }
        }
        else // Data present ont left
        {
            if(previous->left==current)
            {
                previous->left=current->left;
                delete current;
                current=nullptr;
            }
            else
            {
                previous->right=current->left;
                delete current;
                current=nullptr;
            }
        }
        return;
    }
    // CASE 2: Removing a Node
    if(current->left==nullptr && current->right==nullptr)
    {
        if(previous->left==current)
            previous->left=nullptr;
        else
            previous->right=nullptr;
        delete current;
        return;
    }
    // CASE 3: Replaces Node with smallest value in right subtree
    if(current->left != nullptr && current->right != nullptr)
    {
        Node* check=current->right;
        if((current->left==nullptr)&&(current->right==nullptr))
        {
            current=check;
            delete check;
            current -> right = nullptr;
        }
        else // Right child has children
        {
            // If the node's right child has a left child. Move all the way down left to locate smallest element
            if((current->right)->left!=nullptr)
            {
                Node* leftCurrent;
                Node* leftCurrentPrev;
                leftCurrentPrev=current->right;
                leftCurrent=(current->right)->left;
                while(leftCurrent->left != nullptr)
                {
                    leftCurrentPrev=leftCurrent;
                    leftCurrent=leftCurrent->left;
                }
                current->data=leftCurrent->data;
                delete leftCurrent;
                leftCurrentPrev -> left = nullptr;
            }
            else
            {
                Node* temp=current->right;
                current->data=temp->data;
                current->right=temp->right;
                delete temp;
            }
        }
        return;
    }
}


// Removes a word from the tree
void BinarySearchTree::remove(string word)
{
    removeHelper(&root, word);
}

bool existsHelper(Node* tree, string data)
{
    // Checks if curent data are equal to data
    if (tree -> data == data) {
        return true;
    }
    //Checks if left side of tree consists of data needed
    if (tree -> left && existsHelper(tree -> left, data)) {
        return true;
    }
    //Checks if left side of tree consists of data needed
    if (tree -> right && existsHelper(tree -> right, data)) {
        return true;
    }
    return false;
}

// Checks if a word is in the tree
bool BinarySearchTree::exists(std::string word) const
{
    return existsHelper(root, word);
}

std::string inorderHelper(Node *root)
{
    if(root == nullptr)
    {
        return "";
    }
    else
    {
        return inorderHelper(root->left)
        + root->data + " "
        + inorderHelper(root->right);
    }
}

// Creates a string representing the tree in alphabetical order
std::string BinarySearchTree::inorder() const
{
    string res = inorderHelper(root);
    int len = res.length();
    if(len >= 1 && res[len -1] == ' ')
    {
        res.pop_back();
    }
    return res;
}

//Retrieves data and sets them into order
std::string preorderHelper(Node *root)
{
    if(root == nullptr)
    {
        return "";
    }
    else
    {
        return root->data + " "
        + preorderHelper(root->left)
        + preorderHelper(root->right);
    }
}

// Creates a string representing the tree in pre-order
std::string BinarySearchTree::preorder() const
{
    string res = preorderHelper(root);
    int len = res.length();
    if(len >= 1 && res[len -1] == ' ')
    {
        res.pop_back();
    }
    return res;
}

//Retrieves data and sets them into order
std::string postorderHelper(Node *root)
{
    if(root == nullptr)
    {
        return "";
    }
    else
    {
        return postorderHelper(root->left)
        + postorderHelper(root->right)
        + root->data + " ";
    }
}

// Creates a string representing the tree in post-order
std::string BinarySearchTree::postorder() const
{
    string res = postorderHelper(root);
    int len = res.length();
    if(len >= 1 && res[len -1] == ' ')
    {
        res.pop_back();
    }
    return res;
}

// Checks if two trees are equal
bool BinarySearchTree::operator==(const BinarySearchTree &other) const
{
    bool tree = false;
    
    //Check if data are similar
    if (this->root && other.root)
    {
        // If the data match the other root then true
        if (this->root->data == other.root->data && this->root->left == other.root->left && this->root->right == other.root->right)
            tree = true;
    }
    return tree;
}

// Checks if two trees are not equal
bool BinarySearchTree::operator!=(const BinarySearchTree &other) const
{
    if (this == &other)
    {
        return false;
    }
    else
        return true;
}

// Reads in words from an input stream into the tree
std::istream& operator>>(std::istream &in, BinarySearchTree &tree)
{
    return in;
}

// Writes the words, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const BinarySearchTree &tree)
{
    return out << tree.inorder();
}
