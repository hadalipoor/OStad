def generate_devicemanager(modules):
    module_types = ['Buttons', 'LCD16X2s', 'OLEDLCDs', 'Relays', 'SoilMoistureSensors']

    idevicemanager_code_template = '''
#ifndef IDEVICEMANAGER_H
#define IDEVICEMANAGER_H

#include <EBPInterfaces.h>

class IDeviceManager
{{
public:
    virtual ~IDeviceManager(){{}}

    virtual void initialize() = 0;
    virtual void update() = 0;
{getters}
}};

#endif
'''

    devicemanager_code_template = '''
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

class DeviceManager : public IDeviceManager
{{
private:
    AppContext* appContext;
    {module_names}
public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    {getter_implementations}
}};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {{

}}

{initialize}

{update}

{getter_impl}

#endif
'''

    pins_code_template = '''
#ifndef PINS_H
#define PINS_H

class Pins
{{
public:
    static const uint8_t SD_CARD;
    static const uint8_t BUILTIN_LED;
    
    {module_pins}
}};

const uint8_t Pins::SD_CARD = 5;
const uint8_t Pins::BUILTIN_LED = 2;

{module_pin_values}

#endif //PINS_H
'''

    getters = ''
    module_names = []
    getter_implementations = []
    initialize = 'void DeviceManager::initialize()\n{\n'
    update = 'void DeviceManager::update()\n{\n'
    getter_impl = ''
    module_pins = ''
    module_pin_values = ''

    for module_type in module_types:
        if module_type in modules:
            for module in modules[module_type]:
                name = module['Name']
                module_names.append(f'String _{name}Str = "{name}";')
                if 'PinNumber' in module:
                    pin = module['PinNumber']
                    module_pins += 'static const uint8_t ' + name + '_PIN;\n'
                    module_pin_values = (f'const uint8_t Pins::{name}_PIN = {pin};')
    
                if module_type == 'Buttons':
                    getters += f'    virtual Button* {name}() = 0;\n'
                    getter_implementations.append(f'Button* {name}() override;')
                    module_names.append(f'Button* _{name};\n')
                    initialize += f'    _{name} = new Button({module["PinNumber"]}, "{name}", {module["ActiveHigh"]}, {module["PullUpActive"]}, {module["ButtonType"]});\n'
                    # initialize += f'    //appContext->systemContext->getModules()->addButton(_{name});\n\n'
                    update += f'    _{name}->update();\n'
                    getter_impl += f'Button* DeviceManager::{name}()\n{{\n    return appContext->systemContext->getModules()->getButton("{name}");\n}}\n\n'

                elif module_type == 'LCD16X2s':
                    getters += f'    virtual LCD16X2* {name}() = 0;\n'
                    getter_implementations.append(f'LCD16X2* {name}() override;')
                    module_names.append(f'LCD16X2* _{name};\n')
                    initialize += f'    _{name} = new LCD16X2("{name}", {module["Address"]}, {module["Width"]}, {module["Height"]});\n'
                    # initialize += f'    appContext->systemContext->getModules()->addLCD16X2(_{name});\n\n'
                    getter_impl += f'LCD16X2* DeviceManager::{name}()\n{{\n    return appContext->systemContext->getModules()->getLCD16X2("{name}");\n}}\n\n'

                elif module_type == 'OLEDLCDs':
                    getters += f'    virtual OLEDLCD* {name}() = 0;\n'
                    getter_implementations.append(f'OLEDLCD* {name}() override;')
                    module_names.append(f'OLEDLCD* _{name};\n')
                    initialize += f'    _{name} = new OLEDLCD("{name}", {module["Address"]}, {module["Columns"]}, {module["Rows"]});\n'
                    # initialize += f'    appContext->systemContext->getModules()->addOLEDLCD(_{name});\n\n'
                    getter_impl += f'OLEDLCD* DeviceManager::{name}()\n{{\n    return appContext->systemContext->getModules()->getOLEDLCD("{name}");\n}}\n\n'

                elif module_type == 'Relays':
                    getters += f'    virtual Relay* {name}() = 0;\n'
                    getter_implementations.append(f'Relay* {name}() override;')
                    module_names.append(f'Relay* _{name};\n')
                    initialize += f'    _{name} = new Relay({module["PinNumber"]}, "{name}", {module["NormallyOpen"]});\n'
                    # initialize += f'    appContext->systemContext->getModules()->addRelay(_{name});\n\n'
                    update += f'    _{name}->update();\n'
                    getter_impl += f'Relay* DeviceManager::{name}()\n{{\n    return appContext->systemContext->getModules()->getRelay("{name}");\n}}\n\n'

                elif module_type == 'SoilMoistureSensors':
                    getters += f'    virtual SoilMoistureSensor* {name}() = 0;\n'
                    getter_implementations.append(f'SoilMoistureSensor* {name}() override;')
                    module_names.append(f'SoilMoistureSensor* _{name};\n')
                    initialize += f'    _{name} = new SoilMoistureSensor("{name}", "{module["ConnectionType"]}", {module["NodeId"]}, {module["SensorPin"]}, {module["DryThreshold"]}, {module["WetThreshold"]});\n'
                    # initialize += f'    appContext->systemContext->getModules()->addSoilMoistureSensor(_{name});\n\n'
                    getter_impl += f'SoilMoistureSensor* DeviceManager::{name}()\n{{\n    return appContext->systemContext->getModules()->getSoilMoistureSensor("{name}");\n}}\n\n'

    idevicemanager_code = idevicemanager_code_template.format(
        getters=getters,
    )

    devicemanager_code = devicemanager_code_template.format(
        module_names='\n    '.join(module_names),
        getter_implementations='\n    '.join(getter_implementations),
        initialize=initialize+'}',
        update=update+'}',
        getter_impl=getter_impl,
    )

    pins_code = pins_code_template.format(
        module_pins='\n    '.join(module_pins),
        module_pin_values='\n'.join(module_pin_values),
    )

    return {'idevicemanager_code': idevicemanager_code, 'devicemanager_code': devicemanager_code, 'pins_code': pins_code}
