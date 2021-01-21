//
// Created by weicheng qian on 2020/11/24.
//

#ifndef A8_PHISHING_CHECK_SERVICE_HPP
#define A8_PHISHING_CHECK_SERVICE_HPP

#include <iostream>
#include <string>
#include "../rx_application.hpp"
#include "../email_security/email_security.hpp"
#include "../model/entities.hpp"

namespace a8 {

    typedef struct {
        int smtp = RESULT_NEUTRAL;
        std::string smtpMessage;
        int body = RESULT_NEUTRAL;
        std::string bodyMessage;
    } EmailCheckServerResult;

    class PhishingCheckService {
    public:
        static int CheckEmailSMTP(const std::string &email, const std::vector<std::string> &mxServers);

        static EmailCheckServerResult
        CheckEmailOnServer(const EmailInfo &emailInfo, const bool needCheckBody, const bool needCheckSMTP);
    };
}

#endif //A8_PHISHING_CHECK_SERVICE_HPP
