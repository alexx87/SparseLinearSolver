#include <iostream>
#include <vector>

#include "Graph.h"
#include "CholeskySolver.h"
#include "Reordering.h"
#include "ReorderingRCM.h"



int main (void)
{
    /* Matrix data. */
    auto matrix=std::make_shared< Cholesky::CRSMatrix>();
    matrix->RowIndex = { 1, 5, 8, 10, 12, 15, 17, 18, 19};
    matrix->Col =
    { 1,    3,       6, 7,
         2, 3,    5,
            3,             8,
               4,       7,
                  5, 6, 7,
                     6,    8,
                        7,
                           8
    };
    matrix->Value =
    { 7.0,      1.0,           2.0, 7.0,
          -4.0, 8.0,      2.0,
                1.0,                     5.0,
                     7.0,           9.0,
                          5.0, 1.0, 5.0,
                              -1.0,      5.0,
                                   11.0,
                                         5.0
    };
    matrix->zeroIndexing = false;
    std::vector<int64_t> permutation;
    {
        auto data = Reordering::Reordering::Data(matrix->Col, matrix->RowIndex, matrix->Value);
        auto report = Reordering::Reordering::Report();
        auto reordering = Reordering::Reordering();
        auto res = reordering.Run(data, report);
        if (res != Result::Success)
            std::cout << " Error during reordering\n";
        else
            std::cout << "Successful reordering";
        permutation = report.GetPermutation();
    }

    std::vector<int64_t> permutation2;
    { 
        auto matrix = std::make_shared< Cholesky::CRSMatrix>();
        //matrix->RowIndex = { 1, 4, 7, 9, 10, 12, 13};
        //matrix->Col =
        //{ 1, 2,          6,
        //     2, 3, 4, 
        //        3,    5,   
        //           4,      
        //              5, 6,
        //                 6,                 
        //};
        //matrix->Value =
        //{ 1, 2,          6,
        //     2, 3, 4,
        //        3,    5,
        //           4,
        //              5, 6,
        //                 6
        //};

        //matrix->RowIndex = { 1, 4, 5, 9, 12, 13, 15,16,17 };
        //matrix->Col =
        //{ 1, 2,          6, 
        //     2, 
        //        3,    5,    7, 8,
        //           4,       7, 8,
        //              5, 
        //                 6,    8,
        //                    7,
        //                       8
        //};
        //matrix->Value =
        //{ 1, 2,          6,
        //     2,
        //        3,    5,    7, 8,
        //           4,       7, 8,
        //              5,
        //                 6,    8,
        //                    7,
        //                       8
        //};

        matrix->RowIndex = { 1, 4, 9, 12, 15, 17, 20, 22,23,24,25};
        matrix->Col =
        { 1,       4,    6, 
             2, 3,    5,    7,       10,
                3, 4, 5,   
                   4,    6,       9, 
                      5,    7, 
                         6, 7, 8,  
                            7, 8,  
                               8, 
                                  9, 
                                     10
        };
        matrix->Value =
        { 1,       4,    6,
             2, 3,    5,    7,       0,
                3, 4, 5,
                   4,    6,       9,
                      5,    7,
                         6, 7, 8,
                            7, 8,
                               8,
                                  9,
                                     0
        };
        matrix->zeroIndexing = false;
        matrix->ConvertIndicesFromZero();

        auto reordering = Reordering::ReorderingRCM();
        auto data = Reordering::ReorderingRCM::Data(matrix);
        auto report = Reordering::ReorderingRCM::Report();
        auto res=reordering.Run(data, report);
        //auto graph = Reordering::Graph();
        //auto res=graph.Create(matrix);
        
        if (res != Result::Success)
            std::cout << " Error during reordering\n";
        else
            std::cout << "Successful reordering";
        //permutation = report.GetPermutation();
    }

    {
        auto data = Cholesky::CholeskySolver::Data(matrix->Col, matrix->RowIndex, matrix->Value, matrix->zeroIndexing);
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
