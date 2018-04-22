#ifndef TRAITWR_H
#define TRAITWR_H

namespace matrLib {
namespace wr {
    template<typeLib> inline
    auto mk(uint rows, uint cols);

    template<typename T> inline
    auto rows(const T& m);

    template<typename T> inline
    auto cols(const T& m);

    template<typename T> inline
    auto& elem(T& m, int row, int col);

    template<typename T> inline
    const auto& elem(const T& m, int row, int col);

    template<typename T> inline
    void print(const char* prefix, const T& m);

    template<typename T> inline
    auto& assign(T& t, double rv);// kind an operator=()

    template<typename T> inline
    auto& set_size(T& t, uint nrow, uint ncol);

    template<typename T> inline
    auto& fill(T& t, double val);// set all elements to a particular value

    template<typename T> inline
    auto det(const T& t);// determinant

    template<typename T> inline
    auto inv(const T& t);// inverse matrix

    template<typename T> inline
    auto save(const T& t, const char* fileName);

    template<typename T> inline
    auto load(T& t, const char* fileName);

    template<typename T> inline
    auto abs(const T& t);// Obtain the magnitude of each element

    template<typename T> inline
    auto conj(const T& t);// Obtain the complex conjugate of each element in a complex matrix or cube

    template<typename T> inline
    auto max(const T& t);// extremum value of any matrix

    template<typename T> inline
    auto maxAbs(const T& t);

    template<typename T> inline
    auto hermit(const T& t);//hermitian matrix

    template<typename T> inline
    auto trace(const T& t);

    template<typename T> inline
    auto normFrobenius(const T& t);

    template<typename T> inline
    auto normFrobenius2(const T& t);

    template<typename T> inline
    auto nFr(const T& t);// Frobenius norm div by matrMaxElem

    template<typename T> inline
    auto distFrobenius(const T& a, const T& b);

    template<typename T> inline
    auto dFr(const T& a, const T& b);// Frobenius norm div by matrMaxElem(a-b)
}

}

#endif // TRAITWR_H
