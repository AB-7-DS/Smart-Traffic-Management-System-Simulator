

# 🚦 Smart Traffic Management System

## 📖 Overview

The **Smart Traffic Management System** is a practical project designed to replicate real-world traffic management in a city.It is a dynamic traffic management system designed to simulate a city's road network. The system supports essential functionalities like managing intersections, displaying traffic statuses, handling blocked and under-repair roads, and routing vehicles through the network.

---

# ✨ Features

## Graph Representation:
- Represent the city's road network as a directed graph with intersections as vertices and roads as edges.
- Support for dynamic graph updates, including adding and removing vertices and edges.

## Interactive Dashboard:
- **Interactive Console Menu** for users to manage the simulation and handle operations, including:
  - Display the traffic network in the form of an adjacency list.
  - Block, unblock, or mark roads as under repair dynamically.
  - Handle emergency and regular vehicle routing.
  - Manage traffic lights.

## Blocked and Under-Repair Roads:
- Mark roads as blocked or under repair, and ensure routing algorithms respect these road statuses.
- Dynamic updates on road conditions with real-time display of blocked and under-repair roads.

## Pathfinding Algorithms:
- **Dijkstra's Algorithm**: Find and display the shortest path between two intersections while considering road conditions.
- **Breadth-First Search (BFS)** / **Depth-First Search (DFS)**: Explore all possible paths between two intersections, regardless of road conditions.
- **Traffic-Aware Pathfinding**: Automatically account for road closures, repairs, or accidents when calculating paths.

## Congestion Monitoring:
- Real-time tracking of traffic congestion based on the number of vehicles in different areas of the city.
- Congestion status can be displayed and updated based on vehicle movement and road conditions.

## Emergency Vehicle Routing:
- Prioritize emergency vehicles (e.g., ambulances, fire trucks) in the traffic system, enabling faster and safer paths during emergencies.
- Dynamically reroute emergency vehicles, bypassing congested or blocked areas for optimal response times.
- Handle special **emergency vehicle routing** algorithms that factor in road conditions and vehicle priorities.

## Traffic Lights Management:
- Control **traffic light timings** for intersections, allowing dynamic adjustments to optimize traffic flow.
- Traffic light status can be updated manually or automatically based on real-time congestion and vehicle movement data.
- Integration with vehicle routing to ensure that traffic lights are synchronized with the flow of traffic.

## CSV Data Support:
- Load **road network** and **road closure** data from **CSV files** for seamless integration with real-world data or simulation updates.
- Support for importing and exporting traffic data to facilitate further analysis or reporting.

## Vehicle Simulation:
- Simulate the movement of **regular vehicles** and **emergency vehicles** across the road network.
- Dynamic vehicle routing that adapts to road conditions and traffic management settings.
- Track and manage vehicle attributes such as **speed**, **position**, and **destination**.

## Real-Time Data Updates:
- Monitor and update road conditions, vehicle positions, and other relevant data in real-time to reflect the current status of the simulation.
- Provides users with an up-to-date view of the simulation as it evolves.


---

## 🛠️ Setup Instructions



## Prerequisites

- A **C++ compiler** supporting **C++11** or later (e.g., GCC/Clang/MSVC).
- **SFML 2.61** (Simple and Fast Multimedia Library) installed.
- **Make** installed for building the project.
- A **terminal** or **IDE** (e.g., VSCode, CLion) for compilation and execution.
- Run this in ubunbu for visualization and sfml (preferrable).If you wan to use this in Windows then comment the visual part of download specific version of sfml and change a code for it.
## Step-by-Step Setup

### 1. Clone the GitHub Repository

Open a terminal and run the following command to clone the repository:

```bash
git clone https://github.com/your-username/your-repository-name.git
cd your-repository-name

```

### 2. Install SFML 2.61

Make sure SFML 2.61 is installed on your system. Follow the installation instructions for your operating system:

#### For Ubuntu :

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

### 3. Ensure Make is installed

Make sure that Make is installed on your machine. If not, install it:

#### For Ubuntu :

```bash
sudo apt-get install build-essential
```
### 4. Build the Project Using Make

Navigate to your project directory in the terminal, where the Makefile is located, and run:

#### For Ubuntu :

```bash
make
```

### 5. Run the Program

Once the project is compiled, run the program with:

#### For Ubuntu :

```bash
g++ main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
 ./sfml-app
```


## Class Diagram

