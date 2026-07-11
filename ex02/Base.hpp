#ifndef BASE_HPP
#define BASE_HPP

class Base {
    public:
        // The virtual destructor makes this class polymorphic. 
        // Without this, dynamic_cast will flat-out refuse to compile.
        virtual ~Base();
};

#endif