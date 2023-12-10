// ITPDoubleList.hpp
// Defines and implements the ITPDoubleList collection

#pragma once
#include <ostream>
#include <sstream>
#include <stdexcept>

template <typename T>
class ITPDoubleList
{
private:
    
    // Node only used internally to list
    struct Node
    {
        // Data in this node
        T mData;
        // Link to previous node
        Node* mPrev;
        // Link to next node
        Node* mNext;
    };
    
    // Pointer to the head node
    Node* mHead;
    // Pointer to the tail node
    Node* mTail;
    // Number of nodes currently in the list
    unsigned mSize;
    
public:
    // Iterator helper class...
    class Iterator
    {
    private:
        Node* mCurr;
    public:
        // Needed for List access
        friend class ITPDoubleList;
        // Constructors
        //default constructor
        Iterator()
        {
            //set pointer to null
            mCurr = nullptr;
		}
        //parameterized constructor
        Iterator(Node* inCurr)
        {
            //set pointer to current node
            mCurr = inCurr;
        }
        //copy constructor
        Iterator(const Iterator& src)
        {
            
            mCurr = src.mCurr;
        }
        
        // Assignment
        Iterator& operator=(const Iterator& src)
        {
            mCurr = src.mCurr;
            return *this;
		}
        
        // Incrementors / Decrementors
        // ++i
        Iterator& operator++()
        {
            if (mCurr){
                mCurr = mCurr->mNext;
            }
            return *this;
		}
        
        // i++
        //the int is to have two different overloaded functions
        Iterator operator++(int)
        {
            Iterator retval(*this);
            if (mCurr){
                mCurr = mCurr->mNext;
            }
            return retval;
        }
        
        // --i
        Iterator& operator--()
        {
            if (mCurr){
                mCurr = mCurr->mPrev;
            }
            return *this;
        }
        
        // i--
        Iterator operator--(int)
        {
            Iterator retval(*this);
            if (mCurr){
                mCurr = mCurr->mPrev;
            }
            return retval;
        }
        
        // Dereference
        T& operator*() const
        {
            return mCurr->mData;
        }
        
        Node* operator->() const
        {
            return mCurr;
        }
        
        // Comparison
        bool operator==(const Iterator& rhs) const
        {
            
            return (mCurr == rhs.mCurr);
        }
        
        bool operator!=(const Iterator& rhs) const
        {
            
            return (mCurr != rhs.mCurr);
        }
    };
    
    // List functions...
    
    // Function: Default Constructor
    // Purpose: Initializes size to 0 and head/tail to null
    // Input: None
    // Returns: Nothing
    ITPDoubleList()
    {
        mHead = nullptr;
        mTail = nullptr;
        mSize = 0;
    }
    
    // Function: Copy Constructor
    // Purpose: Initializes this list as a deep copy of other
    // Input: Other list to copy (const reference)
    // Returns: Nothing
    ITPDoubleList(const ITPDoubleList& other)
    {
        mSize = 0;
        mTail = nullptr;
        mHead = nullptr;
        
        Node* temp = other.mHead;
        while (temp != nullptr){
            push_back(temp->mData);
            temp = temp->mNext;
        }
        
    }
    
    // Function: Destructor
    // Purpose: Calls the clear function to delete the list
    // Input: None
    // Returns: Nothing
    ~ITPDoubleList()
    {
        clear();
	}
    
    // Function: clear
    // Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
    // Input: None
    // Returns: Nothing
    void clear()
    {
        while (mSize > 0){
            pop_front();
        }
        mTail = nullptr;
        mHead = nullptr;
    }
    
    // Assignment Operator
    // Function: Assignment Operator
    // Purpose: Clear this list, and then make a deep copy of other
    // Input: Other list to copy (const reference)
    // Returns: *this
    ITPDoubleList& operator=(const ITPDoubleList& other)
    {
        clear();
        Node* temp = other.mHead;
        while (temp != nullptr){
            push_back(temp->mData);
            temp = temp->mNext;
        }
        return *this;
    }
    
    // Function: size
    // Purpose: Gets the current size of the linked list
    // Input: None
    // Returns: size of the list
    unsigned size() const
    {
        return mSize;
    }
    
    // Function: push_front
    // Purpose: Inserts a node at the front of the linked list
    // Input: Value to store in the new node
    // Returns: Nothing
    void push_front(const T& value)
    {
        Node* newNode = new Node;
        newNode->mData = value;
        newNode->mPrev = nullptr;
        newNode->mNext = mHead;
        if (mSize == 0){
            mTail = newNode;
        }
        else{
            mHead->mPrev = newNode;
        }
        mHead = newNode;
        mSize++;
    }
    
    // Function: front
    // Purpose: Gets the value of the node at the front of the list
    // Input: None
    // Returns: Value of the node at the front of the list
    T& front()
    {
        if (mHead == nullptr || mSize == 0) {
            throw std::out_of_range("Empty list");
        }
        else{
            return mHead->mData;
        }
        // FIX RETURN VALUE
    }
    
