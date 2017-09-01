#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>
using namespace std;

vector<int> intersection(vector<int> A, vector<int> B){
	vector<int> C;
	int j = 0;
	int i = 0;
	while((i < B.size()) && (j < A.size())){
		if(B[i] > A[j]){
			j++;
		}
		else{
			if(A[j] > B[i]){
				i++;
			}
			else{
				C.push_back(A[j]);
				i++;
				j++;
			}
		}
	}
	return C;
}
int main(){
	vector<int> A;
	vector<int> B;
	vector<int> C;
	int n;
	char a = 'c';
	char b = 'c';
	while(a != 'n'){
		cout << "digite um numero para inserir na lista A: ";
		cin >> n;
		A.push_back(n);
		cout << "Deseja adicionar outro?(s/n): ";
		cin >> a;
	}
	while(b != 'n'){
		cout << "digite um numero para inserir na lista B: ";
		cin >> n;
		B.push_back(n);
		cout << "Deseja adicionar outro?(s/n): ";
		cin >> b;
	}
	C = intersection(A, B);
	cout<< "o vetor de intercecção de A e B é: "<<endl;
	for(int i = 0; i < C.size(); i++){
		cout<< C[i] <<endl;
	}
	return 0;
} 