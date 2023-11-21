#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <vector>
#include <string>

template<typename T>
class IController {
public:

    virtual void RemoveTable() = 0;

    virtual void removeColumn(const String column_name) = 0;

    virtual int Add(T& entity) = 0;

    virtual bool Update(T& entity) = 0;

    virtual bool Delete(int id) = 0;

    virtual T GetById(int id) = 0;

    virtual std::vector<T> GetAll() = 0;

    virtual String GetAllJson() = 0;

    virtual std::vector<T> Get(const String query) = 0;
    
    virtual String GetJson(String query) = 0;
};

#endif // ICONTROLLER_H
