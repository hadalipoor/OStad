import json
import os
from sys_apis import system_apis


input_json_path = ''
ouput_postman_json_path = ''
def generate_postman_json(data):

    # Define default server
    default_server = "192.168.4.1"

    # Parse system_apis JSON and extract Ostad folder
    system_apis_data = json.loads(system_apis)
    ostad_folder = next((item for item in system_apis_data["item"] if item["name"] == "Ostad"), None)

    # Define the skeleton of Postman import JSON
    postman_data = {
        "info": {
            "_postman_id": "0c52ebe2-3143-4c45-b132-8e0746146595",
            "name": data["ProjectName"],
            "schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json"
        },
        "item": []
    }

    # Add Ostad folder if it exists
    if ostad_folder:
        postman_data["item"].append(ostad_folder)

    # Create CRUD operations for each entity
    for entity in data["Entities"]:
        entity_item = {
            "name": entity["name"],
            "item": []
        }
        crud_operations = ["getAll", "getById", "create", "update", "delete"]
        http_methods = ["GET", "GET", "POST", "PUT", "DELETE"]
        for operation, http_method in zip(crud_operations, http_methods):
            query_params = []
            if operation in ["update", "create"]:
                query_params = [{"key": column['name'], "value": "SAMPLE"} for column in entity['columns']]
                if operation == "update":
                    query_params.append({"key": "id", "value": "SAMPLE"})
            elif operation == "getById":
                query_params = [{"key": "id", "value": "SAMPLE"}]
            entity_item["item"].append({
                "name": operation,
                "request": {
                    "method": http_method,
                    "header": [],
                    "url": {
                        "raw": f"http://{default_server}/{entity['name'].lower()}/{operation}",
                        "protocol": "http",
                        "host": [default_server],
                        "path": [entity["name"].lower(), operation],
                        "query": query_params
                    }
                },
                "response": []
            })
        postman_data["item"].append(entity_item)

    # Add APIs from the input file
    for api in data["Apis"]:
        api_item = {
            "name": api["name"],
            "item": []
        }
        for api_sub in api["Apis"]:
            query_params = [{"key": k, "value": str(v)} for k, v in api_sub["Data"].items()]
            api_item["item"].append({
                "name": api_sub["ApiName"],
                "request": {
                    "method": api_sub["Method"],
                    "header": [],
                    "body": {
                        "mode": "raw",
                        "raw": json.dumps(api_sub["Data"])
                    },
                    "url": {
                        "raw": f"http://{default_server}{api_sub['EndPoint']}",
                        "protocol": "http",
                        "host": [default_server],
                        "path": api_sub['EndPoint'].split('/')[1:],
                        "query": query_params
                    }
                },
                "response": []
            })
        postman_data["item"].append(api_item)
    # # Write to Postman import JSON file
    # with open(ouput_postman_json_path, 'w') as file:
    #     json.dump(postman_data, file, indent=4)

    print("Postman import JSON file has been successfully created!")
    return postman_data
