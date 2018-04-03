#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>

namespace usageDetailWithExamples {
    // std::map Introduction
    // std::map is an associative container that store elements in key-value pair.

    // Benefits of using std::map :
    /*
        It stores only unique keys and that too in sorted order based on its assigned sorting criteria.
        As keys are in sorted order therefore searching element in map through key is very fast i.e. it takes logarithmic time.
        In std::map there will be only one value attached with the every key.
        std::map can be used as associative arrays.
        It might be implemented using balanced binary trees.
    */

    void test()
    {
        std::map<std::string, int> mapOfWords;
        // Inserting data in std::map
        mapOfWords.insert(std::make_pair("earth", 1));
        mapOfWords.insert(std::make_pair("moon", 2));
        mapOfWords["sun"] = 3;
        // Will replace the value of already added key i.e. earth
        mapOfWords["earth"] = 4;
        // Iterate through all elements in std::map
        std::map<std::string, int>::iterator it = mapOfWords.begin();
        while (it != mapOfWords.end())
        {
            std::cout << it->first << " :: " << it->second << std::endl;
            it++;
        }
        // Check if insertion is successful or not
        if (mapOfWords.insert(std::make_pair("earth", 1)).second == false)
        {
            std::cout << "Element with key 'earth' not inserted because already existed" << std::endl;
        }
        // Searching element in std::map by key.
        if (mapOfWords.find("sun") != mapOfWords.end())
            std::cout << "word 'sun' found" << std::endl;
        if (mapOfWords.find("mars") == mapOfWords.end())
            std::cout << "word 'mars' not found" << std::endl;
        return;
    }
    
    // Creating std::map objects
    // std::map<std::string, int> mapOfWords;

    // Inserting data in std::map :
    /*
        mapOfWords.insert(std::make_pair("earth", 1));
        mapOfWords.insert(std::make_pair("moon", 2));
        mapOfWords["sun"] = 3;
    */

    // Different between operator [] and insert function:
    /*
        If specified key already existed in map then operator [] will 
        silently change its value where as insert will not replace 
        already added key instead it returns the information i.e. 
        if element is added or not. e.g.

        mapOfWords["earth"] = 4; // Will replace the value of already added key.

        Where as for insert member function,
        mapOfWords.insert(std::make_pair("earth", 1)).second
        will return false.
    */

    // Iterating through all std::map elements:
    /*
        std::map<std::string, int>::iterator it = mapOfWords.begin();
        while(it != mapOfWords.end())
        {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
        }
    */

    // Searching element in std::map by key
    /*
        iterator find (const key_type& k);

        //e.g.

        if(mapOfWords.find("sun") != mapOfWords.end())
        std::cout<<"word 'sun' found"<<std::endl;
        if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl;
    */

    // Searching element in std::map by Value
    // To search element in std::map by value we need to iterate through all of the elements and check for the passed value and return i.e.
    std::map<std::string, int>::iterator serachByValue(std::map<std::string, int> & mapOfWords, int val)
    {
        // Iterate through all elements in std::map and search for the passed element
        std::map<std::string, int>::iterator it = mapOfWords.begin();
        while (it != mapOfWords.end())
        {
            if (it->second == val)
                return it;
            it++;
        }
    }
    void test2()
    {
        std::map<std::string, int> mapOfWords;
        // Inserting data in std::map
        mapOfWords.insert(std::make_pair("earth", 1));
        mapOfWords.insert(std::make_pair("moon", 2));
        mapOfWords["sun"] = 3;

        std::map<std::string, int>::iterator it = serachByValue(mapOfWords, 3);
        if (it != mapOfWords.end())
            std::cout << it->first << " :: " << it->second << std::endl;

        return;
    }
}

namespace mapAndExternalSortingCriteriaOrComparator {
    // Default sorting criteria for keys in std::map is operator ¡°<¡± i.e. std::less<T>. 
    // So, while creating std::map if we don¡¯t specify the external sorting criteria then default criteria will be used.
    struct WordGreaterComparator
    {
        bool operator()(const std::string & left, const std::string & right) const
        {
            return (left > right);
        }
    };

