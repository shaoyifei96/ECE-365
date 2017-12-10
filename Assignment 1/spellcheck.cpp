//spellcheck.cpp
#include <iostream>
#include <fstream>//for file input
#include <time.h>//timing
#include <string>
#include <algorithm>
#include "hash.h"
using namespace std;

//meet a word seperator and check
void write_error(ofstream& out_file, int num_line, bool long_word, bool digit_word, string word, hashTable* dict){
	if (long_word) out_file << "Long word at line "<<num_line<<", starts: "<<word<<endl;
	else if(digit_word || word == "") {}
	else {
		if (!dict->contains(word)) out_file << "Unknown word at line "<<num_line<<": "<<word<<endl;
	}
}

//can read both dict and doc, when reading dict, careful_read can define if a line is processed before inserted
//							  when reading doc, make sure always set careful read to 1
void line_read( bool careful_read, bool checking, 
				ifstream& dict_file, ofstream& out_file, hashTable* dict){//read flag for two useage
    string line;
    int num_line=0;
    while (getline(dict_file,line)){
    	string word="";
    	num_line++;
	    transform(line.begin(), line.end(), line.begin(), ::tolower);
	    int num_char = 0;
	    bool long_word=0;
	    int digit_word=0;
	    if (careful_read){
	    	line+="@";//for else to run at the end of string for checking error of last word
		    for(int i=0; i < line.length(); i++) {
		    	char c = line.at(i);
		    	if(isdigit(c)) {
		    		digit_word = 1;
		    		num_char++;
		    	}//digit clear current, move back to curren   	
		    	else if(isalpha(c) || c == '-' || c == '\'') {
		    		if (num_char+1 > 20) {
		    			long_word = 1;
		    			continue;
		    		}
		    		word+=c;
		    		num_char++;
		    	}
		    	else {
		    		if (checking) write_error(out_file, num_line, long_word, digit_word, word, dict);
		    		else dict->insert(word,NULL);
		    		long_word=0;
		    		digit_word=0;
		    		num_char=0;
		    		word="";
		    	}
			}//lower case
		}
		else{
			dict->insert(line,NULL);
		}

	}
}

//for timing and creating streams and data structure
int main() {
	string dict_dir;
	string doc_dir;
	string out_dir;
	
	cout<<"Enter name of dictionary:";
	cin>>dict_dir;

	clock_t t0,t1;
	t0=clock();	

	ifstream dict_file;
	ifstream doc_file;
	ofstream out_file;
	
	dict_file.open (dict_dir);

	hashTable* dict =new hashTable(25000);
	line_read(0, 0, dict_file, out_file,  dict);
	dict_file.close();
	
	t1=clock();

	cout<<"Total time (in seconds) to load dictionary:"<< ((float)(t1-t0))/CLOCKS_PER_SEC<<endl;
	cout<<"Enter name of input file:";
	cin>>doc_dir;
	cout<<"Enter name of output file:";
	cin>>out_dir;
	
	t0=clock();
	
	doc_file.open(doc_dir);
	out_file.open(out_dir);
    line_read(1, 1, doc_file, out_file,  dict);
	doc_file.close();
	out_file.close();

	t1=clock();

	cout<<"Total time (in seconds) to check document:"<<((float)(t1-t0))/CLOCKS_PER_SEC<<endl;
	
	return 0;

 }
  

