//graph.h
#ifndef _GRAPH_H
#define _GRAPH_H
//include. may not need, will see
#include <list>
#include <fstream>//for file input
#include <string>
#include <sstream>
#include <iostream>
#include <stack>  //for printing
#include <cstdlib>
#include "heap.h"

using namespace std;

const int INF = 10000000;//find the right value

class graph{

public:
	graph(int capacity);
	
	int file_read(string path);
	void insert(string start_v, string end_v, int cost);
	int Dijkstra(string v);
	void print_result(ofstream &output);
private:

	class vertex;

	class edge{
	public:
		edge(vertex* des,int cost){
			this->des  = des;
			this->cost = cost;
		}
		vertex* des;
		int cost;
	};
	
	class vertex {
	public:
		vertex(string id){
			this->id = id;
		}
		string id;
		int dist;
		vertex* prev;
		bool known;
		list<edge*> adj_list;
	};
	
	hashTable *v_mapping;
	list<vertex*> vertex_list;
	string start_v;

};

#endif //graph