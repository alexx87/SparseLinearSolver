#pragma once

#include <vector>
#include <memory>

#include "Result.h"

namespace Cholesky
{
	class CRSMatrix;
}

namespace Reordering
{
	class Graph;

	class ReorderingRCM
	{
	public:
		class Data
		{
		public:
			Data(const std::shared_ptr<Cholesky::CRSMatrix>& iMatrix) :
				_matrix(iMatrix)
			{};
			~Data() = default;

			std::shared_ptr<Cholesky::CRSMatrix> GetMatrix() const  {return _matrix;};
		private:
			std::shared_ptr<Cholesky::CRSMatrix> _matrix;
			friend class ReorderingRCM;
		};
		class Report
		{
		public:
			Report() = default;
			~Report() = default;
			const std::vector<int64_t>& GetPermutation() const { return _permutation; };
		private:
			std::vector<int64_t> _permutation;
			friend class ReorderingRCM;
		};

		ReorderingRCM() = default;
		~ReorderingRCM() = default;
		Result Run(const Data& iData, Report& oReport) const;

	private:
		
		Result _Run(const Data& iData, Report& oReport) const;
		//Find Reversed Cuthull-McKee permutation for full graph
		Result _CalculateRCMForGraph(const Graph& iGraph, std::vector<int>& oPermutation) const;
		//Find Reversed Cuthull-McKee permutation for subgraph
		Result _CalculateRCMForSubgraph(int iRoot, const Graph& iGraph, std::vector<int>& ioMask, std::vector<int>& oPermutation) const;
		//Calculate node degrees for subgraph
		Result _CalculateNodeDegreesForSubgraph(int iRoot, const Graph& iGraph, const std::vector<int>& iMask, std::vector<int>& oNodeDegrees) const;

	private:
		std::shared_ptr<Cholesky::CRSMatrix> _matrix;
	};

}