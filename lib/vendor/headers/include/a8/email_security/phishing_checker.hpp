//
//  phishing_checker.hpp
//  test-mac
//
//  Created by weicheng qian on 2020/2/12.
//

#ifndef phishingchecker_hpp
#define phishingchecker_hpp

#include <stdio.h>
#include <iostream>
#include <a8/utils/dns_query.hpp>
#include "online_checker.hpp"
#include "email_security.hpp"
#include "phishing_unicode.hpp"

namespace a8 {
    class PhishingChecker {
    public:
        PhishingChecker();

        PhishingChecker(std::weak_ptr<CheckCB> cb);

        /**
         * Deprecated. This api will be removed in the next version, please use CheckHeader
         * */
        CheckResult Check(const std::vector<HeaderItem> &headers);

        CheckResult CheckHeader(const std::vector<HeaderItem> &headers);

        /**
         * 0: header is OK, no need to check more, 1: need to check body, 2: need to check smtp
         * */
        int CheckResultSimplify(const CheckResult &checkResult, const ExtCheckInfo &extCheckInfo);

        /**
         * Should call this api async
         * Return: 0: success, other: error code
         * */
        int CheckEmail(const EmailInfo &emailInfo, const ExtCheckInfo &extCheckInfo, CheckResult &checkResult);

        void CheckAsync(const std::string &email, const std::string &replyTo);

        void CheckAsync(const std::string &email, const std::string &replyTo, std::weak_ptr<CheckCB> cb);

        void CheckSMTPAsync(const std::string &email, const std::string &replyTo);

        void CheckSMTPAsync(const std::string &email, const std::string &replyTo, std::weak_ptr<CheckCB> cb);

        // valid:0, invalid:1
        static bool IsValidEmail(const std::string &email);

        static bool HasSpecialName(const std::string &email);

        static std::string AntiPhishing(const std::string &name);

        static std::vector<std::string> AntiPhishing2(const std::string &name);

    private:
        std::shared_ptr<OnlineChecker> onlineChecker;
    };
};
#endif /* phishing_checker_hpp */
