#include <iostream>
#include <vector>
#include "CholeskySolver.h"


int main (void)
{
    /* Matrix data. */
    std::vector<int> ia = { 1, 5, 8, 10, 12, 15, 17, 18, 19};
    std::vector<int> ja =
    { 1,    3,       6, 7,
         2, 3,    5,
            3,             8,
               4,       7,
                  5, 6, 7,
                     6,    8,
                        7,
                           8
    };
    std::vector<double> a = 
    { 7.0,      1.0,           2.0, 7.0,
          -4.0, 8.0,      2.0,
                1.0,                     5.0,
                     7.0,           9.0,
                          5.0, 1.0, 5.0,
                              -1.0,      5.0,
                                   11.0,
                                         5.0
    };

    auto data = Cholesky::CholeskySolver::Data(ia, ja, a);
    auto report = Cholesky::CholeskySolver::Report();

    auto solver = Cholesky::CholeskySolver();
    auto result = solver.Run(data, report);

    if (result != Result::Success)
        std::cout << " Error\n";
    else
        std::cout << "Success";

    std::cin.get();
    return 0;
}
