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

        // �אڂ���u1�v�̐����m�F
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
        // �אڂ���u1�v��1�݂̂̏ꍇ�ɗL��
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
//    grid[y][x] = 1;  // �J�n�ʒu
//
//    for (int i = 1; i < length; ++i) {
//        std::vector<Direction> validDirections;
//
//        // �ړ��\�ȕ�����T��
//        for (const auto& dir : directions) {
//            int nx = x + dir.dx;
//            int ny = y + dir.dy;
//            if (isValidMove(grid, nx, ny)) {
//                validDirections.push_back(dir);
//            }
//        }
//
//        if (validDirections.empty()) {
//            break;  // ����ȏ�i�߂Ȃ��ꍇ�͏I��
//        }
//
//        Direction selectedDir = validDirections[rand() % validDirections.size()];
//        x += selectedDir.dx;
//        y += selectedDir.dy;
//        grid[y][x] = 1;
//    }
//
//    // �o�H�̕\��
//    for (const auto& row : grid) {
//        for (int cell : row) {
//            std::cout << cell << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    return 0;
//}