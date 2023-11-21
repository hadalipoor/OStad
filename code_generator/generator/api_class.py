def get_json_type(py_type):
    json_type = ""
    
    if py_type == str:
        json_type = "String"
    elif py_type == int:
        json_type = "int"
    elif py_type == bool:
        json_type = "bool"
    elif py_type == list:
        json_type = "Array"
    elif py_type == dict:
        json_type = "Object"
    elif py_type == float:
        json_type = "Number"
    else:
        json_type = "Unknown"
        
    return json_type

def generate_apis_file(project_name, apis, entities):
    apis_file_code ='''
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
{api_includes}

void createApis(AppContext* appContext)
{{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    {api_init}

    appContext->systemContext->getNetwork()->addApis(apis);
}}

#endif //APIS_H
    '''
    api_includes = ''
    api_init = ''
    for api in apis:
        api_includes += f"""#include "{api['name']}Apis.h"\n"""
        api_init += f"""
    {api['name']}Apis* {api['name'].lower()}Apis = new {api['name']}Apis(appContext, true);
    apis.push_back({api['name'].lower()}Apis);
    """
        
    for entity in entities:
        api_includes += f"""#include "{entity['name']}Apis.h"\n"""
        api_init += f"""
    {entity['name']}Apis* {entity['name'].lower()}Apis = new {entity['name']}Apis(appContext, true);
    apis.push_back({entity['name'].lower()}Apis);
    """
    apis_file_code = apis_file_code.format(api_includes=api_includes, api_init=api_init)
    return apis_file_code


def generate_permissions_file(project_name, permissions):
    permissions_file_code = '''#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{{
public:
{permissions_declration}

    static void addPermissions(Context* context);
}};

void Permissions::addPermissions(Context* context)
{{
{add_permissions}
}}

{permissions_set_value}

#endif // PERMISSIONS_H
'''
    permissions_declration = ''
    permissions_set_value = ''
    add_permissions = ''
    for permission in permissions:
        permissions_declration += '    static const String '+permission[0]+';\n'
        permissions_set_value += 'const String Permissions::'+permission[0]+' = "'+permission[1]+'";\n'
        add_permissions += '    context->getSecurity()->addPermissionForAdmin(' + permission[0] + ', "' +  project_name + ' Permissions");\n'

    permissions_file_code = permissions_file_code.format(permissions_declration=permissions_declration, permissions_set_value=permissions_set_value, add_permissions=add_permissions)
    return permissions_file_code



def generate_api_class(project_name, api):

    base_code = '''
#ifndef {api_name}Apis_h
#define {api_name}Apis_h


#include "../AppContext.h"
#include "Permissions.h"
class {api_name}Apis : public ApiInterface
{{
private:
    AppContext* context;
    std::string class_path = "{api_url}";

public:
    {api_name}Apis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    {api_methods}
}};

{api_name}Apis::{api_name}Apis(AppContext* cntxt, bool add_apis): context(cntxt) {{
    if (!add_apis) return;

    {handle_methods}
}}

String {api_name}Apis::getClassPath()
{{
    return String(class_path.c_str());
}}


{handler_functions}

String {api_name}Apis::callFunction(String functionName, std::map<String, String> parameters) {{
    {call_functions}
    return "";
}}

#endif //{api_name}Apis_h
'''



    # Prepare API methods and handle_methods
    api_methods = []
    handle_methods = []
    handler_functions = []
    call_functions = []
    permissions = []
    for method in api['Apis']:
        parameters = ''
        var_declaration = ''
        var_definistion = ''
        if_declaration = ''
        var_input = ''
        handle_function_inputs = ''
        api_name = method['ApiName']
        api_method_name = api_name[0].lower() + api_name[1:] # convert first character to lower case
        http_method = method['Method']
        permission_name = api['Url'][1:].upper() + '_' + method['ApiName'].upper()
        permissions.append([permission_name, api['Url'][1:].lower() + '_' + method['ApiName'].lower()])
        if 'Data' in method and len(method['Data']) > 0 :
            var_declaration += f'\n        \n        '
            if_declaration = f'\n        if('
            for key,value in method['Data'].items():
                parameters += get_json_type(type(value)) + ' '
                parameters += key.lower() + ', '
                handle_function_inputs += f'parameters["{key.lower()}"], '
                if_declaration += f'!req->getParams()->isQueryParameterSet("{key.lower()}") || '
                if get_json_type(type(value)) == "String":
                    var_declaration += f'{get_json_type(type(value))} {key.lower()} = getQueryParameterString(req, "{key}");\n        '
                elif get_json_type(type(value)) == "int":
                    var_declaration += f'{get_json_type(type(value))} {key.lower()} = getQueryParameterint(req, "{key}");\n        '
                elif get_json_type(type(value)) == "bool":
                    var_declaration += f'{get_json_type(type(value))} {key.lower()} = boolean(getQueryParameterString(req, "{key}"));\n        '
                elif get_json_type(type(value)) == "EBPDateTime":
                    var_declaration += f'{get_json_type(type(value))} {key.lower()} = EBPDatetime(getQueryParameterString(req, "{key}"));\n        '
                
                var_input += key.lower() + ', '
            
            if_declaration = if_declaration[:-4]
            if_declaration += f'){{\n            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);\n        }}'
        parameters = parameters[:-2]
        var_input = var_input[:-2]
        handle_function_inputs = handle_function_inputs[:-2]
        api_methods.append(f'''
    String handle{api_method_name}({parameters});''')
        handle_methods.append(f'''
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/{api_method_name}"), LambdaResourceNode::REQUEST_METHOD_{http_method}, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{permission_name}) == AuthorizationResults::SUCCESFULL){{return;}}
        {if_declaration}{var_declaration}
        response(res, handle{api_method_name}({var_input}));
    }}));''')
        handler_functions.append(f'''
String {api['name']}Apis::handle{api_method_name}({parameters}) {{
    return "";
}}''')
        call_functions.append(f'''
    if (functionName == "handle{api_method_name}") {{
        handle{api_method_name}({handle_function_inputs});
        return "OK";
    }}''')

    api_methods = ''.join(api_methods)
    handle_methods = ''.join(handle_methods)
    handler_functions = ''.join(handler_functions)
    call_functions = ''.join(call_functions)

    api_class = base_code.format(api_name=api['name'], api_url=api['Url'], api_methods=api_methods, handle_methods=handle_methods, handler_functions=handler_functions, call_functions=call_functions, project_name=project_name)

    return{
        'name' : api['name'] + 'Apis',
        'code' : api_class,
        'permissions' : permissions
    }
