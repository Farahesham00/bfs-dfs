# Markdown Cheat Sheet

Name: Farah Hesham

 
###BFS###



### Explanation in short

bfs is a path planning for robot navigation. 
it explores all the vertices at the same level before moving to the next level. 
      priorety 
      vector<int> dx = {-1, 0, 1, 0};  // Directions: up, right, down, left
      vector<int> dy = {0, 1, 0, -1};
 
 the bfs is searching up cell then right cell then down and so on
 
 the maze is 5x5 and putting -1 as a obstacle and 1 as an open space 
 
 
 

Create a queue data structure to store the nodes to be visited during the BFS traversal.
 in code we use queue which operate in a first in first out type of arrangement and thats what we need in bfs that the first cell has been visited is the cell we put priorty in 
 example : visited up = 1 , right = 2 , down = 3 , left = 4.
 then we go to the first which is 1 and do the priorety on it 
 
 
 
 start point is (0,0)
 goal point is (4,4)
 
 Initialize a visited array or matrix to keep track of visited nodes
u can understande code while u read it because i put some comments to explain it 




## Breadth-First Search (BFS) Path Planning

BFS is a path planning algorithm commonly used for robots navigation. It explores all the vertices at the same level before moving to the next level.

### Priority

To define the priority order for exploration, we use two vectors:

```cpp
vector<int> dx = {-1, 0, 1, 0};  // Directions: up, right, down, left
vector<int> dy = {0, 1, 0, -1};
```

The BFS algorithm searches cells in the following order: up, right, down, and left.

### Maze Representation

In this example, we consider a 5x5 maze where obstacles are represented by -1 and open spaces by 1.

### Queue Data Structure

To store the nodes to be visited during the BFS traversal, we create a queue data structure. In the code, we use a queue that operates in a first-in-first-out (FIFO) arrangement, which matches the behavior required for BFS.

### Algorithm Steps

1. Create an empty queue to store nodes to be visited during BFS traversal.
2. Enqueue the start point and mark it as visited.
3. While the queue is not empty, repeat the following steps:
    - Dequeue the front element from the queue.
    - If the dequeued node matches the goal point, exit the loop (path found).
    - Explore the neighbors of the dequeued node.
        - Check if each neighbor falls within the grid boundaries and is an open space.
        - If the neighbor has not been visited before, enqueue it, mark it as visited, and update its parent.
4. After the BFS traversal, reconstruct the path from the end point to the start point by backtracking using the parent pointers.
5. Return the path.

### Implementation Details

The BFS path planning algorithm involves the following code components:

- `vector<int> dx` and `vector<int> dy`: Priority order for exploring adjacent cells.
- Maze representation: 5x5 maze with -1 as obstacles and 1 as open spaces.
- Queue data structure: Used to store nodes to be visited during BFS traversal.
- Start point: (0,0).
- Goal point: (4,4).
- `visited` array or matrix: Initialized to keep track of visited nodes.
- Code comments: Provided to explain each step of the algorithm.

### Example Usage

To use the BFS path planning algorithm, follow these steps:

1. Define a maze grid with obstacle and open space values.
2. Set the start and goal points.
3. Call the `bfs_path_planning` function with the maze grid, start point, and goal point.
4. If a valid path is found, it will be returned as a sequence of coordinates.
5. If no path is found, an appropriate message will be displayed.

By following these steps and analyzing the provided code comments, you can understand the implementation of the BFS path planning algorithm.


### Code



#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;  //Point, which represents a coordinate in the grid.

vector<Point> bfs_path_planning(vector<vector<int>>& grid, Point start, Point end) 
//function
//start and end point as input parameters 
//returns a vector of Points representing the shortest path.

{
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> parent(rows, vector<Point>(cols, make_pair(-1, -1)));
	//visited to keep track of visited cells
	//parent to store the parent cell for each cell in the grid. 
	//The initial value of each cell in parent is set to make_pair(-1, -1).



    vector<int> dx = {-1, 0, 1, 0};  // Directions: up, right, down, left
    vector<int> dy = {0, 1, 0, -1};

    queue<Point> q;
    q.push(start);
    visited[start.first][start.second] = true;
	//A queue q is created, and the start point is pushed into the queue. 
	//The visited flag for the start point is set to true to mark it as visited.

    while (!q.empty())
	
	
	 {
        Point current = q.front();
        q.pop();

        if (current == end) {
            break;
        }

	// front element of the queue is removed and replace to the current variable. 
	//If the current point is equal to the end point, 
	//loop breaks and found the destination.

        for (int i = 0; i < 4; i++) // 4 direction
		
		{
            int next_row = current.first + dx[i];
            int next_col = current.second + dy[i];
			
			//make variable next row/col adding next values to the current point.

            if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols && !visited[next_row][next_col] && grid[next_row][next_col] == 1) {
                q.push(make_pair(next_row, next_col));
                visited[next_row][next_col] = true;
                parent[next_row][next_col] = current;
            }

			//checks if the next_row/col values are within the grid boundaries
			//has not been visited and is accessible 
			//current point is set as the parent for the next_row and next_col point.
        }
       }

    if (parent[end.first][end.second] == make_pair(-1, -1)) {
        return {};  // No path found
		//If the parent of the end point is make_pair(-1, -1), 
		//it means there is no path, so an empty vector is returned.
    }

    vector<Point> path;
    Point current = end;
    while (current != start) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    vector<vector<int>> grid = {
        {1, -1, -1, 1, 1},
        {1, -1, 1, -1, 1},
        {1, 1, 1, 1, 1},
        {1, -1, 1, -1, 1},
        {1, 1, 1, 1, 1}
    };
//Obstacles are marked with -1, and open spaces are marked with 1. 

    Point start = make_pair(0, 0);
    Point end = make_pair(4, 4);

    // Find the shortest path
    vector<Point> path = bfs_path_planning(grid, start, end);

    // Print the path
    if (!path.empty()) {
        cout << "Shortest path found:" << endl;
        for (const auto& point : path) {
            cout << "(" << point.first << ", " << point.second << ")" << endl;
        }
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}


### output

Shortest path found:
(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)



### Maze image BFS

![alt text](![WhatsApp Image 2023-12-12 at 9 38 55 AM](https://github.com/Farahesham00/bfs-dfs/assets/151152805/c5904048-0a55-49c9-96aa-1ed595dea152)
)






################################################

###DFS###

as same as bfs but a little bit change
Depth-first search is a fundamental algorithm in graph theory, and understanding it is essential for solving many graph-based problems. 
Stacks are a type of container adaptors with LIFO(Last In First Out) type of working, where a new element is added at one end (top) and an element is removed from that end only. 

direction up right down left
dfs is goes as priorety but in tha same cell
example: up = 1 , up = 2 , up = 3 "obstacle i up the go to next direction" right = 4







### output DFS
Path found:
(0, 0)
(1, 0)
(2, 0)
(3, 0)
(4, 0)
(4, 1)
(4, 2)
(4, 3)
(4, 4)

### Maze image DFS

![alt text](![WhatsApp Image 2023-12-12 at 10 01 07 AM](https://github.com/Farahesham00/bfs-dfs/assets/151152805/538973bd-7a6c-4296-855d-baefa6216c6f)
)
 
 
