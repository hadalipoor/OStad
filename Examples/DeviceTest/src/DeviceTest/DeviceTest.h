#ifndef DEVICETEST_H
#define DEVICETEST_H

#include "IDeviceTest.h"
#include "../AppContext.h"
#include "../Config/DefaultDeviceTestConfigs.h"

class DeviceTest : public IDeviceTest {
private:
    AppContext* context;

public:
    DeviceTest(AppContext* context);
    
    void initialize() override;
    void update() override;
};

DeviceTest::DeviceTest(AppContext* context)
    : context(context) {}

void DeviceTest::initialize() {

}

void DeviceTest::update() {

}

#endif //DEVICETEST_H
