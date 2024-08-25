#include "graph.h"
#include "TreeVisualizer.h"

GraphNode::~GraphNode() {
    for (auto& edge : edges) {
        delete edge.first;  
    }
}


void GraphNode::delete_node(std::string name) {
    auto it = std::remove_if(edges.begin(), edges.end(), [&](std::pair<GraphNode*, int> edge) {
        if (edge.first->name == name) {
            delete edge.first;
            return true;
        }
        return false;
    });
    edges.erase(it, edges.end());
}

void GraphNode::insert_node(GraphNode* node) {
    edges.push_back(std::make_pair(node, node->weight));
}

int GraphNode::minDistance(const std::vector<int>& dist, const std::vector<bool>& sptSet) {
    int min = std::numeric_limits<int>::max(), min_index;

    for (int v = 0; v < dist.size(); v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

std::vector<GraphNode*> GraphNode::dijkstra(GraphNode* start, GraphNode* end, TreeVizualizer* visualizer) {
    std::unordered_map<GraphNode*, int> dist;
    std::unordered_map<GraphNode*, GraphNode*> previous;
    std::vector<GraphNode*> unvisited;

    
    for (auto& edge : edges) {
        dist[edge.first] = std::numeric_limits<int>::max();
        unvisited.push_back(edge.first);
    }
    dist[start] = 0;

    while (!unvisited.empty()) {
        
        GraphNode* current = *std::min_element(unvisited.begin(), unvisited.end(),
                                               [&dist](GraphNode* lhs, GraphNode* rhs) {
                                                   return dist[lhs] < dist[rhs];
                                               });

       
        visualizer->drawGraph(current, 0, 0, 10, 10, 0x00FF00);  

        if (current == end) break;

        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());

       
        for (auto& neighbor : current->edges) {
            int alt = dist[current] + neighbor.second;  
            if (alt < dist[neighbor.first]) {
                dist[neighbor.first] = alt;
                previous[neighbor.first] = current;


                visualizer->drawGraph(neighbor.first, 0, 0, 10, 10, 0x0000FF);  
            }
        }
    }


    std::vector<GraphNode*> path;
    for (GraphNode* at = end; at != nullptr; at = previous[at]) {
        path.insert(path.begin(), at);
    }


    for (auto node : path) {
        visualizer->drawGraph(node, 0, 0, 10, 10, 0xFF0000);
    }

    return path;
}
