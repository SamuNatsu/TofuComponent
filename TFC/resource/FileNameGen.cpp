#include "FileNameGen.h"

namespace TFC {
FileNameGen::FileNameGen() {}

FileNameGen::~FileNameGen() {}

void FileNameGen::UpdateTime() {
    time_t sysTime = time(0);
    nowTime = localtime(&sysTime);
}

void FileNameGen::UpdateCounter() {
    ++counter;
}

std::string FileNameGen::GetName() {
    std::string rtn = "";
    for (ull i = 0; i < format.length(); ++i) {
        if((format[i] != '%') && (format[i] != '\\')) {
            rtn += format[i];
        }
        else if (format[i] == '\\') {
            if (i + 1 < format.length()) {
                if (format[i + 1] == '%') {
                    rtn += '%';
                }
                else if (format[i + 1] == '\\') {
                    rtn += '\\';
                }
                ++i;
            }
            else {
                break;
            }
        }
        else if (format[i] == '%') {
            if (i + 1 < format.length()) {
                if (format[i + 1] == 's') {
                    rtn += std::to_string(nowTime->tm_sec);
                }
                else if (format[i + 1] == 'm') {
                    rtn += std::to_string(nowTime->tm_min);
                }
                else if (format[i + 1] == 'h') {
                    rtn += std::to_string(nowTime->tm_hour);
                }
                else if (format[i + 1] == 'd') {
                    rtn += std::to_string(nowTime->tm_mday);
                }
                else if (format[i + 1] == 'n') {
                    rtn += std::to_string(nowTime->tm_mon);
                }
                else if (format[i + 1] == 'y') {
                    rtn += std::to_string(nowTime->tm_year + 1900);
                }
                else if (format[i + 1] == 'c') {
                    rtn += std::to_string(counter);
                }
                ++i;
            }
            else {
                break;
            }
        }
    }

    return rtn;
}

void FileNameGen::SetFormat(const char* fmt) {
    format = fmt;
}
} // TFC
