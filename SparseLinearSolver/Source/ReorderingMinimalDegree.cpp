#include  <ReorderingMinimalDegree.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<unordered_set>
#include <iostream>
#include <algorithm>

#include "Graph.h"

namespace Reordering
{
    Result ReorderingMinimalDegree::Run(const Data& iData, Report& oReport) const
    {
        auto res = _Run(iData, oReport);

        return res;
    }

    Result ReorderingMinimalDegree::_Run(const Data& iData, Report& oReport) const
    {
        auto matrix = iData.GetMatrix();

        auto matrixGraph = Graph::Graph();
        auto res = matrixGraph.Create(matrix);
        if (res != Result::Success)
            return res;

        int root = 0;
        std::vector<int> nodeDegree;
        std::vector<int> reachableSet;
        std::vector<int> neighbourhood;
        std::vector<int> marker;

        res = _FindReachableSet(root, matrixGraph, nodeDegree, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        return res;
    }

    Result ReorderingMinimalDegree::_FindReachableSet(int iRoot, const Graph& iGraph, const std::vector<int>& iNodeDegree, const std::vector<int>& ioMarker, std::vector<int>& oReachableSet, std::vector<int>& oNeighbourhood ) const
    {

        return Result::Success;
    }
}