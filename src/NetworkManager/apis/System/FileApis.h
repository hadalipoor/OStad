#ifndef FILE_API_H
#define FILE_API_H

#include <ArduinoJson.h>
#include "../../../Context.h"
#include "../ApiInterface.h"
#include "../../../FileManager/EBPFile.h"
#include "SystemPermissions.h"

class FileApis : public ApiInterface{
private:
    Context* context;

public:
    std::string class_path = "/fileApi";
    FileApis(Context* context, bool add_apis);
    String getClassPath() override;

    String handleBrowseFolder(String path, int offset, int count, StorageType _storageType);
    String handleOpen(String path, String mod, StorageType _storageType);
    void handleFileUploadAndRedirect(HTTPRequest *req, HTTPResponse *res, String path, StorageType storageType_path);
    void handleRoot(HTTPResponse* res);
    String handleDelete(String path, StorageType _storageType);
    String handleWrite(String path, String content, StorageType _storageType);
    String handleFormat(StorageType _storageType);
    String handleRename(String path, String new_name, StorageType _storageType);
    String handleMove(String source_path, String destination_path, StorageType _storageType);
    String handleCopy(String source_path, String destination_path, StorageType _storageType);
    String handleDuplicate(String path, StorageType _storageType);
    String handleMkDir(String path, StorageType _storageType);
    
    String callFunction(String functionName, std::map<String, String> parameters);
    
};

