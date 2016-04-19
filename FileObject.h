#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <string>

class FileObject
{
private:
    bool mHidden,
        mFolder,
        mExecutable;
    std::string mFileName;
    

public:
    FileObject(std::string);
    void FileType(bool, bool, bool);
    bool GetHidden();
    bool GetFolder();
    bool GetExecutable();
    std::string GetFileName();
};

#endif
