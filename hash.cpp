//hash.cpp
#include <iostream>
#include <climits>//for converting unsigned long
#include "hash.h"


using namespace std;//may not be good idea



hashTable::hashTable(int size){
	this->capacity = this->getPrime(size);
	this->filled   = 0;
	this->data.resize(capacity);
	cout<<"capacity="<<capacity<<endl;
}



int hashTable::insert(const std::string &key, void *pv){
	//check load factor and rehash if grater than .6 rehash

	//cout<<"start of insert !!!!!"<<endl;
	//cout<<"load factor after insert="<<this->filled+1<<"/"<<this->capacity<<endl;
	if(float(this->filled+1)/this->capacity > 0.5) {//!!!!change to 0.5//add 1 to see if capacity over when added
		if(!rehash()) return 2;
	}
	if(this->contains(key)) return 1;
	//get hashes first then loop
	int ini_pos, shift;
	this->get_hash(ini_pos, shift, key);
	//cout<<"ini_pos="<<ini_pos<<"shift="<<shift<<endl;

//two situations: doesnt exisit, or exist but deleted
	for (int i=0; i<this->capacity ; i++){
		//cout<<"i="<<i<<endl;
		//where magic happens
		//cout<<"sum of hash="<<ini_pos+shift*i<<endl;
		int pos =(ini_pos+shift*i)%this->capacity;//every loop add one shift, not i*shift
		//cout<<"hashpos="<<pos<<endl;
		hashItem* item = &this->data[pos];
		//cout<<"occupied?"<<item->isOccupied<<". deleted?"<<item->isDeleted<<endl;
		if (item->isOccupied == 1) {
			cout<<"cell occupied"<<endl;
			if (item->key == key) {
			item->isDeleted = 0;//deleted case
			return 0;
			}
			else continue;
		}
		
		else {//item->isOccupied == 0 
			item->key = key;
			item->pv = pv;
			item->isOccupied = 1;
			item->isDeleted  = 0;
			this->filled++;
			return 0;
		}

	}

	//went throgh everything still not space
	throw std::runtime_error("hashtable filled, bad");
	
}

bool hashTable::contains(const std::string &key){
	int pos = this->findPos(key);
	if (pos == -1) return false;
	else {
		//cout<<"pos found to be"<<pos<<endl;
		return true;
	}
	
}

void * hashTable::getPointer(const std::string &key, bool *b){
	int pos = this->findPos(key);
	if (pos == -1) {
		b=new bool(false);
		return NULL;
	}
	else {
		b=new bool(true);
		return this->data[pos].pv;
	}
}

int hashTable::setPointer(const std::string &key, void *pv){
	int pos = this->findPos(key);
	if(pos == -1) return 1;
	this->data[pos].pv = pv;
	return 0;
}

bool hashTable::remove(const std::string &key){
	int pos = this->findPos(key);
	if(pos == -1) return false;
	this->data[pos].isDeleted = 1;
	return true;
}

void hashTable::get_hash(int &ini_pos, int &shift, const std::string &key){
	int hash_value = this->hash(key);
    ini_pos   = hash_value%this->capacity;
    int hash2_value= this->hash_2(key);
    shift = hash2_value%(this->capacity-1) + 1;//add 1 to make shift not 0, and not out of bound
}//shift !=0 && shift !=capacity

int hashTable::findPos(const std::string &key){
	int ini_pos, shift;
	this->get_hash(ini_pos, shift, key);

	for (int i=0; i<this->capacity ; i++){
		//where magic happens
		//cout<<"sum of hash="<<pos+i*shift<<endl;
		int pos =(ini_pos+shift*i)%this->capacity;
		//cout<<"hashpos="<<pos<<endl;
		hashItem* item = &this->data[pos];
		//cout<<"occupied?"<<item->isOccupied<<". deleted?"<<item->isDeleted<<endl;
		if (item->isOccupied == 1) {
			if(item->isDeleted==0){
				if (item->key == key) return pos;
				//else continue;//occupied by something not deleted
			}
			else{//is deleted true
				if (item->key == key) return -1;
				//else continue;//occupied by something deleted				 
			}
			continue;//combined by two continues on top
		}
		else return -1;
	}
	return -1;//went through all blocks and founds no match
}

unsigned int hashTable::getPrime(int size){
	int primes[26]={//change back to 26
		//delete this one at the end !!!!
		53
		,97
		,193
		,389
		,769
		,1543
		,3079
		,6151
		,12289
		,24593
		,49157
		,98317
		,196613
		,393241
		,786433
		,1572869
		,3145739
		,6291469
		,12582917
		,25165843
		,50331653
		,100663319
		,201326611
		,402653189
		,805306457
		,1610612741};
	for (int i=0; i < sizeof(primes); i++){
		if (2*size < primes[i]) return primes[i];//!!!!!change this to 2 times the size
	}
	throw std::runtime_error("not valid size found");
	
}

//from online hash function:  http://www.cse.yorku.ca/~oz/hash.html
int hashTable::hash (const std::string &key) {
	const char *str = key.c_str();
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    int int_hash = hash & INT_MAX;
	return abs(int_hash);
    }
int hashTable::hash_2(const std::string &key){
	const char *str = key.c_str();
	unsigned long hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;
    int int_hash = hash & INT_MAX;
    return abs(int_hash);
}

bool hashTable::rehash(){
	//rehash means to iterate through everything and change size
	cout<<"rehashinggggggg"<<endl;
	vector<hashItem> new_data = this->data;
	int old_cap = this->capacity;
	int new_cap= this->getPrime(old_cap);
	this->data.clear();
	this->capacity = new_cap;
	this->filled   = 0;
	this->data.resize(new_cap);
	for(int i=0; i < old_cap; i++){
		//only insert when it is not occupied and not deleted 
		if(new_data[i].isOccupied == 1 && new_data[i].isDeleted == 0) this->insert(new_data[i].key, new_data[i].pv);
	}
	new_data.resize(0);
	return true;
}