FileApis::FileApis(Context* cntxt, bool add_apis) : context(cntxt) {
    if (!add_apis) return;
    
    context->getNetwork()->addApi(new ResourceNode("/", LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        this->handleRoot(res);
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/browse_folder"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if(req->getParams()->isQueryParameterSet("path")) {
            String path = getQueryParameterString(req, "path");
            int offset = 0;
            int count = 1000;
            if(req->getParams()->isQueryParameterSet("offset") && req->getParams()->isQueryParameterSet("count")) {
                offset = getQueryParameterint(req, "offset");
                count = getQueryParameterint(req, "count");
            }
            
            StorageType _storageType = storageType;
            if(req->getParams()->isQueryParameterSet("storage_type"))
            {
                _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
            }

            response(res, 200, "application/json", handleBrowseFolder(path, offset, count, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/open"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        if(req->getParams()->isQueryParameterSet("path")) {
            String path = getQueryParameterString(req, "path");
            String content = this->handleOpen(path, "r", _storageType);
            response(res, content);
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        if(req->getParams()->isQueryParameterSet("path")) {
            String path = getQueryParameterString(req, "path");
            String content = handleDelete(path, _storageType);
            response(res, content);
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }

    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/write"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        if(req->getParams()->isQueryParameterSet("path") && req->getParams()->isQueryParameterSet("content")) {
            String path = getQueryParameterString(req, "path");
            String content = handleWrite(path, content, _storageType);
            response(res, handleWrite(path, content, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/format"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        response(res, handleFormat(_storageType));
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/rename"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        if(req->getParams()->isQueryParameterSet("path") && req->getParams()->isQueryParameterSet("new_name")) {
            String path = getQueryParameterString(req, "path");
            String new_name = getQueryParameterString(req, "new_name");
            response(res, handleRename(path, new_name, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/move"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        if(req->getParams()->isQueryParameterSet("source_path") && req->getParams()->isQueryParameterSet("destination_path")) {
            String source_path = getQueryParameterString(req, "source_path");
            String destination_path = getQueryParameterString(req, "destination_path");
            response(res, handleMove(source_path, destination_path, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/copy"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        if(req->getParams()->isQueryParameterSet("source_path") && req->getParams()->isQueryParameterSet("destination_path")) {
            String source_path = getQueryParameterString(req, "source_path");
            String destination_path = getQueryParameterString(req, "destination_path");
            response(res, handleCopy(source_path, destination_path, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/duplicate"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        if(req->getParams()->isQueryParameterSet("path")) {
            String path = getQueryParameterString(req, "path");
            response(res, handleDuplicate(path, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/mkdir"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }
        
        if(req->getParams()->isQueryParameterSet("path")) {
            String path = getQueryParameterString(req, "path");
            response(res, handleMkDir(path, _storageType));
        } else {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
    }));

    context->getNetwork()->addApi(new ResourceNode("/files", LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        String file_html = String(R"rawliteral(
            <!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><title>File Manager</title><style>body{font-family:Arial,sans-serif;color:#333}#container{display:flex;height:100vh}#nav{flex:1;border-right:1px solid #ccc;overflow:auto;padding:20px}#content{flex:2;padding:20px}table{width:100%;border-collapse:collapse}th,td{padding:10px;text-align:left}tr:nth-child(even){background-color:#f2f2f2}.icon{width:20px;height:20px;margin-right:10px}#upload-form{display:flex;align-items:center;gap:10px;margin-bottom:20px}.custom-file-upload{padding:5px 10px;background:#3498db;color:#fff;border-radius:5px;cursor:pointer}.custom-file-upload:hover{background:#2980b9}#file-upload{display:none}.upload-btn{padding:5px 10px;background:#2ecc71;border:none;color:#fff;border-radius:5px;cursor:pointer}.upload-btn:hover{background:#27ae60}#storage-toggle{margin-right:10px}.storage_info{width:0;height:0}#storage-toggle{display:flex;justify-content:center;padding:10px;background-color:#f2f2f2;border-radius:30px;margin-bottom:20px}#storage-toggle label{cursor:pointer;padding:10px 20px;border-radius:20px;font-weight:bold}input[type="radio"]{display:none}input[type="radio"]:checked+label{background-color:#3498db;color:#fff}#file-path{margin-left:10px;border:none;background:#f2f2f2;padding:5px 10px;border-radius:5px;font-size:16px;color:#555;box-shadow:0 2px 5px rgba(0,0,0,.1);transition:box-shadow .3s ease}#file-path:focus{box-shadow:0 2px 5px rgba(0,0,0,.2);outline:none}.custom-file-upload{padding:5px 10px;background:#3498db;color:#fff;border-radius:5px;cursor:pointer;display:inline-block;transition:background .3s ease}.custom-file-upload:hover{background:#2980b9}</style></head><body><div id="container"><div id="nav"><h2>Folders</h2><ul id="folders"></ul></div><div id="content"><div id="storage-toggle"><input type="radio" id="SD" name="storage" value="SD_TYPE" onchange="handleStorageToggle()"><label for="SD">SD</label><input type="radio" id="LittleFS" name="storage" value="SPIFFS_TYPE" checked onchange="handleStorageToggle()"><label for="LittleFS">SPIFFS</label></div><form method="POST" action="/upload_spiffs" enctype="multipart/form-data" id="upload-form"><label for="file-upload" class="custom-file-upload"><i class="fa fa-cloud-upload"></i> Choose File</label><input id="file-upload" type="file" name="data" onchange="showFileName()"/><input type="text" id="file-path" readonly><button type="submit" name="upload" class="upload-btn" title="Upload File">Upload</button></form><h2 id="currentPath"></h2><table><thead><tr><th>Name</th><th>Type</th><th>Size</th><th>Actions</th></tr></thead><tbody id="files"></tbody></table></div></div><div id="storage-info" style="visibility: hidden;"><span id="currentStorage">SD</span></div><script>let currentPath="/",currentData=null,currentStorage="SPIFFS_TYPE";function handleStorageToggle() {
    var form = document.getElementById("upload-form");
    var storageOptions = document.getElementsByName("storage");

    for (var i = 0, length = storageOptions.length; i < length; i++) {
        if (storageOptions[i].checked) {
            // Update the action of the form based on the selected storage type
            form.action = storageOptions[i].value === "SD_TYPE" ? "/upload_sd" : "/upload_spiffs";

            // Update currentStorage to reflect the selected option
            currentStorage = storageOptions[i].value === "SD_TYPE" ? "SD_TYPE" : "SPIFFS_TYPE";
            document.getElementById("currentStorage").textContent = currentStorage === "SD_TYPE" ? "SD" : "SPIFFS";

            // Refresh the file view with the new storage type
            browse(currentPath);
            break;
        }
    }
}
function browse(e){fetch(`/fileApi/browse_folder?path=${e}&storage_type=${currentStorage}`).then(e=>e.json()).then(e=>(currentData=e,updateView(e))).catch(e=>{console.error("Error:",e)})}function updateView(e){document.getElementById("currentPath").textContent=currentPath;const n=document.getElementById("files");while(n.firstChild)n.firstChild.remove();for(const t of e){let e=window.location.origin;const r=document.createElement("tr");let o=t.is_file?"📄":"📁";t.name=t.name.startsWith("/")?t.name.slice(1):t.name;let c=e+"/"+t.name;r.innerHTML=`<td><a href="${c}" target="_blank" class="fileLink"><span class="icon">${o}</span>${t.name}</a></td><td>${t.is_file?"file":"directory"}</td><td>${t.size||""}</td><td><button onclick="openItem('${t.name}')">Open</button><button>Rename</button><button onclick="deleteItem('${t.name}')">Delete</button></td>`,n.appendChild(r)}}function openItem(name) {
    const itemPath = currentPath.endsWith("/") ? currentPath + name : currentPath + "/" + name;
    const item = currentData.find(e => e.name === name);

    if (item && !item.is_file) {
        // If the item is a folder, update currentPath and browse the new path
        currentPath = itemPath;
        browse(currentPath + "/");
    } else if (item && item.is_file) {
        // If the item is a file, open it as before
        fetch(`/fileApi/open?path=${itemPath}&storage_type=${currentStorage}`)
            .then(response => response.text())
            .then(data => {
                const newWindow = window.open("", "_blank");
                newWindow.document.write(`<pre>${data}</pre>`);
            })
            .catch(error => {
                console.error("Error:", error);
            });
    }
}
function deleteItem(e){fetch(`/fileApi/delete?path=${currentPath}${e}&storage_type=${currentStorage}`,{method:"DELETE"}).then(e=>e.headers.get("content-type")==="application/json"?e.json():e.text()).then(e=>{typeof e==="string"||e.success?(alert("Deleted "+e),browse(currentPath)):alert("Error: "+e.error)}).catch(e=>{console.error("Error:",e)})}function showFileName(){const e=document.getElementById("file-upload"),n=document.getElementById("file-path");n.value=e.value.split("\\").pop()}browse(currentPath)</script></body></html>


            )rawliteral");
        response(res, file_html);
    }));

    context->getNetwork()->addApi(new ResourceNode("/upload_spiffs", LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        handleFileUploadAndRedirect(req, res, "/", StorageType::SPIFFS_TYPE);
    }));

    context->getNetwork()->addApi(new ResourceNode("/upload_sd", LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::SSID_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        handleFileUploadAndRedirect(req, res, "/", StorageType::SD_TYPE);
    }));
    
    context->getNetwork()->addUrlNotFound(new ResourceNode("", LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        
        String _path = String(req->getRequestString().c_str());//request->urlDecode(request->url());
        String content_type = "";
        
        StorageType _storageType = storageType;
        if(req->getParams()->isQueryParameterSet("storage_type"))
        {
            _storageType = EBPFile::getStorageType(getQueryParameterString(req, "storage_type"));
        }

        bool file_in_storage = false;
        if (_storageType == StorageType::SD_TYPE)
        {
            if(context->getSD()->exists(_path)) file_in_storage = true;
        }
        else
        {
            if(context->getLittleFS()->exists(_path)) file_in_storage = true;
        }

        if(req->getParams()->isQueryParameterSet("content_type")) {
            content_type = getQueryParameterString(req, "content_type");
        }

        if (file_in_storage)
        {
            DownloadFile(res, _path, content_type, storageType);
        }
        else
        {
            response(res, PAGE_NOT_FOUND_MESSAGE);
        }
        
    }));
}

String FileApis::getClassPath()
{
    return String(class_path.c_str());
}

String FileApis::callFunction(String functionName, std::map<String, String> parameters) {
    StorageType _storageType = EBPFile::getStorageType(parameters["storage_type"]);

    if (functionName == "browse_folder") {
        return handleBrowseFolder(parameters["path"], parameters["offset"].toInt(), parameters["count"].toInt(), _storageType);
    } else if (functionName == "open") {
        return handleOpen(parameters["path"], parameters["mod"], _storageType);
    } else if (functionName == "delete") {
        return handleDelete(parameters["path"], _storageType);
    } else if (functionName == "write") {
        return handleWrite(parameters["path"], parameters["content"], _storageType);
    } else if (functionName == "format") {
        return handleFormat(_storageType);
    } else if (functionName == "rename") {
        return handleRename(parameters["path"], parameters["new_name"], _storageType);
    } else if (functionName == "move") {
        return handleMove(parameters["source_path"], parameters["destination_path"], _storageType);
    } else if (functionName == "copy") {
        return handleCopy(parameters["source_path"], parameters["destination_path"], _storageType);
    } else if (functionName == "duplicate") {
        return handleDuplicate(parameters["path"], _storageType);
    } else {
        return "Error: The function doesn't exist";
    }
}

void FileApis::handleRoot(HTTPResponse* res)
{
    String _path;
    bool fileExists = false;
    _path = "/index.html";
    if (storageType == StorageType::SPIFFS_TYPE)
    {
        if (context->getLittleFS()->exists(_path))
        {
            fileExists = true;
        }
    }
    else if (storageType == StorageType::SD_TYPE)
    {
        if (context->getSD()->exists(_path))
        {
            fileExists = true;
        }
    }

    if (fileExists)
    {
        DownloadFile(res, _path, "text/html", storageType);
        return;
    }
    
    _path = "/files.html";
    if (storageType == StorageType::SPIFFS_TYPE)
    {
        if (context->getLittleFS()->exists(_path))
        {
            fileExists = true;
        }
    }
    else if (storageType == StorageType::SD_TYPE)
    {
        if (context->getSD()->exists(_path))
        {
            fileExists = true;
        }
    }

    if (fileExists)
    {
        DownloadFile(res, _path, "text/html", storageType);
    }
    else{
        RedirectUrl(res, "/files");
    }
}


String FileApis::handleBrowseFolder(String path, int offset, int count, StorageType _storageType) {
    std::vector<FileData> files;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        files = context->getLittleFS()->Browse(path);
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        files = context->getSD()->Browse(path);
    }     

    DynamicJsonDocument doc(2048);
    JsonArray array = doc.to<JsonArray>();

    // Implementing the pagination
    int currentCount = 0;
    for(int i = offset; i < files.size() && currentCount < count; i++, currentCount++) {
        JsonObject obj = array.createNestedObject();
        obj["name"] = files[i].name;
        obj["is_file"] = files[i].isFile;
        obj["is_empty"] = files[i].isEmpty;
        obj["size"] = files[i].size;  
    }

    String response;
    serializeJson(doc, response);

    return response;
}

String FileApis::handleOpen(String path, String mod, StorageType _storageType) {
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        return context->getLittleFS()->open(path, mod)->readString();
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        return context->getSD()->open(path, mod)->readString();
    } 
}

String FileApis::handleDelete(String path, StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        success = context->getLittleFS()->remove(path);
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        success = context->getSD()->remove(path);
    } 

    if (success)
    {
        return "File Deleted Succesfull.";
    }else{
        return "An error occured while Delete file.";
    }    
}

String FileApis::handleWrite(String path, String content, StorageType _storageType) {
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        context->getLittleFS()->open(path, "w");
        context->getLittleFS()->print(content);
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        context->getSD()->open(path, "w");
        context->getSD()->print(content);
    } 
    return "File writed succesfully.";
}

String FileApis::handleFormat(StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        if(context->getLittleFS()->format())
        {
            success = true;
        }
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        if(context->getSD()->format())
        {
            success = true;
        }
    } 

    if (success)
    {
        return "Storage Formated Succesfull";
    }else {
        return "An error occured while formating";
    }
    
}

String FileApis::handleRename(String path, String new_name, StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        if(context->getLittleFS()->rename(path, new_name))
        {
            success = true;
        }
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        if(context->getSD()->rename(path, new_name))
        {
            success = true;
        }
    } 

    if (success)
    {
        return "File renamed Succesfull";
    }else {
        return "An error occured while renaming file";
    }
}

String FileApis::handleMove(String source_path, String destination_path, StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        if (context->getLittleFS()->open(source_path, "w"))
        {
            if(context->getLittleFS()->move(destination_path))
            {
                success = true;
            }
        }
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        if (context->getSD()->open(source_path, "w"))
        {
            if(context->getSD()->move(destination_path))
            {
                success = true;
            }
        }
    } 

    if (success)
    {
        return "File moved Succesfull";
    }else {
        return "An error occured while moving file";
    }
}

String FileApis::handleCopy(String source_path, String destination_path, StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        if (context->getLittleFS()->open(source_path, "w"))
        {
            if(context->getLittleFS()->copy(destination_path))
            {
                success = true;
            }
        }
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        if (context->getSD()->open(source_path, "w"))
        {
            if(context->getSD()->copy(destination_path))
            {
                success = true;
            }
        }
    } 

    if (success)
    {
        return "File copied Succesfull";
    }else {
        return "An error occured while copying file";
    }
}

