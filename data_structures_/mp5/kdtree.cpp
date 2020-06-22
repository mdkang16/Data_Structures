/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <algorithm>
#include <utility>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> &first,
                                const Point<Dim> &second, int curDim) const {
  /**
   * @todo Implement this function!
   */
  if (first[curDim] < second[curDim]) {             /*return true if the first element is bigger*/
    return true;                                    /*than the second element*/
  } else if (first[curDim] == second[curDim]) {     /*if equal, use < operator*/
    return (first < second);
  } else {                                          /*else return false*/
    return false;
  }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> &target,
                                const Point<Dim> &currentBest,
                                const Point<Dim> &potential) const {
  /**
   * @todo Implement this function!
   */
  double curr_dist = 0.0;                         /*initialize current and potential distances*/
  double pot_dist = 0.0;

  for (int i = 0; i < Dim; i++) {                 /*calculate the distance*/
    curr_dist = curr_dist + pow((target[i] - currentBest[i]), 2);
    pot_dist = pot_dist + pow((target[i] - potential[i]), 2);
  }

  if (pot_dist < curr_dist) {                      /*if the current distance is greater*/
    return true;                                   /*return true*/
  } else if (pot_dist == curr_dist) {              /*if they are equal, use < operator*/
    return potential < currentBest;
  } else {                                         /*else return false*/
    return false;
  }
}

template <int Dim> KDTree<Dim>::KDTree(const vector<Point<Dim>> &newPoints) {
  /**
   * @todo Implement this function!
   */
  newvector = newPoints;                            /*set the vector to newvector*/
  size = newvector.size();                          /*initialize the size*/
  const_help(0, newvector.size() - 1, 0, root);     /*call the helper function*/
}

template <int Dim> KDTree<Dim>::KDTree(const KDTree &other) {
  /**
   * @todo Implement this function!
   */
   root = copy(other.root);
}

template <int Dim>
void KDTree<Dim>::const_help(int first, int last, int dimension,
                             KDTreeNode *newroot) {
  int middle_index = (first + last) / 2;                /*calculate the middle index*/
  Quickselect(first, last, dimension, middle_index);    /*sort using helper function*/

  KDTreeNode *subroot = new KDTreeNode();               /*create a new node*/
  root = subroot;                                       /*set it as root*/
  if (newvector.size() > 0)                             /*set the point to the node*/
    subroot->point = newvector[middle_index];

  if (size - (unsigned int)last - 1 == 0) {             /*setting the root*/
    root = subroot;
  } else {                                              /*setting the subroot*/
    newroot = subroot;
  }

  if (first < middle_index - 1) {                       /*recursive call for the first half*/
    const_help(first, middle_index - 1, (dimension + 1) % Dim, subroot->left);
  }
  if (last > middle_index + 1) {                        /*recursive call for the second half*/
    const_help(first, middle_index - 1, (dimension + 1) % Dim, subroot->right);
  }
}

template <int Dim>
void KDTree<Dim>::Quickselect(int first, int last, int dimension,
                              int middle_index) {

  if (first >= last) {                                  /*already sorted, return*/
    return;
  }

  int pivotindex = (first + last) / 2;                  /*initialize the pivot index*/
  pivotindex = Partition(first, last, dimension, pivotindex); /*call the helper function for partition*/

  if (middle_index == pivotindex) {                     /*if the middle index and the */
    return;                                             /*pivot index equal, return*/
  } else if (middle_index < pivotindex) {               /*if pivot index is greater, sort the first half*/
    Quickselect(first, pivotindex - 1, dimension, middle_index);
  } else {                                              /*else, sort the second half*/
    Quickselect(pivotindex + 1, last, dimension, middle_index);
  }
}
template <int Dim>
int KDTree<Dim>::Partition(int first, int last, int dimension, int pivotindex) {
  int index = first;                                    /*set the index as the first element*/
  Point<Dim> pivotvalue = newvector[pivotindex];        /*set the pivot value*/
  std::swap(newvector[pivotindex], newvector[last]);    /*swap the pivot value and the last element*/
  for (int i = first; i < last; i++) {
    if (smallerDimVal(newvector[i], pivotvalue, dimension)) {   /*if smaller than the pivot value*/
      std::swap(newvector[index], newvector[i]);                /*swap the value and the first element*/
      index++;                                                  /*increment the index value*/
    }
  }
  std::swap(newvector[last], newvector[index]);                 /*swap the last and the index value*/
  return index;
}

