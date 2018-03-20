#ifndef TYPELIB_H
#define TYPELIB_H

namespace matrLib {

using uint = unsigned int;

enum stub {
    first=1
};

enum class typeLib : unsigned char {
    null = 0x00,
    unkn = 0x01,
    Arma = 0x10 , // Armadillo
    // also ...
};

}

#endif // TYPELIB_H
