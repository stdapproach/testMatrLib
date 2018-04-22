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
auto& elem<arma::mat>(arma::mat& m, int row, int col){return m(row, col);}

template<> inline
const auto& elem<arma::mat>(const arma::mat& m, int row, int col){return m(row, col);}

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

        template<enumT>
        static auto loadNumber(const char* fileName);

        template<> inline
        static auto loadNumber<typeLib::Arma>(const char* fileName) {
            auto t = arma::mat(1, 1);
            t.load(fileName);
            auto res = wr::elem(t, 0, 0);
            return res;
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

        template<enumT, typename M>
        static auto abs(M& t);

        template<> inline
        static auto abs<typeLib::Arma>(arma::mat& t) {
            return arma::abs(t);
        }
    };


    template<> inline
    auto rows<arma::mat>(const arma::mat& m){return m.n_rows;}// .n_rows and .n_cols are read only

    template<> inline
    auto cols<arma::mat>(const arma::mat& m){return m.n_cols;}



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
    auto det(const arma::mat& t) {
        return arma::det(t);
    }

    template<> inline
    auto inv(const arma::mat& t) {
        arma::mat res = arma::inv(t);
        return res;
    }

    template<> inline
    auto save(const arma::mat& t, const char* fileName) {
        return t.save(fileName, arma::raw_ascii);
    }

    template<> inline
    auto load(arma::mat& t, const char* fileName) {
        return t.load(fileName);
    }

    auto getInterval(const arma::mat& t) {
        return std::make_tuple(t.min(), t.max());
    }

    template<typename T> inline
    auto intervalToString(const std::tuple<T,T>& t) {
        std::ostringstream buf;
        buf << "(" << std::get<0>(t) << "; " << std::get<1>(t) << ")";
        return buf;
    }

    template<typename T> inline
    auto variation(const T& A, const T& B);

    template<> inline
    auto variation(const arma::mat& A, const arma::mat& B)
    {
       using M = arma::mat;
       M B2 = B;
       auto absB = matrLib::wr::_::for_each_abs<typeLib::Arma>(B2);
       M res0 = A-B;
       auto res = matrLib::wr::_::for_each_abs<typeLib::Arma>(res0);
       auto maxB2Elem = absB.max();
       return matrLib::wr::_::for_each<typeLib::Arma, arma::mat, arma::mat::elem_type>(
                   res, [maxB2Elem](arma::mat::elem_type& val){ val /= maxB2Elem;}
       );
    }

    template<> inline// Obtain the magnitude of each element
    auto abs(const arma::mat& t) {
        arma::mat res = arma::abs(t);
        return res;
    }

    template<> inline// Obtain the complex conjugate of each element in a complex matrix or cube
    auto conj(const arma::mat& t) {
        arma::mat res = arma::conj(t);
        return res;
    }

    template<> inline// extremum value of any matrix
    auto max(const arma::mat& t) {
        return t.max();
    }

    template<> inline
    auto maxAbs(const arma::mat& t) {
        auto a = arma::abs(t);
        return a.max();
    }

    template<> inline//hermitian matrix
    auto hermit(const arma::mat& t) {
        auto r = t.t();
        return r;
    }

    template<> inline
    auto trace(const arma::mat& t) {
        auto r = arma::trace(t);
        return r;
    }

    template<> inline
    auto normFrobenius(const arma::mat& t) {
        auto r = arma::norm(t, "fro");
        return r;
    }

    template<> inline
    auto normFrobenius2(const arma::mat& t) {
        auto th = hermit(t);
        auto m = t*th;
        auto tr = trace(m);
        auto res = sqrt(tr);
        return res;
    }

    template<> inline// Frobenius norm div by matrMaxElem
    auto nFr(const arma::mat& t) {
        auto n0 = normFrobenius(t);
        auto maxElem = maxAbs(t);
        auto res = n0/maxElem;
        return res;
    }

    template<> inline
    auto distFrobenius(const arma::mat& a, const arma::mat& b) {
        arma::mat c = a-b;
        auto res = normFrobenius(c);
        return res;
    }

    template<> inline// Frobenius norm div by matrMaxElem(a-b)
    auto dFr(const arma::mat& a, const arma::mat& b) {
        auto d0 = distFrobenius(a, b);
        arma::mat c = a-b;
        auto denom = maxAbs(c);
        return d0/denom;
    }
}

}

#endif // WRARMA_H
