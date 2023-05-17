#pragma once

#include <vector>
#include "Result.h"

namespace Reordering
{
	class ReorderingRCM
	{
	public:
		class Data
		{
		public:
			Data(const std::vector<int64_t>& iColomns, const std::vector<int64_t>& iRowIndex, const std::vector<double>& iValues) :
				_values(iValues), _colomns(iColomns), _rowIndex(iRowIndex)
			{};
			~Data() = default;
		private:
			std::vector<double> _values;
			std::vector<int64_t> _colomns;
			std::vector<int64_t> _rowIndex;
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

	};

}