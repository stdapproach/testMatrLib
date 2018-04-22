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
    const auto stdDeviation = 1.0e-5;

    auto testGilbert7 = [](double stdDev) {
        constexpr auto M{typeLib::Arma};
        auto G7 = wr::_::load<M>("../tests/Gilbert7_o.prn");//wr::print("G7:", G7);

        auto testDet = [](const arma::mat& Matr, const char* pathOriginDet, double maxDevRel) {
            auto detG7_t = wr::det(Matr);
            constexpr auto M{typeLib::Arma};
            auto detG7_o = wr::_::loadNumber<M>(pathOriginDet);
            test::checkValue("dev(detG)", detG7_t, detG7_o, 4.e5);
            test::checkValueRel("devRel(detG)", detG7_t, detG7_o, maxDevRel);
        };
        testDet(G7, "../tests/detGilbert7_o.prn", stdDev);
        //
        auto testInvMatr = [](const arma::mat& Matr, const char* pathOriginInv, double maxDevRel) {
            auto invG7_t = wr::inv(Matr);
            invG7_t.print("invG7_t:");
            constexpr auto M{typeLib::Arma};
            auto invG7_o = wr::_::load<M>(pathOriginInv);
            //
            auto fr = wr::normFrobenius(invG7_o);
            cout << "Frob=" << fr << endl;

            auto fr2 = wr::normFrobenius2(invG7_o);
            cout << "Frob2=" << fr2 << endl;

            auto nFr = wr::nFr(invG7_o);
            cout << "nFr=" << nFr << endl;

            auto distFr = wr::distFrobenius(invG7_t, invG7_o);
            cout << "distFr=" << distFr << endl;

            auto dFr = wr::dFr(invG7_t, invG7_o);
            cout << "dFr=" << dFr << endl;

        };
        //testInvMatr(G7, "../tests/invG7_o.prn", stdDev);
    };
    testGilbert7(stdDeviation);
    //

    return 0;
}
