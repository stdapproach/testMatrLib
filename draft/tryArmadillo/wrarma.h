#ifndef WRARMA_H
#define WRARMA_H

#include <tuple>
#include "description.h"
#include "traitwr.h"

namespace matrLib {
namespace wr {
    template<> inline
    auto mk<typeLib::Arma>(uint rows, uint cols){return arma::mat(rows, cols);}

    struct _ {
        using enumT = unsigned char;

        template<enumT>
        static auto make(uint rows, uint cols);

        template<> inline
        static auto make<typeLib::Arma>(uint rows, uint cols){
            return arma::mat(rows, cols);
        }

        template<enumT>
        static auto make();

        template<> inline
        static auto make<typeLib::Arma>(){
            return arma::mat(1, 1);
        }

        template<enumT>
        static auto load(const char* fileName);

        template<> inline
        static auto load<typeLib::Arma>(const char* fileName) {
            arma::mat&& t = arma::mat(1, 1);
            /*auto res =*/ t.load(fileName);
            return t;
        }

        template<enumT, typename M, typename Elem>
        static auto for_each(M& t, std::function<void(Elem& val)> f);

        template<> inline
        static auto for_each
        <typeLib::Arma, arma::mat, arma::mat::elem_type>(
                arma::mat& t, std::function<void(arma::mat::elem_type& val)> f) {
            t.for_each(f);
            return t;
        }

        template<enumT, typename M>
        static auto for_each_abs(M& t);

        template<> inline
        static auto for_each_abs<typeLib::Arma>(arma::mat& t) {
            return for_each<typeLib::Arma, arma::mat, arma::mat::elem_type>(t, [](arma::mat::elem_type& val) { val = fabs(val); });
        }

        template<enumT t>
        static auto matVariation(
                const typename description<t>::type&,
                const typename description<t>::type&);

        template<> inline
        static auto matVariation<typeLib::Arma>(
                const description<typeLib::Arma>::type& A,
                const description<typeLib::Arma>::type& B){
           using M = description<typeLib::Arma>::type;
           M B2 = B;
           auto absB = matrLib::wr::_::for_each_abs<typeLib::Arma>(B2);
           M res0 = A-B;
           auto res = matrLib::wr::_::for_each_abs<typeLib::Arma>(res0);
           auto maxB2Elem = absB.max();
           return matrLib::wr::_::for_each<typeLib::Arma, arma::mat, arma::mat::elem_type>(
                       res, [maxB2Elem](arma::mat::elem_type& val){ val /= maxB2Elem;}
           );
        }
    };


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
