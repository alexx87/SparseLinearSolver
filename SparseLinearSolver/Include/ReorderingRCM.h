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

	private:
		std::shared_ptr<Cholesky::CRSMatrix> _matrix;
	};

}