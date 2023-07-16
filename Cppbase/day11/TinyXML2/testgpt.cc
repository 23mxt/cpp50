#include "tinyxml2.h"
#include <iostream>
#include <fstream>

int main() {
    // 创建一个 XML 文档对象
    tinyxml2::XMLDocument doc;

    // 加载 XML 文件
    if (doc.LoadFile("coolshell.xml") != tinyxml2::XML_SUCCESS) {
        std::cout << "无法加载 XML 文件" << std::endl;
        return 1;
    }

    // 创建一个 TXT 文件流
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cout << "无法打开输出文件" << std::endl;
        return 1;
    }

    // 获取根元素
    tinyxml2::XMLElement* root = doc.RootElement();

    // 遍历每个子元素
    for (tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        // 获取元素名称
        const char* elemName = elem->Name();

        // 获取元素的文本内容
        const char* elemText = elem->GetText();

        // 将元素名称和文本内容写入到 TXT 文件
        outputFile << "Element Name: " << elemName << std::endl;
        outputFile << "Element Text: " << elemText << std::endl;
        outputFile << std::endl;
    }

    // 关闭文件流
    outputFile.close();

    std::cout << "XML 文件已成功解析并保存到 TXT 文件" << std::endl;

    return 0;
}
