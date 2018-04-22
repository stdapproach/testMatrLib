#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "wrarma.h"

namespace mathUtil {

    template<typename M> inline
    M matVariation(const M& A, const M& B) {
        M B2 = B;
        auto absB = matrLib::wr::abs(B2);
        M res0 = A-B;
        auto res = matrLib::wr::abs(res0);
        auto maxB2Elem = absB.max();
        return matrLib::wr::for_each(res, [maxB2Elem](arma::mat::elem_type& val){ val /= maxB2Elem;});
    }

    inline
    auto variation(const double& A, const double& B) {
    return fabs(A-B) / fabs(B);
}

}

#endif // MATHUTIL_H
