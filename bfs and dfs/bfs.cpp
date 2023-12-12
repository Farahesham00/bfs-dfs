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