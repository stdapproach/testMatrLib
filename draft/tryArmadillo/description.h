#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <string>

#include <armadillo>

#include "typelib.h"

namespace matrLib {

template<typeLib type> struct description;

template<> struct description<typeLib::Arma> {
    static constexpr auto name{"Armadillo"};
    static std::string version(){return arma::arma_version::as_string();}
    static constexpr auto typeCode{typeLib::Arma};
    using type = arma::mat;
    static constexpr uint origin{0};// index for the first element
};

}
#endif // DESCRIPTION_H
