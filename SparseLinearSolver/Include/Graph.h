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
		const std::vector<int>& GetNodes() const  { return _nodes; };
		const std::vector<int>& GetAdjacency() const { return _adjacency; };

		Result FindRootNode(int& ioRoot, const std::vector<int>& iMask, std::vector<int>& oIndexLevels, std::vector<int>& oLevels) const;

	private:
		//Generation of level structure with root node on zero level fron masked subgraph
		Result _GenerateRootedLevelStructure(int iRoot, const std::vector<int>& iMask, std::vector<int>& oIndexLevels, std::vector<int>& oLevels) const;

	private:
		std::vector<int> _nodes;
		std::vector<int> _adjacency;
	};
}