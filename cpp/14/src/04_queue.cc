#include <iostream>
#include <queue>  // for std::queue
#include <vector>

struct Position {
  int row, col, distance;
};

int main() {
  std::vector<std::vector<int>> maze = {{0, 1, 0, 0, 0},
                                        {0, 1, 0, 1, 0},
                                        {0, 0, 0, 1, 0},
                                        {1, 1, 0, 0, 0},
                                        {0, 0, 0, 1, 0}};  // 0: path, 1: wall
  std::queue<Position> q;
  q.push({0, 0, 0});  // Start at (0,0), we want to reach (4,4)
  maze[0][0] = 1;     // Mark as visited

  int dx[] = {-1, 1, 0, 0};  // up, down, left, right
  int dy[] = {0, 0, -1, 1};

  while (!q.empty()) {
    Position curr = q.front();
    q.pop();

    if (curr.row == 4 && curr.col == 4) {  // Reached goal (4,4)
      std::cout << "Escaped! Distance: " << curr.distance << std::endl;
      return 0;
    }

    for (int i = 0; i < 4; i++) {
      int nr = curr.row + dx[i];
      int nc = curr.col + dy[i];

      if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5 && maze[nr][nc] == 0) {
        maze[nr][nc] = 1;
        q.push({nr, nc, curr.distance + 1});
      }
    }
  }
  std::cout << "No path found!" << std::endl;
  return 0;
}
