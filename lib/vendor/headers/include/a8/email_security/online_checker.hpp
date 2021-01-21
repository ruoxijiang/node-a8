//
// Created by weicheng qian on 2020/3/16.
//

#ifndef A8_ONLINE_CHECKER_HPP
#define A8_ONLINE_CHECKER_HPP

#include <string>
#include <vector>
#include "email_security.hpp"

namespace a8 {
    class OnlineChecker {
    public:
        OnlineChecker();

        OnlineChecker(std::weak_ptr<CheckCB> cb);

        ~OnlineChecker();

        static void CheckAll(const std::string &email, const std::string &replyTo, std::weak_ptr<CheckCB> cb);

        void CheckAllAsync(const std::string &email, const std::string &replyTo);

        static void CheckAllAsync(const std::string &email, const std::string &replyTo, std::weak_ptr<CheckCB> cb);

        static int CheckSMTP(const std::string &email, std::weak_ptr<CheckCB> cb);

        void CheckSMTPAsync(const std::string &email, const std::string &replyTo);

        static void CheckSMTPAsync(const std::string &email, const std::string &replyTo, std::weak_ptr<CheckCB> cb);

        static int CheckSMTPLocal(const std::string &smtpServer, const std::string &email);

        static std::string EHLO(const std::string &mxServer);

        static bool IsExchange(const std::string &domain);

        static bool IsGmail(const std::string &domain);

    private:
        static void
        CheckBLByDomains(const std::string &email, const std::vector<std::string> &domains, std::weak_ptr<CheckCB> cb);

        static void
        CheckBLByIPs(const std::string &email, const std::vector<std::string> &mxServers, std::weak_ptr<CheckCB> cb);

        static void CheckSPFDMARC(const std::string &domain, std::weak_ptr<CheckCB> cb);

        static void CheckSMTPWithReplyTo(const std::string &email, const std::string &replyTo,
                                         std::weak_ptr<CheckCB> cb);

        static int CheckSPFClient(const std::string &smtpServer);

        static void
        CheckBLByIPsInternal(const std::string &email, const std::vector<std::string> &ipbls,
                             const std::vector<std::string> &reversedIps, std::weak_ptr<CheckCB> cb);

    private:
        std::weak_ptr<CheckCB> callback;
        static std::string dbls[];
        static std::string ipbls[];
    };
}

#endif //A8_ONLINE_CHECKER_HPP
