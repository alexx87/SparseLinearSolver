#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include "Result.h"

namespace Cholesky
{
	struct CRSMatrix
	{
		int N=0, NZ=0;
		std::vector<double> Value;
		std::vector<int64_t> Col, RowIndex;
		bool zeroIndexing = true;
		Result ConvertIndicesFromZero()
		{
			if (zeroIndexing)
				return Result::Success;

			for (auto& col : Col)
			{
				col--;
			}
			for (auto& rowIdx : RowIndex)
			{
				rowIdx--;
			}
			zeroIndexing = true;
			return Result::Success;
		}
		void PrintFullMatrix()
		{
			std::cout << "\n";
			for (int64_t i = 0; i < int64_t(RowIndex.size()-1); i++)
			{
				int64_t startRowIdx = RowIndex[i];
				int64_t endRowIdx = RowIndex[i + 1] - 1;

				auto startCol = Col[startRowIdx];
				for (int64_t ii = 0; ii < startCol; ++ii)
				{
					std::cout << "      ";
				}
				
				for (int64_t j = startRowIdx; j <= endRowIdx; j++)
				{  
					auto deltaIdx = (Col[j] - startCol)-1;
					startCol = Col[j];
					if (deltaIdx > 0)
					{
						for (int64_t ii = 0; ii < deltaIdx; ++ii)
						{
							std::cout.width(6);
							std::cout << 0.0;
						}
					}

					std::cout.width(6);
					std::cout << std::setprecision(3)<< Value[j];
				}

				for (int64_t j = Col[endRowIdx]+1; j < int64_t(RowIndex.size()-1); ++j)
				{
					std::cout.width(6);
					std::cout << 0.0;
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	};

	class CholeskySolver
	{
	public:
		class Data
		{
		public:
			Data(const std::vector<int64_t>& iColomn, const std::vector<int64_t>& iRowIndex, std::vector<double>& iValues, bool iZeroIndexing);
			
			void EnableIndexFromZero(bool iFlag) { _enableIndexFromZero = iFlag; };
		private:
			friend class CholeskySolver;

			std::shared_ptr<CRSMatrix> _matrix;
			bool _enableIndexFromZero = false;
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

		Result _Cmod(int j, int  k);
		Result _CDiv(int iColomn);


		std::shared_ptr<CRSMatrix> _mtx;
		std::shared_ptr<CRSMatrix> _lMtx;
	};
}