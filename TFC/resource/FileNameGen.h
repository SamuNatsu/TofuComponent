#ifndef FILENAMEGEN_H
#define FILENAMEGEN_H

#include <ctime>

#include <string>

namespace TFC {
 // FileNameGenerator
class FileNameGen {
public:
     // Construction & Destruction
    FileNameGen();
    ~FileNameGen();
     // Update
    void UpdateTime();
    void UpdateCounter();
     // Get
    std::string GetName();
     // Set
    void SetFormat(const char*);
private:
    using ull = unsigned long long;

    tm* nowTime = nullptr;
    ull counter = 0;
    std::string format = "";
};
} // TFC

#endif // FILENAMEGEN_H
