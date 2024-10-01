#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

const int INF = INT_MAX;  // Infinity constant to represent unreachable nodes

// Class to handle Floyd-Warshall Algorithm
class RouteOptimizer {
private:
    int numLocations;
    vector<vector<int>> distanceMatrix;

public:
    RouteOptimizer(int n) : numLocations(n) {
        distanceMatrix.resize(n, vector<int>(n, INF));

        // Set the diagonal to 0 because the distance to the same node is 0
        for (int i = 0; i < n; i++) {
            distanceMatrix[i][i] = 0;
        }
    }

    // Function to add a road between two nodes with a certain distance
    void addRoad(int u, int v, int dist) {
        distanceMatrix[u][v] = dist;
        distanceMatrix[v][u] = dist;  // Assuming it's a bidirectional road
    }

    // Floyd-Warshall algorithm to calculate shortest paths
    void calculateShortestPaths() {
        for (int k = 0; k < numLocations; k++) {
            for (int i = 0; i < numLocations; i++) {
                for (int j = 0; j < numLocations; j++) {
                    if (distanceMatrix[i][k] != INF && distanceMatrix[k][j] != INF &&
                        distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j]) {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    }
                }
            }
        }
    }

    // Function to get the shortest distance between two locations
    int getShortestDistance(int u, int v) {
        return distanceMatrix[u][v];
    }

    // Function to print the shortest path distance matrix
    void printShortestPaths() {
        for (int i = 0; i < numLocations; i++) {
            for (int j = 0; j < numLocations; j++) {
                if (distanceMatrix[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << distanceMatrix[i][j] << " ";
                }
            }
            cout << endl;
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
    int numLocations = 4;
    RouteOptimizer routeOptimizer(numLocations);

    // Adding roads between locations (u, v) with distances
    routeOptimizer.addRoad(0, 1, 4);
    routeOptimizer.addRoad(1, 2, 5);
    routeOptimizer.addRoad(0, 2, 10);
    routeOptimizer.addRoad(2, 3, 3);

    // Calculate shortest paths
    routeOptimizer.calculateShortestPaths();
    cout << "Shortest paths between all locations:\n";
    routeOptimizer.printShortestPaths();

    // Example setup for CargoOptimizer
    int vanCapacity = 50;  // Capacity of the van
    CargoOptimizer cargoOptimizer(vanCapacity);

    vector<int> packages = {20, 10, 15, 5, 8};  // List of package sizes

    // Maximize cargo space
    int packagesLoaded = cargoOptimizer.maximizeCargoSpace(packages);
    cout << "Number of packages loaded: " << packagesLoaded << endl;

    return 0;
}
