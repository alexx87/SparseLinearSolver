#pragma once

#include <vector>
#include <memory>
#include "Result.h"

namespace Cholesky
{
	struct CRSMatrix
	{
		int N=0, NZ=0;
		std::vector<double> Value;
		std::vector<int> Col, RowIndex;
	};

	class CholeskySolver
	{
	public:
		class Data
		{
		public:
			Data(const std::vector<int>& iColomn, const std::vector<int>& iRowIndex, std::vector<double>& iValues);
			std::shared_ptr<CRSMatrix> _matrix;
		private:
			friend class CholeskySolver;
		};

		class Report
		{
			public:
				Report() = default;

		};

		CholeskySolver() =default;
		~CholeskySolver() = default;

		Result Run(const Data& iData, Report& oReport);
	private:
		/// Защита от копирования
		CholeskySolver operator=(const CholeskySolver&) = delete;
		//CholeskySolver(const CholeskySolver&) = delete;

		Result _Run(const Data& iData, Report& oReport);

	};
}