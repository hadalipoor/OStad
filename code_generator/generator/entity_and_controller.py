def generate_crud(project_name, entity):

    entity_name_upper = entity['name'].upper()
    entity_name = entity['name']
    entity_name_lower = entity['name'].lower()
    
    function_declaration_input = ', '.join([f'{col["type"]} {col["name"]}' for col in entity['columns']])
    main_function_input = ', '.join([f'{col["name"]}' for col in entity['columns']])
    function_input = ', '.join([f'{col["name"]}' for col in entity['columns']])
    # var_declaration = '\n    '.join([f'std::string {col["name"]};\n        req->getParams()->getQueryParameter("{col["name"]}", {col["name"]});' for col in entity['columns']])
    var_declaration = '\n    '.join([f'{col["type"]} {col["name"]} = getQueryParameter{col["type"]}(req, "{col["name"]}");' for col in entity['columns']])
    check_params = ' || '.join([f'!req->getParams()->isQueryParameterSet("{col["name"]}")' for col in entity['columns']])
    callfunction_input = ''
    for col in entity['columns']:
        callfunction_input += f'''parameters["{col['name']}"]'''
        if col['type'] == 'int' or col['type'] == 'bool':
            callfunction_input += '.toInt()'
        callfunction_input += ', '
    callfunction_input = callfunction_input[:-2]
    code_struct = '''#ifndef {entity_name_upper}APIS_h
#define {entity_name_upper}APIS_h

#include "../AppContext.h"
#include "../Database/Controllers/{entity_name}Controller.h"
#include "Permissions.h"

class {entity_name}Apis : public ApiInterface
{{
private:
    AppContext* context;
    {entity_name}Controller* {entity_name_lower}Controller;
    std::string class_path = "/{entity_name_lower}";

public:
    {entity_name}Apis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate({function_declaration_input});
    String handleupdate(int id, {function_declaration_input});
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
}};

{entity_name}Apis::{entity_name}Apis(AppContext* cntxt, bool add_apis): context(cntxt) {{
    {entity_name_lower}Controller = new {entity_name}Controller(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{entity_name_upper}_CREATE) == AuthorizationResults::SUCCESFULL){{return;}}
        if ({check_params})
        {{
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }}
        
        {var_declaration}

        response(res, handlecreate({main_function_input}));
    }}));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{entity_name_upper}_UPDATE) == AuthorizationResults::SUCCESFULL){{return;}}
        if (!req->getParams()->isQueryParameterSet("id") || {check_params})
        {{
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }}

        int id = getQueryParameterint(req, "id");
        {var_declaration}
        
        response(res, handleupdate(id, {main_function_input}));
    }}));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{entity_name_upper}_DELETE) == AuthorizationResults::SUCCESFULL){{return;}}
        if (!req->getParams()->isQueryParameterSet("id"))
        {{
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }}
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }}));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{entity_name_upper}_GET) == AuthorizationResults::SUCCESFULL){{return;}}
        response(res, handlegetAll());
    }}));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{entity_name_upper}_GET) == AuthorizationResults::SUCCESFULL){{return;}}
        if (!req->getParams()->isQueryParameterSet("id"))
        {{
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }}

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }}));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {{
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::{entity_name_upper}_GET) == AuthorizationResults::SUCCESFULL){{return;}}
        if (!req->getParams()->isQueryParameterSet("query"))
        {{
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }}

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }}));
}}

String {entity_name}Apis::getClassPath()
{{
    return String(class_path.c_str());
}}

String {entity_name}Apis::handlecreate({function_declaration_input}) {{
    {entity_name}Entity* {entity_name_lower}Entity = new {entity_name}Entity({function_input});
    int id = {entity_name_lower}Controller->Add(*{entity_name_lower}Entity);
    if (id != -1)
    {{
        return CREATE_SUCCESFULL_MESSAGE;
    }}
    
    return CREATE_FAILED_MESSAGE;
}}
String {entity_name}Apis::handleupdate(int id, {function_declaration_input}) {{
    {entity_name}Entity* {entity_name_lower}Entity = new {entity_name}Entity(id, {function_input});
    
    if ({entity_name_lower}Controller->Update(*{entity_name_lower}Entity))
    {{
        return UPDATE_SUCCESFULL_MESSAGE;
    }}
    
    return UPDATE_FAILED_MESSAGE;
}}
String {entity_name}Apis::handledelete(int id) {{
    
    if ({entity_name_lower}Controller->Delete(id))
    {{
        return DELETE_SUCCESFULL_MESSAGE;
    }}
    
    return DELETE_FAILED_MESSAGE;
}}
String {entity_name}Apis::handlegetAll() {{
    return {entity_name_lower}Controller->GetAllJson();
}}
String {entity_name}Apis::handlegetById(int id) {{
    return {entity_name_lower}Controller->GetById(id).toJson();
}}
String {entity_name}Apis::handleget(String query) {{
    return {entity_name_lower}Controller->GetJson(query);
}}

String {entity_name}Apis::callFunction(String functionName, std::map<String, String> parameters) {{
    
    if (functionName == "handlecreate") {{
        return handlecreate({callfunction_input});
    }}
    if (functionName == "handleupdate") {{
        return handleupdate(parameters["id"].toInt(), {callfunction_input});
    }}
    if (functionName == "handledelete") {{
        return handledelete(parameters["id"].toInt());
    }}
    if (functionName == "handlegetAll") {{
        return handlegetAll();
    }}
    if (functionName == "handlegetById") {{
        return handlegetById(parameters["id"].toInt());
    }}
    if (functionName == "handleget") {{
        return handleget(parameters["query"]);
    }}
    return String(NO_FUNCTION_MESSAGE + functionName);
}}

#endif //{entity_name_upper}Apis_h

    '''    
    permissions = []
    permissions.append([entity_name.upper() + '_CREATE', entity_name_lower+'_create'])
    permissions.append([entity_name.upper() + '_UPDATE', entity_name_lower+'_update'])
    permissions.append([entity_name.upper() + '_DELETE', entity_name_lower+'_delete'])
    permissions.append([entity_name.upper() + '_GET', entity_name_lower+'_get'])

    code = code_struct.format(entity_name_upper=entity_name_upper, entity_name=entity_name, entity_name_lower=entity_name_lower, 
                              function_declaration_input=function_declaration_input, function_input=function_input, main_function_input=main_function_input,
                              var_declaration=var_declaration, check_params=check_params, project_name=project_name, callfunction_input= callfunction_input)
    
    return {
        'code' : code,
        'api_name' : entity['name'] + "Apis",
        'permissions' : permissions
    } 