```mermaid
classDiagram
    class Vertex {
        +string name
        +EdgeNode* edges
        +Vertex(string name)
    }

    class Edge {
        +Vertex* destination
        +int travelTime
        +bool blocked
        +bool underRepaired
        +isBlocked() bool
        +setBlocked(bool status)
        +isUnderRepaired() bool
        +setUnderRepaired(bool status)
        +Edge(Vertex* destination, int travelTime)
    }

    class EdgeNode {
        +Edge* edge
        +EdgeNode* next
        +EdgeNode(Edge* edge)
    }

    class VertexNode {
        +Vertex* vertex
        +VertexNode* next
        +VertexNode(Vertex* vertex)
    }

    class Graph {
        +VertexNode* headVertex
        +addVertex(string name)
        +findVertex(string name)
        +addEdge(string start, string end, int travelTime)
        +loadRoadData(string filename)
        +displayRoadStatuses()
        +markEdgeAsBlocked(string intersection1, string intersection2, bool isBlocked)
        +markEdgesAsUnderRepaired(string intersection1, string intersection2, bool isUnderRepaired)
        +displayBlockedEdges()
        +addEdgeToVertex(Vertex* vertex, Edge* edge)
        +printAdjacencyList()
        +isBlocked(string nodeName1, string nodeName2)
        +getNeighbors(string nodeName, string* neighbors, int& count)
        +getEdgeWeight(string start, string end)
        +getVertices(string* vertices, int& count)
        +getVertexCount()
        +getAllEdges(string edges[][3], int& count)
    }

    class Accident_roads {
        +AccidentNode* head
        +AccidentNode* underRepairHead
        +blockRoad(string start, string end, Graph& cityGraph)
        +Accident_roads()
        +~Accident_roads()
        +loadRoadData(Graph& graph)
        +markIntersectionsAsBlocked(Graph& graph, string intersection1, string intersection2, bool isBlocked)
        +displayBlockedIntersections(Graph& graph)
        +displayUnderRepairIntersections(Graph& graph)
        +displayBlockedRoads()
        +displayUnderRepairRoads()
    }

    class AccidentNode {
        +string intersection1
        +string intersection2
        +bool isBlocked
        +AccidentNode* next
        +AccidentNode(string i1, string i2, bool blocked)
    }

    class CongestionMaxHeap {
        +RoadNode* root
        +inorder(RoadNode* root)
        +CongestionMaxHeap()
        +makeHeap(RoadNode* hashTableArray, int size)
        +insert(RoadNode* newNode)
        +heapifyUp(RoadNode*& newNode)
        +printHeap()
        +mostCongested() RoadNode*
        +inorder()
        +heapifyDown(RoadNode* node)
    }

    class CongestionMonitoring {
        +const int hashTableSize
        +RoadNode hashTable[HASH_TABLE_SIZE]
        +CongestionMonitoring(Vehicle* vehiclesHead)
        +makeHashTable(Vehicle* vehiclesHead)
        +updateHashTable(Vehicle* prevPos, Vehicle* currentPos)
        +printHashTable()
        +deleteTable()
        +findRoadNode(char start, char end)
        +getTravelTime(char start, char end, int prevTime) int
        +getTravelTime(char start, char end, Graph& cityGraph) int
        +numberOfCongestionEvents()
    }

    class RoadNode {
        +char start
        +char end
        +int congestionCount
    }

    class Vehicles {
        +Vehicle* head
        +Vehicles()
        +~Vehicles()
        +insertAtHead(string VehicleID, string startIntersection, string endIntersection, string priorityLevel)
        +enqueue(string VehicleID, string startIntersection, string endIntersection, string priorityLevel)
        +insertAfterPosition(int position, string VehicleID, string startIntersection, string endIntersection, string priorityLevel)
        +insertAfterID(string ID, string VehicleID, string startIntersection, string endIntersection, string priorityLevel)
        +deleteAtStart()
        +deleteAtEnd()
        +deleteAtIndex(int position)
        +deleteAtID(string ID)
        +isEmpty()
        +printVehicles()
        +findIDInVehicles(string vehicleID)
        +loadAndReadCSVs()
        +getHead()
        +addPaths(GPS& gps)
    }

    class Vehicle {
        +string vehicleID
        +string startIntersection
        +string endIntersection
        +string priorityLevel
        +string* path
        +int currentIntersectionInPath
        +int pathLength
        +bool presetPath
        +Vehicle* next
        +Vehicle(string vehicleID, string startIntersection, string endIntersection, string priorityLevel)
        +moveForward(string nextIntersectionId = "")
        +printVehicle()
        +setPath(string path)
        +printPath()
    }

    class TrafficSignal {
        +string state
        +int transitionTime
        +char intersectionId
        +int duration
        +TrafficSignal* next
        +TrafficSignal(string state = "red", char intersectionId = '-', int duration = 60, int transitionTime = 5)
        +getState() string
        +setState(string state)
        +display()
        +print()
        +getIntersectionId() int
        +getDuration() int
        +getTransitionTime() int
        +advanceState()
    }

    class TrafficLightManagement {
        +TrafficSignal* headSignal
        +TrafficLightManagement()
        +makeTrafficSignals()
        +updateTrafficSignals(CongestionMonitoring& ht)
        +addSignal(TrafficSignal* signal)
        +printGreenTimes()
        +getSignal(string intersection)
    }

    class GPS {
        +Graph* graph
        +int vertexCount
        +vertexNames[MAX_VERTICES]
        +getVertexIndex(string name)
        +findAllPathsDFS(Vertex* start, Vertex* end, string path[], int pathIndex, string allPaths[][MAX_VERTICES], int& allPathsCount, bool visited[], int totalWeight[], int& totalWeightCount)
        +GPS(Graph* graph)
        +printAllPaths(string startName, string endName)
        +rerouteEmergencyVehicle(string startName, string endName)
        +getPathAsString(string startName, string endName)
        +findAllOptimalPaths(Vertex* start, Vertex* end, string path[], int pathIndex, string allPaths[][MAX_VERTICES], int& allPathsCount, bool visited[], int totalWeight[], int& totalWeightCount)
        +printAllPathsDijkstra(string startName, string endName)
    }

    class RoadQueue {
        +RoadNode* head
        +RoadNode* tail
        +RoadQueue()
        +enqueue(RoadNode*& newNode)
        +dequeue()
        +printQueue()
        +isEmpty()
    }

    Vertex "1" -- "*" EdgeNode : has
    EdgeNode "*" -- "1" Edge : contains
    VertexNode "1" -- "*" Vertex : stores
    VertexNode "*" -- "1" Graph : contains
    Graph "1" -- "*" Vertex : manages
    Accident_roads "1" -- "*" AccidentNode : manages
    AccidentNode "*" -- "1" Graph : affects
    CongestionMaxHeap "1" -- "*" RoadNode : manages
    CongestionMonitoring "1" -- "*" RoadNode : tracks
    CongestionMonitoring "*" -- "*" Vehicle : monitors
    Vehicles "1" -- "*" Vehicle : manages
    TrafficSignal "1" -- "*" Vertex : controls
    TrafficLightManagement "1" -- "*" TrafficSignal : manages
    GPS "1" -- "1" Graph : uses
    RoadQueue "1" -- "*" RoadNode : manages
```

