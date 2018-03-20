#include <iostream>

#include "wrarma.h"
#include "mathutil.h"

#include "test.h"

int main()
{
    using namespace matrLib;
    using namespace std;

    constexpr auto M{typeLib::Arma};
    cout << "libName: " << description<M>::name << endl;
    cout << "libVersion: " << description<M>::version() << endl;

    //test::byArmaExample1();

    auto G7 = wr::_::load<M>("../tests/Gilbert7_o.prn");
    wr::print("G7:", G7);
    //
    auto detG7_t = wr::det(G7);
    auto detG7_o_m = wr::_::load<M>("../tests/detGilbert7_o.prn");
    auto detG7_o = wr::elem(detG7_o_m, 0, 0);
    cout << "detG7_t=" << detG7_t << " , detG7_o=" << detG7_o << endl;
    cout << "variation(detG7)=" << mathUtil::variation(detG7_t, detG7_o) << endl;
    //
    auto invG7_t = wr::inv(G7);
    //invG7_t.print("invG7_t:");
    auto invG7_o = wr::_::load<M>("../tests/invG7_o.prn");
    //
    auto mVarInvG7 = wr::_::matVariation<M>(invG7_t, invG7_o);
    mVarInvG7.print("mVarInvG7:");
    auto interval = wr::getInterval(mVarInvG7);
    cout << wr::intervalToString(interval).str() << endl;

    return 0;
}
