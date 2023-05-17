#include  "ReorderingRCM.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>

namespace Reordering
{
    Result ReorderingRCM::Run(const Data& iData, Report& oReport) const
    {
        auto res = _Run(iData, oReport);

        return res;
    }

    Result ReorderingRCM::_Run(const Data& iData, Report& oReport) const
    {
        auto& values = iData._values;
        auto& rowIndex = iData._rowIndex;
        auto& colomns = iData._colomns;

        //auto res = _GetGraph(rowIndex, colomns);


        return Result::Success;
    }
    
}