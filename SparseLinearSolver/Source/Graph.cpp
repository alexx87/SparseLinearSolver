#include "Graph.h"
#include "CholeskySolver.h"

namespace Reordering
{
    Result Graph::Create(const std::shared_ptr<Cholesky::CRSMatrix>& iMatrix)
    {
        _nodes.push_back(0);
        for (int row = 0; row < iMatrix->RowIndex.size()-1; ++row)
        {
            for (int i = 0; i < _nodes.size() - 1; ++i)
            {
                for (int j = _nodes[i]; j < _nodes[i+1] ; ++j)
                {
                    if (_adjacency[j] == row)
                        _adjacency.push_back(i);
                }
            }
            for (int64_t i = iMatrix->RowIndex[row] + 1; i != iMatrix->RowIndex[row+1]; ++i)
            {
                _adjacency.push_back(int(iMatrix->Col[i]));
            }
            
            _nodes.push_back(int(_adjacency.size()));
        }

        return Result::Success;
    }
    Result Graph::FindRootNode(int& ioRoot, const std::vector<int>& iMask) const
    {
        std::vector<int> indexLevels;
        std::vector<int> levels;
        auto res=_GenerateRootedLevelStructure(ioRoot, iMask, indexLevels, levels);
        if (res != Result::Success)
            return res;
        auto numberOfLevels = indexLevels.size() - 1;
        auto maskedGraphSize = indexLevels.back();
        if (numberOfLevels ==1|| maskedGraphSize == numberOfLevels)
            return Result::Success;
        auto numberOfNewLevels = numberOfLevels + 1;

        auto iterationCount = 0;
        while (iterationCount<maskedGraphSize )
        {
            iterationCount++;
            auto lastLevelBegin = indexLevels[numberOfLevels - 1];
            auto lastLevelEnd = indexLevels[numberOfLevels];
            int minDegree = maskedGraphSize;
            auto rootCandidate = levels[lastLevelBegin];
            for (auto lastLevelNodeIdx = lastLevelBegin; lastLevelNodeIdx < lastLevelEnd; ++lastLevelNodeIdx)
            {
                auto lastLevelNode = levels[lastLevelNodeIdx];
                int nodeDegree = 0;
                for (int adjacentNodeIdx = _nodes[lastLevelNode]; adjacentNodeIdx < _nodes[lastLevelNode + 1]; ++adjacentNodeIdx)
                {
                    auto adjacentNode = _adjacency[adjacentNodeIdx];
                    if (iMask[adjacentNode] == 1)
                    {
                        nodeDegree++;
                    }
                }
                if (nodeDegree < minDegree)
                {
                    rootCandidate = lastLevelNode;
                    minDegree = nodeDegree;
                }
            }

            res = _GenerateRootedLevelStructure(rootCandidate, iMask, indexLevels, levels);
            if (res != Result::Success)
                return res;
            numberOfNewLevels = indexLevels.size() - 1;
            if (numberOfNewLevels <= numberOfLevels)
                break;
            if (numberOfLevels == maskedGraphSize)
                break;
            numberOfLevels = numberOfNewLevels;
            ioRoot = rootCandidate;
        }

        return Result::Success;
    }
    Result Graph::_GenerateRootedLevelStructure(int iRoot, const std::vector<int>& iMask, std::vector<int>& oIndexLevels, std::vector<int>& oLevels) const
    {
        oIndexLevels.clear();
        oLevels.clear();
        auto mask = iMask;
        mask[iRoot] = 0;
        oLevels.push_back(iRoot);
        oIndexLevels.push_back(0);
        oIndexLevels.push_back(int(oLevels.size()));

        int levelWidth = 1;

        while (levelWidth > 0)
        {
            levelWidth = 0;
            auto levelBegin = oIndexLevels[int(oIndexLevels.size()) - 2];
            auto levelEnd = oIndexLevels[int(oIndexLevels.size()) - 1];

            for (auto rootNodeIdx = levelBegin; rootNodeIdx < levelEnd; ++rootNodeIdx)
            {
                auto rootNode = oLevels[rootNodeIdx];
                for (auto adjNode = _nodes[rootNode]; adjNode < _nodes[rootNode + 1]; ++adjNode)
                {
                    auto adjacentNode = _adjacency[adjNode];
                    if (mask[adjacentNode] == 1)
                    {
                        oLevels.push_back(adjacentNode);
                        mask[adjacentNode] = 0;
                        levelWidth++;
                    }
                }
            }
            if (levelWidth > 0)
            {
                oIndexLevels.push_back(int(oLevels.size()));
            }
        }
        return Result::Success;
    }
}