    void test()
    {
        std::cout << "Default sorting criteria for keys i.e. operator < for std::string" << std::endl;
        // Default sorting criteria for keys i.e. operator < for std::string
        std::map<std::string, int > mapOfWords;

        mapOfWords.insert(std::make_pair("earth", 1));
        mapOfWords.insert(std::make_pair("moon", 2));
        mapOfWords.insert(std::make_pair("sun", 3));

        std::map<std::string, int>::iterator it = mapOfWords.begin();
        for (; it != mapOfWords.end(); it++)
            std::cout << it->first << " :: " << it->second << std::endl;

        std::cout << "External sorting criteria for keys " << std::endl;
        std::map<std::string, int, WordGreaterComparator > mapOfWords_2;

        mapOfWords_2.insert(std::make_pair("earth", 1));
        mapOfWords_2.insert(std::make_pair("moon", 2));
        mapOfWords_2.insert(std::make_pair("sun", 3));
        for (std::map<std::string, int>::iterator it = mapOfWords_2.begin(); it != mapOfWords_2.end(); it++)
            std::cout << it->first << " :: " << it->second << std::endl;

        // Compile Error as 2 std::map objects have different sorting criteria0
        //if(mapOfWords == mapOfWords_2)
        //    std::cout<<"Maps are same"<<std::endl;

        return;
    }
}

namespace usingUserDefinedClassObjectsAsKeys {
    /*
    to use user defined class objects as keys in std::map we should have either,

    Default sorting criteria i.e. operator < defined for our Class.
    std::map should be assigned with an external sorting criteria i.e. comparator that can compare two objects of your user defined class.
    */

    // Overloading operator < for sorting of keys
    // Suppose our class is User that has id and name properties. To use this class as key in std::map we will overload operator <.
    class User
    {
        std::string m_id;
        std::string m_name;
    public:
        User(std::string name, std::string id)
            :m_id(id), m_name(name)
        {}
        const std::string& getId() const {
            return m_id;
        }
        const std::string& getName() const {
            return m_name;
        }
        bool operator< (const User& userObj) const
        {
            if (userObj.m_id < this->m_id)
                return true;
        }
    };

    void test1()
    {
        std::map<User, int> m_UserInfoMap;

        m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "3"), 100));
        m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "1"), 120));
        m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.Z", "2"), 300));

        std::map<User, int>::iterator it = m_UserInfoMap.begin();
        for (; it != m_UserInfoMap.end(); it++)
        {
            std::cout << it->first.getName() << " :: " << it->second << std::endl;
        }
    }

    // Using Comparator for sorting of keys:
    struct UserNameComparator
    {
        bool operator()(const User & left, const User & right) const
        {
            return (left.getName() > right.getName());
        }
    };

    void test2()
    {
        std::map<User, int, UserNameComparator> m_UserInfoMap;

        m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "3"), 100));
        m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.X", "1"), 120));
        m_UserInfoMap.insert(std::make_pair<User, int>(User("Mr.Z", "2"), 300));

        std::map<User, int, UserNameComparator>::iterator it =
            m_UserInfoMap.begin();
        for (; it != m_UserInfoMap.end(); it++)
        {
            std::cout << it->first.getName() << " :: " << it->second << std::endl;
        }
    }
}

namespace setVsMapHowToChooseRightAssociativeContainer {
    /*
        Set :
            Set is an associative container which we need to store unique elements.
            It always keeps the elements in sorted order.
            Internally it maintains a balanced binary search tree of elements. Therefore when we search an element inside the set then it takes only log(n) complexity to search it.
        
        Important Point about set ¨C Once added then cannot change i.e.
    */
    void test1()
    {
        std::set<std::string> setOfDepartments;

        setOfDepartments.insert("First");
        setOfDepartments.insert("Second");
        setOfDepartments.insert("Third");
        std::for_each(setOfDepartments.begin(), setOfDepartments.end(), [](std::string elem) {
            std::cout << (elem) << " , ";
        });

        // Now Try to change the element

        std::set<std::string>::iterator it = setOfDepartments.find("Second");
        if (it != setOfDepartments.end())
        {
            std::cout << std::endl << *it;
            //*it = "Fourth"; // NOT ALLOWED
        }
    }

