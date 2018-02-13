#include <iostream>
#include <string>

#include <armadillo>

using namespace std;
using namespace arma;

namespace matrLib {

enum class typeLib : unsigned char {
    null = 0x00,
    unkn = 0x01,
    Arma = 0x10 , // Armadillo
    // also ...
};

template<typeLib type> struct description;

template<> struct description<typeLib::Arma> {
    static std::string name(){return "Armadillo";}
    static std::string version(){return arma_version::as_string();}
};

template<typeLib type> struct wr;

template<> struct wr<typeLib::Arma> {
    template<typename T=double>inline
    static Mat <T> mk(unsigned int rows, unsigned int cols){return Mat <T>(rows, cols);}
};

}

int main()
{
    using namespace matrLib;
    const auto tArma{typeLib::Arma};
    cout << "Hello World!" << endl;
    cout << "libName: " << description<tArma>::name() << endl;
    cout << "libVersion: " << description<tArma>::version() << endl;

    auto A = wr<tArma>::mk(2,3);
    //mat A(2,3);  // directly specify the matrix size (elements are uninitialised)

    cout << "A.n_rows: " << A.n_rows << endl;  // .n_rows and .n_cols are read only
    cout << "A.n_cols: " << A.n_cols << endl;

//    A(1,2) = 456.0;  // directly access an element (indexing starts at 0)
//    A.print("A:");

//    A = 5.0;         // scalars are treated as a 1x1 matrix
//    A.print("A:");


//    A.set_size(4,5); // change the size (data is not preserved)
//    A.fill(5.0);     // set all elements to a particular value
//    A.print("A:");

//    // endr indicates "end of row"
//      A << 0.165300 << 0.454037 << 0.995795 << 0.124098 << 0.047084 << endr
//        << 0.688782 << 0.036549 << 0.552848 << 0.937664 << 0.866401 << endr
//        << 0.348740 << 0.479388 << 0.506228 << 0.145673 << 0.491547 << endr
//        << 0.148678 << 0.682258 << 0.571154 << 0.874724 << 0.444632 << endr
//        << 0.245726 << 0.595218 << 0.409327 << 0.367827 << 0.385736 << endr;

//      A.print("A:");

    return 0;
}
