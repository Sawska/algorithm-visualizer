#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include "TreeVisualizer.h"

class TreeVizualizer;

class GraphNode {
public:
    std::string name;
    int weight;
    std::vector<std::pair<GraphNode*, int>> edges; 

    GraphNode(std::string n, int w) : name(n), weight(w) {}
    GraphNode() : weight(0) {}
    ~GraphNode();

    void delete_node(std::string name);
    void insert_node(GraphNode* node);
    std::vector<GraphNode*> dijkstra(GraphNode* start, GraphNode* end,TreeVizualizer* visualizer);
    int minDistance(const std::vector<int>& dist, const std::vector<bool>& sptSet);
};

#endif // GRAPH_H
