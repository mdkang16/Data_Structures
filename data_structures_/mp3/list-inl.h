/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* ptr=head_;
  ListNode* temp;
  head_= tail_= NULL;
  length_=0;

  while(ptr != NULL)
  {
    temp=ptr;
    ptr=ptr->next;
    delete temp;
  }

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* insert_front = new ListNode(ndata);
  if(head_ != NULL)
  {
    insert_front->next=head_;
    head_->prev=insert_front;
    head_=insert_front;
  }
  else if(head_ == NULL)
  {
    insert_front->prev=insert_front->next=NULL;
    head_=tail_=insert_front;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* insert_back = new ListNode(ndata);
  if(head_ != NULL)
  {
    insert_back->prev=tail_;
    tail_->next=insert_back;
    tail_=insert_back;
  }
  else if(head_ == NULL)
  {
    insert_back->prev=insert_back->next=NULL;
    head_=tail_=insert_back;
  }
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if(startPoint==endPoint)
  {
    return;
  }
  ListNode* temp;
  ListNode* start_point = startPoint;
  ListNode* start_prev = startPoint->prev;
  ListNode* end_next = endPoint->next;

  while(start_point!=endPoint)
  {
    temp=start_point->prev;
    start_point->prev = start_point->next;
    start_point->next = temp;
    start_point=start_point->prev;
  }

  temp=start_point->prev;
  start_point->prev=start_prev;
  start_point->next=temp;
  endPoint=startPoint;
  endPoint->next=end_next;

  start_prev != NULL ? start_prev->next=start_point : head_=start_point;
  end_next != NULL ? end_next->prev=endPoint : tail_=endPoint;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if((n==0) || (head_==NULL))
  {
    return;
  }
  ListNode* startPoint=head_;
  ListNode* endPoint=head_;

  while(startPoint != NULL)
  {
    for(int i=0; i<n-1; i++)
    {
      if(endPoint->next != NULL)
      {
        endPoint=endPoint->next;
      }
    }
    reverse(startPoint, endPoint);
    startPoint=endPoint=endPoint->next;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(head_==NULL)
  {
    return;
  }
  if(head_==tail_)
  {
    return;
  }

  ListNode* curr=head_;
  ListNode* temp;
  ListNode* nextnode;

  while(curr->next != NULL && curr->next->next != NULL)
  {
    temp=curr->next;
    nextnode=curr->next->next;
    curr->next=nextnode;
    nextnode->prev=curr;
    temp->prev=tail_;
    tail_->next=temp;
    temp->next=NULL;
    tail_=temp;
    curr=nextnode;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* split_node=NULL;

  if(start==NULL){
    return start;
  }
  for(int i=0; i<splitPoint; i++){
    if(start->next==NULL){
      return start;
    }
    start=start->next;
  }
  split_node=start;
  split_node->prev->next=NULL;
  split_node->prev=NULL;
  return split_node;

}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
ListNode* mergeptr=NULL;

mergeptr=head_=first;
mergeptr->prev=NULL;

if(second->data < first->data){
  mergeptr=head_=second;
  second=second->next;
}
else{
  first=first->next;
}

while(first!=NULL && second!=NULL){
  if(first->data < second->data){
    mergeptr->next=first;
    first->prev=mergeptr;
    mergeptr=first;
    first=first->next;
  }
  else{
    mergeptr->next=second;
    second->prev=mergeptr;
    mergeptr=second;
    second=second->next;
  }
}
if(first==NULL && second!=NULL){
  mergeptr->next=second;
}
else if(first!=NULL && second==NULL){
  mergeptr->next=first;
}
mergeptr->next->prev=mergeptr;
return head_;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode* ptr1=start;
  ListNode* ptr2=start;
  ListNode* result=NULL;

  if(chainLength==1){
    start->prev=NULL;
    start->next=NULL;
    return start;
  }

  else if(chainLength!=1){
    for(int i=0; i<chainLength/2; i++){
      ptr2=ptr2->next;
    }

    ptr2->prev->next=NULL;
    ptr2->prev=NULL;
    ptr1=mergesort(ptr1, chainLength/2);
    ptr2=mergesort(ptr2, chainLength-chainLength/2);
    result=merge(ptr1, ptr2);
  }
  return result;
}
