/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: CacheList starter file                              */
/*                                                                 */
/*  Author1 Name: Tim Roberts		 							   */
/*      - Struct Node
/*		- Class const_iterator
/*		- Class iterator
/*		- begin(), end(), cbegin(),cend()
/*		- CacheList(), insert(), search()
/*		- empty(), size()                                          */
/*																   */
/*  Author2 Name: Jared Cotton		 							   
		- erase(loc)	
		- erase(first, last)
		- search(key) --> re-did Tim''s version to get working correctly
		- merge(other)
		- CacheList:
		- destructor
		- copy constructor/assignment
		- move construtor/assignment							   */
/*                                                                 */
/*******************************************************************/

#include <cstdlib>
#include <utility>

template <typename T>

class CacheList
{
	struct Node
	{
		T _data;
		Node *_next;
		Node *_prev;
		int _acc;

		Node(const T &data = T{}, Node *nx = nullptr, Node *pr = nullptr, int ac = 0) :
			_data(data), _next(nx), _prev(pr), _acc(ac) {}
	};

	Node *_front;
	Node *_back;
	int _size;

public:
	class const_iterator
	{
		friend class CacheList;
		Node *_curr;

	public:
		//Default Constructor
		const_iterator() : _curr(nullptr) {}

		//Custom Constructor
		const_iterator(Node *n) : _curr(n) {}

		//Prefix ++ operator
		const_iterator operator++() { return _curr = _curr->_next; }

		//Postfix ++ operator
		const_iterator operator++(int)
		{
			const_iterator og = *this;

			_curr = _curr->_next;

			return og;
		}

		//Prefix -- operator
		const_iterator operator--() { return _curr = _curr->_prev; }

		//Postfix -- operator
		const_iterator operator--(int)
		{
			const_iterator og = *this;

			_curr = _curr->_prev;

			return og;
		}

		//Operator == overload to show if two const_iterators point to the same Node
		bool operator==(const_iterator rhs) { return _curr == rhs._curr; }

		//Operator != overload to show if two const_iterators point to different Nodes
		bool operator!=(const_iterator rhs) { return _curr != rhs._curr; }

		//Dereferencing operator overload to show the current Nodes data
		const T &operator*() const { return _curr->_data; }

	protected:
		//Returns the current Node
		Node* getCurr() const { return _curr; }
	};

	class iterator : public const_iterator
	{

	public:
		//Default Constructor
		iterator() : const_iterator() {}

		//Custom Constructor
		iterator(Node *n) : const_iterator(n) {}

		//Prefix ++ operator
		iterator operator++()
		{
			const_iterator::operator++();

			return *this;
		}

		//Postfix ++ operator
		iterator operator++(int)
		{
			iterator og = *this;

			const_iterator::operator++();

			return og;
		}

		//Prefix -- operator
		iterator operator--()
		{
			const_iterator::operator--();

			return *this;
		}

		//Postfix -- operator
		iterator operator--(int)
		{
			iterator og = *this;

			const_iterator::operator--();

			return og;
		}

		//Dereferencing operator overload to show the current Nodes data
		T &operator*() { return const_iterator::getCurr()->_data; }

		//Dereferencing operator overload to show the current Nodes data as a constant
		const T &operator*() const { return const_iterator::getCurr()->_data; }
	};
	CacheList();
	~CacheList();
	CacheList(const CacheList &rhs);
	CacheList &operator=(const CacheList &rhs);
	CacheList(CacheList &&rhs);
	CacheList &operator=(CacheList &&rhs);

	//Returns the first node with data if there is any, 
	//else it returns back
	iterator begin() { return iterator(_front->_next); }

	//Returns the point past the last Node with data
	iterator end() { return iterator(_back); }

	//Returns the first node with data if there is any, 
	//else it returns back
	const_iterator cbegin() const { return const_iterator(_front->_next); }

	//Returns the point past the last Node with data
	const_iterator cend() const { return const_iterator(_back); }
	void insert(const T &data);
	iterator search(const T &data);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	void merge(CacheList &other);
	bool empty() const;
	int size() const;
};

//Default Constructor
template <typename T>
CacheList<T>::CacheList() : 
	_front(new Node()), _back(new Node), _size(0)
{
	_front->_next = _back;
	_back->_prev = _front;
}

/*
Author: Jay Cotton
Date Edited: 10/15/2020
*/
template <typename T>
CacheList<T>::~CacheList()
{
	iterator current = this->begin();

	while (current != this->end())
	{
		auto del = current.getCurr();
		current++;
		delete del;
	}

	delete this->_front;
	delete this->_back;
}

/*
Author: Jay Cotton
Date Edited: 10/15/2020
*/
template <typename T>
CacheList<T>::CacheList(const CacheList &rhs) :
	_front(new Node()), _back(new Node), _size(0)
{
	_front->_next = _back;
	_back->_prev = _front;

	*this = rhs;
}

