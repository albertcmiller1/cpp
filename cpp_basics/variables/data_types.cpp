#include <iostream> 
#include <climits>
#include <cfloat>

int main(){
    // no need to put signed keyword since ints use that be default 
    short blue {4};
    signed short int foo = 1;           // at least 16 bits
    signed int bar = 2;                 // at least 16 bits 
    signed long int bazz(4);            // at least 32 bits 
    signed long long int boop = 5;      // at least 64 bits 


    // unsigned ints can never be negative 
    unsigned short int fazz = 4;                    // at least 16 bits 
    unsigned int blazz = 8;                         // at least 16 bits      
    unsigned long int jazzz = 9;                    // at least 32 bits 
    unsigned long int jazz {12'432'352'233};        // at least 32 bits 
    unsigned long long int zz = 44;                 // at least 64 bits 

    // non int numbers 
    float loo = 23.32;                  // 7 decimal digits 
    double boo = 53.12;                 // 15 decimal digits      
    long double noo = 23.53;            // 19 decimal digits 

    // bools 
    // true = any non zero number 
    // false = 0 
    bool isTrue = true;
    bool isFalse = false; 

    std::cout << "the value of isTrue is " << isTrue << std::endl;      // prints 1
    std::cout << "the value of isFalse is " << isFalse << std::endl;    // prints 0
    std::cout << "\n" << std::endl;

    // chars must be single quote 
    char middle = 'c'; 
    char middle_initial{'c'};

    // cool functions 
    std::cout << "size is " << sizeof(loo) << std::endl; // returns the number of bytes used 
    std::cout << "float size " << sizeof(float) << std::endl; // returns the number of bytes used 
    std::cout << "\n" << std::endl;

    std::cout << "max values: " << std::endl;
    std::cout << "char: " << CHAR_MAX << std::endl;
    std::cout << "int: " << INT_MAX << std::endl;
    std::cout << "short: " << SHRT_MAX << std::endl;
    std::cout << "long: " << LONG_MAX << std::endl;
    std::cout << "long long: " << LLONG_MAX << std::endl;

    std::cout << "\n" << std::endl;


    std::cout << "min values: " << std::endl;
    std::cout << "char: " << CHAR_MIN << std::endl;
    std::cout << "int: " << INT_MIN << std::endl;
    std::cout << "short: " << SHRT_MIN << std::endl;
    std::cout << "long: " << LONG_MIN << std::endl;
    std::cout << "long long: " << LLONG_MIN << std::endl;
}