    /*
        Map:
            Map is a associative container that is used to store key-value pair of elements with unique keys.
            It always keeps the inserted pairs in sorted order based on the key.
            Internally it maintains a balanced binary search tree to store keys. Therefore when searching key inside the map takes only log(n) complexity.
            We cannot modify the key of any inserted pair in map.
            We can modify the value associated with a key in any inserted pair in map.
    */
    void test2()
    {
        // Map of Department and Employee count in that Department
        std::map<std::string, int > mapOfDepEmpCount;

        mapOfDepEmpCount.insert(std::make_pair("First", 0));
        mapOfDepEmpCount.insert(std::make_pair("Second", 0));
        mapOfDepEmpCount.insert(std::make_pair("Third", 0));

        std::map<std::string, int >::iterator it = mapOfDepEmpCount.find("Second");
        if (it != mapOfDepEmpCount.end())
        {
            std::cout << std::endl << "Department = " << it->first << " :: No. Of Employees = " << it->second << std::endl;
            // You can change the value associated with the key
            it->second = 10;
            //it->first = "sss"; // You cannot chage the key
        }

        it = mapOfDepEmpCount.find("Second");
        if (it != mapOfDepEmpCount.end())
        {
            std::cout << std::endl << "Department = " << it->first << " :: No. Of Employees = " << it->second << std::endl;

        }
    }

    // When to choose SET and when MAP?
}

namespace insertExample {
    /*
        Map internally store elements in a pair of key value i.e.
        std::pair<key Type, Value Type>

        pair<iterator,bool> insert (const value_type& element);

        bool represents the result of insertion and iterator represents the position of newly added element in map.

        If insertion in map is successful then,
        bool ¡ª> true
        Iterator ¡ª-> Points to Position of newly added element.

        If insertion in map failed then,
        bool ¡ª> false
        Iterator ¡ª-> Pointing to the passed pair
    */

    void testResult(
        std::pair<std::map<std::string, int>::iterator, bool> & result) {
        // Check if Insertion was successful
        if (result.second == false) {
            // Insertion Failed
            std::cout << "Failed to add . duplicate key :: " << result.first->first
                << std::endl;
        }
        else {
            // Insertion was successful
            std::cout << "Successful in Adding , key :: " << result.first->first
                << std::endl;
        }
    }

    void test() {
        // Map of string and int
        std::map<std::string, int> mapOfWordCount;

        // Pair of Map Iterator and bool
        std::pair<std::map<std::string, int>::iterator, bool> result;

        // Insert Element in map
        result = mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
        // Test its result
        testResult(result);

        // Insert Element in map
        result = mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
        // Test its result
        testResult(result);

        // Insert Element in map
        result = mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
        // Test its result
        testResult(result);

        // Try to add duplicate element
        result = mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
        // Test its result
        testResult(result);

        // Create a map iterator and point to beginning of map
        std::map<std::string, int>::iterator it = mapOfWordCount.begin();

        std::cout << "*****************************" << std::endl;
        // Iterate over a map using std::for_each and Lambda function
        std::for_each(mapOfWordCount.begin(), mapOfWordCount.end(),
            [](std::pair<std::string, int> element) {
            // Accessing KEY from element
            std::string word = element.first;
            // Accessing VALUE from element.
            int count = element.second;
            std::cout << word << " :: " << count << std::endl;
        });

        return;
    }
}

