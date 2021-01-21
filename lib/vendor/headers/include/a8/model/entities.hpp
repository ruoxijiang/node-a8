//
// Created by weicheng qian on 2020/4/24.
//

#ifndef A8_MODEL_ENTITIES_HPP
#define A8_MODEL_ENTITIES_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace a8 {

    class OrganizationInfo {
    public:
        void FromJson(const nlohmann::json &data);

    public:
        int id = 0; //db row id
        int code = 0; // 0: success, 1: error, 2: parse-error, 404: not found, xxx:other
        std::string name;
        std::string domain;
        std::string homepage;
        std::string description;
        std::string profileImag;
        std::string facebook;
        std::string linkedin;
        std::string twitter;
        time_t updateTime = 0;
    };

    class VendorEmail {
    public:
        void FromJson(const nlohmann::json &data);

    public:
        int id = 0;
        int code = 0; // 0: success, 1: error, 2: parse-error, 404: not found, xxx:other
        std::string email;
        std::string name;
        time_t updateTime = 0;
    };

    typedef struct {
        int id = 0;
        int code = 0; // 0: success, 1: error, 2: parse-error, 3: drop duplicate result, 404: not found, xxx:other
        std::string email;
        std::string name;
        std::string title;
        std::string linkedin;
        time_t updateTime = 0;
        int version = 0;
        int source; //SearchEngine: local cache, google, custom search, bing, edison
    } LinkedInProfile;

    class DNSRecord {
    public:
        int id = 0;
        std::string domain;
        std::string type;
        std::string result;
        time_t updateTime = 0;
    public:
        void SetRecords(const std::vector<std::string> &records);

        std::vector<std::string> GetRecords();
    };

    typedef struct {
        int id = 0;
        std::string email;
        int spf = -1;
        int spfClient = -1;
        int dkim = -1;
        int dmarc = -1;
        int smtp = -1;
        int dbl = -1;
        int dblProcess = 0;
        time_t updateTime = 0;
    } EmailCheckResult;

    enum EmailCheckResultField {
        EmailCheckResultFieldNone = 0,
        EmailCheckResultFieldAll = 1,
        EmailCheckResultFieldSPF = 2,
        EmailCheckResultFieldSPFClient = 3,
        EmailCheckResultFieldDKIM = 4,
        EmailCheckResultFieldDMARC = 5,
        EmailCheckResultFieldSMTP = 6,
        EmailCheckResultFieldDBL = 7,
        EmailCheckResultFieldDBLProcess = 8
    };

    class IMAPSMTPSetting {
    public:
        void FromJson(const nlohmann::json &data);

        std::string ToJsonString();

    public:
        std::string domain;
        std::string imap_host;
        int imap_port = 993;
        std::string imap_security;
        std::string smtp_host;
        int smtp_port = 465;
        std::string smtp_security;
    };
}
#endif //A8_MODEL_ENTITIES_HPP
