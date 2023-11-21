import shutil
import json
import os

from entity_and_controller import generate_entity_and_controller, generate_crud
from api_class import generate_api_class, generate_apis_file, generate_permissions_file
from config import generate_config, generate_config_key
from devicemanager import generate_devicemanager
from project_class import generate_main_classes, generate_project_class
from postman import generate_postman_json
from certificate_generator import generate_certificate

def generate_file(file_path, code):
    # This function writes code to a file. It first checks if the file already exists.
    if not os.path.exists(file_path):
        with open(file_path, 'w') as f:
            f.write(code)

def generate_all(json_data):
    # This function orchestrates the entire code generation process.

    # Step 1: Load the JSON data.
    project_name = json_data["ProjectName"]
    project_path = json_data["ProjectPath"]
    entities = json_data["Entities"]
    apis = json_data["Apis"]
    configs = json_data["Configs"]
    modules = json_data["Modules"]

    # Step 2: Generate the code.
    entity_code = [generate_entity_and_controller(entity) for entity in entities]
    cruds_code = [generate_crud(project_name, entity) for entity in entities]
    api_code = [generate_api_class(project_name, api) for api in apis]
    device_manager_code = generate_devicemanager(modules)
    config_code = generate_config(configs, project_name)
    config_key_code = generate_config_key(configs, project_name)
    project_code = generate_project_class(project_name)
    main_code = generate_main_classes(project_name)
    apis_file = generate_apis_file(project_name, apis, entities)
    postman_import = generate_postman_json(json_data)
    permissions = []
    
    # Step 3: Create directories if they do not exist.
    os.makedirs(os.path.join(project_path, project_name, 'postman_import'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src', 'Apis'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src', 'Config'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src', 'Database', 'Controllers'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src', 'Database', 'Entities'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src', 'DeviceManager'), exist_ok=True)
    os.makedirs(os.path.join(project_path, project_name, 'src', project_name), exist_ok=True)

    # Step 4: Write the code to .h files.
    for entity in entity_code:
        generate_file(os.path.join(project_path, project_name, 'src', 'Database', 'Entities', entity['entity_name'] + '.h'), entity['code'])
        generate_file(os.path.join(project_path, project_name, 'src', 'Database', 'Controllers', entity['controller_name'] + '.h'), entity['controller_code'])
            
    for crud in cruds_code:
        generate_file(os.path.join(project_path, project_name, 'src', 'Apis', crud['api_name'] + '.h'), crud['code'])
        for permission in crud['permissions']:
            permissions.append(permission)

    for api in api_code:
        generate_file(os.path.join(project_path, project_name, 'src', 'Apis', api['name'] + '.h'), api['code'])
        for permission in api['permissions']:
            permissions.append(permission)

    permissions_code = generate_permissions_file(project_name, permissions)
    
    # Call the function and capture the output
    cert_key_data = generate_certificate()



    generate_file(os.path.join(project_path, project_name, 'src', 'Apis', 'Apis.h'), apis_file)
    generate_file(os.path.join(project_path, project_name, 'src', 'Apis', 'Permissions.h'), permissions_code)

    generate_file(os.path.join(project_path, project_name, 'src', 'Config', project_name + 'Config.h'), config_code['config_code'])
    generate_file(os.path.join(project_path, project_name, 'src', 'Config', 'Default' + project_name + 'Configs.h'), config_code['default_config_code'])
    generate_file(os.path.join(project_path, project_name, 'src', 'Config', project_name + 'ConfigKeys.h'), config_key_code)
    generate_file(os.path.join(project_path, project_name, 'src', 'Database', 'Controllers', project_name + 'ConfigController.h'), config_code['config_controller_code'])

    generate_file(os.path.join(project_path, project_name, 'src', 'DeviceManager', 'DeviceManager.h'), device_manager_code['devicemanager_code'])
    generate_file(os.path.join(project_path, project_name, 'src', 'DeviceManager', 'IDeviceManager.h'), device_manager_code['idevicemanager_code'])

    generate_file(os.path.join(project_path, project_name, 'src', project_name, 'I'+project_name+'.h'), project_code['iproject_code'])
    generate_file(os.path.join(project_path, project_name, 'src', project_name, project_name+'.h'), project_code['project_code'])
    
    # generate_file(os.path.join(project_path, project_name, 'src', 'Pins.h'), device_manager_code['pins_code'])
    generate_file(os.path.join(project_path, project_name, 'src', 'AppContext.h'), main_code['appcontext_code'])
    generate_file(os.path.join(project_path, project_name, 'src', 'Runtime.h'), main_code['runtime_code'])
    generate_file(os.path.join(project_path, project_name, 'src', 'cert_key.h'), cert_key_data)
    generate_file(os.path.join(project_path, project_name, project_name + '.ino'), main_code['main_ino_code'])
    generate_file(os.path.join(project_path, project_name, 'postman_import', project_name + '.json'), json.dumps(postman_import))
    return { 'message' : f"Code generation for the project '{project_name}' is complete. You can find all the generated files at:\n{project_path}.\n\n\n*** Enjoy It! :) ***\nhadalipoor@gmail.com\nOStad.wiki",
            'project_path' : project_path,
            'project_name' : project_name
    }