namespace iterateOverAMap {
    // Iterate over a map using STL Iterator
    /*
        First of all, create an iterator of std::map and initialize it to the beginning of map i.e.
        std::map<std::string, int>::iterator it = mapOfWordCount.begin();
        Access key from iterator using, it->first
        Access value from iterator using, it->second
    */
    void test()
    {
        std::map<std::string, int> mapOfWordCount;
        // Insert Element in map
        mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
        mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 5));

        // Create a map iterator and point to beginning of map
        std::map<std::string, int>::iterator it = mapOfWordCount.begin();

        // Iterate over the map using Iterator till end.
        while (it != mapOfWordCount.end())
        {
            // Accessing KEY from element pointed by it.
            std::string word = it->first;

            // Accessing VALUE from element pointed by it.
            int count = it->second;

            std::cout << word << " :: " << count << std::endl;

            // Increment the Iterator to point to next entry
            it++;
        }
        return;
    }

    // Iterating over the map using C++11 range based for loop
    void test2()
    {
        std::map<std::string, int> mapOfWordCount;
        // Insert Element in map
        mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
        mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 5));

        // Create a map iterator and point to beginning of map
        std::map<std::string, int>::iterator it = mapOfWordCount.begin();

        // Iterate over the map using c++11 range based for loop
        for (std::pair<std::string, int> element : mapOfWordCount) {
            // Accessing KEY from element
            std::string word = element.first;
            // Accessing VALUE from element.
            int count = element.second;
            std::cout << word << " :: " << count << std::endl;
        }
    }

    // Iterating over the map using std::for_each and lambda function
    void test3()
    {
        std::map<std::string, int> mapOfWordCount;
        // Insert Element in map
        mapOfWordCount.insert(std::pair<std::string, int>("first", 1));
        mapOfWordCount.insert(std::pair<std::string, int>("second", 2));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 3));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 4));
        mapOfWordCount.insert(std::pair<std::string, int>("third", 5));

        // Create a map iterator and point to beginning of map
        std::map<std::string, int>::iterator it = mapOfWordCount.begin();

        // Iterate over a map using std::for_each and Lambda function
        std::for_each(mapOfWordCount.begin(), mapOfWordCount.end(),
            [](std::pair<std::string, int> element) {
            // Accessing KEY from element
            std::string word = element.first;
            // Accessing VALUE from element.
            int count = element.second;
            std::cout << word << " :: " << count << std::endl;
        });

        return;
    }
}

namespace iterateAMapInReverseOrder {
    void test()
    {
        // Creating & Initializing a map of String & Ints
        std::map<std::string, int> mapOfWordCount = {
            { "aaa", 10 },
            { "ddd", 11 },
            { "bbb", 12 },
            { "ccc", 13 }
        };

        // Create a map iterator and point to the end of map
        std::map<std::string, int>::reverse_iterator it = mapOfWordCount.rbegin();

        // Iterate over the map using Iterator till beginning.
        while (it != mapOfWordCount.rend()) {
            // Accessing KEY from element pointed by it.
            std::string word = it->first;

            // Accessing VALUE from element pointed by it.
            int count = it->second;

            std::cout << word << " :: " << count << std::endl;

            // Increment the Iterator to point to next entry
            it++;
        }

        return;
    }
}

namespace checkIfAGivenKeyExists {
    /*
        Map internally store elements in Key-Value pair. It provides 2 member functions to check if a given key exists in map i.e.
            std::map::find
            std::map::count

        Check if map contains a key using std::map::count
        size_type count (const key_type& K) const;
        It finds & returns the count of number of elements in map with key K. 
        As map contains elements with unique key only. So, it will return 1 if key exists else 0.
    */
    void test1()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = {
            { "is", 6 },
            { "the", 5 },
            { "hat", 9 },
            { "at", 6 }
        };


        // Check if key 'hat' exists in the map
        if (wordMap.count("hat") > 0)
        {
            std::cout << "'hat' Found" << std::endl;
        }
        else
        {
            std::cout << "'hat' Not Found" << std::endl;
        }

        // Check if key 'hello' exists in the map
        if (wordMap.count("hello") > 0)
        {
            std::cout << "'hello' Found" << std::endl;
        }
        else
        {
            std::cout << "'hello' Not Found" << std::endl;
        }

