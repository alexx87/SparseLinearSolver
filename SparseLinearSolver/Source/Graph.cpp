#include "Graph.h"
#include "CholeskySolver.h"

namespace Reordering
{
    Result Graph::Create(const std::shared_ptr<Cholesky::CRSMatrix>& iMatrix)
    {
        iMatrix->PrintFullMatrix();
        int a = 0;
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
            for (int i = iMatrix->RowIndex[row] + 1; i != iMatrix->RowIndex[row+1]; ++i)
            {
                _adjacency.push_back(iMatrix->Col[i]);
            }
            
            _nodes.push_back(int(_adjacency.size()));
        }

        return Result::Success;
    }
}