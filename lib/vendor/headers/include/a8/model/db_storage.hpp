//
//  Created by luzhixin on 2020/10/22.
//

#ifndef A8_DB_STORAGE_HPP
#define A8_DB_STORAGE_HPP

#include <string>
#include <vector>
#include "entities.hpp"

#if defined(__DESKTOP__)
#include "vendor/sqlite/sqlite3.h"
#else

#include <sqlite3.h>

#endif

namespace a8 {
    class DbException {
    public:
        DbException(int errCode);

        DbException(int errCode, std::string errMsg);

        DbException(int errCode, std::string errMsg, std::string sqlStr);

        ~DbException();

        int GetErrorCode() const;

        std::string GetErrorMsg() const;

        std::string GetSqlStr() const;

    private:
        int m_errCode;
        std::string m_errMsg;
        std::string m_sqlStr;
    };

    class DbStatement {
    public:
        DbStatement();

        ~DbStatement();

        void Setup(sqlite3_stmt *stmt);

        void Bind(int pos, int value);

        void Bind(int pos, uint32_t value);

        void Bind(int pos, long long value);

        void Bind(int pos, unsigned long long value);

        void Bind(int pos, double value);

        void Bind(int pos, const std::string &value);

        void Bind(int startPos, const std::vector<std::string> &values);

        bool Next();

        int GetInt(int field, int defaultValue = INT32_MAX);

        long long GetLongLong(int field, long long defaultValue = INT64_MAX);

        double GetDouble(int field, double defaultValue = 0);

        std::string GetText(int field);

    private:
        sqlite3_stmt *m_stmt;
    };

    class DbConnect {
    public:
        DbConnect(const std::string &dbpath);

        ~DbConnect();

        int PrepareStatement(const std::string &sqlStr, DbStatement &stmt);

        void Execute(const std::string &sqlStr);

        void BeginTransaction();

        void Commit();

        void Rollback();

        std::vector<std::string> GetTableNames();

        void DropAllTables();

    private:
        sqlite3 *m_conn;
        bool m_inTransaction;
    };

    class A8DbConnect : public DbConnect {
    public:
        A8DbConnect(const std::string &dbpath);

        ~A8DbConnect();

        void InitDB();

        void UpgradeDB(const int oldVersion, const int newVersion);

        std::vector<OrganizationInfo> GetOrganizationInfosByDomain(const std::string &domain);

        std::vector<OrganizationInfo> GetOrganizationInfosByDomains(const std::vector <std::string> &domains, bool fullmode);

        void InsertOrganizationInfo(const OrganizationInfo &org);

        void ReplaceOrganizationInfo(const OrganizationInfo &org);

        void DeleteOrganizationInfoById(int id);

        void DeleteOrganizationInfoByDomain(const std::string &domain);

        std::vector<LinkedInProfile> GetLinkedInProfilesByEmail(const std::string &email);

        void InsertLinkedInProfile(const LinkedInProfile &linkedIn);

        void ReplaceLinkedInProfile(const LinkedInProfile &linkedIn);

        void DeleteLinkedInProfileById(int id);

        void DeleteLinkedInProfileByEmail(const std::string &email);

        std::vector<VendorEmail> GetVendorEmailsByEmail(const std::string &email);

        void InsertVendorEmail(const VendorEmail &vendor);

        void ReplaceVendorEmail(const VendorEmail &vendor);

        void DeleteVendorEmailById(int id);

        void DeleteVendorEmailByEmail(const std::string &email);

        std::vector<DNSRecord> GetDNSRecordsByDomainAndType(const std::string &domain, const std::string &type);

        std::vector<DNSRecord>
        GetDNSRecordsByDomainsAndType(const std::vector<std::string> &domains, const std::string &type);

        void InsertDNSRecord(const DNSRecord &dnsRecord);

        void ReplaceDNSRecord(const DNSRecord &dnsRecord);

        void DeleteDNSRecordById(int id);

        void DeleteDNSRecordByDomainAndType(const std::string &domain, const std::string &type);

        std::vector<EmailCheckResult> GetEmailCheckResultByEmail(const std::string &email);

        void InsertEmailCheckResult(const EmailCheckResult &checkResult);

        void ReplaceEmailCheckResult(const EmailCheckResult &checkResult);

        void DeleteEmailCheckResultById(int id);

        void DeleteEmailCheckResultByEmail(const std::string &email);

    private:
        void Config();
    };
}

#endif /* db_storage_hpp */