        return;
    }

    // Check if map contains a key using std::map::find
    // iterator find (const key_type& k);
    void test2()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = {
            { "is", 6 },{ "the", 5 },
            { "hat", 9 },{ "at", 6 }
        };

        // Create an iterator of map
        std::map<std::string, int>::iterator it;

        // Find the element with key 'hat'
        it = wordMap.find("hat");

        // Check if element exists in map or not
        if (it != wordMap.end()) {
            // Element with key 'hat' found
            std::cout << "'hat' Found" << std::endl;

            // Access the Key from iterator
            std::string key = it->first;
            // Access the Value from iterator
            int value = it->second;

            std::cout << "key = " << key << " :: Value = " << value << std::endl;
        }
        else {
            // Element with key 'hat' Not Found
            std::cout << "'hat' Not Found" << std::endl;
        }

        // Find the element with key 'hello'
        it = wordMap.find("hello");

        // Check if element exists in map or not
        if (it != wordMap.end()) {
            // Element with key 'hello' found
            std::cout << "'hello' Found" << std::endl;

            // Access the Key from iterator
            std::string key = it->first;
            // Access the Value from iterator
            int value = it->second;

            std::cout << "key = " << key << " :: Value = " << key << std::endl;

        }
        else {
            // Element with key 'hello' Not Found
            std::cout << "'hello' Not Found" << std::endl;
        }

        return;
    }
}

namespace searchByValue {
    /*
        Map internally store elements in Key-Value pair. In which keys are unique but values can be duplicate. 
        There are member functions to search pairs by key i.e. 
        std::map::find(). But there is no direct function to search for all the elements with given value.
    */
    /*
    * Generic implementation to search if a given value exists in a map or not.
    * Adds all the keys with given value in the vector
    */
    template<typename K, typename V>
    bool findByValue(std::vector<K> & vec, std::map<K, V> mapOfElemen, V value)
    {
        bool bResult = false;
        auto it = mapOfElemen.begin();
        // Iterate through the map
        while (it != mapOfElemen.end())
        {
            // Check if value of this entry matches with given value
            if (it->second == value)
            {
                // Yes found
                bResult = true;
                // Push the key in given map
                vec.push_back(it->first);
            }
            // Go to next entry in map
            it++;
        }
        return bResult;
    }
    void test()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = {
            { "is", 6 },
            { "the", 5 },
            { "hat", 9 },
            { "at", 6 }
        };

        // Create a vector of string
        std::vector<std::string> vec;

        int value = 6;

        // Find all the keys with value 6
        bool result = findByValue(vec, wordMap, value);

        if (result)
        {
            std::cout << "Keys with value " << value << " are," << std::endl;
            for (auto elem : vec)
            {
                std::cout << elem << std::endl;
            }
        }
        else
        {
            std::cout << "No Key is found with the given value" << std::endl;
        }

        return;
    }
}

namespace eraseElementBykeyOrIteratorOrRange {
    /*
        std::map provides 3 overloaded version of erase() to remove elements from map i.e.

            Erase by key
            Erase by Iterator
            Erase a range

        Erase Element from Map by Key
            size_type erase (const key_type& k);
            It returns the number of elements deleted, but as there can be unique keys only in std::map. 
            Therefore it will return 1 if element is deleted else it will return 0 if given key is not found in map.
    */

    void test()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = { { "is", 6 },{ "the", 5 },
        { "hat", 9 },{ "at", 6 },{ "of", 2 },{ "hello", 1 } };

        std::cout << "Map Entries Before Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        // Removes the element from map with given key.
        int result = wordMap.erase("is");

        // Check if element is actually deleted from map
        if (result == 1)
            std::cout << "Element with key 'is' deleted" << std::endl;
        else
            std::cout << "Element with key 'is' Not Found" << std::endl;


