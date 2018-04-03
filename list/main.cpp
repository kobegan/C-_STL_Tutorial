#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
#include <string>

namespace tutorialExampleAndUsageDetails {
    /*
    What is std::list ?
    std::list is sequential STL container that is internally implemented as doubly linked list.
    i.e. every element in the list is stored at a seperate memory location i.e. called node and it also contains a pointer to the previous and next node.

    Vector vs List
    Creating a std::list of int and pushing elements in front and back
    //Inserting elements at end in list
    listOfNumbers.push_back(5);
    listOfNumbers.push_back(6);

    //Inserting elements at front in list
    listOfNumbers.push_front(2);
    listOfNumbers.push_front(1);
    List Contents are now,
    1 2 5 6
    */

    // Different ways to Initialize a List
    /*
    Inserting elements in the std::list
    insert(iterator_position,elem)
    It allocates a new node and copy the passed element to it and then inserts that node before iterator position iterator_position and returns the position of the newly added element.

    It has several other overloaded implementations i.e.
    insert(iterator_position,other_list_begin,other_list_end)
    // insert(pos,elem) member function. Let's iterate to
    // 3rd position
    it = listOfNumbers.begin();
    it++;
    it++;
    // Iterator 'it' is at 3rd position.
    listOfNumbers.insert(it, 4);
    Now List contents will be,
    1 2 4 5 6
    */

    // Iterating over a std::list of elements and display them
    /*
    // Iterating over list elements and display them
    it = listOfNumbers.begin();
    while(it != listOfNumbers.end())
    {
    std::cout<<(*it)<<"  ";
    it++;
    }
    std::cout<<std::endl;
    */

    //Erasing elements from std::list
    /*
    erase(iterator_position,elem)
    It erases the element at the passed node and change the left and right pointers of previous and next nodes. Also returns iterator of next node element. This operation takes O(1) time,

    It has an other overloaded implementations i.e.
    erase(other_list_begin,other_list_end)
    */

    //Removing elements from a std::list based on some condition
    /*
    ::remove(value) member function of std::list removes all the elements whose value is equivalent to passed value.
    ::remove_if(predicate) member function of std::list removes all the elements for which predicate(element) returns true.
    //Lets remove all elements with value greater than 3.
    listOfNumbers.remove_if([](int elem)
    {
    if(elem > 3)
    return true;
    else
    return false;
    });
    */
    void test()
    {
        std::list<int> listOfNumbers;

        //Inserting elements at end in list
        listOfNumbers.push_back(5);
        listOfNumbers.push_back(6);

        //Inserting elements at front in list
        listOfNumbers.push_front(2);
        listOfNumbers.push_front(1);

        // Iterating over list elements and display them
        std::list<int>::iterator it = listOfNumbers.begin();
        while (it != listOfNumbers.end())
        {
            std::cout << (*it) << "  ";
            it++;
        }
        std::cout << std::endl;


        //Inserting elements in between the list using
        // insert(pos,elem) member function. Let's iterate to
        // 3rd position
        it = listOfNumbers.begin();
        it++;
        it++;
        // Iterator 'it' is at 3rd position.
        listOfNumbers.insert(it, 4);


        // Iterating over list elements and display them
        it = listOfNumbers.begin();
        while (it != listOfNumbers.end())
        {
            std::cout << (*it) << "  ";
            it++;
        }
        std::cout << std::endl;


        //Erasing elements in between the list using
        // erase(position) member function. Let's iterate to
        // 3rd position
        it = listOfNumbers.begin();
        it++;
        it++;
        // Iterator 'it' is at 3rd position. Now erase this element.
        listOfNumbers.erase(it);


        // Iterating over list elements and display them
        it = listOfNumbers.begin();
        while (it != listOfNumbers.end())
        {
            std::cout << (*it) << "  ";
            it++;
        }
        std::cout << std::endl;

        //Lets remove all elements with value greater than 3. 
        listOfNumbers.remove_if([](int elem) {
            if (elem > 3)
                return true;
            else
                return false;
        });

        it = listOfNumbers.begin();
        while (it != listOfNumbers.end())
        {
            std::cout << (*it) << "  ";
            it++;
        }
        std::cout << std::endl;
    }
}

namespace diferenceBetweenVectorAndList {
    // Both vector and list are sequential containers of C++ Standard Template Library. 
    // But there are many differences between them because of their internal implementation i.e. 
    // List stores elements at non contiguous memory location i.e. it internally uses a doubly linked list i.e.
    // Whereas, vector stores elements at contiguous memory locations like an array i.e.

