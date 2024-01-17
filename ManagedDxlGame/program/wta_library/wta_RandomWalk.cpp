#include "wta_RandomWalk.h"

namespace wta
{
    bool RandomWalk
        ::IsValidMove(const std::vector<std::vector<int>>& grid
                      , tnl::Vector3 pos, int height , int width)
    {
        if (pos.x < 0 || pos.x >= width 
            || pos.y < 0 || pos.y >= height 
            || grid[pos.y][pos.x] == 1)
        {
            return false;
        }

        // 隣接する「1」の数を確認
        int adjacent_ones = 0;
        
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int nx = pos.x + dx;
                int ny = pos.y + dy;

                if (nx >= 0 && nx < width && ny >= 0
                    && ny < height && grid[ny][nx] == 1)
                {
                    ++adjacent_ones;
                }
            }
        }
        // 隣接する「1」が1つのみの場合に有効
        return adjacent_ones == 1;
    }
}
//
//int main() {
//    srand(static_cast<unsigned int>(time(nullptr)));
//
//    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));
//    std::vector<sDirection> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };
//
//    int x = width / 2;
//    int y = height / 2;
//    grid[y][x] = 1;  // 開始位置
//
//    for (int i = 1; i < length; ++i) {
//        std::vector<Direction> validDirections;
//
//        // 移動可能な方向を探す
//        for (const auto& dir : directions) {
//            int nx = x + dir.dx;
//            int ny = y + dir.dy;
//            if (isValidMove(grid, nx, ny)) {
//                validDirections.push_back(dir);
//            }
//        }
//
//        if (validDirections.empty()) {
//            break;  // これ以上進めない場合は終了
//        }
//
//        Direction selectedDir = validDirections[rand() % validDirections.size()];
//        x += selectedDir.dx;
//        y += selectedDir.dy;
//        grid[y][x] = 1;
//    }
//
//    // 経路の表示
//    for (const auto& row : grid) {
//        for (int cell : row) {
//            std::cout << cell << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    return 0;
//}