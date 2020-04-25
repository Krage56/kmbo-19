#ifndef LLIST_H
#define LLIST_H

#include <cstddef>

// Linked list of integers

class LList
{
    class Container {
        explicit Container(const int& value, Container* next = nullptr);
        ~Container();
        int value;
        Container* next;
        friend  class LList;
        void insertNext(const int& value);
        void insertNext(Container* container);
        void removeNext();
    };

public:

	LList();                         // construct new collection
	~LList();                        // free resources
    LList(const LList& copyList); //copy-constructor
    LList& operator=(const LList& copyList);
	void push_back(int val);         // add new value at the end:  [1 2 3 4] -> [1 2 3 4 5]
	void push_front(int val);        // add new value at the begin [1 2 3 4] -> [5 1 2 3 4]
	void pop_back(int val);          // remove at the end          [1 2 3 4] -> [1 2 3]
	void pop_front(int val);         // remove at the front        [1 2 3 4] -> [2 3 4]
	size_t size() const;             // get actual number of items [1 2 3 4] -> 4
	int& operator[](size_t idx);     // get rw access ot specific item addressing by idx
	int  operator[](size_t idx) const; //get read-only access
	void erase_at(size_t idx);       // remove item at specific position: [1 2 3 4], 2 -> [1 2 4]
	void insert_at(size_t idx, int val); // insert item at specific position: [1 2 3 4], 1, 5 -> [1 5 2 3 4]
	void reverse();                  // reverse item sequense: [1 2 3 4] -> [4 3 2 1]
    LList reverse() const;          //reverse list for constant-object

#if ENABLE_MOVE
    LList(LList&& moveList) noexcept;
    LList& operator=(LList&& moveList) noexcept;
#endif
    void forceContainersDelete(Container* container);
private:
    Container*	_head;
    size_t	_size;
    Container* getContainer(size_t pos) const;
    void insertContainer(size_t pos, LList::Container *container);

};

#endif //LLIST_H
