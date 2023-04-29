#include "CholeskySolver.h"

//#pragma optimize("", off)

namespace Cholesky
{
	CholeskySolver::Data::Data(const std::vector<int>& iColomn, const std::vector<int>& iRowIndex, std::vector<double>& iValues, bool iZeroIndexing)
	{
		_matrix = std::make_shared<CRSMatrix>();
		_matrix->Col = iColomn;
		_matrix->RowIndex = iRowIndex;
		_matrix->Value = iValues;
		_matrix->zeroIndexing = iZeroIndexing;
		return;
	}

	Result CholeskySolver::Run(const Data& iData, Report& oReport)
	{
		auto result = _Run(iData, oReport);
		return result;
	}

	Result CholeskySolver::_Run(const Data& iData, Report& oReport)
	{
		auto result = Result::Success;

		_mtx = iData._matrix;
		if (!_mtx->zeroIndexing)
		{
			auto res = _ConvertIndicesFromZero();
			if (res != Result::Success)
				return res;
		}

		if (!_mtx)
			return Result::InvalidData;
		_lMtx = std::make_shared<CRSMatrix>();
		_lMtx->Col = _mtx->Col;
		_lMtx->RowIndex = _mtx->RowIndex;
		_lMtx->Value = _mtx->Value;

		_lMtx->PrintFullMatrix();
		for (int i = 0; i < _lMtx->RowIndex.size()-1; ++i)
		{
			if (_CDiv(i) != Result::Success)
				continue;
		}
		_lMtx->PrintFullMatrix();

		return result;
	}

	Result CholeskySolver::_ConvertIndicesFromZero()
	{
		for (auto& col : _mtx->Col)
		{
			col--;
		}
		for (auto& rowIdx : _mtx->RowIndex)
		{
			rowIdx--;
		}
		_mtx->zeroIndexing = true;
		return Result::Success;
	}

	Result CholeskySolver::_Cmod(int j, int  k)
	{
		return Result::Success;
	}
	Result  CholeskySolver::_CDiv(int iColomn)
	{
		if (iColomn >= _mtx->RowIndex.size() - 1)
			return Result::InvalidData;

		//symmetric case
		int startRowIdx = _mtx->RowIndex[iColomn] ;
		int endRowIdx = _mtx->RowIndex[iColomn + 1];

		if (_lMtx->Value[startRowIdx] < 0.0)
			return Result::InvalidData;

		auto divide = sqrt(_mtx->Value[startRowIdx]);

		_lMtx->Value[startRowIdx] = divide;
		
		if (divide < 1e-15)
		{
			return Result::InvalidData;
		}
		for (int i = 0; i < iColomn; i++)
		{
			int startRowIdx = _mtx->RowIndex[i] ;
			int endRowIdx = _mtx->RowIndex[i + 1]-1 ;
			for (int j = startRowIdx; j <= endRowIdx; j++)
			{
				if (_mtx->Col[j] != iColomn)
					continue;
				_lMtx->Value[j] = _mtx->Value[j] / divide;
			}
		}
		return Result::Success;
	}

	//void SparseMatrix::SparseMatVec(CRSMatrix& mtx, double* R, double* Y)
	//{
	//	for (int i = 0; i < mtx.N; i++)
	//	{
	//		int K1 = mtx.RowIndex[i];
	//		int K2 = mtx.RowIndex[i + 1] - 1;
	//		Y[i] = 0;
	//		for (int j = K1; j <= K2; j++)
	//		{
	//			Y[i] = Y[i] + mtx.Value[j] * R[mtx.Col[j]];
	//		}
	//	}
	//}
	//void SparseMatrix::SparseSolveLowerTriang(CRSMatrix& mtx, double* Y, double* X)
	//{
	//	X[0] = Y[0];
	//	for (int i = 1; i < mtx.N; i++)
	//	{
	//		int K1 = mtx.RowIndex[i];
	//		int K2 = mtx.RowIndex[i + 1] - 1;
	//		X[i] = Y[i];
	//		for (int j = K1; j <= K2; j++)
	//		{
	//			X[i] = X[i] + mtx.Value[j] * X[mtx.Col[j]];
	//		}
	//	}
	//}

}