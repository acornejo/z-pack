#ifndef __BASE_H__
#define __BASE_H__

#include <map>
#include <string>
#include <iostream>

class Base {
private:
    typedef std::map<std::string, Base*(*)()> derived_map_t;
    static derived_map_t map;

public:
    virtual ~Base() {}
    virtual const std::string &ClassName() const = 0;
    virtual Base *Copy() const = 0;
    static Base *createInstanceByName(const std::string &classname) {
        derived_map_t::const_iterator it = map.find(classname);
        if (it != map.end())
            return it->second();
        else
            return nullptr;
    }
    static void registerClass(const std::string &classname, Base *(*constructor)()) {
        map.insert(std::make_pair(classname, constructor));
    }
};

template<typename T>
Base *createType() { return new T; }

template<typename T>
class BaseRegister {
public:
    static const std::string classname;
    static Base *(*constructor)();
    BaseRegister() {
        Base::registerClass(classname, constructor);
    }
};

template<typename T>
class BaseObject: public Base {
private:
    static const BaseRegister<T> __type_info;
public:
    const std::string &ClassName() const {
        return BaseRegister<T>::classname;
    }
    Base *Copy() const {
        return BaseRegister<T>::constructor();
    }
};


class DerivedOne: public BaseObject<DerivedOne> {
public:
    int prop_one;
};

class DerivedTwo: public BaseObject<DerivedTwo> {
public:
    int prop_two;
};

#endif//__BASE_H__
