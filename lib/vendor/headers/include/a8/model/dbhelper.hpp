//
// Created by weicheng qian on 2020/4/24.
//

#ifndef A8_DBHELPER_HPP
#define A8_DBHELPER_HPP

#include "db_storage.hpp"

#ifndef __DISABLE_A8_SQLITE__

namespace a8 {
    class DBhelper {
    public:
        DBhelper();

        DBhelper(const std::string &workDirectory);

        void Save(OrganizationInfo &info);

        void Save(std::vector<OrganizationInfo> &infos);

        std::vector<OrganizationInfo>
        QueryOrganizationInfos(const std::vector<std::string> &domains, bool fullmode = false);

        void Delete(OrganizationInfo &info);

        void Save(LinkedInProfile &profile);

        LinkedInProfile QueryLinkedInProfile(const std::string &email);

        void Delete(LinkedInProfile &profile);

        void Save(VendorEmail &vendor);

        VendorEmail QueryVendorEmail(const std::string &email);

        void Delete(const VendorEmail &vendor);

        void Save(DNSRecord &dnsRecord);

        void Save(const std::map<std::string, std::vector<std::string>> &dnsRecords, const std::string &type);

        DNSRecord QueryDNSRecord(const std::string &domain, const std::string &type);

        std::vector<DNSRecord> QueryDNSRecords(const std::vector<std::string> &domains, const std::string &type);

        void Delete(const DNSRecord &dnsRecord);

        void Save(EmailCheckResult &checkResult, EmailCheckResultField field);

        EmailCheckResult QueryEmailCheckResult(const std::string &email);

        void Delete(const EmailCheckResult &checkResult);

        ~DBhelper();

    public:
        void TestDB();

    private:
        int CheckDB(int &currentVersion);

        int SaveDBInfo();

        int WatchDog(bool open);

    private:
        std::string dbpath;
        std::string dbInfoPath;
        std::string dbWatchDogPath;
    };
}

#else

namespace a8 {

    class DBhelper {
    public:
        DBhelper() {

        }

        DBhelper(const std::string &dbpath) {

        }

        void Save(OrganizationInfo &info) {}

        void Save(std::vector<OrganizationInfo> &infos) {}

        std::vector<OrganizationInfo> QueryOrganizationInfos(const std::vector<std::string> &domains, bool fullmode = false) {return std::vector<OrganizationInfo>();}

        void Delete(OrganizationInfo &info){}

        void Save(LinkedInProfile &profile){}

        LinkedInProfile QueryLinkedInProfile(const std::string &email){return LinkedInProfile();}

        void Delete(LinkedInProfile &profile){}

        void Save(VendorEmail &vendor){}

        VendorEmail QueryVendorEmail(const std::string &email){return VendorEmail();}

        void Delete(const VendorEmail &vendor){}

        void Save(DNSRecord &dnsRecord){}

        void Save(const std::map<std::string, std::vector<std::string>> &dnsRecords, const std::string &type){}

        DNSRecord QueryDNSRecord(const std::string &domain, const std::string &type){return DNSRecord();}

        std::vector<DNSRecord> QueryDNSRecords(const std::vector<std::string> &domains, const std::string &type){return std::vector<DNSRecord>();}

        void Delete(const DNSRecord &dnsRecord){}

        void Save(EmailCheckResult &checkResult, EmailCheckResultField field){}

        EmailCheckResult QueryEmailCheckResult(const std::string &email){return EmailCheckResult();}

        void Delete(const EmailCheckResult &checkResult){}

        ~DBhelper() {

        }
    };
}

#endif  // __DISABLE_A8_SQLITE__

#endif // A8_DBHELPER_HPP