template <int Dim>
const KDTree<Dim> &KDTree<Dim>::operator=(const KDTree &rhs) {
  /**
   * @todo Implement this function!
   */
   if(this!=&rhs){
     clear(root);
     root=copy(rhs.root);
   }

  return *this;
}

template <int Dim> KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
  //   delete root;
}

template <int Dim>
void KDTree<Dim>::clear() {
  clear(root);
  root=NULL;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode *subNode){
  if (subNode == NULL)
          return;

      clear(subNode->left);
      clear(subNode->right);
      delete subNode;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &query) const {
  /**
   * @todo Implement this function!
   */
  Point<Dim> current_best;                /*set up the current best, the point vector*/
  int first = 0;
  int last = newvector.size() - 1;
  double smaller_rad = 0.0;
  neighbor_help(first, last, smaller_rad, 0, query, current_best);
  return current_best;
}
template <int Dim>
void KDTree<Dim>::neighbor_help(int first, int last, double smaller_rad,
                                int dimension, const Point<Dim> &query,
                                Point<Dim> &current_best) const {
  int middle_index = (first + last) / 2;            /*set the middle index*/
  double current_rad = 0.0;
  if (first > last) {                    /*if the first element is greater, return*/
    return;
  }
  if (first == last) {                  /*if first element and the last element equal*/
    if (shouldReplace(query, current_best, newvector[first])) { /*if should bereplaced*/
      current_best = newvector[first];                          /*reset the current best*/
    }
    return;
  }


//if query is smaller than the median, call the neighbor helper function for
//the range of the first element to the middle index-1
//if should be replaced, reset the current best as the median
//calculate the current radius and the smaller radius
//if smaller radius is greater than or equal to the current radius
//call the neighbor helper function for the range of middle index+1 to the last element

  if (smallerDimVal(query, newvector[middle_index], dimension)) {
    neighbor_help(first, middle_index - 1, smaller_rad, (dimension + 1) % Dim,
                  query, current_best);
    if (shouldReplace(query, current_best, newvector[middle_index])) {
      current_best = newvector[middle_index];
    }
    current_rad = pow(query[dimension] - newvector[middle_index][dimension], 2);
    smaller_rad = radius(current_best, query);
    if (current_rad <= smaller_rad) {
      neighbor_help(middle_index + 1, last, smaller_rad, (dimension + 1) % Dim,
                    query, current_best);
    }
  }

  //if query is greater than the median, call the neighbor helper function for
  //the range of the the middle index+1 to the last element
  //if should be replaced, reset the current best as the median
  //calculate the current radius and the smaller radius
  //if smaller radius is greater than or equal to the current radius
  //call the neighbor helper function for the range of first element to the middle index+1

  else {
    neighbor_help(middle_index + 1, last, smaller_rad, (dimension + 1) % Dim,
                  query, current_best);
    if (shouldReplace(query, current_best, newvector[middle_index])) {
      current_best = newvector[middle_index];
    }
    current_rad = pow(query[dimension] - newvector[middle_index][dimension], 2);
    smaller_rad = radius(current_best, query);
    if (current_rad <= smaller_rad) {
      neighbor_help(first, middle_index - 1, smaller_rad, (dimension + 1) % Dim,
                    query, current_best);
    }
  }
}

template <int Dim>
double KDTree<Dim>::radius(const Point<Dim> &pt_one,
                           const Point<Dim> &pt_two) const {
  double res = 0.0;
  for (int i = 0; i < Dim; i++) {                     /*calculate the radius*/
    res = res + pow(pt_one[i] - pt_two[i], 2);        /*using the power of 2*/
  }
  return res;
}
