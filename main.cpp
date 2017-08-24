#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;

class Graph{
    private:
        vector<vector<int>> adj;
    public:
        void add_node(int node); // add a node
        void add_edge(int node1, int node2); // add
        int size();
};

int Graph::size(){
    return adj.size();
}

int Graph::size_adj(int node){
    return adj[node].size();
}

void Graph::add_edge(int f_node, int s_node){
        adj[f_node].push_back(s_node);
        adj[s_node].push_back(f_node);
    }
}

int main(){

    Graph g;

    int a = 1;
    g.add_node(a);

    fstream js_fl;
    js_fl.open("graph.js", fstream::out | fstream::trunc);

    js_fl << "$(document).ready(function() {\n";
    js_fl << "var width = $(document).width();\n";
    js_fl << "var height = $(document).height();\n";
    js_fl << "var g = new Graph();\n";
    js_fl << "g.edgeFactory.template.style.directed = false;\n";
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        js_fl << "g.addNode(\"" << to_string(i) << "\");\n" ;
    }
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        js_fl << "g.addEdge(\"" << to_string(a) << "\",\"" << to_string(b) << "\");\n";
    }

    js_fl << "var layouter = new Graph.Layout.Ordered(g, topological_sort(g));\n";
    js_fl << "var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);\n});";

    return 0;
}