        std::cout << "Map Entries After Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        return;
    }

    /*
        Erase Element from Map by Iterator
            iterator erase (const_iterator position);
            It returns the iterator of the next element.
    */
    void test2()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = { { "is", 6 },{ "the", 5 },
        { "hat", 9 },{ "at", 6 },{ "of", 2 },{ "hello", 1 } };

        std::cout << "Map Entries Before Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;


        // Get the iterator of element with key 'of'
        std::map<std::string, int>::iterator it = wordMap.find("of");

        // Check if iterator is valid.
        if (it != wordMap.end())
        {
            // Remove the element pointed by iterator
            wordMap.erase(it);

            std::cout << "Element Removed" << std::endl;
        }
        else
            std::cout << "Key Not Found" << std::endl;


        std::cout << "Map Entries After Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;
        return;
    }

    // Erase Element from Map by Iterator Range
    void test3()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = { { "is", 6 },{ "the", 5 },
        { "hat", 9 },{ "at", 6 },{ "of", 2 },{ "hello", 1 } };

        std::cout << "Map Entries Before Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        // Create an iterator pointing to begin of map
        std::map<std::string, int>::iterator it1 = wordMap.begin();

        // Create an iterator pointing to begin of map
        std::map<std::string, int>::iterator it2 = wordMap.begin();
        // Increment Iterator
        it2++;
        // Increment Iterator
        it2++;
        // Itr2 is now pointing to 3rd element


        // Check if iterator is valid.
        if (it1 != wordMap.end() && it2 != wordMap.end())
        {
            // Remove the element pointed by iterator
            wordMap.erase(it1, it2);
            std::cout << "Elements Removed" << std::endl;
        }
        else
            std::cout << "Key Not Found" << std::endl;

        std::cout << "Map Entries After Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        return;
    }
}

namespace operatorUsageDetauls {
    /*
        std::map has Operator[] i.e.
            mapped_type& operator[] (const key_type& k);
        operator [] works in Find or Create Mode i.e. 
        when called with a key K, it will try to look for element 
        with given key K and can go in below 2 directions i.e.
            1. If any element is found with key K, then it will return the reference of its value.
            2. But if there is no element in map with K, then it will create a new element in map 
                with key K and assign default value of value_type in its value field. 
                Then it will return the value of newly created element as reference.
    */
    void test1()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = {
            { "is", 6 },
            { "the", 5 }
        };
        // As there is no element with key 'Hello'
        // So, operator [] will create a new element in map
        // with key as 'Hello' and default value, which in this case
        // will be 0.
        int & value1 = wordMap["Hello"];

        // Display the value
        std::cout << "value of 'Hello' = " << value1 << std::endl;

        // Fetch the value for key 'is'
        // As key already exist therefore will not create new entry
        // Will just return the reference of value
        int & value2 = wordMap["is"];

        // Display the value
        std::cout << "value of 'is' = " << value2 << std::endl;


        // As [] returns the value by reference, therefore
        // it will override the new value.
        wordMap["is"] = 4;

        int & value3 = wordMap["is"];

        // Display the value
        std::cout << "value of 'is' = " << value3 << std::endl;


        // Override the value of element with key 'is'
        wordMap["is"] = 4;

        // Will create a new wntry with Key 'Thanks' and override its
        // default value 0 with 10.
        wordMap["Thanks"] = 10;


        std::cout << "***********Map Entries***********" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        return;
    }

    // Using operator[] with User Defined objects as Value
    // As operator[] can create new entry with default value. 
    // So, if we are using a User defined class or struct as value in a map, 
    // then its must to have default constructor in it.
    struct Occurance
    {
        int count;

        // Default Constructor
        // Un Comment it to compile the code
        /*
        Occurance()
        {
        this->count = 0;
        }
        */

        // Parametrized constructor
        Occurance(int count)
        {
            this->count = count;
        }
    };
    void test2()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, Occurance> wordMap = {
            { "is", Occurance(6) },
            { "the", Occurance(5) }
        };


        // As key is not in map, so operator[] will create new entry
        // With default value of value field. Therefore, Will compile
        // only if Occurance sruct has default constructor.
        Occurance occur = wordMap["Hello"];

        return;
    }
}

namespace eraseByValueOrCallbackWhileIteratingOrErase_if {
    // Erasing elements by value
    // Algorithm Used
    template <typename K, typename V>
    int erase_if(std::map<K, V> & mapOfElemen, V value)
    {
        int totalDeletedElements = 0;
        auto it = mapOfElemen.begin();
        //Iterate through the map
        while (it != mapOfElemen.end())
        {
            // Check if value of this entry matches with given value
            if (it->second == value)
            {
                totalDeletedElements++;
                // Erase the current element, erase() will return the
                // next iterator. So, don't need to increment
                it = mapOfElemen.erase(it);
            }
            else
            {
                // Go to next entry in map
                it++;
            }
        }
        return totalDeletedElements;
    }

