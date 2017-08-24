$(document).ready(function() {
var width = $(document).width();
var height = $(document).height();
var g = new Graph();
g.edgeFactory.template.style.directed = false;
g.addNode("1");
g.addNode("2");
g.addNode("3");
g.addNode("4");
g.addNode("5");
g.addNode("6");
g.addNode("7");
g.addNode("8");
g.addEdge("1","2");
g.addEdge("3","4");
g.addEdge("2","5");
g.addEdge("6","7");
g.addEdge("8","1");
g.addEdge("2","4");
g.addEdge("1","7");
g.addEdge("2","8");
var layouter = new Graph.Layout.Ordered(g, topological_sort(g));
var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);
});