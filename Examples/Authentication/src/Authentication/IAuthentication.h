#ifndef IAUTHENTICATION
#define IAUTHENTICATION

class IAuthentication {
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
};

#endif // IAUTHENTICATION