/*
Author: Jay Cotton
Date Edited: 10/15/2020
*/
template <typename T>
CacheList<T> &CacheList<T>::operator=(const CacheList &rhs)
{
	if (this != &rhs && nullptr != &rhs)
	{
		iterator current = this->begin();

		while (current != this->end())
		{
			auto del = current.getCurr();
			current++;
			delete del;
		}

		_front->_next = _back;
		_back->_prev = _front;

		for (const_iterator copy = rhs.cbegin(); copy != rhs.cend(); copy++)
			this->insert(*copy);

		this->_size = rhs._size;
	}

	return *this;
}

template <typename T>
CacheList<T>::CacheList(CacheList &&rhs) : 
	_front(new Node()), _back(new Node), _size(0)
{
	_front->_next = _back;
	_back->_prev = _front;

	*this = std::move(rhs);
}

template <typename T>
CacheList<T> &CacheList<T>::operator=(CacheList &&rhs)
{
	if (this != &rhs && nullptr != &rhs)
	{
		iterator current = this->begin();

		while (current != this->end())
		{
			auto del = current.getCurr();
			current++;
			delete del;
		}

		//steal resources from rhs
		_front->_next = rhs._front->_next;
		_front->_next->_prev = _front;
		_back->_prev = rhs._back->_prev;
		_back->_prev->_next = _back;
		_size = rhs._size;

		//set rhs to empty state
		rhs._front->_next = rhs._back;
		rhs._back->_prev = rhs._front;
		rhs._size = 0;
	}
	return *this;
}

//Creates a new Node with the data provided
//and places it at the end of the list with
//an access count of zero.
template <typename T>
void CacheList<T>::insert(const T &data)
{
	Node *nn = new Node(data, _back);

	if (_front->_next == _back)
	{
		nn->_prev = _front;
		_front->_next = nn;
		_back->_prev = nn;
	}
	else
	{
		nn->_prev = _back->_prev;
		_back->_prev->_next = nn;
		_back->_prev = nn;
	}
	_size++;
}

/*
Author: Jay Cotton
Date Edited: 10/15/2020

Description: This function takes a parameter 'data' of templated type 'T' and searches the current CacheList for it.
			 IF it finds an instance of 'data' in the list it increments it's nodes access count by 1 and rearranges the list accordingly.
			 It returns an iterator pointing either to the matching node or this->end() if no match was found.
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::search(const T &data)
{
	iterator current = this->begin();

	for (current; current != this->end(); current++)
	{
		if (current.getCurr()->_data == data)
		{
			current.getCurr()->_acc++;

			for (iterator reorder = this->begin(); reorder != this->end(); reorder++)
			{
				if (reorder.getCurr() != current.getCurr() && reorder.getCurr()->_acc <= current.getCurr()->_acc)
				{
					auto re = reorder.getCurr();
					auto cur = current.getCurr();

					cur->_next->_prev = cur->_prev;
					cur->_prev->_next = cur->_next;

					cur->_next = re;
					cur->_prev = re->_prev;
					re->_prev = cur;
					cur->_prev->_next = cur;

					break;
				}
			}
			break;
		}
	}

	return current;
}

/*
Author: Jay Cotton
Date Edited: 10/14/2020

Description: This function takes an iterator 'it' pointing to a node which it then deletes.
			 It returns an iterator pointing to the node which was after the deleted node.
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator it)
{
	auto current = it.getCurr();

	current->_next->_prev = current->_prev;
	current->_prev->_next = current->_next;

	it++;

	delete current;

	_size--;

	return it;
}

/*
Author: Jay Cotton
Date Edited: 10/14/2020

Description: This function takes parameters of iterators 'first' and 'last' and deletes all nodes from 'first' until but not including 'last'.
			 It returns the parameter 'last' which points to the node following the last deleted node.
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator first, iterator last)
{
	while (first != last)
		first = this->erase(first);

	return last;
}

/*
Author: Jay Cotton
Date Edited: 10/15/2020

Description: This function takes a parameter 'other' of type CacheList which it then 'merges' with the current CacheList 'this'.
			 Merging means that all nodes from 'other' are MOVED to 'this' and put in order of _acc alongside existing nodes.
			 (IF access count of a merging node is equal to the access count of one or more nodes in the current list it is placed behind those nodes.)
*/
template <typename T>
void CacheList<T>::merge(CacheList &other)
{
	if (!other.empty())
	{
		if(this->empty())
		{
			*this = std::move(other);
		}
		else
		{
			iterator current = this->begin();
			iterator merge = other.begin();

			while(merge != other.end())
			{	
				auto mer = merge.getCurr();
				auto cur = current.getCurr();
				
				if(merge.getCurr()->_acc > current.getCurr()->_acc || cur == this->_back)
				{
					merge++;

					mer->_prev = cur->_prev;
					mer->_prev->_next = mer;
					mer->_next = cur;
					cur->_prev = mer;;
				}
				else
				{
					current++;
				}
			}

			this->_size = this->_size + other._size;
			other._size = 0;
			other._front->_next = other._back;
			other._back->_next = other._front;
		}
	}
}

//Returns true if the list is empty
template <typename T>
bool CacheList<T>::empty() const
{
	return _front->_next == _back;
}

//Returns the number of nodes in the list
template <typename T>
int CacheList<T>::size() const
{
	return _size;
}
