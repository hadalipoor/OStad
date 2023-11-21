#ifndef LAMBDARESOURCENODE_H
#define LAMBDARESOURCENODE_H

#include <map>
#include <string>
#include <functional>

class LambdaResourceNode : public httpsserver::ResourceNode {
public:
    LambdaResourceNode(const std::string &path, const std::string &method, 
                       std::function<void(HTTPRequest *, HTTPResponse *)> lambda)
    : httpsserver::ResourceNode(path, method, &LambdaResourceNode::staticHandler), 
      lambda_(lambda) {
        lambdaMap_[path] = lambda;
    }

    static const std::string REQUEST_METHOD_GET;
    static const std::string REQUEST_METHOD_POST;
    static const std::string REQUEST_METHOD_PUT;
    static const std::string REQUEST_METHOD_DELETE;

private:
    std::function<void(HTTPRequest *, HTTPResponse *)> lambda_;
    static std::map<std::string, std::function<void(HTTPRequest *, HTTPResponse *)>> lambdaMap_;

    static void staticHandler(HTTPRequest *req, HTTPResponse *res) {
        std::string path = req->getRequestString(); // Get the path from the request
        auto it = lambdaMap_.find(path);
        if (it != lambdaMap_.end()) {
            it->second(req, res); // Execute the lambda function associated with the path
        }
    }
};

std::map<std::string, std::function<void(HTTPRequest *, HTTPResponse *)>> LambdaResourceNode::lambdaMap_;


const std::string LambdaResourceNode::REQUEST_METHOD_GET = "GET";
const std::string LambdaResourceNode::REQUEST_METHOD_POST = "POST";
const std::string LambdaResourceNode::REQUEST_METHOD_PUT = "PUT";
const std::string LambdaResourceNode::REQUEST_METHOD_DELETE = "DELETE";
#endif //LAMBDARESOURCENODE_H