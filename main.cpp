#include "adjacencyList.h"
#include <unordered_set>
#include <stack>

std::string findMinDist(std::forward_list<std::string>& unvisited, std::unordered_map<std::string, dijkstrasElement>& table);
void dijkstrasAlgo(adjacencyList& adjList, std::unordered_set<std::string>& visited, std::forward_list<std::string>& unvisited, std::unordered_map<std::string, dijkstrasElement>& table);
std::stack<std::string>&& shortestRoute(std::string start, std::string end, std::unordered_map<std::string, dijkstrasElement>& table);

int main () {
    std::string filename = "json/stations.json";
    adjacencyList adjList(filename);

    std::string start = "Sungai Nibong";
    std::string end = "Simpang Ampat";

    std::unordered_set<std::string> visited;
    
    auto unvisited = adjList.copyUnvisited();
    auto table = adjList.makeTable(start);

    dijkstrasAlgo(adjList, visited, unvisited, table);
    auto route = shortestRoute(start, end, table);

    std::cout << "From " << start << " to " << end << std::endl;
    while(!route.empty()) {
        std::cout << route.top() << ( (route.size() > 1) ? " -> " : ""); 
        route.pop();
    }

    std::cout << std::endl << "Total arbitrary distance: " << table[end].shortestDist << "km" << std::endl;
}

std::string findMinDist(std::forward_list<std::string>& unvisited, std::unordered_map<std::string, dijkstrasElement>& table) {
    int min = INT_MAX;
    std::string minStation;
    for(auto& stations : unvisited) {
        int curr = table[stations].shortestDist;
        if(curr < min) {
            min = curr;
            minStation = stations;
        }
    }
    return minStation;
}

void dijkstrasAlgo(adjacencyList& adjList, std::unordered_set<std::string>& visited, std::forward_list<std::string>& unvisited, std::unordered_map<std::string, dijkstrasElement>& table) {
    while(!unvisited.empty()) {
        std::string currStation = findMinDist(unvisited, table);
        int currDistance = table[currStation].shortestDist;
        auto neighbours = adjList.getConnectionList(currStation);
        
        // if unvisited and has a shorter distance, update table
        for(auto& [neighbour, distance] : neighbours) {
            int currSum = currDistance + distance;
            if (visited.find(neighbour) == visited.end() && currSum < table[neighbour].shortestDist) { 
                table[neighbour].shortestDist = currSum;
                table[neighbour].prevStation = currStation;
            }
        }
        unvisited.remove(currStation);
        visited.insert(currStation);
    }
}

std::stack<std::string>&& shortestRoute(std::string start, std::string end, std::unordered_map<std::string, dijkstrasElement>& table) {
    auto shortestPath = new std::stack<std::string>;

    std::string currStation = end;
    while (currStation != start) {
        shortestPath->push(currStation);
        currStation = table[currStation].prevStation;
    }
    shortestPath->push(start);
    return std::move(*shortestPath);
}