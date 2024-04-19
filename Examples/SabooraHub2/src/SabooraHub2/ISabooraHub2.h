#ifndef ISABOORAHUB2
#define ISABOORAHUB2

class ISabooraHub2 {
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
    virtual void toggleGardeLight() = 0;
    virtual void toggleGazeboLight() = 0;
    virtual void OpenTheDoor() = 0;
};

#endif // ISABOORAHUB2
