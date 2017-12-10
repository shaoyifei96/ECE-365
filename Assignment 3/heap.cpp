//heap.cpp
#include "hash.h"
#include "heap.h"

using namespace std;
//comments in header

heap::heap(int capacity){
	data.resize(capacity+1);//;leave 1 for 0th pos
	this->capacity = capacity;
	this->cur_size = 0;
	mapping = new hashTable(capacity);
}

int heap::insert(const std::string &id, int key, void *pv){
	if (cur_size+1 > capacity) return 1;
	if (mapping -> contains(id)) return 2;
	node * new_node = new node();
	new_node -> id   = id;
	new_node -> key  = key;
	new_node -> pData= pv;
	cur_size++;
	data[cur_size]  = *new_node;
	mapping->insert(id, &data[cur_size]);
	percolateUp(cur_size);//perculate up b
	return 0;
}

int heap::setKey(const std::string &id, int key){
	if (! mapping -> contains(id)) return 1;
	bool b;
	node *pn = static_cast<node *> (mapping->getPointer(id, &b));
	if      (key < pn->key) {
		pn->key = key;
		percolateUp(getPos(pn));

	}
	else if (key > pn->key) {
		pn->key = key;
		percolateDown(getPos(pn));
	}
	else {}
	return 0;
}

int heap::deleteMin(string *pId, int *pKey, void **ppData){
	if (cur_size == 0) return 1;
	if (pId   != NULL) *pId  = data[1].id;
	if (pKey  != NULL) *pKey = data[1].key;
	if (ppData!= NULL) *(static_cast<void **> (ppData)) = data[1].pData;
	mapping->remove(data[1].id);
	data[1]=data[cur_size];
	// node empty;
	// data[cur_size]= empty;
	//no need to delete since will overwirte when insert
	cur_size --;//change size before percolate so if statements in 
	//percolate can work
	percolateDown(1);
	return 0;
}

int heap::remove(const string &id, int *pKey, void **ppData){
	if(cur_size == 0) return 1;
	bool b;
	node * pn = static_cast<node *> (mapping->getPointer(id, &b));
	if (!b) return 1;//cannot find
	int index = getPos(pn);
	if (pKey  != NULL) *pKey = data[index].key;
	if (ppData!= NULL) *(static_cast<void **> (ppData)) = data[index].pData;
	setKey(data[index].id,data[1].key-1);//set key smaller than samllest, 
	//may go into negative, which is not considered 
	deleteMin();
	return 0;
}

void heap::percolateUp(int posCur){
	node ini_node = data[posCur];
	while(posCur>1){
		node* parent_node = &data[posCur/2];
		node* this_node = &data[posCur];//get their pointers
		if (ini_node.key < parent_node->key){
			*this_node = *parent_node;//does this work
			mapping->setPointer(this_node->id, this_node);
			posCur=posCur/2;
		}
		else break;
	data[posCur]=ini_node;
	mapping->setPointer(data[posCur].id, &data[posCur]);
		//if this < than parent
	}
}

void heap::percolateDown(int posCur){
	mapping->setPointer(data[posCur].id, &data[posCur]);
	node ini_node = data[posCur];
	while(true){
		node* parent      = &data[posCur];
		node* left_child  = &data[posCur*2];
		node* right_child = &data[posCur*2+1];//get their pointers
		if (ini_node.key > right_child->key && posCur*2+1 <= cur_size){
			if(left_child->key > right_child->key && posCur*2 <= cur_size){
				*parent = *right_child;	
				posCur=posCur*2+1;
				//swap right and parent
			}
			else{
				*parent = *left_child;
				posCur=posCur*2;
			}
		}
		else if(ini_node.key > left_child->key && posCur*2 <= cur_size){
			*parent = *left_child;	
			posCur=posCur*2;
		}
		else {
			data[posCur]=ini_node;
			mapping->setPointer(data[posCur].id, &data[posCur]);
			break;
		}
		//following line when if or else if happen
		mapping->setPointer(parent->id, parent);
	}
}

int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

int heap::get_size(){
	return this->cur_size;
}