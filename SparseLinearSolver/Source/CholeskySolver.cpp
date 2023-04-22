#include "CholeskySolver.h"

//#pragma optimize("", off)

namespace Cholesky
{
	CholeskySolver::Data::Data(const std::vector<int>& iColomn, const std::vector<int>& iRowIndex, std::vector<double>& iValues)
	{
		_matrix = std::make_shared<CRSMatrix>();
		_matrix->Col = iColomn;
		_matrix->RowIndex = iRowIndex;
		_matrix->Value = iValues;
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

		auto _mtx = iData._matrix;
		if (!_mtx)
			return Result::InvalidData;

		return result;
	}
}