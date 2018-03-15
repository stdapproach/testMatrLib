#include <iostream>
#include "wrarma.h"

#include "mathutil.h"

using namespace arma;

void testByArmaExample1() {
    using namespace matrLib;
    auto A = wr::mk<typeLib::Arma>(2, 3);
    cout << "A.n_rows: " << wr::rows(A) << endl;
    cout << "A.n_cols: " << wr::cols(A) << endl;

    wr::elem(A, 1, 2) = 456.0;  // directly access an element (indexing starts at 0)
    wr::print("A:", A);
    //================

    wr::assign(A, 5.0);// scalars are treated as a 1x1 matrix
    wr::print("A:", A);

    wr::set_size(A, 4, 5); // change the size (data is not preserved)
    wr::print("A:", wr::fill(A, 5));

    // endr indicates "end of row"
    A << 0.165300 << 0.454037 << 0.995795 << 0.124098 << 0.047084 << endr
      << 0.688782 << 0.036549 << 0.552848 << 0.937664 << 0.866401 << endr
      << 0.348740 << 0.479388 << 0.506228 << 0.145673 << 0.491547 << endr
      << 0.148678 << 0.682258 << 0.571154 << 0.874724 << 0.444632 << endr
      << 0.245726 << 0.595218 << 0.409327 << 0.367827 << 0.385736 << endr;
    A.print("A:");
    cout << "det(A): " << wr::det(A) << endl;

    // inverse
    cout << "inv(A): " << endl << wr::inv(A) << endl;

    // save matrix as a text file
    wr::save(A, "A.txt");

    // load from file
    mat B;
    wr::load(B, "A.txt");
    B.print("B:");
    //cout << "A==B: " << (A == B) << endl;
}

//using M = matrLib::description<matrLib::typeLib::Arma>::type;
//auto matVariation(const M& A, const M& B) {
//    M B2 = B;
//    auto absB = matrLib::wr::for_each_abs(B2);
//    M res0 = A-B;
//    auto res = matrLib::wr::for_each_abs(res0);
//    auto maxB2Elem = absB.max();
//    return matrLib::wr::for_each(res, [maxB2Elem](arma::mat::elem_type& val){ val /= maxB2Elem;});
//}


int main()
{
    using namespace matrLib;
    const auto tArma{typeLib::Arma};
    cout << "Hello World!" << endl;
    cout << "libName: " << description<tArma>::name << endl;
    cout << "libVersion: " << description<tArma>::version() << endl;

    //testByArmaExample1();

    auto G7 = wr::mk<typeLib::Arma>(1, 1);
    bool res = wr::load(G7, "../tests/Gilbert7_o.prn");
    G7.print("G7:");
    //
    auto detG7_t = wr::det(G7);
    auto detG7_o_m = wr::mk<typeLib::Arma>(1, 1);
    wr::load(detG7_o_m, "../tests/detGilbert7_o.prn");
    auto detG7_o = wr::elem(detG7_o_m, 0, 0);
    cout << "detG7_t=" << detG7_t << " , detG7_o=" << detG7_o << endl;
    cout << "variation(detG7)=" << mathUtil::variation(detG7_t, detG7_o) << endl;
    //
    auto invG7_t = wr::inv(G7);
    //invG7_t.print("invG7_t:");
    auto invG7_o = wr::mk<typeLib::Arma>(1, 1);
    wr::load(invG7_o, "../tests/invG7_o.prn");
    //
    using M = matrLib::description<matrLib::typeLib::Arma>::type;
    auto mVarInvG7 = mathUtil::matVariation<M>(invG7_t, invG7_o);
    mVarInvG7.print("mVarInvG7:");
    auto interval = wr::getInterval(mVarInvG7);
    cout << wr::intervalToString(interval).str() << endl;

    return 0;
}
