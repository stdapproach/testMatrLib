#ifndef WRARMA_H
#define WRARMA_H

#include <tuple>
#include "description.h"
#include "traitwr.h"

namespace matrLib {
namespace wr {
    template<> inline
    auto mk<typeLib::Arma>(uint rows, uint cols){return arma::mat(rows, cols);}

    template<> inline
    auto rows<arma::mat>(const arma::mat& m){return m.n_rows;}// .n_rows and .n_cols are read only

    template<> inline
    auto cols<arma::mat>(const arma::mat& m){return m.n_cols;}

    template<> inline
    auto& elem<arma::mat>(arma::mat& m, int row, int col){return m(row, col);}

    template<> inline
    const auto& elem<arma::mat>(const arma::mat& m, int row, int col){return m(row, col);}

    template<> inline
    void print<arma::mat>(const char* prefix, const arma::mat& m){m.print(prefix);}

    template<> inline
    auto& assign<arma::mat>(arma::mat& m, double rv){m = rv; return m;}

    template<> inline// change the size (data is not preserved)
    auto& set_size<arma::mat>(arma::mat& m, uint nrow, uint ncol){m.set_size(nrow, ncol); return m;}

    template<> inline
    auto& fill<arma::mat>(arma::mat& t, double val) {
        t.fill(val);
        return t;
    }

    template<> inline
    auto det<arma::mat>(const arma::mat& t) {
        return arma::det(t);
    }

    template<> inline
    auto inv<arma::mat>(const arma::mat& t) {
        return arma::inv(t);
    }

    template<> inline
    auto save<arma::mat>(const arma::mat& t, const char* fileName) {
        return t.save(fileName, arma::raw_ascii);
    }

    template<> inline
    auto load<arma::mat>(arma::mat& t, const char* fileName) {
        return t.load(fileName);
    }

    auto for_each(arma::mat& t, std::function<void(arma::mat::elem_type& val)> f) {
        t.for_each(f);
        return t;
    }

    auto for_each_abs(arma::mat& t) {
        return for_each(t, [](arma::mat::elem_type& val) { val = fabs(val); });
    }

    auto getInterval(const arma::mat& t) {
        return std::make_tuple(t.min(), t.max());
    }

    template<typename T>
    auto intervalToString(const std::tuple<T,T>& t) {
        std::ostringstream buf;
        buf << "(" << std::get<0>(t) << "; " << std::get<1>(t) << ")";
        return buf;
    }
}

}

#endif // WRARMA_H
