#include  "ReorderingRCM.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>

#include "Graph.h"

namespace Reordering
{
    Result ReorderingRCM::Run(const Data& iData, Report& oReport) const
    {
        auto res = _Run(iData, oReport);

        return res;
    }

    Result ReorderingRCM::_Run(const Data& iData, Report& oReport) const
    {
        auto matrix = iData.GetMatrix();

        auto matrixGraph = Graph::Graph();
        auto res = matrixGraph.Create(matrix);
        if (res != Result::Success)
            return res;
        
        int root = 0;
        std::vector<int> mask;
        mask.resize(matrixGraph.GetNodes().size()-1, 1);
        std::vector<int> oIndexLevels;
        std::vector<int> oLevels;
        matrixGraph.FindRootNode(root, mask, oIndexLevels, oLevels);



        return Result::Success;
    }
    
}