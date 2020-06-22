/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements (int num){
  for(int i=0; i<num; i++){             //push the elements into the vector
    vset.push_back(-1);
  }
  return;
}

int DisjointSets::find (int elem)	{
  if(vset[elem] < 0){                   //check for the root, which has a negative element
    return elem;
  }
  else{                                 //recursively find the root
    return find(vset[elem]);
  }
}

void DisjointSets::setunion (int a, int b){
  int root_a = find(a);                         //find the root of each element
  int root_b = find(b);
  int size = vset[root_a] + vset[root_b];       //set the new size

//if the root of the first element has less height or if there is a tie,
//connect the second element to the first element
  if(vset[root_a] < vset[root_b] || vset[root_a] == vset[root_b]){
    vset[root_b] = root_a;
    vset[root_a] = size;
  }
  else{                             //else, connect to the second element
    vset[root_a] = root_b;
    vset[root_b] = size;
  }
}

int DisjointSets::size(int elem){
  int root_elem = find(elem);         //find the root, which has the height
  return root_elem;
}