def generate_entity_and_controller(entity):
    # Entity and Controller class templates
    entity_template = """#ifndef {ENTITY_NAME_UPPER}ENTITY_H
#define {ENTITY_NAME_UPPER}ENTITY_H

#include <OStad.h>

class {EntityName}Entity : public Entity {{
public:
    {CONSTANT_COLUMNS}

    {Attributes}

    {EntityName}Entity()  : Entity(){{}}

    {EntityName}Entity(int id, {EntityArguments}) : Entity() {{
        this->id = id;
        {AssignAttributes}

        {AddColumns}
    }}

    {EntityName}Entity({EntityArguments}) : 
        {EntityName}Entity(0, {PassArguments})  {{}}

    static {EntityName}Entity fromEntity(Entity entity)
    {{
        {EntityName}Entity {entityName}entity = {EntityName}Entity();
        {entityName}entity.fromString(entity.toString());
        return {entityName}entity;
    }}

    // Setters and Getters for each field
}};

{COLUMN_DEFINITIONS}

#endif // {ENTITY_NAME_UPPER}ENTITY_H"""

    controller_template = """#ifndef {CONTROLLER_NAME_UPPER}_H
#define {CONTROLLER_NAME_UPPER}_H

#include <OStad.h>
#include "../Entities/{EntityName}Entity.h"
#include "../../AppContext.h"

class {ControllerName} : public MainController<{EntityName}Entity> {{
public:
    AppContext* appContext;
    {ControllerName}(AppContext* appContext, StorageType _storageType) : MainController<{EntityName}Entity>(appContext->systemContext ,"{entity_name}", _storageType), appContext(appContext) {{}}
}};

#endif // {CONTROLLER_NAME_UPPER}_H"""

    # Step 1: Generate the code for the Entity class.
    attributes = ''
    entity_arguments = ''
    assign_attributes = ''
    add_columns = ''
    constant_columns = ''
    column_definitions = ''

    for column in entity["columns"]:
        attribute = column["name"]
        value = column["type"]
        value_type = 'String' if value == 'string' else value

        attributes += f'{value_type} {attribute};\n    '
        entity_arguments += f'{value_type} _{attribute}, '
        assign_attributes += f'{attribute} = _{attribute};\n        '
        if value_type == 'EBPDateTime':
            add_columns += f'addColumn(COLUMN_{attribute.upper()}, {attribute}.toDateTimeString(), "{value}");\n        '
        else:
            add_columns += f'addColumn(COLUMN_{attribute.upper()}, String({attribute}), "{value}");\n        '
        constant_columns += f'static const String COLUMN_{attribute.upper()};\n    '
        column_definitions += f'const String {entity["name"]}Entity::COLUMN_{attribute.upper()} = "{attribute}";\n'
    
    entity_code = entity_template.format(
        ENTITY_NAME_UPPER=entity["name"].upper(),
        EntityName=entity["name"],
        entityName=entity["name"].lower(),
        Attributes=attributes,
        EntityArguments=entity_arguments[:-2],
        AssignAttributes=assign_attributes,
        AddColumns=add_columns,
        CONSTANT_COLUMNS=constant_columns,
        COLUMN_DEFINITIONS=column_definitions,
        PassArguments=', '.join([f'_{attr["name"]}' for attr in entity["columns"]])
    )

    # Step 2: Generate the code for the Controller class.
    controller_name = entity["name"] + 'Controller'
    controller_code = controller_template.format(
        CONTROLLER_NAME_UPPER=controller_name.upper(),
        ControllerName=controller_name,
        EntityName=entity["name"],
        entity_name=entity["name"].lower()
    )

    return {
        'entity_name': entity["name"] + "Entity",
        'api_name': entity["name"] + "Apis",
        'controller_name': entity["name"] + "Controller",
        'code': entity_code,
        'controller_code': controller_code
    }
