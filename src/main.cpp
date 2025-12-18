#include <iostream>
#include <vector>
#include <fstream>

void file_read()
{
    std::string myText;

    std::ifstream MyReadFile("../test.json");

    while (getline(MyReadFile, myText))
    {
        std::cout << myText << std::endl;
    }

    MyReadFile.close();
}
int main()
{
    file_read();
    return 0;
}