    void test()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = { { "is", 6 },{ "the", 5 },
        { "hat", 9 },{ "at", 6 } };

        std::cout << "Map Entries Before Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        // Erase all the elements with value 6
        int deletedCount = erase_if(wordMap, 6);

        std::cout << "Total elements deleted = " << deletedCount << std::endl;

        std::cout << "Map Entries After Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;
    }

    //Erasing elements by Callback
    /*
    * Generic implementation to erase elements by Callback
    * It iterates over all the elements and for every element it executes
    * the callback, if it returns the true then it will delete
    * that entry and move to next.
    */
    template<typename K, typename V>
    int erase_if(std::map<K, V> & mapOfElemen, bool(*functor)(V))
    {
        int totalDeletedElements = 0;
        auto it = mapOfElemen.begin();
        // Iterate through the map
        while (it != mapOfElemen.end())
        {
            // Check if value of this entry matches with given value
            if (functor(it->second))
            {
                totalDeletedElements++;
                // Erase the current element, erase() will return the
                // next iterator. So, don't need to increment
                it = mapOfElemen.erase(it);
            }
            else
            {
                // Go to next entry in map
                it++;
            }
        }
        return totalDeletedElements;
    }

    bool isODD(int val)
    {
        if (val % 2 == 1)
            return true;
        else
            return false;
    }

    void test2()
    {
        // Map of string & int i.e. words as key & there
        // occurrence count as values
        std::map<std::string, int> wordMap = {
            { "is", 6 },
            { "the", 5 },
            { "hat", 9 },
            { "at", 6 }
        };

        std::cout << "Map Entries Before Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;

        // Erase all the elements whose value is ODD
        int deletedCount = erase_if(wordMap, &isODD);

        std::cout << "Total elements deleted = " << deletedCount << std::endl;

        std::cout << "Map Entries After Deletion" << std::endl;
        // Print the map elements
        for (auto elem : wordMap)
            std::cout << elem.first << " :: " << elem.second << std::endl;


        return;
    }
}

namespace usingSTLtoVerifyBracketsOrParenthesesCombination {
    /*
        In this we will see how to check if a given string take valid combination of open and close brackets i.e.

            (4+{8-[22+8]*}] contains valid order of open and close brackets.

            ({5+8]) contains invalid combination of open and close brackets.

            Bracket combinations to be used,

            { , }
            [,]
            (,)
        
        Algo Used:
            Create a empty stack of characters
            Traverse characters in string one by one.
            If any open bracket is encountered, then push that in stack
            If any type of close bracket is encountered then match it¡¯s open bracket counterpart with top of stack.
            If match is successful then pop character from stack.
            If match is unsuccessful then RETURN FALSE.
            If stack is empty RETURN TRUE;
            If stack is not empty RETURN FALSE;
    */
    using namespace std;
    bool isOpenBracket(char val, map<char, char> mapOfBrackets)
    {
        map<char, char>::iterator it = mapOfBrackets.begin();
        while (it != mapOfBrackets.end())
        {
            if (it->second == val)
            {
                return true;
            }
            it++;
        }
        return false;
    }
    bool testBracket(string s)
    {
        stack<char> bracketStack;
        map<char, char> bracketMap;

        bracketMap['}'] = '{';
        bracketMap[')'] = '(';
        bracketMap[']'] = '[';

        for (int i = 0; i < s.size(); i++)
        {
            if (isOpenBracket(s[i], bracketMap))
                bracketStack.push(s[i]);

            if (bracketMap.find(s[i]) != bracketMap.end())
            {
                if (bracketStack.empty())
                    return false;
                if (bracketStack.top() != bracketMap[s[i]])
                {
                    return false;
                }
                else
                    bracketStack.pop();

            }
        }
        if (bracketStack.size() > 0)
            return false;
        else
            return true;
    }
}

int main()
{
    return 0;
}