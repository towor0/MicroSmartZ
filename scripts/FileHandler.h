#include <string>
#include <map>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

#ifndef MICROSMARTZ_FILEHANDLER_H
#define MICROSMARTZ_FILEHANDLER_H

/*
 * FileHandler
 * Allowing the user to store and open files
 */

class FileHandler {
    std::string path;
    std::string port;
    std::string cwFilePath;
public:
    FileHandler();
    std::string openFileDialog();
    std::string openFileDialogSketch();
    std::string readFileContent(const std::string& filePath);
    void saveToFile(const std::string& filePath, const std::string& content);
    void uploadCode();
    void setPath(std::string path);
    void setCWFilePath(std::string path);
    std::string getCWFilePath();
};


#endif //MICROSMARTZ_FILEHANDLER_H
