//
// Created by weicheng qian on 2020/4/3.
//

#ifndef A8_EMAIL_SECURITY_HPP
#define A8_EMAIL_SECURITY_HPP

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

#define RESULT_FAILE 2
#define RESULT_NEUTRAL 1
#define RESULT_PASS 0
#define RESULT_UNKNOW -1

namespace a8 {
    // DMARC = SPF & DKIM & (plus logic), so if DMARC is pass, SPF & DKIM MUST be pass
    // If sendVia is not Empty, show the sender(this is normal sender)
    // If DMARC=0, show good(a green icon),
    // If DMARC=1,do nothing(not enough info to check)
    // If DMARC=2, show 'sendVia' field, and
    // If SPF or DKIM is false, then show WARNING
    typedef struct {
        std::string sentVia; //This is used to Info the user
        int spfPass = RESULT_UNKNOW; //2: failed, 1:neutral(not sure),  0: success, -1: unknown
        int dkimPass = RESULT_UNKNOW; //2: failed, 1:neutral(not sure),  0: success, -1: unknown
        int dmarcPass = RESULT_UNKNOW; //2: failed, 1:neutral(not sure),  0: success, -1: unknown
        int sentViaPass = RESULT_UNKNOW; //2: failed, 1:neutral(not sure),  0: success, -1: unknown
        int smtpPass = RESULT_UNKNOW; //3: sure fake email, 2: can not receive email, 1: connection error,  0: success, -1: unknown
        int spamPass = RESULT_UNKNOW; // 2: failed(spam db > 0), 0: success, -1: unknown
        int bodyPass = RESULT_UNKNOW; // -1: unknown, 0:success, 1:neutral(not sure), 2: phishing
    } CheckResult;
    typedef struct {
        bool isStrange;
        bool isColleague;
        bool isWellKnownProvider;
    } ExtCheckInfo;
    typedef struct {
        std::string type; //mxs, ips, smtp, dbl, dbl2, spf(server configuration), spf-client(verify other server), dmarc
        std::string domain;
        // success:0, failed:1.
        // For smtp: 0->success, 1->connection failed, 2->send mail failed, 3: sure for invaid(no mx record or gmail user not exists).
        // For spf-client: 0->success, 1->connection failed, 2->spf check failed.
        int code;
        std::vector<std::string> results;
    } OnlineResult;
    typedef struct {
        int type;//0: string, 1: vector
        std::string header; // the name of the header,such as From, To, Subject
        std::string value; // If type=0, get value from this field
        std::vector<std::string> values; // If type=1, get value from this field
    } HeaderItem;
    typedef struct {
        std::string owner;
        std::string identify;
        std::string src; //marked by user or AI
        int label;  // normal(0) or phishing(1)
        std::string body;
        std::vector<HeaderItem> imapHeaders;
    } EmailInfo;

    class CheckCB {
    public:
        virtual void OnResult(std::shared_ptr<OnlineResult> result) = 0;
    };
}

#endif //A8_EMAIL_SECURITY_HPP
