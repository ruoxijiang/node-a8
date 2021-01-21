//
// Created by Dalio on 2020/5/9.
//

#ifndef A8_PHISHING_UNICODE_HPP
#define A8_PHISHING_UNICODE_HPP

#include <string>
#include <unistd.h>
#include <map>
#include <vector>

namespace a8 {
    class PhishingUnicode {
    public:

        static std::shared_ptr<PhishingUnicode> GetInstance();

        PhishingUnicode();

        std::string AntiPhishing(const std::string &input);

        std::vector<std::string> AntiPhishing2(const std::string &input);

        //only for test
        static std::string getTestString();

        static int getTestStringCount();

        static std::string getTestString(int index);

    private:

        std::vector<std::vector<std::string>> GenerateCandidates(const std::string &input);

        std::vector<std::string> Decare(const std::vector<std::vector<std::string>> &sets);

        std::wstring StringToWstring(const std::string str);

        std::string WstringToString(const std::wstring w_str);

        std::string Substr(const std::string &input, int length);

    private :
        std::map<std::string, std::wstring> confuseStrMap;
    };
}
#endif //A8_PHISHING_UNICODE_HPP
