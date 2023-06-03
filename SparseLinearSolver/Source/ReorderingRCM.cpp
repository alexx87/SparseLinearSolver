#include  "ReorderingRCM.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<unordered_set>
#include <iostream>
#include <algorithm>

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
        res=matrixGraph.FindRootNode(root, mask, oIndexLevels, oLevels);
        if (res != Result::Success)
            return res;

        std::vector<int> permutation;
        res = _CalculateRCMForSubgraph(root, matrixGraph, mask, permutation);

        return Result::Success;
    }
    Result ReorderingRCM::_CalculateNodeDegreesForSubgraph(int iRoot, const Graph& iGraph, const std::vector<int>& iMask, std::vector<int>& oNodeDegrees, std::vector<int>& oLevels) const
    {
        oNodeDegrees.resize(iGraph.GetNodes().size() - 1, 0);

        std::unordered_set<int> usedNodes;
        oLevels.push_back(iRoot);
        usedNodes.insert(iRoot);
        auto startLevel = 0;
        auto endLevel = int(oLevels.size());

        while (endLevel - startLevel > 0)
        {
            for (int i = startLevel; i < endLevel; ++i)
            {
                auto node = oLevels[i];
                auto startAdjNodes = iGraph.GetNodes()[node];
                auto endAdjNodes = iGraph.GetNodes()[node + 1];
                int nodeDegree = 0;
                for (int j = startAdjNodes; j < endAdjNodes; ++j)
                {
                    auto adjNode = iGraph.GetAdjacency()[j];
                    if (iMask[adjNode] == 0)
                        continue;
                    nodeDegree++;
                    if (usedNodes.find(adjNode) == usedNodes.end())
                    {
                        oLevels.push_back(adjNode);
                        usedNodes.insert(adjNode);
                    }
                }
                oNodeDegrees[node] = nodeDegree;
            }
            startLevel = endLevel;
            endLevel = int(oLevels.size());
        }
        return Result::Success;
    }
    Result ReorderingRCM::_CalculateRCMForSubgraph(int iRoot, const Graph& iGraph, std::vector<int>& ioMask, std::vector<int>& oPermutation) const
    {
        if (ioMask[iRoot] == 0)
            return Result::InvalidData;

        std::vector<int> nodeDegrees;
        std::vector<int> levels;
        auto res = _CalculateNodeDegreesForSubgraph(iRoot, iGraph, ioMask, nodeDegrees, oPermutation);
        if (res != Result::Success)
            return res;

        ioMask[iRoot] = 0;
        auto startLevel = 0;
        auto endLevel = 1;

        //while (endLevel - startLevel > 0)
        //{
        //    for (int i = startLevel; i < endLevel; ++i)
        //    {
        //        auto node = oPermutation[i];
        //        auto startAdjNodes = iGraph.GetNodes()[node];
        //        auto endAdjNodes = iGraph.GetNodes()[node + 1];
        //        for (int j = startAdjNodes; j < endAdjNodes; ++j)
        //        {
        //            auto adjNode = iGraph.GetAdjacency()[j];
        //            if (ioMask[adjNode] == 0)
        //                continue;
        //            ioMask[adjNode] = 0;
        //            oPermutation.push_back(adjNode);
        //        }
        //        std::sort(oPermutation)
        //    }
        //}

        return Result::Success;
    }
}