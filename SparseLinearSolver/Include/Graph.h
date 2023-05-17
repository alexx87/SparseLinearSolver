#pragma once

#include <vector>
#include "Result.h"
#include <memory>

namespace Cholesky
{
	class CRSMatrix;
}

namespace Reordering
{
	class Graph
	{
	public:
		Graph() = default;
		~Graph() = default;

		Result Create(const std::shared_ptr<Cholesky::CRSMatrix>& iMatrix) ;
		std::vector<int>& GetNodes() { return _nodes; };
		std::vector<int>& GetAdjacency() { return _adjacency; };
	private:
		std::vector<int> _nodes;
		std::vector<int> _adjacency;
	};
}