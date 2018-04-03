#include <queue>

namespace queueAndHowItWorksInternally {
    /*
    Deque is a double ended queue container that provides insertion 
    and deletion at both ends i.e. front and back with
    high performance unlike vector that provides 
    high performance insertion at end i.e. back only.

    Inserting an element in front of deque,
    dequeObj.push_front(4);
    dequeObj.push_front(3);

    Inserting an element in back/end of deque,
    dequeObj.push_back(5);
    dequeObj.push_back(6);
    Now Deque will contain elements in following order,
    3, 4, 5, 6

    Deleting element from front of deque,
    dequeObj.pop_front();
    Now Deque will contain elements in following order,
    4, 5, 6

    Deleting element from back of deque,
    dequeObj.pop_back();

    Now Deque will contain elements in following order,
    4, 5
    */

    //How std::deque works internally
    /*
    A deque is generally implemented as a collection of memory blocks. These memory blocks contains the elements at contiguous locations.
    When we create a deque object it internally allocates a memory block to store the elements at continuous location.
    When we insert an element in end it stores that in allocated memory block 
    until it gets filled and when this memory block gets filled 
    with elements then it allocates a new memory block and 
    links it with the end of previous memory block. Now further 
    inserted elements in the back are stored in this new memory block.
    */
}

namespace dequeAndVectorWhatToChoose {
    // the differences between vector and deque STL Containers.

    // Vector provides insertion and deletion at middle and end only. Whereas, deque provides operations for insertion at front, middle and end.
    // Vector provides good performance while insertion and deletion at end only and bad performance for insertion and deletion at middle.
    // Deque provides same kind of performance as vector for insertion & deletion at end and middle. Apart from that deque provides good performance for insertion and deletion at front also.
    // As Vector stores elements contiguously, where as deque internally contains a list of memory chunks which store elements contiguously. 
    
    // Performance of addition and deletion at end for vector is better than deque.
    // No Iterator invalidation happens in deque for insertion and deletion at front and end because like vectors
    // Iterator invalidation happens in deque just like vector, if insertion or deletion takes place in the middle.
    // Just like vector, deque also supports random access operations i.e. operator [] and at() function. Although performance of random access in deque will be little slower than vector.

    // When to choose deque over vector:
    // One should choose deque over vector if he wants to either add or delete from both the ends like implementing a Queue.

    // When to choose vector over deque:
    // One should choose vector if insertion or deletions are required mostly in end like implementing a Stack.
}

int main()
{
    return;
}