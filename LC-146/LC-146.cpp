/*
	Implement cache: 
		Doubly linked: Of nodes holding (key, value) of each cache entry
						The linked list holds the cache entries in the order of most recently accessed to least recently accessed, from head to tail
		Hash-Map: Maps the key value of each cache entry to the node of that cache entry in the linked list
		
	get(key):
		Get the node with the key value
		Remove this node from its previous position in the linked list and attach it to the head of the linked list
		Return the value corresponding to that key
		
		Corner Cases:
			1. Requested key does not exist
			2. If the node for key is the head node
			3. if the node for key is the tail node
			
	
	put(int key, int value):
		Create a new node with key, value. Attach it to the head of the linked list.
		Add a hash entry for this key --> node*
		
		Corner Cases:
			1. Key already exists in the cache
			2. Cache already full: Eviction
			3. First cache entry being added
*/


#include <vector>
#include <unordered_map>

using namespace std;

class node
{
public:
	int key;
	int value;
	struct node* prev;
	struct node* next;
	
	node()
	{
		key = -1;
		value = -1;
		prev = nullptr;
		next = nullptr;
	}
	
	// node (key = -1, value=-1, prev=nullptr, next=nullptr);
	
	node(int key, int value) //, node* prev, node* next)
	{
		this->key = key;
		this->value = value;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

class LRUCache 
{
private:
	int cacheCapacity;
	unordered_map<int, node*> hash;		// Map the key with the node pointer in the linked list
	node* head, *tail;
	int cacheSize = 0;
	
public:
	LRUCache(int capacity) 
	{
		this->cacheCapacity = capacity;
		head = nullptr;
		tail = nullptr;
	}
	
	
	// Get the node with the key value
	// Remove this node from its previous position in the linked list and attach it to the head of the linked list
	// Return the value corresponding to that key
	int get(int key) 
	{			
		// Corner Case: If the node does not exist
		if (hash.find(key) == hash.end())
		{
			return -1;
		}
				
		// Corner case: If the node to be selected is the head node. No need to rearrange the linked list
		if (hash[key] == head)
		{
			node* keyNode = hash[key];
			return keyNode->value;
		}
		
		// Corner case: If the node to be selected is the tail node
		if (hash[key] == tail)
		{
			node* keyNode = hash[key];
					
			// Reattach nodes around keynode
			keyNode->prev->next = nullptr;	
			tail = keyNode->prev;	// Assign new tail	
			
			// Attach keynode at head
			head->prev = keyNode;
			keyNode->prev = nullptr;
			keyNode->next = head;			
			head = keyNode;		// Assign new head

			return keyNode->value;
		}
		
		// Node with key		
		node* keyNode = hash[key];
		
		// Reattach nodes around keynode
		keyNode->prev->next = keyNode->next;
		keyNode->next->prev = keyNode->prev;
		
		// Attach keynode at head
		head->prev = keyNode;
		keyNode->prev = nullptr;
		keyNode->next = head;
		head = keyNode;		// Assign new head
		
		return keyNode->value;
	}
	
	
	// Create a new node with key, value. Attach it to the head of the linked list.
	// Add a hash entry for that key --> node*
	void put(int key, int value) 
	{
		// Corner case: If the key already exists in the cache, just update the hash value and move the node to the head
		if (hash.find(key) != hash.end())
		{
			node* keyNode = hash[key];
			keyNode->value = value;
			
			get(key);		// Call this so that this node with the updated value now moves to the head
			
			return;
		}
		
		// Corner Case: If the cache is already in full capacity, evict the Least Recently Used entry from it
		if (this->cacheSize == this->cacheCapacity)
		{
			node* newTail;
			
			// Corner case: if the cache capacity is just 1, remove the one node carefully
			if (this->cacheCapacity == 1)
			{
				hash.erase(tail->key);
				delete tail;
				
				head = nullptr;
				tail =  nullptr;
			}
			
			// If the capacity is > 1
			else
			{
				newTail = tail->prev;
				newTail->next = nullptr;
				
				hash.erase(tail->key);
				delete tail;
				
				tail = newTail;
			}
			
			cacheSize--;
		}
		
		// If first node being added
		if (head == nullptr)
		{
			head = new node(key, value);
			tail = head;
			hash[key] = this->head;		// Hash the key to the linked list node
		}
		
		else
		{
			// Make a new node with the value in it. Attach it to the head of the linked list
			node* newNode = new node(key, value);
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			
			hash[key] = newNode;	// Hash the key to the linked list node
		}
		
		cacheSize++;
	}	
};