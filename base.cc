#include "base.h"
#include <cassert>
#include <typeinfo>
#include <iostream>

Base::derived_map_t Base::map;

#define SERIALIZE(DerivedClass)\
template<> const std::string BaseRegister<DerivedClass>::classname(#DerivedClass);\
template<> Base *(*BaseRegister<DerivedClass>::constructor)()(&createType<DerivedClass>);\
template<> const BaseRegister<DerivedClass> BaseObject<DerivedClass>::__type_info = BaseRegister<DerivedClass>();

SERIALIZE(DerivedOne)
SERIALIZE(DerivedTwo)

int main() {
    DerivedOne *one = new DerivedOne();
    assert(one != nullptr);
    DerivedTwo *two = new DerivedTwo();
    assert(two != nullptr);

    DerivedOne *one_byname = dynamic_cast<DerivedOne*>(Base::createInstanceByName("DerivedOne"));
    assert(one_byname != nullptr);
    DerivedTwo *two_byname = dynamic_cast<DerivedTwo*>(Base::createInstanceByName("DerivedTwo"));
    assert(two_byname != nullptr);

    delete one;
    delete two;
    return 0;
}
