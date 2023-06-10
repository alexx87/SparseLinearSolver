#include  <ReorderingRCM.h>

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
        
        std::vector<int> permutation;
        res = _CalculateRCMForGraph( matrixGraph, permutation);

        return res;
    }
    Result ReorderingRCM::_CalculateRCMForGraph(const Graph& iGraph, std::vector<int>& oPermutation) const
    {
        std::vector<int> mask;
        mask.resize(iGraph.GetNodes().size() - 1, 1);

        auto res = Result::Success;
        int root = 0;
        for (int i = 0; i<int(mask.size()); ++i)
        {
            if (mask[i] == 0)
                continue;
            root = i;

            res = iGraph.FindRootNode(root, mask);
            if (res != Result::Success)
                return res;
            res = _CalculateRCMForSubgraph(root, iGraph, mask, oPermutation);
            if (res != Result::Success)
                return res;
        }

        return Result::Success;
    }
    Result ReorderingRCM::_CalculateNodeDegreesForSubgraph(int iRoot, const Graph& iGraph, const std::vector<int>& iMask, std::vector<int>& oNodeDegrees) const
    {
        oNodeDegrees.resize(iGraph.GetNodes().size() - 1, 0);

        std::unordered_set<int> usedNodes;
        std::vector<int> levels;
        levels.push_back(iRoot);
        usedNodes.insert(iRoot);
        auto startLevel = 0;
        auto endLevel = int(levels.size());

        while (endLevel - startLevel > 0)
        {
            for (int i = startLevel; i < endLevel; ++i)
            {
                auto node = levels[i];
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
                        levels.push_back(adjNode);
                        usedNodes.insert(adjNode);
                    }
                }
                oNodeDegrees[node] = nodeDegree;
            }
            startLevel = endLevel;
            endLevel = int(levels.size());
        }
        return Result::Success;
    }
    Result ReorderingRCM::_CalculateRCMForSubgraph(int iRoot, const Graph& iGraph, std::vector<int>& ioMask, std::vector<int>& oPermutation) const
    {
        if (ioMask[iRoot] == 0)
            return Result::InvalidData;

        std::vector<int> nodeDegrees;
        auto res = _CalculateNodeDegreesForSubgraph(iRoot, iGraph, ioMask, nodeDegrees);
        if (res != Result::Success)
            return res;

        oPermutation.push_back(iRoot);
        ioMask[iRoot] = 0;
        auto startLevel = 0;
        auto endLevel = int(oPermutation.size());

        while (endLevel - startLevel > 0)
        {
            for (int i = startLevel; i < endLevel; ++i)
            {
                auto node = oPermutation[i];
                auto startAdjNodes = iGraph.GetNodes()[node];
                auto endAdjNodes = iGraph.GetNodes()[node + 1];
                int numberedNodes = 0;
                for (int j = startAdjNodes; j < endAdjNodes; ++j)
                {
                    auto adjNode = iGraph.GetAdjacency()[j];
                    if (ioMask[adjNode] == 0)
                        continue;
                    ioMask[adjNode] = 0;
                    numberedNodes++;
                    oPermutation.push_back(adjNode);
                }
                std::sort(oPermutation.end() - numberedNodes, oPermutation.end(), [&nodeDegrees](int left, int right) {return nodeDegrees[left] < nodeDegrees[right]; });
            }
            startLevel = endLevel;
            endLevel = int(oPermutation.size());
        }

        int cashe = 0;
        auto last = int(oPermutation.size())-1;
        for (int i = 0; i< int(oPermutation.size()) / 2; ++i)
        {
            cashe = oPermutation[i];
            oPermutation[i] = oPermutation[last - i];
            oPermutation[last - i] = cashe;
        }
        return Result::Success;
    }
}