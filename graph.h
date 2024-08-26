#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include "TreeVisualizer.h"

class TreeVizualizer;

#include <memory>  

class GraphNode {
public:
    std::string name;
    int weight;
    std::vector<std::pair<std::unique_ptr<GraphNode>, int>> edges; 

    GraphNode(std::string n, int w) : name(n), weight(w) {}
    GraphNode() : weight(0) {}
    ~GraphNode() = default;

    void delete_node(const std::string& name);
    void insert_node(std::unique_ptr<GraphNode> node);
    std::vector<GraphNode*> dijkstra(GraphNode* start, GraphNode* end, TreeVizualizer* visualizer);
    int minDistance(const std::vector<int>& dist, const std::vector<bool>& sptSet);
};




#endif // GRAPH_H
