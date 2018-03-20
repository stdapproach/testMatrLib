#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "wrarma.h"

namespace test {

inline
void byArmaExample1() {
    using namespace matrLib;
    using namespace std;
    //
    constexpr auto M = typeLib::Arma;

    auto A = wr::_::make<M>(2, 3);
    cout << "A.n_rows: " << wr::rows(A) << endl;
    cout << "A.n_cols: " << wr::cols(A) << endl;

    wr::elem(A, 1, 2) = 456.0;  // directly access an element (indexing starts at 0)
    wr::print("A:", A);

    wr::assign(A, 5.0);// scalars are treated as a 1x1 matrix
    wr::print("A:", A);

    wr::set_size(A, 4, 5); // change the size (data is not preserved)
    wr::print("A:", wr::fill(A, 5));

    {
        using namespace arma;
        // endr indicates "end of row"
        A << 0.165300 << 0.454037 << 0.995795 << 0.124098 << 0.047084 << endr
          << 0.688782 << 0.036549 << 0.552848 << 0.937664 << 0.866401 << endr
          << 0.348740 << 0.479388 << 0.506228 << 0.145673 << 0.491547 << endr
          << 0.148678 << 0.682258 << 0.571154 << 0.874724 << 0.444632 << endr
          << 0.245726 << 0.595218 << 0.409327 << 0.367827 << 0.385736 << endr;
        A.print("A:");
        cout << "det(A): " << wr::det(A) << ", det(A): -0.0246018" << endl;
    }

    // inverse
    cout << "inv(A): " << endl << wr::inv(A) << endl;

    // save matrix as a text file
    wr::save(A, "A.txt");

    // load from file
    auto B = wr::_::load<M>("A.txt");
    wr::print("B:", B);
}

}

#endif // TEST_H
