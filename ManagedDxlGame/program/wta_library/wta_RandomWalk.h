#pragma once
#include "../dxlib_ext/dxlib_ext.h"

namespace wta
{
    class RandomWalk
    {
    private:

        bool IsValidMove(const std::vector<std::vector<int>>& grid
                         , tnl::Vector3 pos,int height =20,int width=10);
    };

};