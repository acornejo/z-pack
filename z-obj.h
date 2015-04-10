// http://stackoverflow.com/questions/582331/is-there-a-way-to-instantiate-objects-from-a-string-holding-their-class-name

class ZInputStream {
    template <typename T>
    void prop(const std::string &name, T &) {
        stream << T;
    }
};

class ZOutputStream {
    template <typename T>
    void prop(const std::string &name, T &) {
        stream >> T;
    }
};

class Zmsg {
public:
    virtual void serialize(Zstream *m) = 0;
    void store(ZOutputStream &m, Zmsg *obj) {
        assert(obj);
        m  << obj->ClassName();
        obj->serialize (m);
    }
    static Zmsg *load(ZInputStream &m) {
        std::string classname;
        m >> classname;
        Zmsg *obj = CreateByClassName(classname);
        assert(obj);
        obj->serialize (m);
    }
};


class Obj: public Zmsg {
private:
    static ZRegister<Obj> reg;

public:
    Obj(): Zmsg() {
    }

    template <class Archive>
    virtual void serialize(Archive &m) {
        m.prop("i", i);
        m.prop("j", j);
    }
}

// how to remove this!
ZRegister<Obj> Obj::reg("Obj");


void receive(const std::string &tag, Zmsg *msg) {

}

void send(const std::string &tag, Zmsg *msg) {

}

class ZPipeIn {
    void connect(const std::string &host);
    void subscribe(const std::string &tag, recv_t);
};

class ZPipeOut {
    void bind(const std::string &host);
    void publish(const std::string &tag, Zmsg *msg);
};
