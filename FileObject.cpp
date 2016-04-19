#include "FileObject.h"

FileObject::FileObject(std::string FileName = "\nError, filename not recieved!\n")
{
    mFileName = FileName;
}

void FileObject::FileType(bool tHidden, bool tFolder, bool tExecutable)
{
    mHidden = tHidden;
    mFolder = tFolder;
    mExecutable = tExecutable;
}

bool FileObject::GetHidden()
{
    return mHidden;
}

bool FileObject::GetFolder()
{
    return mFolder;
}

bool FileObject::GetExecutable()
{
    return mExecutable;
}

std::string FileObject::GetFileName()
{
    return mFileName;
}
