/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
  if(subRoot==NULL)
  {
    return;
  }

  Node* temp=subRoot->right;
  subRoot->right=subRoot->left;
  subRoot->left=temp;

mirror(subRoot->right);
mirror(subRoot->left);

}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
  Node *currNode, *preNode;
  if (root == NULL)
    return true;
  currNode = root;
  while (currNode != NULL) {
    if (currNode->left == NULL) {
      currNode = currNode->right;
      if (currNode != NULL) {
        if (currNode->left != NULL) {
          if (currNode->left->elem > currNode->elem) {
            return false;
          }
        }
        if (currNode->right != NULL) {
          if (currNode->right->elem < currNode->elem) {
            return false;
          }
        }
      }
    } else {
      preNode = currNode->left;
      while (preNode->right != NULL && preNode->right != currNode)
        preNode = preNode->right;
      if (preNode->right == NULL) {
        preNode->right = currNode;
        if (currNode->left == NULL) {
          currNode = currNode->left;
          if (currNode != NULL) {
            if (currNode->left != NULL) {
              if (currNode->left->elem > currNode->elem) {
                return false;
              }
            }
            if (currNode->right != NULL) {
              if (currNode->right->elem < currNode->elem) {
                return false;
              }
            }
          }
        } else {
          preNode->right = NULL;
          currNode = currNode->right;

          if (currNode != NULL) {
            if (currNode->left != NULL) {
              if (currNode->left->elem > currNode->elem) {
                return false;
              }
            }
            if (currNode->right != NULL) {
              if (currNode->right->elem < currNode->elem) {
                return false;
              }
            }
          }
        }
      }
    }
  }
  return true;

}



/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
 template <typename T>
 bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const{

   if (subRoot == NULL){
     return true;
   }

   T left_elem = subRoot->elem;
   T right_elem = left_elem;
   bool left_side = false;
   bool right_side = left_side;

   if(subRoot->left != NULL){
     left_side = isOrderedRecursive(subRoot->left);
     left_elem = find(subRoot->left);
   }
   else if (subRoot->left == NULL){
     left_side = true;
   }

   if(subRoot->right != NULL){
     right_side = isOrderedRecursive(subRoot->right);
     right_elem = find(subRoot->right);
   }
   else if (subRoot->right == NULL){
     right_side = true;
   }

   if(left_side==true && right_side==true){
     if(subRoot->elem >=left_elem && subRoot->elem <=right_elem)
     {
       return true;
     }
   }
   return false;
 }

 template <typename T>
 T BinaryTree<T>::find(const Node* subRoot) const {
   if(subRoot->left != NULL)
   {
     return find(subRoot->left);
   }
   else
   {
     return subRoot->elem;
   }

   if(subRoot->right != NULL)
   {
    return find(subRoot->right);
   }
   else
   {
     return subRoot->elem;
   }
 }


template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
 template <typename T>
 void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
 {
     // your code here
     vector<T> vec;
     printPaths(root, paths, vec);
 }

 template <typename T>
 void BinaryTree<T>::printPaths(const Node* subRoot, vector<vector<T> > &paths, vector<T> &vec) const {
   if(subRoot==NULL){
     return;
   }
   vec.push_back(subRoot->elem);
   if (subRoot->left == NULL && subRoot->right == NULL){
     paths.push_back(vec);
     vec.pop_back();
     return;
   }
   if (subRoot->left != NULL){
     printPaths(subRoot->left, paths, vec);
   }
   if (subRoot->right != NULL){
     printPaths(subRoot->right, paths, vec);
   }
   vec.pop_back();
 }
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
 template <typename T>
 int BinaryTree<T>::sumDistances() const
 {
     // your code here
     return sumDistances(root, 0);
 }

 template <typename T>
 int BinaryTree<T>::sumDistances(const Node* subRoot, int distance) const {
   const Node* left;
   const Node* right;
   if (subRoot==NULL){
     return 0;
   }
   else{
     left=subRoot->left;
     right=subRoot->right;
     return (distance + sumDistances(left, distance+1) + sumDistances(right, distance+1));
   }
 }
