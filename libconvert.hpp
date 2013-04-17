/*  =======================================================================
 *  libconvert.hpp
 *
 *  Type conversion functions.
 *  See http://www.parashift.com/c++-faq-lite/misc-technical-issues.html
 *
 *  Author: Vincent Leroy <vincent.n.leroy@gmail.com>
 *  Version: 1.0.0
 *  Last edit: 10/04/2013
 *  ======================================================================= 
 */

#ifndef LIBCONVERT_H
#define LIBCONVERT_H

#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <stdexcept>

namespace cvt {

    class BadConversion : public std::runtime_error {
        public:
            BadConversion(const std::string& s) : std::runtime_error(s) { }
    };

    template<typename T>
    inline std::string stringify(const T& x) {
        /*  Converts any type or class supporting the << operator to a string.
         *  Convenient to build strings out of heteregeneously typed sets of variables.
         *  Sample usage:
         *      std::string s = "this is a Foo: " + stringify(x);
         */

        std::ostringstream o;
        if (!(o << x))
            throw BadConversion(  std::string("stringify(") + typeid(x).name() + ")"  );
        return o.str();
    }


    template<typename T>
    inline void convert(const std::string& s, T& x, bool failIfLeftoverChars = true) {
        /*  Converts a string to any type supporting iostream.
         *  Sample usage:
         *      std::string s = ...a string representation of a Foo...;
         *      ...
         *      Foo x;
         *      convert(s, x);
         *  x is then set to the values s represents.
         */

        std::istringstream i(s);
        char c;
        if (!(i >> x) || (failIfLeftoverChars && i.get(c)))
            throw BadConversion(s);
    }


    template<typename T>
    inline T convertTo(const std::string& s, bool failIfLeftoverChars = true) {
        /*  Converts any type to any type.
         *  Sample usage:
         *      std::string a = "1";
         *      int b = converTo<int>(a);
         */

        T x;
        convert(s, x, failIfLeftoverChars);
        return x;
    }
}

#endif // LIBCONVERT_H
