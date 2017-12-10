//graph.cpp
#include "graph.h"


using namespace std;

graph::graph(int cap){
	v_mapping = new hashTable(cap);
}

int graph::file_read(string path){
	ifstream file;
	string line;
	file.open (path);
	while(getline(file,line)){
		istringstream iss(line);
		string start; 
		iss >> start; 
		string end;
		iss >> end;
		int cost;
		iss >> cost; 
		this->insert(start, end, cost);
	}

	
	file.close();
	return 0;
	
}




void graph::insert(string start_v, string end_v, int cost){
	if(! this->v_mapping->contains(start_v)) {
		this->vertex_list.push_back(new vertex(start_v));
		this->v_mapping->insert(start_v, this->vertex_list.back());
	}
	if(! this->v_mapping->contains(end_v)) {
		this->vertex_list.push_back(new vertex(end_v));
		this->v_mapping->insert(end_v, this->vertex_list.back());
	}
	vertex * s_v = static_cast<vertex *> (this->v_mapping->getPointer(start_v));
	vertex * t_v = static_cast<vertex *> (this->v_mapping->getPointer(end_v));
	s_v->adj_list.push_back(new edge(t_v, cost));
}	
//done

int graph::Dijkstra(string v){
	if (! this->v_mapping->contains(v)) return 1; //check if exist
	this->start_v = v;
	vertex * v_pointer = static_cast<vertex *> (this->v_mapping->getPointer(v));
	
	heap d_pqueue(this->v_mapping->get_size());
	for(list<vertex*>::iterator list_it = vertex_list.begin();list_it != vertex_list.end(); list_it++){
		if (*list_it == v_pointer){
			(*list_it)->dist = 0;
		}
		else (*list_it)->dist = INF;
		(*list_it)->known = false;
		(*list_it)->prev  = NULL;
		vertex* this_v = *list_it;//for debuggin reason
		d_pqueue.insert(this_v->id, this_v->dist, this_v);
	}//importing complete

	while(d_pqueue.get_size() > 0){
		string *id = new string ("dummy");//dummy helps with segment fault in deletemin
		int *key = new int(0);
		void* pData = new vertex("dummy");
		void** ppData= &pData;
		d_pqueue.deleteMin(id, key, ppData);
		vertex * vertex_p = static_cast<vertex *> (*ppData);
		vertex_p->known = true;

		for (list<edge*>::iterator edge_it = vertex_p->adj_list.begin(); 
			edge_it != vertex_p->adj_list.end(); edge_it++){
			vertex* dest=(*edge_it)->des;
			if(dest->known != true){
				int new_dist=vertex_p->dist+(*edge_it)->cost;
				if(new_dist < dest->dist){
					d_pqueue.setKey(dest->id, new_dist);
					dest -> dist = new_dist;
					dest -> prev = vertex_p;
				}
			}
		}
	}


	return 0;//success
}

void graph::print_result(ofstream &output){
	for(list<vertex*>::iterator list_it = vertex_list.begin();list_it != vertex_list.end(); list_it++){
		bool path_e = 1;
		vertex* cur_v = *list_it;
		output<<cur_v->id<<": ";
		stack<string> path;   
		while(cur_v->id != this->start_v){
			if(cur_v->prev == NULL) {
				path_e = 0;
				break;
			}
			path.push(cur_v->id);
			cur_v=cur_v->prev;
		}
		if (path_e){
		output<<(*list_it)->dist<<" ["<<this->start_v;
		while(!path.empty()){
			output<<", "<<path.top();
			path.pop();
		}
		output<<"]"<<endl;
		}
		else output<<"NO PATH"<<endl;
	}

}