#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <functional>

using namespace std;

const int INF = INT_MAX;  // Infinity constant to represent unreachable nodes

// Class to handle Dijkstra's Algorithm
class RouteOptimizer {
private:
    int numLocations;
    vector<vector<pair<int, int>>> adjList;  // Adjacency list to store graph (node, weight)

public:
    RouteOptimizer(int n) : numLocations(n) {
        adjList.resize(n);
    }

    // Function to add a road between two nodes with a certain distance
    void addRoad(int u, int v, int dist) {
        adjList[u].push_back({v, dist});
        adjList[v].push_back({u, dist});  // Assuming it's a bidirectional road
    }

    // Dijkstra's algorithm to calculate shortest paths from a single source
    vector<int> calculateShortestPaths(int source) {
        vector<int> dist(numLocations, INF);
        dist[source] = 0;

        // Min-heap priority queue to pick the node with the smallest distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // If the current distance is greater than the already found shortest distance, skip
            if (currDist > dist[u]) continue;

            // Explore neighbors of node u
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // Function to print the shortest distances from a source to all other locations
    void printShortestPaths(int source, const vector<int>& distances) {
        for (int i = 0; i < numLocations; i++) {
            if (distances[i] == INF) {
                cout << "Distance from location " << source << " to " << i << ": INF" << endl;
            } else {
                cout << "Distance from location " << source << " to " << i << ": " << distances[i] << " units" << endl;
            }
        }
    }
};

// Greedy class to maximize cargo space utilization
class CargoOptimizer {
private:
    int vanCapacity;

public:
    CargoOptimizer(int capacity) : vanCapacity(capacity) {}

    // Function to optimize cargo placement using a greedy approach
    int maximizeCargoSpace(vector<int> &packages) {
        // Sort the packages in descending order of size
        sort(packages.begin(), packages.end(), greater<int>());
        
        int usedCapacity = 0;
        int packagesLoaded = 0;

        for (int package : packages) {
            if (usedCapacity + package <= vanCapacity) {
                usedCapacity += package;
                packagesLoaded++;
            } else {
                break;  // Stop when the van is full
            }
        }

        return packagesLoaded;
    }
};

// Main system to handle route planning and cargo optimization
int main() {
    // Example setup for RouteOptimizer
    int numLocations = 5;  // Number of locations (nodes)
    RouteOptimizer routeOptimizer(numLocations);

    // Adding roads between locations (u, v) with distances
    routeOptimizer.addRoad(0, 1, 4);
    routeOptimizer.addRoad(0, 2, 2);
    routeOptimizer.addRoad(1, 2, 1);
    routeOptimizer.addRoad(1, 3, 7);
    routeOptimizer.addRoad(2, 3, 3);
    routeOptimizer.addRoad(3, 4, 1);

    // Calculate shortest paths from source (e.g., location 0)
    int source = 0;
    vector<int> shortestPaths = routeOptimizer.calculateShortestPaths(source);

    // Print the shortest paths from source to all other locations
    cout << "Shortest paths from location " << source << ":\n";
    routeOptimizer.printShortestPaths(source, shortestPaths);

    // Example setup for CargoOptimizer
    int vanCapacity = 50;  // Capacity of the van
    CargoOptimizer cargoOptimizer(vanCapacity);

    vector<int> packages = {20, 10, 15, 5, 8};  // List of package sizes

    // Maximize cargo space
    int packagesLoaded = cargoOptimizer.maximizeCargoSpace(packages);
    cout << "\nNumber of packages loaded: " << packagesLoaded << endl;

    return 0;
}
