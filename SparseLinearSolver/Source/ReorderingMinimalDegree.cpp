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
        nodeDegree.resize(matrixGraph.GetNodes().size(), 0);
        marker.resize(matrixGraph.GetNodes().size(), 0);

        res = _FindReachableSet(root, matrixGraph, nodeDegree, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        res = _FactorGraphTransformation(root, matrixGraph, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        root = 1;
        res = _FindReachableSet(root, matrixGraph, nodeDegree, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        res = _FactorGraphTransformation(root, matrixGraph, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        root = 2;
        res = _FindReachableSet(root, matrixGraph, nodeDegree, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        res = _FactorGraphTransformation(root, matrixGraph, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        root = 3;
        res = _FindReachableSet(root, matrixGraph, nodeDegree, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        res = _FactorGraphTransformation(root, matrixGraph, marker, reachableSet, neighbourhood);
        if (res != Result::Success)
            return res;

        return res;
    }

    Result ReorderingMinimalDegree::_FindReachableSet(int iRoot, const Graph& iGraph, const std::vector<int>& iNodeDegree, std::vector<int>& ioMarker, std::vector<int>& oReachableSet, std::vector<int>& oNeighbourhood ) const
    {
        oReachableSet.clear();
        auto startAdjNodes = iGraph.GetNodes()[iRoot];
        auto endAdjNodes = iGraph.GetNodes()[iRoot + 1];

        for (int i = startAdjNodes; i < endAdjNodes; ++i)
        {
            auto adjNode = iGraph.GetAdjacency()[i];
            if (ioMarker[adjNode] != 0)
                continue;
            if (iNodeDegree[adjNode] >= 0)
            {
                oReachableSet.push_back(adjNode);
                ioMarker[adjNode] = 1;
                continue;
            }
            ioMarker[adjNode] = -1;
            oNeighbourhood.push_back(adjNode);
            std::vector<int> stack;
            stack.push_back(adjNode);
            while (!stack.empty())
            {
                auto subsetNode = stack.back();
                stack.pop_back();
                auto startAdjNeigbourNodes = iGraph.GetNodes()[subsetNode];
                auto endAdjNeigbourNodes = iGraph.GetNodes()[subsetNode + 1];
                for (int j = startAdjNeigbourNodes; j < endAdjNeigbourNodes; ++i)
                {
                    auto adjNeigbourNode = iGraph.GetAdjacency()[j];
                    auto absNode = std::abs(adjNeigbourNode);
                    if (adjNeigbourNode < 0)
                        stack.push_back(absNode);
                    else if (adjNeigbourNode == std::numeric_limits<int>::max())
                        break;
                    else
                    {
                        if (ioMarker[absNode] != 0)
                            continue;
                        oReachableSet.push_back(absNode);
                        ioMarker[absNode] = 1;
                    }
                }
            }
        }

        return Result::Success;
    }
    Result ReorderingMinimalDegree::_FactorGraphTransformation(int iRoot, Graph& ioGraph, const std::vector<int>& iMarker, const std::vector<int>& iReachableSet, const std::vector<int>& iNeighbourhood) const
    {
        auto node = iRoot;

        int reachsetCount = 0;
        int neighbourCount=0;
        while (reachsetCount != iReachableSet.size())
        {
            auto startAdjNodes = ioGraph.GetNodes()[node];
            auto endAdjNodes = ioGraph.GetNodes()[node + 1] - 1;
            for (int i = startAdjNodes; i <= endAdjNodes; ++i)
            {
                ioGraph.GetAdjacency()[i] = iReachableSet[reachsetCount];
                reachsetCount++;
                if (reachsetCount > iReachableSet.size())
                {
                    ioGraph.GetAdjacency()[i + 1] = std::numeric_limits<int>::max();
                    break;
                }
            }

            if (reachsetCount == iReachableSet.size())
                break;

            auto link = ioGraph.GetNodes()[node + 1];
            node = -link;
            if (link < 0)
            {
                node = iNeighbourhood[neighbourCount];
                neighbourCount++;
                ioGraph.GetAdjacency()[endAdjNodes] = -node;
            }
        }

        for (int i = 0; i < iReachableSet.size(); ++i)
        {
            auto currNode = iReachableSet[i];
            if (iMarker[currNode] < 0)
                continue;
            auto startAdjNodes = ioGraph.GetNodes()[currNode];
            auto endAdjNodes = ioGraph.GetNodes()[currNode + 1];
            for (int j = startAdjNodes; j < endAdjNodes; ++j)
            {
                auto adjnode = ioGraph.GetAdjacency()[j];
                if (iMarker[adjnode] >= 0)
                    continue;
                ioGraph.GetAdjacency()[j] = iRoot;
                break;
            }
        }

        return Result::Success;
    }
}