#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

namespace exampleAndTutorial {
    /*
    std::set is an associative container

    Benefits and Features of std::set:
    1. It doesn't allow duplicate elements i.e. it only contains unique elements.
    2. Std::set can contain element of any specified type in template argument i.e.
    3. std::set internally store elements in balanced binary tree.
    4. By default std::set uses the operator < for comparing two elements 
       and but if user passes the external sorting criteria i.e. 
       comparator then it uses that instead of default operator <.
    5. std::set will keep the inserted elements in sorted order 
       based on the assigned sorting criteria i.e. 
       either by default criteria operator < or by passed comparator (if passed).
    */
    void test()
    {
        std::set<int> setOfNumbers;

        // Lets insert four elements
        setOfNumbers.insert(4);
        setOfNumbers.insert(3);
        setOfNumbers.insert(5);
        setOfNumbers.insert(1);

        // Only 3 elements will be inserted
        std::cout << "Set Size = " << setOfNumbers.size() << std::endl;

        // Iterate through all the elements in a set and display the value.
        for (std::set<int>::iterator it = setOfNumbers.begin(); it != setOfNumbers.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << "\n";
        return;
    }

    // How to search an element in std::set:
    // Using find member function,

    // iterator find(const value_type& val) const;
    // It Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end.
    void test2()
    {
        std::set<std::string> setOfNumbers;

        // Lets insert four elements
        setOfNumbers.insert("first");
        setOfNumbers.insert("second");
        setOfNumbers.insert("third");
        setOfNumbers.insert("first");

        // Search for element in set using find member function
        std::set<std::string>::iterator it = setOfNumbers.find("second");
        if (it != setOfNumbers.end())
            std::cout << "'first'  found" << std::endl;
        else
            std::cout << "'first' not found" << std::endl;

        // Search for element in set using find member function
        it = setOfNumbers.find("fourth");
        if (it != setOfNumbers.end())
            std::cout << "'fourth'  found" << std::endl;
        else
            std::cout << "'fourth' not found" << std::endl;

        return;
    }

    // Why should we use std::set::find member method instead of std::find standard generic algorithm?
    
    // Because find member function knows its internal data structure is balance binary search tree 
    // and hence designed to operate on that only therefore it will take much lesser time then standard algorithm std::find.

    // How std::set verifies while insertion if element is already added or not:
    
    // By default std::set uses the operator < .
    // It internally maintains a binary balanced tree and 
    // during insertion it compares the new element with already present nodes and 
    // finds the right position of new element in tree. 
    // If that element is already present then it doesn¡¯t insert the new element.
    // It uses the following logic to check if two elements like a and b are equal or not,
    // If a<b is false and b<a is false. Then it means a and b are equal.

    // How to remove an element in std::set :
    /*
        Using member function erase i.e.
        iterator  erase (const_iterator position);
        size_type erase (const value_type& val);
        iterator  erase (const_iterator first, const_iterator last);
    */
    void test3()
    {
        std::set<std::string> setOfNumbers;

        // Lets insert four elements
        setOfNumbers.insert("first");
        setOfNumbers.insert("second");
        setOfNumbers.insert("third");
        setOfNumbers.insert("first");

        // Iterate through all the elements in a set and display the value.
        for (std::set<std::string>::iterator it = setOfNumbers.begin(); it != setOfNumbers.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << std::endl;

        setOfNumbers.erase("third");

        // Iterate through all the elements in a set and display the value.
        for (std::set<std::string>::iterator it = setOfNumbers.begin(); it != setOfNumbers.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << std::endl;
        return;
    }
}

namespace exampleAndTutorialWithUserDefinedClasses {
    // If you want to use std::set with user defined classes and use default sorting criteria then overload operator < in the class.
    class Message
    {
    public:
        std::string m_MsgContent;
        std::string m_sentBy;
        std::string m_recivedBy;

        Message(std::string sentBy, std::string recBy, std::string msg) :
            m_MsgContent(msg), m_sentBy(sentBy), m_recivedBy(recBy)
        {}

        bool operator< (const Message & msgObj) const
        {
            std::string rightStr = msgObj.m_MsgContent + msgObj.m_sentBy + msgObj.m_recivedBy;
            std::string leftStr = this->m_MsgContent + this->m_sentBy + this->m_recivedBy;
            return (leftStr < rightStr);
        }
        friend std::ostream& operator<<(std::ostream& os, const Message& obj);

    };
    std::ostream& operator<<(std::ostream& os, const Message& obj)
    {
        os << obj.m_sentBy << " :: " << obj.m_MsgContent << " :: " << obj.m_recivedBy << std::endl;
        return os;
    }
    
    void test()
    {
        std::set<Message> setOfMsgs;

        Message msg1("user_1", "Hello", "user_2");
        Message msg2("user_1", "Hello", "user_3");
        Message msg3("user_3", "Hello", "user_1");
        // A Duplicate Message
        Message msg4("user_1", "Hello", "user_3");

        setOfMsgs.insert(msg1);
        setOfMsgs.insert(msg2);
        setOfMsgs.insert(msg3);
        setOfMsgs.insert(msg4);

        // msg4 will not get inserted because its duplicate as per the current operator < implementation.

        // Iterate through all the elements in a set and display the value.
        for (std::set<Message>::iterator it = setOfMsgs.begin(); it != setOfMsgs.end(); ++it)
            std::cout << *it;

        return;
    }

    // But What if we enhance our requirement i.e.
    // Now we want to keep only single message sent by each user i.e.only one sent message is allowed per user.Then what ? ?
    /*
        Option 1 :
        Modify operator <, but then it can hamper our previous requirements and it might be possible that we don¡¯t have write access to operator <.

        Option 2:
        Create a new set and use an external soring criteria i.e Comparator. We will discuss this in next article.
    */
}

namespace exampleAndTutorialWithExternalSortingCriteriaOrComparator {
    // Requirement:
    // we want to keep only single message sent by each user i.e.only one sent message is allowed per user and we can¡¯t modify operator <.

    // Use external sorting criteria i.e. comparator
    class Message
    {
    public:
        std::string m_MsgContent;
        std::string m_sentBy;
        std::string m_recivedBy;

        Message(std::string sentBy, std::string recBy, std::string msg) :
            m_MsgContent(msg), m_sentBy(sentBy), m_recivedBy(recBy)
        {}
        friend std::ostream& operator<<(std::ostream& os, const Message& obj);

    };
    std::ostream& operator<<(std::ostream& os, const Message& obj)
    {
        os << obj.m_sentBy << " :: " << obj.m_MsgContent << " :: " << obj.m_recivedBy << std::endl;
        return os;
    }
    // Now create a Message comparator,
    class MessageUserComparator
    {
        std::string m_userName;
    public:
        MessageUserComparator(std::string userName) :
            m_userName(userName)
        {}
        bool operator() (const Message& msg1, const Message& msg2) const
        {
            if (msg1.m_sentBy < msg2.m_sentBy)
                return true;
            else
                return false;
        }
    };
    void test()
    {
        Message msg1("user_1", "Hello", "user_2");
        Message msg2("user_1", "Hello", "user_3");
        Message msg3("user_3", "Hello", "user_1");
        Message msg4("user_1", "Hello", "user_3");

        // std::set that contains the messages sent by user - "user_1"
        std::cout << "set that contains the messages sent by user - user_1" << std::endl;
        std::set<Message, MessageUserComparator> setOfMsgs_1(MessageUserComparator("user_1"));

        setOfMsgs_1.insert(msg1);
        setOfMsgs_1.insert(msg2);
        setOfMsgs_1.insert(msg3);
        setOfMsgs_1.insert(msg4);
        // msg1, msg2 and msg4 are duplicates according to MessageUserComparator implementation
        // hence only 2 element are actually inserted in std::set
        // Iterate through all the elements in a set and display the value.
        for (std::set<Message>::iterator it = setOfMsgs_1.begin(); it != setOfMsgs_1.end(); ++it)
            std::cout << *it;

        return;
    }
}

namespace accessElementByIndex {
    // std::set is an associative container, which internally store elements in a balanced binary search tree and it doesn¡¯t provide random access operator [].
    // Therefore accessing a random element from set by index is little tricky.

    // Accessing nth element in Set
    /*
        Suppose we have a set of strings i.e.
        std::set<std::string> setOfStr =
        { "bb", "ee", "dd", "aa", "ll" };
        Now, to access an element at nth index we need to create an iterator pointing to starting position and keep on  increment the iterator till nth element is reached i.e.
        std::set<std::string>::iterator setIt = setOfStr.begin();
        for(int i = 0; i < 3; i++)
        setIt++;

        std::cout<<"3rd Element in set = "<<*setIt<<std::endl;
    */

    // Accessing nth element using std::advance
    /*
        // Iterator to the beginning of set
        std::set<std::string>::iterator iter = setOfStr.begin();

        // It will move forward the passed iterator by passed value
        std::advance(iter, 3);

        std::cout << "3rd Element in set = " << *iter << std::endl;
    */

    // Accessing nth element using std::next
    /*
        // std::next internally iterate through n elements to reach
        // nth element and returns the iterator of 3rd element in the set
        std::set<std::string>::iterator it = std::next(setOfStr.begin(), 3);

        std::cout<<"3rd Element in set = "<<*it<<std::endl;
    */

    // Creating generic method to access nth element from any set

    /*
    * Access nth element from a set.
    * It returns a pair of Element and bool.
    * bool represents if nth element exists in set or not.
    * if bool is true them First element of pair T contains the element value
    */
    template <typename T>
    std::pair<T, bool> getNthElement(std::set<T> & searchSet, int n)
    {
        std::pair<T, bool> result;
        if (searchSet.size() > n)
        {
            result.first = *(std::next(searchSet.begin(), n));
            result.second = true;
        }
        else
            result.second = false;

        return result;
    }

    void test()
    {
        std::set<std::string> setOfStr =
        { "bb", "ee", "dd", "aa", "ll" };

        std::cout << "***** Set Contents *****" << std::endl;
        for (std::string elem : setOfStr)
            std::cout << elem << std::endl;

        std::cout << "***** Accessing Elements by Index ***" << std::endl;

        // Access 3rd element
        std::pair<std::string, bool> result = getNthElement(setOfStr, 3);

        if (result.second)
            std::cout << "3rd Element in set = " << result.first << std::endl;
        else
            std::cout << "3rd Element in set not found" << std::endl;


        // Access 7th element
        result = getNthElement(setOfStr, 7);

        if (result.second)
            std::cout << "7th Element in set = " << result.first << std::endl;
        else
            std::cout << "7th Element in set not found" << std::endl;
    }
}

namespace differentWaysToInsertElements {
    // Inserting a Single element in Set and checking the result

    /*
        pair<iterator,bool> insert (const value_type& val);
        If insertion is successful then value of bool flag in returned pair will be true and iterator in it will
        point to the newly inserted element.
    */
    void insertInSet(std::set<std::string> & setOfStrs, std::string str)
    {
        // A pair of set iterator and bool
        std::pair<std::set<std::string>::iterator, bool> result;

        // Insert Returns a pair of iterator and bool
        result = setOfStrs.insert(str);

        // Check if element added successfuly
        if (result.second)
            std::cout << str << " - Inserted successfuly" << std::endl;
        else
            std::cout << str << " - Not Inserted successfuly" << std::endl;
    }

    void test()
    {
        std::set<std::string> setOfStrs;


        insertInSet(setOfStrs, "Hi");
        // Try to insert the duplicate element.
        insertInSet(setOfStrs, "Hi");

        insertInSet(setOfStrs, "the");
        insertInSet(setOfStrs, "is");
        insertInSet(setOfStrs, "Hello");

        std::cout << "**Map Contents***" << std::endl;

        for (auto elem : setOfStrs)
            std::cout << elem << std::endl;

        return;
    }

    // Inserting an Iterator Range into a Set

    /*
        template <class InputIterator> 
        void insert (InputIterator first, InputIterator last);

        It accepts a range of input iterators and one by one all the elements in set while traversing through the range( first to last-1).
    */
    void test2()
    {
        std::vector<std::string> vecOfStrs = { "Hi", "Hello", "is", "the", "at", "Hi", "is" };

        std::set<std::string> setOfStrs;

        // Insert a Range in set
        // Range here is start and end iterators of a vector
        setOfStrs.insert(vecOfStrs.begin(), vecOfStrs.end());

        // It will insert all the elements in vector to set, but as
        // set contains only unique elements, so duplicate elements will
        // be automatically rejected.

        // But there is no way to find out how many actually inserted
        // because it doesn't return any value.

        std::cout << "**Map Contents***" << std::endl;

        for (auto elem : setOfStrs)
            std::cout << elem << std::endl;

        return;
    }

    // Inserting a Initializer List in Set

    /*
        void insert (initializer_list<value_type> il);

        It accepts a initializer list and insert all elements in it to the set.
    */
    void test3()
    {
        std::set<std::string> setOfStrs;

        // Insert a Initializer list in the set
        setOfStrs.insert({ "Hi", "Hello", "is", "the", "at", "Hi", "is" });

        // It will insert all the elements in initializer_list to set, but as
        // set contains only unique elements, so duplicate elements will
        // be automatically rejected.

        // But there is no way to find out how many actually inserted
        // because it doesn't return any value.

        std::cout << "**Map Contents***" << std::endl;

        for (auto elem : setOfStrs)
            std::cout << elem << std::endl;
        return;
    }
}

namespace defferentWaysToIterateOverASet {
    // Iterating over a Set using Iterators
    /*
        // Creating a iterator pointing to start of set
        std::set<std::string>::iterator it = setOfStr.begin();

        // Iterate till the end of set
        while (it != setOfStr.end())
        {
            // Print the element
            std::cout << (*it) << " , ";
            //Increment the iterator
            it++;
        }
    */

    // Iterating a set in backward direction using reverse_iterator
    /*
        // Creating a reverse iterator pointing to end of set i.e. rbegin
        std::set<std::string>::reverse_iterator revIt = setOfStr.rbegin();

        // Iterate till the start of set i.e. rend
        while (revIt != setOfStr.rend())
        {
            // Print the element
            std::cout << (*revIt) << " , ";
            //Increment the iterator
            revIt++;
        }
    */

    // Iterating over a set using Range base for loop
    /*
        // Iterate over all elements of set
        // using range based for loop
        for (auto elem : setOfStr)
        {
            std::cout << elem << " , ";
        }
    */

    // Iterating over a set using std::for_each and range based for loop
    /*
        // Iterate over all elements using for_each
        // and lambda function
        std::for_each(setOfStr.begin(), setOfStr.end(), [](const std::string & str)
                                                {
                                                    std::cout<<str<<" , ";
                                                });
    */

    void test()
    {
        // Set of strings
        std::set<std::string> setOfStr =
        { "jjj", "khj", "bca", "aaa", "ddd" };

        std::cout << "*** Iterating Set in Forward Direction using Iterators ***"
            << std::endl;

        // Creating a iterator pointing to start of set
        std::set<std::string>::iterator it = setOfStr.begin();

        // Iterate till the end of set
        while (it != setOfStr.end())
        {
            // Print the element
            std::cout << (*it) << " , ";
            //Increment the iterator
            it++;
        }
        std::cout << std::endl;

        std::cout << "*** Iterating Set in Reverse Direction using Iterators ***"
            << std::endl;

        // Creating a reverse iterator pointing to end of set i.e. rbegin
        std::set<std::string>::reverse_iterator revIt = setOfStr.rbegin();

        // Iterate till the start of set i.e. rend
        while (revIt != setOfStr.rend())
        {
            // Print the element
            std::cout << (*revIt) << " , ";
            //Increment the iterator
            revIt++;
        }
        std::cout << std::endl;

        std::cout << "*** Iterating Set using range based for loop ***"
            << std::endl;

        // Iterate over all elements of set
        // using range based for loop
        for (auto elem : setOfStr)
        {
            std::cout << elem << " , ";
        }
        std::cout << std::endl;

        std::cout << "*** Iterating Set using for_each algo & Lambda function ***"
            << std::endl;

        // Iterate over all elements using for_each
        // and lambda function
        std::for_each(setOfStr.begin(), setOfStr.end(), [](const std::string & str)
        {
            std::cout << str << " , ";
        });
        std::cout << std::endl;
    }
}

namespace differnetWaysToEraseDeleteAnElement {
    // Removing element from set By Iterator
    // Removing element from set By Value
    // Removing element from set By Iterator Range
    void test()
    {
        //Set Of Strings
        std::set<std::string> setOfStrs = { "Hi", "Hello", "is", "the", "at", "Hi", "is", "from", "that" };

        // Printing Contents of Set
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        // Search for element "is"
        std::set<std::string>::iterator it = setOfStrs.find("is");

        // Check if Iterator is valid
        if (it != setOfStrs.end())
        {
            // Deletes the element pointing by iterator it
            setOfStrs.erase(it);
        }

        // Printing Contents of Set
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        // Iterator pointing to "Hi" in Set
        std::set<std::string>::iterator start = setOfStrs.find("Hi");
        // Iterator pointing to "from" in Set
        std::set<std::string>::iterator last = setOfStrs.find("from");

        // Check if both start and last iterators are valid
        if (start != setOfStrs.end() && last != setOfStrs.end())
        {
            // Erase all elements from "Hi" to "from"
            setOfStrs.erase(start, last);
        }

        // Printing Contents of Set
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        // Erase element "that" from set
        setOfStrs.erase("that");

        // Printing Contents of Set
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        return;
    }
}

namespace eraseElementsWhileIteratingAndGenericErase {
    // Erasing elements from std::set while Iterating
    void test1()
    {
        // Set of Strings
        std::set<std::string> setOfStrs = { "Hi", "Hello", "is", "the", "at", "Hi", "is", "from", "that" };

        // Printing Set on console
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        // Create an iterator pointing to start of set
        std::set<std::string>::iterator it = setOfStrs.begin();

        // Iterate over the set till end
        while (it != setOfStrs.end())
        {
            if (it->size() > 3)
            {
                // Remove string from set if length is greater than 3.
                it = setOfStrs.erase(it);
            }
            else
                it++;
        }
        // Printing Set on console
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        return;
    }
    /*
    * Creating a generic function that will erase elements from container
    * while iterating if any given condition matches.
    *
    * It accepts following arguments
    *
    * 1.) Container i.e. set, list or vector
    * 2.) Iterator pointing to start of range
    * 3.) Iterator pointing to end of range
    * 4.) Callback to check if it needs to delete the current element
    *
    * It Iterates over the range and check if element needs to be deleted using passed checker callback.
    * If Yes then it deletes the element
    */
    template <typename S, typename T>
    void erase_if(S & container, T first, T last, std::function<bool(T)> checker)
    {
        while (first != last)
        {
            if (checker(first))
            {
                first = container.erase(first);
            }
            else
                first++;
        }

    }
    // Creating generic erase_if for std::set
    void test2()
    {
        typedef std::set<std::string>::iterator SetIter;

        // Set Of String
        std::set<std::string> setOfStrs = { "Hi", "Hello", "is", "the", "at", "Hi", "is", "from", "that" };

        // Printing Set Contents
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        // Callback to check if size of string is greater than 2.
        std::function<bool(SetIter)> lambda = [](SetIter it) -> bool {
            return it->size() > 2;
        };
        // Remove all strings from set whose length is greater than 3.
        erase_if<>(setOfStrs, setOfStrs.begin(), setOfStrs.end(), lambda);


        // Printing Set Contents
        std::copy(setOfStrs.begin(), setOfStrs.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;

        return;
    }
}

int main()
{
    //exampleAndTutorial::test();
    //exampleAndTutorial::test2();
    //exampleAndTutorial::test3();

    //exampleAndTutorialWithUserDefinedClasses::test();
    exampleAndTutorialWithExternalSortingCriteriaOrComparator::test();
    return 0;
}