#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <string>
#include <vector>
#include <limits.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Connection {
    std::string stationName;
    int distance;
};

struct dijkstrasElement {
    int shortestDist;
    std::string prevStation;
};

typedef std::forward_list<Connection> connectionList;

class adjacencyList {
public:
    adjacencyList(std::string filename);
    std::forward_list<std::string>&& copyUnvisited();
    std::unordered_map<std::string, dijkstrasElement>&& makeTable(std::string start);
    connectionList& getConnectionList(std::string station);
    ~adjacencyList();
private:
    int size = 0;
    std::unordered_map<std::string, connectionList> adjList;
    std::string* unvisited;
    std::string* visited;
    void initStation(std::string& station);
    void initUnvisited();
};

#endif