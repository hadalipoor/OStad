def generate_project_class(project_name):

    iproject_code = f"""\
#ifndef I{project_name.upper()}
#define I{project_name.upper()}

class I{project_name} {{
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
}};

#endif // I{project_name.upper()}
"""

    project_code = f"""\
#ifndef {project_name.upper()}_H
#define {project_name.upper()}_H

#include "I{project_name}.h"
#include "../AppContext.h"
#include "../Config/Default{project_name}Configs.h"

class {project_name} : public I{project_name} {{
private:
    AppContext* context;

public:
    {project_name}(AppContext* context);
    
    void initialize() override;
    void update() override;
}};

{project_name}::{project_name}(AppContext* context)
    : context(context) {{}}

void {project_name}::initialize() {{

}}

void {project_name}::update() {{

}}

#endif //{project_name.upper()}_H
"""
    return {'iproject_code': iproject_code, 'project_code': project_code}

def generate_main_classes(project_name):
    appcontext_code = f"""\
#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "{project_name}/I{project_name}.h"

class AppContext
{{
private:
    IDeviceManager* _deviceManager;
    IConfig* {project_name.lower()}Config;
    I{project_name}* {project_name.lower()};

public:
    AppContext(Context* context): systemContext(context){{}}
    ~AppContext(){{}}

    IDeviceManager* getDeviceManager() {{ return _deviceManager; }}
    void setDeviceManager(IDeviceManager* deviceManager) {{ _deviceManager = deviceManager; }}

    IConfig* get{project_name}Config() {{ return {project_name.lower()}Config; }}
    void set{project_name}Config(IConfig* config) {{ {project_name.lower()}Config = config; }}
    
    I{project_name}* get{project_name}() {{ return {project_name.lower()}; }}
    void set{project_name.lower()}(I{project_name}* _{project_name.lower()}) {{ {project_name.lower()} = _{project_name.lower()}; }}
    
    Context* systemContext;
}};

#endif //APPCONTEXT_H
"""


    runtime_code = f"""
#ifndef RUNTIME_H
#define RUNTIME_H

#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define OSTAD_NETWORK_ENABLE

#include "AppContext.h"
#include "DeviceManager/DeviceManager.h"
#include "Config/{project_name}Config.h"
#include "{project_name}/{project_name}.h"
#include "Apis/Apis.h"
#include "cert_key.h"

// LogLevel definition
#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR

class Runtime
{{
private:
    OStad* ostad;
    {project_name}Config* {project_name.lower()}Config;
    DeviceManager* deviceManager;
    {project_name}* {project_name.lower()};

public:
    Runtime();
    void update();

    AppContext* appContext;
    Context* systemContext;
}};

Runtime::Runtime()
{{
    // CertificateData certificateData;
    // certificateData.certificate = const_cast<unsigned char*>(certificate);
    // certificateData.privatekey = const_cast<unsigned char*>(private_key);
    // certificateData.certificate_length = sizeof(certificate);
    // certificateData.privateky_length = sizeof(private_key);

    // ostad = new OStad(StorageType::SPIFFS_TYPE, certificateData);
    // If you want to use HTTPS on ESP32 server, add certificate and private_key and uncomment above code and comment below line
    ostad = new OStad(StorageType::SPIFFS_TYPE);

    
    systemContext = ostad->getContext();
    appContext = new AppContext(systemContext);

    {project_name.lower()}Config = new {project_name}Config(appContext);
    deviceManager = new DeviceManager(appContext);
    {project_name.lower()} = new {project_name}(appContext);

    appContext->set{project_name}Config({project_name.lower()}Config);    
    appContext->setDeviceManager(deviceManager);

    appContext->set{project_name.lower()}({project_name.lower()});

    //initialize {project_name.lower()}Config first of all initialization
    {project_name.lower()}Config->initialize();
    deviceManager->initialize();
    {project_name.lower()}->initialize();

    createApis(appContext);

    Permissions::addPermissions(systemContext);
    
    ostad->begin();
}}

void Runtime::update()
{{
    ostad->update();
    deviceManager->update();
    {project_name.lower()}->update();
}}

#endif //RUNTIME_H
"""

    main_ino_code = f"""\
#include "src/Runtime.h"

Runtime* runtime;

void setup() {{
  Serial.begin(115200);
  LittleFS.begin(true);
  runtime = new Runtime();
}}
void loop() {{
  runtime->update();
}}
"""
    return {'appcontext_code': appcontext_code, 'runtime_code': runtime_code, 'main_ino_code': main_ino_code}
