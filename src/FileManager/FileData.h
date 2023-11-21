#ifndef FILEDATA_H
#define FILEDATA_H

class FileData
{
private:
    
public:
    FileData(String _name, int _size, bool _isFolder, bool _isEmpty);
    ~FileData();
    String name;
    int size;
    bool isFile;
    bool isEmpty;

};

FileData::FileData(String _name, int _size, bool _isFolder, bool _isEmpty)
{
    name = _name;
    size = _size;
    isFile = _isFolder;
    isEmpty = _isEmpty;
}

FileData::~FileData()
{
}


#endif