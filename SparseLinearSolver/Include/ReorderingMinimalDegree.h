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

	class ReorderingMinimalDegree
	{
	public:
		class Data
		{
		public:
			Data(const std::shared_ptr<Cholesky::CRSMatrix>& iMatrix) :
				_matrix(iMatrix)
			{};
			~Data() = default;

			std::shared_ptr<Cholesky::CRSMatrix> GetMatrix() const { return _matrix; };
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

		ReorderingMinimalDegree() = default;
		~ReorderingMinimalDegree() = default;
		//Find minimal degree permutation 
		Result Run(const Data& iData, Report& oReport) const;

	private:
		Result _Run(const Data& iData, Report& oReport) const;

		Result _FindReachableSet(int iRoot, const Graph& iGraph, const std::vector<int>& iNodeDegree, std::vector<int>& ioMarker, std::vector<int>& oReachableSet, std::vector<int>& oNeighbourhood) const;
		
		Result _FactorGraphTransformation(int iRoot, Graph& ioGraph, const std::vector<int>& iMarker, const std::vector<int>& iReachableSet, const std::vector<int>& iNeighbourhood) const;

	private:
		std::shared_ptr<Cholesky::CRSMatrix> _matrix;
	};

}