String FileApis::handleDuplicate(String path, StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        if (context->getLittleFS()->open(path, "w"))
        {
            if(context->getLittleFS()->duplicate())
            {
                success = true;
            }
        }
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        if (context->getSD()->open(path, "w"))
        {
            if(context->getSD()->duplicate())
            {
                success = true;
            }
        }
    } 

    if (success)
    {
        return "File moved Succesfull";
    }else {
        return "An error occured while renaming file";
    } 
}

String FileApis::handleMkDir(String path, StorageType _storageType) {
    bool success = false;
    if (_storageType == StorageType::SPIFFS_TYPE)
    {
        if (LittleFS.mkdir(path))
        {
            success = true;
        }
    }
    else if (_storageType == StorageType::SD_TYPE)
    {
        if (SD.mkdir(path))
        {
            success = true;            
        }
    } 

    if (success)
    {
        return "Folder Created Succesfully";
    }
    else
    {
        return "Error Ocured While Creating Folder.";
    } 
}

void FileApis::handleFileUploadAndRedirect(HTTPRequest *req, HTTPResponse *res, String path, StorageType storageType_path) {
  // Check if it's a POST request
  if (req->getMethod() == "POST") {
    // Use the HTTPMultipartBodyParser to parse the uploaded file
    HTTPBodyParser *parser = new HTTPMultipartBodyParser(req);

    while (parser->nextField()) {
      std::string name = parser->getFieldName();
      std::string filename = parser->getFieldFilename();

      // Check if the field is a file
      if (name == "data") {
        // Check file name validity and all that, but we skip that.
        std::string pathname = std::string(path.c_str()) + filename;
        File file;
        if (storageType_path == StorageType::SD_TYPE)
        {
            file = SD.open(pathname.c_str(), "w");
        }
        else
        {
            file = LittleFS.open(pathname.c_str(), "w");
        }
        
        size_t fileLength = 0;

        // Write the file content
        while (!parser->endOfField()) {
          byte buf[512];
          size_t readLength = parser->read(buf, 512);
          file.write(buf, readLength);
          fileLength += readLength;
        }

        file.close();
        delete parser;

        // Redirect to "/files" after successful file upload
        RedirectUrl(res, "/files");
        return;
      }
    }

    // If no file field found, send an error response
    res->setStatusCode(400);
    res->setStatusText("Bad Request");
    res->println("400 Bad Request - No file uploaded");
  } else {
    // If it's not a POST request, send an error response
    res->setStatusCode(405);
    res->setStatusText("Method Not Allowed");
    res->println("405 Method Not Allowed - Only POST requests are allowed");
  }
}



#endif // FILE_API_H

