//dijkstra's main
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>//for timeing

using namespace std;

int main(){

	string file_name, output_file;
	
	cout << "Enter name of input file: ";
	cin >> file_name;

	int * 2d_map[1001][1001]
	ifstream file;
	string line, A, B, C;
	file.open (file_name);

	while(1){
		if (!getline(file, A)) break;
		getline(file, B);
		getline(file, C);
		process(A, B, C, 2d_map);

	}

	
	file.close();
	
    //use get pointer to chek if entered vertex is valid	
   
	cout << "Enter name of output file: ";
    cin >> output_file;
    ofstream output(output_file);
	

	return 0;
	
}

int process(string A, string B, string C, int * map){
	cout<<map[4]

	return 0;
}