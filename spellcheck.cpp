//spellcheck.cpp

#include <iostream>
#include <time.h>
#include "hash.h"
using namespace std;
int main() {
	clock_t t0,t1,t2;
	t0=clock();
	//std::cout<<"hello world"<<std::endl;
	hashTable* dict =new hashTable(2);
	int int_a = 4455;
	int* yammy = &int_a;
	for (int i=0; i<1000; i++){
	cout<<dict->insert(to_string(i)+"that guy",yammy)<<endl;
	//cout<<dict->insert("that guy"+to_string(i),yammy)<<endl;
	}
	t1=clock();
	cout<<dict->contains("that guy")<<endl;
	cout<<dict->contains("tis guy")<<endl;
	cout<<dict->contains("tisa guy")<<endl;
	cout<<dict->contains("tisa guasy")<<endl;
	cout<<"jello"<<endl;
	t2=clock();
	cout<<"insert time = "<<t1-t0<<endl;
	cout<<"check contain time = "<<t2-t1<<endl;
	return 0;
}
