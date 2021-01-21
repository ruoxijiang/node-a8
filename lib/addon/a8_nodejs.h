#ifndef A8_NODEJS_H
#define A8_NODEJS_H
#include <vector>
#include <string>

typedef struct {
    std::string platform;
    std::string userAgent;
    std::string nativeVersion;
} PlatformInfo;

PlatformInfo GetPlatformInfo() {
    return {
            "macOS",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.111 Safari/537.36",
            "1.0",
    };
}


#endif //A8_NODEJS_H
