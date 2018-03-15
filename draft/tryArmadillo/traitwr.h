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
}

}

#endif // TRAITWR_H
