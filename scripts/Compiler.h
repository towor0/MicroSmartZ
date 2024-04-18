#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <iostream>

#ifndef MICROSMARTZ_COMPILER_H
#define MICROSMARTZ_COMPILER_H

/*
 * Compiler
 * Use for compiling MicroSmartZ files to Sketch/Hex files
 */


class Compiler {
public:
    Compiler();
    std::string exportSketch(const std::string &content);
    int numArgs(const std::string &name);
    std::string codeToSketch(const std::string& name, std::vector<std::string> strArgs);
};


#endif //MICROSMARTZ_COMPILER_H
