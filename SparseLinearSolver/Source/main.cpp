
#include <iostream>
#include <fstream>


int main (void)
{
    /* Matrix data. */
    int n = 8;
    int ia[9] = { 1, 5, 8, 10, 12, 15, 17, 18, 19};
    int ja[18] =
    { 1,    3,       6, 7,
         2, 3,    5,
            3,             8,
               4,       7,
                  5, 6, 7,
                     6,    8,
                        7,
                           8
    };
    double a[18] = 
    { 7.0,      1.0,           2.0, 7.0,
          -4.0, 8.0,      2.0,
                1.0,                     5.0,
                     7.0,           9.0,
                          5.0, 1.0, 5.0,
                              -1.0,      5.0,
                                   11.0,
                                         5.0
    };
   
    std::ofstream fout;

    std::cin.get();
    return 0;
}