    // Function: pop_front
    // Purpose: Removes the node at the front of the list
    // Input: None
    // Returns: None
    void pop_front()
    {
        if (mSize == 0){
            throw std::out_of_range("Empty list");
        }
        else if (mSize == 1){
            delete mHead;
            mHead = nullptr;
            mTail = nullptr;
        }
        else{
            Node* delHead = mHead;
            mHead = mHead->mNext;
            mHead->mPrev = nullptr;
            delete delHead;
            begin();
        }
        mSize--;
    }
    
    // Function: push_back
    // Purpose: Inserts a node at the end of the linked list
    // Input: Value to store in the new node
    // Returns: Nothing
    void push_back(const T& value)
    {
        Node* newNode = new Node;
        newNode->mData = value;
        newNode->mPrev = mTail;
        newNode->mNext = nullptr;
        if (mSize == 0){
            mHead = newNode;
        }
        else{
            mTail->mNext = newNode;
        }
        mTail = newNode;
        mSize++;
    }
    
    // Function: front
    // Purpose: Gets the value of the node at the front of the list
    // Input: None
    // Returns: Value of the node at the front of the list
    T& back()
    {
        if (mSize == 0){
            throw std::out_of_range("Empty list");
        }
        else{
            return mTail->mData;
        }
    }

    // Function: pop_back
    // Purpose: Removes the node at the end of the list
    // Input: None
    // Returns: None
    void pop_back()
    {
        if (mSize == 0){
            throw std::out_of_range("Empty list");
        }
        else if (mSize == 1){
            delete mTail;
            mHead = nullptr;
            mTail = nullptr;
        }
        else{
            Node* delTail = mTail;
            mTail = mTail->mPrev;
            mTail->mNext = nullptr;
            delete delTail;
        }
        mSize--;
        
    }
    
    // Function: begin
    // Purpose: Gets an iterator for the start of the list
    // Input: None
    // Returns: Iterator pointing to beginning of list
    Iterator begin() const
    {
        // TODO: Fill in
        return Iterator(mHead); // FIX RETURN VALUE
    }
    
    // Function: end
    // Purpose: Gets an iterator for the end of the list
    // Input: None
    // Returns: Iterator pointing to end of list
    Iterator end() const
    {
        // TODO: Fill in
        return Iterator(mTail); // FIX RETURN VALUE
    }

	// Function: erase
	// Purpose: Removes the item at the node pointed to by i
	// Input: Iterator pointing to a valid node to remove before
	// Returns: A new iterator pointing to the node after the removed item
    Iterator erase(Iterator& i)
    {
        if (i.mCurr == mHead){
            pop_front();
            return begin();
        }
        else if (i.mCurr == mTail){
            pop_back();
            return end();
        }
        else{
            Node* before = i.mCurr->mPrev;
            Node* after = i.mCurr->mNext;
            Node* toDel = i.mCurr;
            delete toDel;
            before->mNext = after;
            after->mPrev = before;
            mSize--;
            return Iterator(after);
        }
    }

	// Function: insert
	// Purpose: Inserts a list item before node pointed to by i
	// Input: Iterator pointing to a valid node to insert before
	// Returns: A new iterator pointing to the inserted value
    Iterator insert(Iterator& i, const T& val)
    {
        if (i.mCurr == nullptr) {
                throw std::invalid_argument("Invalid iterator");
            }
        if (i.mCurr == mHead){
            push_front(val);
            return begin();
        }
        else if (i.mCurr == mTail){
            push_back(val);
            return end();
        }
        else{
            Node* before = i.mCurr->mPrev;
            Node* after = i.mCurr->mNext;
            Node* insertVal = new Node;
            insertVal->mData = val;
            insertVal->mPrev = before;
            insertVal->mNext = after;
            before->mNext = insertVal;
            after->mPrev = insertVal;
            mSize++;
            return Iterator(insertVal);
        }
    }
    
public:
    // Function: Output Stream Operator
    // Purpose: Prints the contents of the list to the provided stream
    // Written in the format of {x, y, ..., z}
    // Input: Stream to write to, list to write
    // Output: Stream after values are written
    friend std::ostream& operator<<(std::ostream& os, const ITPDoubleList<T>& list)
    {
        os << "{";
        for (const auto& items : list){
            os << items.mData;
            if (items != list.end()){
                os << ", ";
            }
        }
        os << "}";
        return os;
    }
    
    // Function: toString
    // Purpose: Converts list to a string
    // Input: None
    // Output: String (in the format as the ostream)
    std::string toString() const
    {
        std::string retVal;
        retVal.append("{");
        for (const auto& item : *this){
            retVal.append(std::to_string(item.mData));
            if (item != end()){
                retVal.append(", ");
            }
        }
        retVal.append("}");
        return retVal; 
    }
    
    // Function: toReverseString
    // Purpose: Outputs the list in reverse
    // Input: None
    // Output: String in reverse
    std::string toReverseString() const
    {
        std::string retVal;
        retVal.append("{");
        Node* temp = mTail;
        while (temp != nullptr){
            retVal.append(temp->mData);
            if (temp != mHead){
                retVal.append(", ");
            }
            temp = temp->mPrev;
        }
        retVal.append("}");
        return retVal;
    }
};
