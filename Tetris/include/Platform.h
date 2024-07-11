#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <vector>
#include <string>

class Platform {
public:
    static Platform& GetPlatform() {
        static Platform ObjPlatform;
        ObjPlatform.DoPlatform();
        return ObjPlatform;
    }

    void PrintPlatform();

    Platform(const Platform&) = delete;
    Platform& operator=(const Platform&) = delete;

    std::vector<std::string> platform;
    const int height = 48;
    const int width = 59;

private:
    void DoPlatform();

    Platform() = default;
};

#endif