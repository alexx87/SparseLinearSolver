#include <iostream>
#include <vector>
#include "CholeskySolver.h"
#include "Reordering.h"

int main (void)
{
    /* Matrix data. */
    std::vector<int64_t> rowIndex = { 1, 5, 8, 10, 12, 15, 17, 18, 19};
    std::vector<int64_t> colomns =
    { 1,    3,       6, 7,
         2, 3,    5,
            3,             8,
               4,       7,
                  5, 6, 7,
                     6,    8,
                        7,
                           8
    };
    std::vector<double> values = 
    { 7.0,      1.0,           2.0, 7.0,
          -4.0, 8.0,      2.0,
                1.0,                     5.0,
                     7.0,           9.0,
                          5.0, 1.0, 5.0,
                              -1.0,      5.0,
                                   11.0,
                                         5.0
    };

    std::vector<int64_t> permutation;
    {
        auto data = Reordering::Reordering::Data(colomns, rowIndex, values);
        auto report = Reordering::Reordering::Report();
        auto reordering = Reordering::Reordering();
        auto res = reordering.Run(data, report);
        if (res != Result::Success)
            std::cout << " Error during reordering\n";
        else
            std::cout << "Successful reordering";
        permutation = report.GetPermutation();
    }

    {
        bool zeroIndexing = false;
        auto data = Cholesky::CholeskySolver::Data(colomns, rowIndex, values, zeroIndexing);
        auto report = Cholesky::CholeskySolver::Report();
        auto solver = Cholesky::CholeskySolver();
        auto res = solver.Run(data, report);
        if (res != Result::Success)
            std::cout << " Error during factorization\n";
        else
            std::cout << "Successful numerical factorization";
    }

    std::cin.get();
    return 0;
}
