#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>

using namespace std;

#define iv pair<int, vector<int>>

fstream js_fl;
map<int, string> mat_map;
vector<int> Maximo, Maximal;
int edge1, edge2;

class Graph{
    private:
        vector<vector<int>> adj;

        vector<int> intersection(vector<int> A, vector<int> B);
        vector<int> uniom(vector<int> A, int a);
    public:
        Graph();
        Graph(int size);
        int size();
        int size_adj(int node);
        void add_edge(int node1, int node2); // add
        void print_vertices_size();
        void print_graph();
        vector<int>& operator[](int  index);
        void bron_kerbosch(vector<int> R, vector<int> P, vector<int> X);
};

Graph::Graph(int size){
    for(int i = 0; i < size; i++){
        vector<int> a;
        adj.push_back(a);
    }
}

vector<int>& Graph::operator[](int index){
    if (index > adj.size() || index < 0)
        throw std::out_of_range("Index out of range");
    return adj[index];
}

int Graph::size(){
    return adj.size();
}

int Graph::size_adj(int node){
    return adj[node].size();
}

void Graph::add_edge(int f_node, int s_node){
        f_node--;
        s_node--;

        adj[f_node].push_back(s_node);
        adj[s_node].push_back(f_node);
        sort(adj[f_node].begin(), adj[f_node].end());
        sort(adj[s_node].begin(), adj[s_node].end());
        adj[f_node].erase(unique(adj[f_node].begin(), adj[f_node].end()), adj[f_node].end());
        adj[s_node].erase(std::unique(adj[s_node].begin(), adj[s_node].end()), adj[s_node].end());
}

void Graph::print_graph(){
    system("clear");
    cout << "Matricula       Grau" << endl;
    for(int i = 0; i < adj.size(); i++){
        cout << "map: " << mat_map[i] << " v: " << i << endl;
        cout << "   |--->";
        for(int j = 0; j < adj[i].size(); j++){
            cout << " e: " << adj[i][j]+1;
        }
        cout << endl;
    }
}

vector<int> Graph::intersection(vector<int> A, vector<int> B){
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

vector<int> Graph::uniom(vector<int> A, int a){
    A.push_back(a);
    return A;
}

void Graph::bron_kerbosch(vector<int> R, vector<int> P, vector<int> X){
	if(P.empty() && X.empty()){
		if(R.size() == 5){
			Maximal = R;
		}
		if(R.size() > Maximo.size()){
			Maximo = R;
		}
        return;
	}
	for(int i = 0; i < P.size();i++){

    	bron_kerbosch(uniom(R, P[i]), intersection(P, adj[P[i]]), intersection(X, adj[P[i]]));
    	P.erase(P.begin() + i);
    	X.push_back(P[i]);
	}
}

bool compare_by_size(iv a, iv b) {
    return (a.second.size() < b.second.size());
}

void Graph::print_vertices_size(){
    priority_queue<iv ,vector<iv>, function<bool(iv, iv)>> pq(compare_by_size);
    for(int i = 0; i < adj.size(); i++){
        pq.push(make_pair(i, adj[i]));
    }
    while(not pq.empty()){
        cout << mat_map[pq.top().first] << " --> " << pq.top().second.size() << endl;
        pq.pop();
    }
}

int menu(Graph &g){
    int a;
    while(a != 3){
        system("cls || clear");
        cout << "|------------------------Menu--------------------------|\n";
        cout << "|1 - Matriculas e seus graus                           |\n";
        cout << "|2 - Imprimir clique maximal e maximo                  |\n";
        cout << "|3 - Sair do Programa                                  |\n";
        cout << "|                                                      |\n";
        cout << "|--- A vizualizacao do grafo esta disponivel no arquivo|\n";
        cout << "|--- graph.html que está dentro da pasta do trabalho.--|\n";
        cout << "|                                                      |\n";
        cout << "|+++++NAO ESQUECA DE LER O ARQUVO LEIA-ME ANTES.txt++++|\n";
        cout << "--------------------------------------------------------\n";

        cin >> a;
        if(a == 1){
            g.print_vertices_size();

            cout << "Aperte <enter> para voltar ao menu\n";
            getchar();
            getchar();
        }

        if(a == 2){
            vector<int> P, R, X;
            for(int i = 0; i < 49; i++){
            	P.push_back(i);
            }
            g.bron_kerbosch(R, P, X);
            /*cout << Maximo.size() <<endl;
            cout << Maximal.size() <<endl;*/
            cout << "----CLIQUE MAXIMAL DE TAMANHO 5----- " << endl;
            cout << "Matriculas dos vertices: ";
 			for(int i = 0; i < Maximal.size(); i++){
 				cout<< mat_map[Maximal[i]]<<", ";
 			}
 			cout<<endl;
            cout << "Numero dos vertices: ";
            for(int i = 0; i < Maximal.size(); i++){
                cout<< Maximal[i]+1 <<", ";
            }
            cout << "\n" <<endl;
            cout << "----CLIQUE MAXIMO DO GRAFO----- " << endl;
            cout << "Matriculas dos vertices: ";
 			for(int i = 0; i < Maximo.size(); i++){
 				cout<< mat_map[Maximo[i]]<<", ";
 			}
            cout<<endl;
            cout << "Numero dos vertices: ";
 			for(int i = 0; i < Maximo.size(); i++){
 				cout<< Maximo[i]+1 <<", ";
 			}
            cout << "\n" << endl;
            cout << "Aperte <enter> para voltar ao menu\n";
            getchar();
            getchar();
        }
    }
}

void process_line(string &line, Graph &g, int indice){
    int cont = 0, j = 0;
    string aux;
    for(int i = 0; line[i] != '\0'; i++){

        if(line[i] == '#'){
            string aux2(2, 0);
            aux[j] = '\0';
            if(cont < 1) mat_map[indice-1] = aux;
            if(cont >= 1){
                aux2[0] = aux[0], aux2[1] = aux[1];
                int vert = stoi(aux2);
                g.add_edge(indice, vert);
                js_fl << "g.addEdge(\"" << to_string(indice) << "\",\"" << to_string(vert) << "\");\n";
            }
            j = 0;
            aux.clear();
            if(line[i+1] == '\0') continue;
            i++;
            cont++;
        }
        aux.push_back(line[i]);
        j++;
    }
}

int main(){
    int a = 49;
    Graph g(a);
    int indice = 1;
    string line;
    ifstream mat_fl;

    js_fl.open("graph.js", fstream::out | fstream::trunc);
    mat_fl.open("amigos_tag20172.txt", fstream::in);

    js_fl << "$(document).ready(function() {\n";
    js_fl << "var width = $(document).width();\n";
    js_fl << "var height = $(document).height();\n";
    js_fl << "var render = function(r, n) {var set = r.set().push(r.rect(n.point[0]-5, n.point[1]-15, 10, 10).attr({\"fill\": \"#F00\", r : \"12px\", \"stroke-width\" : n.distance == 0 ? \"1px\" : \"1px\" })).push(r.text(n.point[0], n.point[1] + 10, (n.label || n.id)));return set;};\n";
    js_fl << "var g = new Graph();\n";
    js_fl << "g.edgeFactory.template.style.directed = false;\n";


    for(int i = 1; i <= 49; i++){
        js_fl << "g.addNode(\"" << to_string(i) << "\", {render:render});\n" ;
    }

    while(getline(mat_fl, line)){
        process_line(line, g, indice);
        indice++;
        mat_fl.sync();
    }

    menu(g);

    js_fl << "var layouter = new Graph.Layout.Spring(g);\n";
    js_fl << "var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);\n});";

    return 0;
}
