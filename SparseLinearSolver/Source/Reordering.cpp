#include "Reordering.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mkl_pardiso.h"
#include "mkl_types.h"
#include <iostream>


namespace Reordering
{
	Result Reordering::Run(const Data& iData, Report& oReport) const
	{
        auto& values = iData._values;
        auto& rowIndex = iData._rowIndex;
        auto& colomns = iData._colomns;

        auto nRows = int64_t(rowIndex.size()) - 1;

        auto& permutation = oReport._permutation;
        permutation.resize(nRows, 0);


        MKL_INT mtype = -2;       /* Real symmetric matrix */

        MKL_INT nrhs = 0;     /* Number of right hand sides. */
        
        /* Internal solver memory pointer pt, */
        void* pt[64];
        /* -------------------------------------------------------------------- */
        /* .. Initialize the internal solver memory pointer. This is only */
        /* necessary for the FIRST call of the PARDISO solver. */
        /* -------------------------------------------------------------------- */
        for (auto i = 0; i < 64; i++)
        {
            pt[i] = 0;
        }


        /* Pardiso control parameters. */
        MKL_INT iparm[64];
        MKL_INT maxfct, mnum, phase, error, msglvl;
        /* Auxiliary variables. */
        double ddum;          /* Double dummy */
        /* -------------------------------------------------------------------- */
        /* .. Setup Pardiso control parameters. */
        /* -------------------------------------------------------------------- */
        for (auto i = 0; i < 64; i++)
        {
            iparm[i] = 0;
        }
        iparm[0] = 1;         /* No solver default */
        iparm[1] = 2;         /* Fill-in reordering from METIS */
        iparm[3] = 0;         /* No iterative-direct algorithm */
        iparm[4] = 2;         /* Get permutation   */
        iparm[5] = 0;         /* Write solution into x */
        iparm[6] = 0;         /* Not in use */
        iparm[7] = 2;         /* Max numbers of iterative refinement steps */
        iparm[8] = 0;         /* Not in use */
        iparm[9] = 13;        /* Perturb the pivot elements with 1E-13 */
        iparm[10] = 1;        /* Use nonsymmetric permutation and scaling MPS */
        iparm[11] = 0;        /* Not in use */
        iparm[12] = 0;        /* Maximum weighted matching algorithm is switched-off (default for symmetric). Try iparm[12] = 1 in case of inappropriate accuracy */
        iparm[13] = 0;        /* Output: Number of perturbed pivots */
        iparm[14] = 0;        /* Not in use */
        iparm[15] = 0;        /* Not in use */
        iparm[16] = 0;        /* Not in use */
        iparm[17] = -1;       /* Output: Number of nonzeros in the factor LU */
        iparm[18] = -1;       /* Output: Mflops for LU factorization */
        iparm[19] = 0;        /* Output: Numbers of CG Iterations */
        maxfct = 1;           /* Maximum number of numerical factorizations. */
        mnum = 1;         /* Which factorization to use. */
        msglvl = 1;           /* Print statistical information in file */
        error = 0;            /* Initialize error flag */
        
        /* -------------------------------------------------------------------- */
        /* .. Reordering and Symbolic Factorization. This step also allocates */
        /* all memory that is necessary for the factorization. */
        /* -------------------------------------------------------------------- */
        phase = 11;
        PARDISO(pt, &maxfct, &mnum, &mtype, &phase,
            &nRows, values.data(), rowIndex.data(), colomns.data(), permutation.data(), &nrhs, iparm, &msglvl, &ddum, &ddum, &error);
        if (error != 0)
        {
            return Result::InvalidData;
        }

        phase = -1;           /* Release internal memory. */
        PARDISO(pt, &maxfct, &mnum, &mtype, &phase,
            &nRows, values.data(), rowIndex.data(), colomns.data(), permutation.data(), &nrhs, iparm, &msglvl, &ddum, &ddum, &error);
        if (error != 0)
        {
            return Result::InvalidData;
        }

        std::cout << "\nReordering completed ...";
        std::cout << "\nNumber of nonzeros in factors = "<< iparm[17];
        std::cout << "\nNumber of factorization MFLOPS = "<< iparm[18];
        std::cout << "\n";

        return Result::Success;
	}
}