#include "FileHandler.h"

#ifdef _WIN32
#include <windows.h>
#endif

std::string FileHandler::openFileDialog() {
    std::string filePath;

#ifdef _WIN32
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "MicroSmartZ Files (*.mcsz)\0*.mcsz\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = sizeof(szFileName);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "mcsz";

    if (GetSaveFileName(&ofn) == TRUE) {
        filePath = ofn.lpstrFile;
    }
#endif

    return filePath;
}

void FileHandler::saveToFile(const std::string &filePath, const std::string &content) {
    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << content;
        outputFile.close();
        std::cout << "File saved successfully." << std::endl;
    } else {
        std::cerr << "Unable to save file." << std::endl;
    }
}

std::string FileHandler::readFileContent(const std::string &filePath) {
    std::string content;

    std::ifstream inputFile(filePath);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            content += line + "\n";
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }

    return content;
}

std::string FileHandler::openFileDialogSketch() {
    std::string filePath;

#ifdef _WIN32
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "Arduino Sketch Files (*.ino)\0*.ino\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = sizeof(szFileName);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "ino";

    if (GetSaveFileName(&ofn) == TRUE) {
        filePath = ofn.lpstrFile;
    }
#endif

    return filePath;
}

void FileHandler::uploadCode() {
    std::string boardType = "arduino:avr:uno";
    std::string sketchPath = path + "/temp/temp.ino";
    std::string cliPath = path + "/arduino-cli";

    std::string command = cliPath + " compile --fqbn " + boardType + " " + sketchPath;

    int result = std::system(command.c_str());
    if (result == 0) {
        std::cout << "Sketch compiled successfully." << std::endl;
    } else {
        std::cerr << "Failed to compile the sketch." << std::endl;
    }
    command = cliPath + " upload -p COM3 --fqbn " + boardType + " " + sketchPath;
    result = std::system(command.c_str());
}


FileHandler::FileHandler() {

}

void FileHandler::setPath(std::string path) {
    this->path = path;
}

void FileHandler::setCWFilePath(std::string path) {
    cwFilePath = path;
}

std::string FileHandler::getCWFilePath() {
    return cwFilePath;
}

