#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;

vector<Point> dfs_path_planning(vector<vector<int>>& grid, Point start, Point end) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> parent(rows, vector<Point>(cols, make_pair(-1, -1)));

    vector<int> dx = {-1, 0, 1, 0};  // Directions: up, right, down, left
    vector<int> dy = {0, 1, 0, -1};

    stack<Point> st;
    st.push(start);
    visited[start.first][start.second] = true;

    while (!st.empty()) {
        Point current = st.top();
        st.pop();

        if (current == end) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int next_row = current.first + dx[i];
            int next_col = current.second + dy[i];

            if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols && !visited[next_row][next_col] && grid[next_row][next_col] != -1) {
                st.push(make_pair(next_row, next_col));
                visited[next_row][next_col] = true;
                parent[next_row][next_col] = current;
            }
        }
    }

    if (parent[end.first][end.second] == make_pair(-1, -1)) {
        return {};  // No path found
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

    Point start = make_pair(0, 0);
    Point end = make_pair(4, 4);

    vector<Point> path = dfs_path_planning(grid, start, end);

    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (const auto& point : path) {
            cout << "(" << point.first << ", " << point.second << ")" << endl;
        }
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}