# Outputs

```text
------ Simulation Dashboard ------
1. Display City Traffic Network
2. Display Traffic Signal Status
3. Display Congestion Status
4. Display Blocked Roads
5. Handle Emergency Vehicle Routing
6. Block Road due to Accident
7. Simulate Vehicle Routing
8. Add Intersection
9. Remove Intersection
10. Add Road
11. Remove Road
12. Exit Simulation
Enter your choice:
```

### Display City Traffic Network
```text
 1.Road Network 2.Road Status   0.Exit
Your choice: 1
A -> (B, 5), (C, 15), (D, 20), (G, 25), (H, 22)
B -> (C, 10), (D, 9), (E, 14), (F, 15), (H, 17)
C -> (D, 7), (E, 12), (H, 13)
D -> (E, 3), (F, 10), (G, 18)
E -> (F, 8), (H, 15)
F -> (G, 6), (I, 11)
G -> (H, 9), (J, 12)
H -> (I, 7), (J, 8)
I -> (J, 5)
J -> (K, 10)
K -> (L, 14)
L -> (M, 6)
M -> (N, 8)
N -> (O, 10)
O -> (P, 12)
P -> (Q, 5)
Q -> (R, 15)
R -> (S, 7)
S -> (T, 9)
T -> (U, 6)
U -> (V, 10)
V -> (W, 8)
W -> (X, 6)
X -> (Y, 5)
Y -> (Z, 7)
Z ->
```
### Road Status
```text
Your choice: 2
A -> (B, Open), (C, Open), (D, Open), (G, Blocked), (H, Open)
B -> (C, Blocked), (D, Open), (E, Open), (F, Under Repair), (H, Open)
C -> (D, Open), (E, Open), (H, Under Repair)
D -> (E, Open), (F, Open), (G, Open)
E -> (F, Open), (H, Open)
F -> (G, Open), (I, Open)
G -> (H, Open), (J, Blocked)
H -> (I, Blocked), (J, Open)
I -> (J, Open)
J -> (K, Open)
K -> (L, Blocked)
L -> (M, Open)
M -> (N, Under Repair)
N -> (O, Blocked)
O -> (P, Open)
P -> (Q, Under Repair)
Q -> (R, Blocked)
R -> (S, Open)
S -> (T, Blocked)
T -> (U, Open)
U -> (V, Under Repair)
V -> (W, Open)
W -> (X, Blocked)
X -> (Y, Open)
Y -> (Z, Open)
Z ->
```
### Display Traffic Signal Status

