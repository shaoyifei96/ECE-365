#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
#include <string>
using namespace std;

bool map[1001][1001] = { false };
int fill_table(string A, string B, string C);
string print_result(string A, string B);
void parse(string file_name, string output_file);

int main(){
	string file_name, output_file;

	cout << "Enter name of input file: ";
	cin >> file_name;
	
	cout << "Enter name of output file: ";
	cin >> output_file;
	
	parse(file_name,output_file);	

	return 0;
	
}

void parse(string file_name, string output_file){
	ifstream file;
	ofstream output(output_file);
	file.open (file_name);
	string A, B, C;
	while(true){
		if (!getline(file, A)) break;
		if (!getline(file, B)) break;
		if (!getline(file, C)) break;
		if (!fill_table(A, B, C)) {
			output<<print_result(A,B)<<endl;
		}
		else output<<"*** NOT A MERGE ***"<<endl;
	}
	file.close();	
}

string print_result(string A, string B){
	int i = A.length();
	int j = B.length();
	map[0][0]= true;
	string out="";
	while(i > 0 && j > 0 ){//if both are bigger than 0, check the map
		if (map[j-1][i]){
			j--;
			out=B[j]+out;
		}
		else {
			i--;
			out=(char)toupper(A[i])+out;
		}
	}
	while(i==0 && j>0){//then dont have to check, just finish
		j--;
		out=B[j]+out;
	}
	while(j==0 && i>0){
		i--;
		out=(char)toupper(A[i])+out;
	}
	return out;
}

int fill_table(string A, string B, string C){
	if (A.length() + B.length()!=C.length()) return 1;
	//fill target to false so if observe change then it is changed
	//fill first row and first colome. then fill the middle row by row	
	//reset values of size A,B
	for(int j=0; j<= B.length();j++){
		for (int i=0; i <= A.length();i++){
			map[j][i]=false;
		}
	}
	for (int i=0; i < A.length();i++){
		if (A[i] == C[i]) {
			map[0][i+1] = true;
		}
		else break;
	}
	for (int j=0; j < B.length();j++){
		if (B[j] == C[j]) {
			map[j+1][0] = true;
		}
		else break;
	}
	//   A    A
	//B[     ][i j-1]
	//B[i-1 j][*    ]
	for(int j=1; j<= B.length();j++){
		for (int i=1; i <= A.length();i++){
			//cout<<"i"<<i<<"j"<<j<<endl;
			if( map[j-1][i] || map [j][i-1]){//some path valid
				if(B[j-1] == C[i+j-1] && A[i-1] == C[i+j-1] ){//both current step valid
					//so no matter which path it is from(top->down, or left->right), true
					map[j][i] = true;
				}
				else if(B[j-1] == C[i+j-1] && map[j-1][i]){//match on B, so has to step down
					map[j][i] = true;
				}
				else if(A[i-1] == C[i+j-1] && map[j][i-1]){//match on A, so has to step right
					map[j][i] = true;
				}
			}
			//!!!NOT THE SAME AS BELOW!!!
			//* if (C[i+j-1]==A[i-1] || C[i+j-1]==B[j-1]){
			//* 		//cout<<"C"<<i+j-1<<C[i+j-1]<<"  "<<"A"<<i-1<<A[i-1]<<" or "<<"B"<<j-1<<B[j-1]<<endl;
			//* 	map[j][i]= map[j][i-1] || map[j-1][i];
			//* }
		}
	}
	if(map[B.length()][A.length()]==false) return 1;	

	return 0;
}
