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
		std::vector<int> Col, RowIndex;
		bool zeroIndexing = true;
		void PrintFullMatrix()
		{
			for (int i = 0; i < RowIndex.size()-1; i++)
			{
				int startRowIdx = RowIndex[i];
				int endRowIdx = RowIndex[i + 1] - 1;

				auto startCol = Col[startRowIdx];
				for (int ii = 0; ii < startCol; ++ii)
				{
					std::cout << "     ";
				}
				
				for (int j = startRowIdx; j <= endRowIdx; j++)
				{  
					auto deltaIdx = (Col[j] - startCol)-1;
					startCol = Col[j];
					if (deltaIdx > 0)
					{
						for (int ii = 0; ii < deltaIdx; ++ii)
						{
							std::cout.width(5);
							std::cout << 0.0;
						}
					}

					std::cout.width(5);
					std::cout << std::setprecision(3)<< Value[j];
				}

				for (int j = Col[endRowIdx]+1; j < RowIndex.size()-1; ++j)
				{
					std::cout.width(5);
					std::cout << 0.0;
				}
				std::cout << std::endl;
			}

			//std::cout.width(10);
			//std::cout << "Print Row Index\n";
			//for (int i = 0; i < RowIndex.size(); i++)
			//{
			//	std::cout.width(5);
			//	std::cout << RowIndex[i] << " ";
			//}
			//std::cout << "\nPrint Colomns\n";
			//for (int i = 0; i < Col.size(); i++)
			//{
			//	std::cout.width(5);
			//	std::cout << Col[i] << " ";
			//}
			//std::cout << "\nPrint Values\n";
			//for (int i = 0; i < Value.size(); i++)
			//{
			//	std::cout.width(5);
			//	std::cout << Value[i] << " ";
			//}
			//std::cout << "\n";
		}
	};

	class CholeskySolver
	{
	public:
		class Data
		{
		public:
			Data(const std::vector<int>& iColomn, const std::vector<int>& iRowIndex, std::vector<double>& iValues, bool iZeroIndexing);
			
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
		Result _ConvertIndicesFromZero();

		Result _Cmod(int j, int  k);
		Result _CDiv(int iColomn);


		std::shared_ptr<CRSMatrix> _mtx;
		std::shared_ptr<CRSMatrix> _lMtx;
	};
}