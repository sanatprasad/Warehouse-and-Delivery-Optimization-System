# Warehouse-and-Delivery-Optimization-System

# Delivery Route Optimization Project (C++ with OOP)

## Project Overview

This project is designed to optimize delivery routes from multiple warehouses to customer locations (houses). It leverages **Object-Oriented Programming (OOP)** principles and graph algorithms to minimize travel distances, account for fuel constraints, and maximize truck load efficiency. The primary focus is on developing an extensible, modular design for real-world logistics optimization.

## Key Features

1. **Object-Oriented Design**: 
   - The project employs **classes and objects** to represent entities such as **Graph**, **Warehouse**, and **Truck**.
   - Abstraction and encapsulation are used to separate different functionalities like route calculation, load management, and fuel planning.

2. **Graph Representation**: 
   - Cities, warehouses, and roads are modeled using a graph data structure, where nodes represent locations and edges represent roads with weights indicating distances.

3. **OOP Concepts Applied**:
   - **Encapsulation**: Data and methods are grouped into relevant classes such as `Graph` and `Truck`.
   - **Inheritance**: Classes can be extended to introduce more specialized behaviors (e.g., different types of trucks or warehouses).
   - **Polymorphism**: Functions like `findBestRoute()` can be overridden to implement custom route-finding strategies based on fuel efficiency or shortest paths.

4. **Graph Algorithms**:
   - **Dijkstra’s Algorithm** and **Floyd-Warshall Algorithm** are implemented for finding the shortest paths between warehouses and houses.
   - These algorithms are encapsulated within the `Graph` class, providing clean separation between the graph structure and route-finding logic.

5. **Fuel and Load Optimization**:
   - Trucks have limited fuel capacities and load limits, modeled using a `Truck` class that encapsulates these constraints.
   - The project uses a **Knapsack Algorithm** to ensure trucks are loaded efficiently, balancing distance traveled with load capacity.

6. **Modular and Extensible**:
   - The project design makes it easy to extend functionality by adding more features (e.g., additional types of vehicles, dynamic route adjustments) without affecting existing code.

## Functions and OOP Concepts Explained

1. **Class Definitions**:
   - **Graph Class**:
     - Encapsulates nodes, edges, and methods like `addEdge()`, `dijkstra()`, and `floydWarshall()`.
     - **Encapsulation**: Data members (nodes, edges) are kept private and only accessible via public methods.
   - **Truck Class**:
     - Stores information like fuel capacity, load capacity, and methods for calculating fuel usage and checking load limits.
     - **Abstraction**: Trucks are abstracted as objects with fuel and load properties, allowing the user to focus on truck behaviors rather than implementation details.

2. **Graph Representation**:
   - `addEdge(int src, int dest, int weight)`: Adds a bidirectional edge between two nodes in the graph, encapsulating the connection between cities.
   - **Encapsulation** ensures that graph data (nodes, edges) is only modified via controlled methods.

3. **Dijkstra’s Algorithm**:
   - `dijkstra(int src)`: Finds the shortest path from the source warehouse to all destinations. Encapsulated within the `Graph` class, ensuring that pathfinding is a graph-specific behavior.
   - **Polymorphism**: This method can be overridden to implement other pathfinding algorithms as needed.

4. **Floyd-Warshall Algorithm**:
   - `floydWarshall()`: Encapsulates the logic for finding shortest paths between all pairs of nodes.
   - This method is part of the `Graph` class and uses encapsulation to keep graph data private, modifying it only through defined methods.

5. **Truck Load Management**:
   - `Truck::knapsack(int weight[], int value[], int capacity, int n)`: A member function of the `Truck` class that uses the knapsack algorithm to optimize truck loading.
   - **Encapsulation**: Load and capacity constraints are encapsulated within the `Truck` class, providing a clear interface for interacting with delivery vehicles.

6. **Fuel Calculation**:
   - `Truck::calculateFuel(int distance)`: Computes fuel consumption based on the distance of the route.
   - **Abstraction**: The complexity of fuel calculation is hidden behind a simple method, making it easier to use.

## Object-Oriented Design Principles

1. **Encapsulation**: Each entity (Graph, Truck, etc.) is encapsulated into its own class, with clearly defined interfaces (methods) to interact with them.
   
2. **Abstraction**: Complex logic like pathfinding and fuel calculations is abstracted behind simple method calls. Users interact with high-level concepts without needing to understand the inner workings.

3. **Inheritance**: The project can easily be extended with different types of trucks or warehouses by inheriting and overriding base class methods.

4. **Polymorphism**: Functions like `findBestRoute()` can be overridden to introduce new routing strategies, allowing flexible and scalable design.

## How to Use

1. Clone the repository.
   ```bash
   git clone <repo-url>
ks are loaded efficiently, balancing distance traveled with load capacity.
Modular and Extensible:

The project design makes it easy to extend functionality by adding more features (e.g., additional types of vehicles, dynamic route adjustments) without affecting existing code.
Functions and OOP Concepts Explained:
Class Definitions:

Graph Class:
Encapsulates nodes, edges, and methods like addEdge(), dijkstra(), and floydWarshall().
Encapsulation: Data members (nodes, edges) are kept private and only accessible via public methods.
Truck Class:
Stores information like fuel capacity, load capacity, and methods for calculating fuel usage and checking load limits.
Abstraction: Trucks are abstracted as objects with fuel and load properties, allowing the user to focus on truck behaviors rather than implementation details.
Graph Representation:

addEdge(int src, int dest, int weight): Adds a bidirectional edge between two nodes in the graph, encapsulating the connection between cities.
Encapsulation ensures that graph data (nodes, edges) is only modified via controlled methods.
Dijkstra’s Algorithm:

dijkstra(int src): Finds the shortest path from the source warehouse to all destinations. Encapsulated within the Graph class, ensuring that pathfinding is a graph-specific behavior.
Polymorphism: This method can be overridden to implement other pathfinding algorithms as needed.
Floyd-Warshall Algorithm:

floydWarshall(): Encapsulates the logic for finding shortest paths between all pairs of nodes.
This method is part of the Graph class and uses encapsulation to keep graph data private, modifying it only through defined methods.
Truck Load Management:

Truck::knapsack(int weight[], int value[], int capacity, int n): A member function of the Truck class that uses the knapsack algorithm to optimize truck loading.
Encapsulation: Load and capacity constraints are encapsulated within the Truck class, providing a clear interface for interacting with delivery vehicles.
Fuel Calculation:

Truck::calculateFuel(int distance): Computes fuel consumption based on the distance of the route.
Abstraction: The complexity of fuel calculation is hidden behind a simple method, making it easier to use.
Object-Oriented Design Principles:
Encapsulation: Each entity (Graph, Truck, etc.) is encapsulated into its own class, with clearly defined interfaces (methods) to interact with them.

Abstraction: Complex logic like pathfinding and fuel calculations is abstracted behind simple method calls. Users interact with high-level concepts without needing to understand the inner workings.

Inheritance: The project can easily be extended with different types of trucks or warehouses by inheriting and overriding base class methods.

Polymorphism: Functions like findBestRoute() can be overridden to introduce new routing strategies, allowing flexible and scalable design.

How to Use:
Clone the repository.
bash
Copy code
git clone <repo-url>
Compile the code using g++ or any C++ compiler.
bash
Copy code
g++ DeliveryOptimization.cpp -o DeliveryOptimization
Run the executable and provide the required inputs (number of warehouses, roads, fuel, load, etc.).
bash
Copy code
./DeliveryOptimization
