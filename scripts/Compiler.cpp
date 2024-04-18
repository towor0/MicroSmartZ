#include "Compiler.h"

Compiler::Compiler() {

}

std::string Compiler::exportSketch(const std::string &content) {
    // Split string by line
    std::vector<std::string> contentSplit;
    std::vector<std::string> emptyStringVector;
    std::stringstream ss(content);
    std::stringstream sketchCode;
    std::string contentLine;
    while (std::getline(ss, contentLine)) {
        contentSplit.push_back(contentLine);
    }
    // Processing each line to Blocks
    for (const auto& con : contentSplit) {
        std::vector<std::vector<std::string>> lineContent;
        int layer = 0;
        for (char c : con) {
            if (layer + 1 > lineContent.size()) lineContent.emplace_back(emptyStringVector);
            if (c == '(') layer ++;
            else if (c == ')') layer --;
            else if (c == ',') lineContent[layer].emplace_back("");
            else {
                if (lineContent[layer].empty()) lineContent[layer].emplace_back("");
                lineContent[layer][lineContent[layer].size()-1] += c;
            }
        }
        if (!lineContent.empty()){
            std::stack<std::string> curr, prev;
            for (int i = lineContent.size() - 1; i >= 0; i--) {
                for (auto strContent: lineContent[i]) {
                    if (strContent.empty()) {
                        curr.push("");
                    } else if (strContent[0] == '*') {
                        std::vector<std::string> tempStrArgs;
                        for (int i = 0; i < numArgs(strContent.substr(1)); i++) {
                            tempStrArgs.insert(tempStrArgs.begin(), prev.top());
                            prev.pop();
                        }
                        curr.push(codeToSketch(strContent.substr(1), tempStrArgs));
                    } else {
                        curr.push(strContent);
                    }
                }
                prev = curr;
                curr = std::stack<std::string>();
            }
            sketchCode << prev.top() << "\n";
            prev.pop();
        }
    }
    return sketchCode.str();
}

int Compiler::numArgs(const std::string &name) {
    // Basic Blocks
    if (name == "Set") return 2;
    if (name == "Get") return 1;
    if (name == "Add") return 2;
    if (name == "Minus") return 2;
    if (name == "Multiply") return 2;
    if (name == "Divide") return 2;

    // Advanced Blocks
    if (name == "Equal") return 2;
    if (name == "Greater") return 2;
    if (name == "Less") return 2;
    if (name == "And") return 2;
    if (name == "Or") return 2;
    if (name == "Not") return 1;
    if (name == "While") return 1;
    if (name == "If") return 1;
    if (name == "ElseIf") return 1;
    if (name == "Else") return 0;
    if (name == "End") return   0;

    // Micro Blocks
    if (name == "SetOutputPin") return 1;
    if (name == "SetInputPin") return 1;
    if (name == "SetInputButtonPin") return 1;
    if (name == "Setup") return 0;
    if (name == "Loop") return 0;
    if (name == "WritePin") return 2;
    if (name == "ReadPin") return 1;
    if (name == "On") return 0;
    if (name == "Off") return 0;
    if (name == "Wait") return 1;

    return 0;
}

std::string Compiler::codeToSketch(const std::string &name, std::vector<std::string> strArgs) {
    std::stringstream sketchCode;

    // Basic Blocks
    if (name == "Set") {
        if (strArgs[1].find('.')!=std::string::npos) sketchCode << "float microsmartz_" << strArgs[0] << "=" << strArgs[1] << "f;";
        else sketchCode << "int microsmartz_" << strArgs[0] << "=" << strArgs[1] << ";";
    }
    if (name == "Get") sketchCode << "microsmartz_" << strArgs[0];
    if (name == "Add") sketchCode << "(" << strArgs[0] << "+" << strArgs[1] << ")";
    if (name == "Minus") sketchCode << "(" << strArgs[0] << "-" << strArgs[1] << ")";
    if (name == "Multiply") sketchCode << "(" << strArgs[0] << "*" << strArgs[1] << ")";
    if (name == "Divide") sketchCode << "(" << strArgs[0] << "/" << strArgs[1] << ")";

    // Advanced Blocks
    if (name == "Equal") sketchCode << "(" << strArgs[0] << "==" << strArgs[1] << ")";
    if (name == "Greater") sketchCode << "(" << strArgs[0] << ">" << strArgs[1] << ")";
    if (name == "Less") sketchCode << "(" << strArgs[0] << "<" << strArgs[1] << ")";
    if (name == "And") sketchCode << "(" << strArgs[0] << "&&" << strArgs[1] << ")";
    if (name == "Or") sketchCode << "(" << strArgs[0] << "||" << strArgs[1] << ")";
    if (name == "Not") sketchCode << "(!" << strArgs[0] << ")";
    if (name == "While") sketchCode << "while (" << strArgs[0] << ") {";
    if (name == "If") sketchCode << "if (" << strArgs[0] << ") {";
    if (name == "ElseIf") sketchCode << "else if (" << strArgs[0] << ") {";
    if (name == "Else") sketchCode << "else {";
    if (name == "End") sketchCode << "}";

    // Micro Blocks
    if (name == "SetOutputPin") sketchCode << "pinMode(" << strArgs[0] << ",OUTPUT);";
    if (name == "SetInputPin") sketchCode << "pinMode(" << strArgs[0] << ",INPUT);";
    if (name == "SetInputButtonPin") sketchCode << "pinMode(" << strArgs[0] << ",INPUT_PULLUP);";
    if (name == "Setup") sketchCode << "void setup() {";
    if (name == "Loop") sketchCode << "void loop() {";
    if (name == "WritePin") sketchCode << "digitalWrite(" << strArgs[1] << "," << strArgs[0] << ");";
    if (name == "ReadPin") sketchCode << "digitalRead(" << strArgs[0] << ")";
    if (name == "On") sketchCode << "HIGH";
    if (name == "Off") sketchCode << "LOW";
    if (name == "Wait") sketchCode << "delay(" << strArgs[0] << ");";
    return sketchCode.str();
}