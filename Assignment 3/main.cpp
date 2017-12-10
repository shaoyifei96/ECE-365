//dijkstra's main
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>//for timeing
#include "graph.h"

using namespace std;

int main(){
	graph graph_map(200000);
	string file_name, start_v, output_file;
	
	cout << "Enter name of graph file: ";
	cin >> file_name;
	graph_map.file_read(file_name);
	
    //use get pointer to chek if entered vertex is valid	
    clock_t t1, t2;
    do {
        cout << "Enter a valid vertex id for the string vertex: ";
        cin >> start_v;
        t1 = clock();
    } while((graph_map.Dijkstra(start_v))); 

    t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
	
	cout << "Enter name of output file: ";
    cin >> output_file;
    ofstream output(output_file);
	graph_map.print_result(output);

	return 0;
	
}