```text
Enter your choice: 2
Intersection A Green Time: 30s
Intersection B Green Time: 40s
Intersection C Green Time: 50s
Intersection D Green Time: 25s
Intersection E Green Time: 35s
Intersection F Green Time: 20s
Intersection G Green Time: 15s
Intersection H Green Time: 30s
Intersection I Green Time: 25s
Intersection J Green Time: 20s
Intersection K Green Time: 35s
Intersection L Green Time: 25s
Intersection M Green Time: 30s
Intersection N Green Time: 20s
Intersection O Green Time: 15s
Intersection P Green Time: 30s
Intersection Q Green Time: 25s
Intersection R Green Time: 40s
Intersection S Green Time: 30s
Intersection T Green Time: 25s
Intersection U Green Time: 20s
Intersection V Green Time: 15s
Intersection W Green Time: 20s
Intersection X Green Time: 25s
Intersection Y Green Time: 30s
Intersection Z Green Time: 35s

```
### Display Congestion Status

```text
A to B -> Vehicles: 6
G to H -> Vehicles: 5
B to C -> Vehicles: 4
X to Y -> Vehicles: 2
H to I -> Vehicles: 3
E to F -> Vehicles: 1
F to G -> Vehicles: 4
N to O -> Vehicles: 1
M to N -> Vehicles: 2
R to S -> Vehicles: 2
D to E -> Vehicles: 3
L to M -> Vehicles: 1
I to J -> Vehicles: 1
T to U -> Vehicles: 1
C to D -> Vehicles: 4
S to T -> Vehicles: 1
P to Q -> Vehicles: 1
U to V -> Vehicles: 1
W to X -> Vehicles: 1
J to K -> Vehicles: 2
O to P -> Vehicles: 1

Most congested road: A to B
```

### Display Blocked Roads
```text
Which Road to display?:
 1.Blocked roads        2.Under Repair Roads    0.Exit
Your choice: 1
Blocked Roads:
- A to F is blocked.
- B to C is blocked.
- H to I is blocked.
- G to J is blocked.
- A to G is blocked.
- K to L is blocked.
- N to O is blocked.
- Q to R is blocked.
- S to T is blocked.
- W to X is blocked.
Which Road to display?:
 1.Blocked roads        2.Under Repair Roads    0.Exit
Your choice: 2
Under Repair Roads:
- C to D is under repair.
- C to H is under repair.
- B to F is under repair.
- M to N is under repair.
- P to Q is under repair.
- U to V is under repair.
```
### Handle Emergency Vehicle Routing
```text
Enter your choice: 5
Enter the start intersection : A
Enter the end intersection : G
Emergency Vehicle is being routed...... 
Emergency Vehicle Path: A B F G

```
### Block Road due to Accident
```text
Enter your choice: 6
Enter the start intersection to block: A
Enter the end intersection to block: B

Updated Blocked Roads:
Blocked Roads:
- A to F is blocked.
- B to C is blocked.
- H to I is blocked.
- G to J is blocked.
- A to G is blocked.
- K to L is blocked.
- N to O is blocked.
- Q to R is blocked.
- S to T is blocked.
- W to X is blocked.
- A to B is blocked.

```
###  Simulate Vehicle Routing
```text
Enter your choice: 7
Enter Type of Algorithm :     
 1.DFS  2.Dijkstra      0.Exit
Your choice: 1
Enter the start intersection : A
Enter the end intersection : G
Start: A, End: G
Paths:
Path: A B C D E F G | Weight: 39
Path: A B C D F G | Weight: 38
Path: A B C D G | Weight: 40
Path: A B C E F G | Weight: 41
Path: A B D E F G | Weight: 31
Path: A B D F G | Weight: 30
Path: A B D G | Weight: 32
Path: A B E F G | Weight: 33
Path: A B F G | Weight: 26
Path: A C D E F G | Weight: 39
Path: A C D F G | Weight: 38
Path: A C D G | Weight: 40
Path: A C E F G | Weight: 41
Path: A D E F G | Weight: 37
Path: A D F G | Weight: 36
Path: A D G | Weight: 38
Path: A G | Weight: 25
Enter Type of Algorithm :
 1.DFS  2.Dijkstra      0.Exit
Your choice: 2
Enter the start intersection : A
Enter the end intersection : G
All paths from A to G:
Path: A G | Current Weight: 25      
Path: A D G | Current Weight: 38    
Path: A B D G | Current Weight: 32  
Path: A B F G | Current Weight: 26  
Path: A C D G | Current Weight: 40  
Path: A D F G | Current Weight: 36  
Path: A B D F G | Current Weight: 30
Path: A B E F G | Current Weight: 33
Enter Type of Algorithm :
 1.DFS  2.Dijkstra      0.Exit
Your choice: 0
Exiting ......
```
### Add Intersection
```text
Enter your choice: 8
Enter the name of the intersection to add: AB
Added succesfully....
```
### Remove Intersection