    /*
    1.) Insertion and Deletion
    Insertion and Deletion in List is very efficient as compared to vector
    Whereas, in vector insertion and deletion at start or middle will make all elements to shift by one. 
    Also, if there is insufficient contiguous memory in vector at the time of insertion, 
    then a new contiguous memory will be allocated and all elements will be copied there.

    2.) Random Access:
    As List is internally implemented as doubly linked list, therefore no random access is possible in List. It means, to access 15th element in list we need to iterate through first 14 elements in list one by one.
    Whereas, vector stores elements at contiguous memory locations like an array. Therefore, in vector random access is possible i.e. we can directly access the 15th element in vector using operator [] i.e.

    3.) Iterator Invalidation
    Deleting or Inserting an element in List does not invalidate any iterator because during insertion and deletion no element is moved from its position only a couple pointers are changed.

    4.) Special Member functions
    As std::list do not provide random access, there many STL algorithms that uses Random Access Iterators can not be used with List. Hence std::list provides some extra functions for Sorting, Splicing, Removing elements and identifying unique elements.
    Vector provides the random access and hence can be used with STL algorithms that uses Random Access Iterators.
    */
}

namespace diferentWaysToInitializeAList {
    /*
    1. Creating an Empty List in C++
    std::list<int> listOfInts;

    2. Creating & Initializing a List with Fill Constructor
    std::list<int> listOfInts(5, 119);
    It will create a list with 5 elements and each is initialized with a copy of element passed as second argument i.e. 119 in our case.

    3. Creating & Initializing a List with c++11¡¯s initializer_list
    In C++11 new overloaded constructor of std::list is introduced that can receive an initializer_list as argument and can initialize list elements with a copy of elements in initializer_list i.e.
    std::list<int> listOfInts({2,8,7,5,3,1,4});

    4. Initializing a std::list with a std::vector or an Array
    std::vector<int> vecOfInt( { 2, 8, 7, 5, 3, 1, 4 });

    // Create a list and initialize it with vector
    std::list<int> listOfInts(vecOfInt.begin(), vecOfInt.end());

    int arr[] = { 2, 8, 7, 5, 3, 1, 4 };

    // Create a list and initialize it with vector
    std::list<int> listOfInts(arr, arr + sizeof(arr) / sizeof(int));
    */
}

