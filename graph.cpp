#include "graph.h"
#include "TreeVisualizer.h"




void GraphNode::delete_node(const std::string& name) {
    auto it = std::remove_if(edges.begin(), edges.end(), [&](std::pair<std::unique_ptr<GraphNode>, int>& edge) {
        return edge.first->name == name;
    });
    edges.erase(it, edges.end());
}

void GraphNode::insert_node(std::unique_ptr<GraphNode> node) {
    edges.push_back(std::make_pair(std::move(node), node->weight));
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
        dist[edge.first.get()] = std::numeric_limits<int>::max();
        unvisited.push_back(edge.first.get());
    }
    dist[start] = 0;

    while (!unvisited.empty()) {

        
        GraphNode* current = *std::min_element(unvisited.begin(), unvisited.end(),
                                               [&dist](GraphNode* lhs, GraphNode* rhs) {
                                                   return dist[lhs] < dist[rhs];
                                               });

        
        visualizer->drawGraph(current, 0, 0, 10, 10, 0x00FF00);
        glfwSwapBuffers(visualizer->window);
        visualizer->delay(0.5f); 

        if (current == end) break;

        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());

        
        for (auto& neighbor : current->edges) {
            int alt = dist[current] + neighbor.second;
            if (alt < dist[neighbor.first.get()]) {
                dist[neighbor.first.get()] = alt;
                previous[neighbor.first.get()] = current;

                
                visualizer->drawGraph(neighbor.first.get(), 0, 0, 10, 10, 0x0000FF);
                glfwSwapBuffers(visualizer->window);
                visualizer->delay(0.5f);
            }
        }
        
    
        visualizer->drawGraph(current, 0, 0, 10, 10, 0xFFFFFF);  
        glfwSwapBuffers(visualizer->window);
    }

    
    std::vector<GraphNode*> path;
    for (GraphNode* at = end; at != nullptr; at = previous[at]) {
        path.insert(path.begin(), at);
    }


    for (auto node : path) {
        visualizer->drawGraph(node, 0, 0, 10, 10, 0xFF0000);  
        glfwSwapBuffers(visualizer->window);
        visualizer->delay(0.5f);
    }

    return path;
}