```text
Enter your choice: 9
Enter the name of the intersection to remove: A
Intersection A removed successfully.

```
### Graph after adding and removing Intersections
```text
B -> (C, 10), (D, 9), (E, 14), (F, 15), (H, 17)
C -> (D, 7), (E, 12), (H, 13)
D -> (E, 3), (F, 10), (G, 18)
E -> (F, 8), (H, 15)
F -> (G, 6), (I, 11)
G -> (H, 9), (J, 12)
H -> (I, 7), (J, 8)
I -> (J, 5)
J -> (K, 10)
K -> (L, 14)
L -> (M, 6)
M -> (N, 8)
N -> (O, 10)
O -> (P, 12)
P -> (Q, 5)
Q -> (R, 15)
R -> (S, 7)
S -> (T, 9)
T -> (U, 6)
U -> (V, 10)
V -> (W, 8)
W -> (X, 6)
X -> (Y, 5)
Y -> (Z, 7)
Z ->
AB ->
```
### Add Road

```text
Enter your choice: 10
Enter the start intersection: AB
Enter the end intersection: B
Enter the travel time: 33


```
After adding road:
```text
B -> (C, 10), (D, 9), (E, 14), (F, 15), (H, 17)
C -> (D, 7), (E, 12), (H, 13)
D -> (E, 3), (F, 10), (G, 18)
E -> (F, 8), (H, 15)
F -> (G, 6), (I, 11)
G -> (H, 9), (J, 12)
H -> (I, 7), (J, 8)
I -> (J, 5)
J -> (K, 10)
K -> (L, 14)
L -> (M, 6)
M -> (N, 8)
N -> (O, 10)
O -> (P, 12)
P -> (Q, 5)
Q -> (R, 15)
R -> (S, 7)
S -> (T, 9)
T -> (U, 6)
U -> (V, 10)
V -> (W, 8)
W -> (X, 6)
X -> (Y, 5)
Y -> (Z, 7)
Z ->
AB -> (B, 33)
```
### Remove Road

```text
Enter your choice: 11
Enter the start intersection to remove the road: F
Enter the end intersection to remove the road: G
Road between F and G removed successfully.

```
After Removing,
```text
B -> (C, 10), (D, 9), (E, 14), (F, 15), (H, 17)
C -> (D, 7), (E, 12), (H, 13)
D -> (E, 3), (F, 10), (G, 18)
E -> (F, 8), (H, 15)
F -> (I, 11)
G -> (H, 9), (J, 12)
H -> (I, 7), (J, 8)
I -> (J, 5)
J -> (K, 10)
K -> (L, 14)
L -> (M, 6)
M -> (N, 8)
N -> (O, 10)
O -> (P, 12)
P -> (Q, 5)
Q -> (R, 15)
R -> (S, 7)
S -> (T, 9)
T -> (U, 6)
U -> (V, 10)
V -> (W, 8)
W -> (X, 6)
X -> (Y, 5)
Y -> (Z, 7)
Z ->
AB -> (B, 33)
```
### Exiting Simulation

```text
Enter your choice: 12
Exiting Simulation. Goodbye!
```