namespace eraseElementsFromAList {
    /*
    std::list provides 2 member function to delete elements using iterators i.e.
    iterator erase (const_iterator position);
    It deletes the element representing by passed iterator ¡°position¡± and returns the iterator of element next to last deleted element.
    iterator erase (const_iterator first, const_iterator last);
    It accepts a range of elements as an argument and deletes all the elements in range (firs, last]
    */
    void test()
    {
        // Create a list and initialize it with 7 elements
        std::list<int> listOfInts({ 2, 3, 4, 6, 4, 9, 1, 2, 8, 9, 4, 6, 2, 4, 9 });

        //Display The List
        std::copy(listOfInts.begin(), listOfInts.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        // Iterator itList points to element next to begin
        std::list<int>::iterator itList = ++(listOfInts.begin());

        // Erasing element represented by iterator itList i.e. 3
        itList = listOfInts.erase(itList);

        //Display The List
        std::copy(listOfInts.begin(), listOfInts.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        //Increment iterator
        itList++;

        // Erase a range of elements i.e. 6 to end
        listOfInts.erase(itList, listOfInts.end());

        //Display The List
        std::copy(listOfInts.begin(), listOfInts.end(),
            std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}

namespace removeElementsFromAList {
    // std::list provides two member functions for removing elements based on value i.e. std::list::remove and std::list::remove_if.

    //Using std::list::remove to remove element by value
    // void remove (const value_type& val);
    // It removes all the elements from a list that matches the passed element val. 
    void test()
    {
        // Create a list and initialize it with 7 elements
        std::list<int> listOfInts({ 2, 3, 4, 6, 4, 9, 1, 2, 8, 9, 4, 6, 2 });

        // Remove all elements with value 4
        listOfInts.remove(4);

        // Iterate over the list using range based loop
        for (int val : listOfInts)
            std::cout << val << ",";
        std::cout << std::endl;
    }

    //Using std::list::remove_if to remove elements from a List based on Criterion
    // template <class Predicate>
    // void remove_if(Predicate predCallback);
    void test2()
    {
        // Create a list and initialize it with 7 elements
        std::list<int> listOfInts({ 2, 3, 4, 6, 4, 9, 1, 2, 8, 9, 4, 6, 2 });

        // Remove only first occurrence of element with value 4

        listOfInts.remove_if([](const int & val) {
            if (val >= 2 && val < 5)
                return true;
            else
                return false;
        });

        // Iterate over the list using range based loop
        for (int val : listOfInts)
            std::cout << val << ",";
        std::cout << std::endl;
    }
}

namespace removeElementsFromListWhileIterating {
    void test()
    {
        // Create a list and initialize it with 10 elements
        std::list<int> listOfInts({ 2, 3, 3, 4, 8, 9, 4, 6, 8, 3 });

        // Iterate over the list using Iterators and erase elements
        // which are multiple of 3 while iterating through list
        std::list<int>::iterator it = listOfInts.begin();
        while (it != listOfInts.end()) {
            // Remove elements while iterating
            if ((*it) % 3 == 0) {
                // erase() makes the passed iterator invalid
                // But returns the iterator to the next of deleted element
                it = listOfInts.erase(it);
            }
            else
                it++;
        }

        // Iterate over the list using for_each & Lambda Function and display contents
        std::for_each(listOfInts.begin(), listOfInts.end(), [](const int & val) {
            std::cout << val << ",";
        });
        std::cout << std::endl;
    }
}

namespace getElementByIndex {
    /*
    std::list<std::string> listOfStrs = { "First", "Sec", "Third", "Fourth", "Fifth", "Sixth"};

    Accessing nth element in std::list using std::advance
    
    template <class InputIterator, class Distance>
    void advance (InputIterator& it, Distance n);

    It advances the given iterator by n positions. Now lets access element at 3rd position using std::advance.
    // Create iterator pointing to first element
    std::list<std::string>::iterator it = listOfStrs.begin();

    // Advance the iterator by 2 positions,
    std::advance(it, 2);

    Accessing nth element in std::list using std::next()
    Lets see how to access element at 3rd position by std::next()
    auto it1 = std::next(listOfStrs.begin(), 2);
    */

    void test()
    {
        std::list<std::string> listOfStrs =
        { "First", "Sec", "Third", "Fourth", "Fifth", "Sixth" };

        /**** Finding nth element using std::advance() ******/

        // Find 3rd element from list

        // Create iterator pointing to first element
        std::list<std::string>::iterator it = listOfStrs.begin();

        // Advance the iterator by 2 positions,
        std::advance(it, 2);

        // Now iterator it points to 3rd element
        std::cout << "3rd element = " << *it << std::endl;

        /**** Finding nth element using std::next() ******/

        // Find 3rd element from list

        // It returns a new iterator pointing to n position after the
        // base iterator given as first argument
        auto it1 = std::next(listOfStrs.begin(), 2);

        std::cout << "3rd element = " << *it1 << std::endl;
    }
}

namespace searchAnElement {
    // Searching an element in std::list using std::find()
    void test()
    {
        std::list<std::string> listOfStrs = {
            "is", "of",
            "the", "Hi",
            "Hello", "from" };

        // Check if an element exists in list

        // Create a list Iterator
        std::list<std::string>::iterator it;

        // Fetch the iterator of element with value 'the'
        it = std::find(listOfStrs.begin(), listOfStrs.end(), "the");

        // Check if iterator points to end or not
        if (it != listOfStrs.end())
        {
            // It does not point to end, it means element exists in list
            std::cout << "'the' exists in list " << std::endl;
        }
        else
        {
            // It points to end, it means element does not exists in list
            std::cout << "'the' does not exists in list" << std::endl;
        }
    }
    // Generic contains() method for std::list
    /*
    * Generic function to find if an element of any type exists in list
    */
    template <typename T>
    bool contains(std::list<T> & listOfElements, const T & element)
    {
        // Find the iterator if element in list
        auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
        //return if iterator points to end or not. It points to end then it means element
        // does not exists in list
        return it != listOfElements.end();
    }
    void test2()
    {
        std::list<std::string> listOfStrs =
        { "is", "of", "the", "Hi", "Hello", "from" };

        // Check if an element exists in list
        bool result = contains(listOfStrs, std::string("is"));
    }
}

int main()
{
    tutorialExampleAndUsageDetails::test();

    eraseElementsFromAList::test();
    return 0;
}