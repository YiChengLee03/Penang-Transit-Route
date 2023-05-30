#include "adjacencyList.h"

adjacencyList::adjacencyList(std::string filename) {
    std::ifstream file(filename);
    json json1 = json::parse(file);

    for(auto& [station, neighbours] : json1.items()) {
        std::string currentStation = station;
        initStation(currentStation);
        for(auto& neighbour : neighbours) {
            std::string name = neighbour["name"];
            int distance = neighbour["distance"];
            initStation(name);
            adjList[currentStation].push_front(Connection{name, distance});
        }
    }
    visited = new std::string[size];
    unvisited = new std::string[size];
    initUnvisited();
}

std::forward_list<std::string>&& adjacencyList::copyUnvisited() {
    auto list = new std::forward_list<std::string>;
    for(int i = 0; i < size; ++i)
        list->push_front(unvisited[i]);
    return std::move(*list);
}

std::unordered_map<std::string, dijkstrasElement>&& adjacencyList::makeTable(std::string start) {
    auto table = new std::unordered_map<std::string, dijkstrasElement>;
    table->insert({start, {0, ""}});
    for(auto& [station, connection] : adjList) {
        if(station != start)
            table->insert({station, {INT_MAX, ""}});
    }
    return std::move(*table);
}

connectionList& adjacencyList::getConnectionList(std::string station) {
    return adjList[station];
}

adjacencyList::~adjacencyList() {
    delete[] visited;
    delete[] unvisited;
}

void adjacencyList::initStation(std::string& station) {
    if(adjList.find(station) == adjList.end()) {
        adjList.insert({station, {}});
        ++size;
    }
}

void adjacencyList::initUnvisited() {
    auto begin = unvisited;
    for(auto& [station, neighbours] : adjList) {
        std::string currentStation = station;
        *begin = station;
        ++begin;
    }
}