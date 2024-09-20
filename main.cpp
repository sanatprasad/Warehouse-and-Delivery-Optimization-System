#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int V = 50;  // Maximum number of nodes

// Comparator for sorting items based on weight
bool comp(pair<int, int>& a, pair<int, int>& b) {
    return a.second < b.second;
}

class DeliveryGraph {
public:
    vector<pair<int, int>> adj[V];
    vector<vector<int>> dist;

    DeliveryGraph() {
        dist = vector<vector<int>>(V, vector<int>(V, 1e7));
    }

    // Initialize distances for Floyd-Warshall algorithm
    void initializeDistances() {
        for (int i = 0; i < V; i++) {
            for (auto adjNode : adj[i]) {
                dist[i][adjNode.first] = adjNode.second;
            }
        }

        // Self-loop distance = 0
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
        }
    }

    // Floyd-Warshall Algorithm to calculate shortest paths
    void floydWarshall() {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j] &&
                        dist[i][k] != 1e7 && dist[k][j] != 1e7) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Shortest path using Dijkstra's algorithm
    vector<int> shortestPath(int srcNode, int destNode) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> distance(V, 1e9), parent(V);

        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        distance[srcNode] = 0;
        pq.push({0, srcNode});

        while (!pq.empty()) {
            int node = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            for (auto adjNode : adj[node]) {
                int nextNode = adjNode.first;
                int edgeWeight = adjNode.second;

                if (dist + edgeWeight < distance[nextNode]) {
                    distance[nextNode] = dist + edgeWeight;
                    pq.push({distance[nextNode], nextNode});
                    parent[nextNode] = node;
                }
            }
        }

        if (distance[destNode] == 1e9)
            return {-1};

        vector<int> path;
        int node = destNode;
        while (parent[node] != node) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(srcNode);
        reverse(path.begin(), path.end());
        return path;
    }
};

class WarehouseSystem {
    vector<int> warehouses;
    vector<int> gasStations;
    DeliveryGraph graph;
    int tankCapacity;
    
public:
    WarehouseSystem(vector<int> wh, vector<int> gs, int capacity) 
        : warehouses(wh), gasStations(gs), tankCapacity(capacity) {}

    // Select the best warehouse based on proximity to houses
    int selectWarehouse(const vector<pair<int, int>>& houses) {
        vector<pair<int, int>> warehouseDistances;

        for (auto house : houses) {
            int closestWarehouse = -1;
            int minDistance = 1e7;

            for (auto warehouse : warehouses) {
                if (graph.dist[warehouse][house.first] < minDistance) {
                    minDistance = graph.dist[warehouse][house.first];
                    closestWarehouse = warehouse;
                }
            }
            warehouseDistances.push_back({closestWarehouse, minDistance});
        }

        vector<int> warehouseCount(warehouses.size(), 0);
        for (auto wd : warehouseDistances) {
            for (int i = 0; i < warehouses.size(); i++) {
                if (wd.first == warehouses[i]) {
                    warehouseCount[i]++;
                }
            }
        }

        int selectedWarehouse = distance(warehouseCount.begin(), max_element(warehouseCount.begin(), warehouseCount.end()));
        return warehouses[selectedWarehouse];
    }

    // Knapsack algorithm to select items to load in van
    vector<pair<int, int>> packageItems(vector<pair<int, int>>& items, int capacity) {
        sort(items.begin(), items.end(), comp);

        vector<pair<int, int>> selectedItems;
        int currentCapacity = 0;
        for (auto item : items) {
            if (currentCapacity + item.second <= capacity) {
                selectedItems.push_back(item);
                currentCapacity += item.second;
            }
        }
        return selectedItems;
    }

    // Calculate total distance for delivery
    int totalDistance(vector<pair<int, int>>& deliveries) {
        int totalDistance = 0;
        int currentWarehouse = selectWarehouse(deliveries);

        for (auto delivery : deliveries) {
            totalDistance += graph.dist[currentWarehouse][delivery.first];
            currentWarehouse = delivery.first;
        }

        return totalDistance;
    }

    // Find nearest gas station
    int findNearestGasStation(int node) {
        int minDistance = 1e9;
        int gasStationID = -1;

        for (int gs : gasStations) {
            if (graph.dist[node][gs] < minDistance) {
                minDistance = graph.dist[node][gs];
                gasStationID = gs;
            }
        }

        return gasStationID;
    }

    // Print delivery path with refueling stops
    void printDeliveryPath(vector<pair<int, int>>& deliveries) {
        int currentWarehouse = selectWarehouse(deliveries);
        int totalDistance = totalDistance(deliveries);
        int remainingFuel = tankCapacity;

        cout << "Starting from warehouse " << currentWarehouse << endl;

        for (auto delivery : deliveries) {
            vector<int> path = graph.shortestPath(currentWarehouse, delivery.first);

            for (int i = 0; i < path.size() - 1; i++) {
                if (remainingFuel - graph.dist[path[i]][path[i + 1]] <= 0) {
                    int gasStation = findNearestGasStation(path[i]);
                    cout << "Refueling at gas station " << gasStation << endl;
                    totalDistance += graph.dist[path[i]][gasStation] + graph.dist[gasStation][path[i + 1]];
                    remainingFuel = tankCapacity;
                }
                remainingFuel -= graph.dist[path[i]][path[i + 1]];
                cout << path[i] << " -> ";
            }
            cout << delivery.first << endl;
            currentWarehouse = delivery.first;
        }

        cout << "Total Distance Covered: " << totalDistance << endl;
    }
};

int main() {
    vector<int> warehouses = {1, 48, 29, 36};
    vector<int> gasStations = {25, 17, 27, 38};
    int tankCapacity = 250;

    WarehouseSystem system(warehouses, gasStations, tankCapacity);

    // Example deliveries (node, package weight)
    vector<pair<int, int>> deliveries = {{2, 50}, {3, 75}, {4, 100}};

    system.printDeliveryPath(deliveries);

    return 0;
}
