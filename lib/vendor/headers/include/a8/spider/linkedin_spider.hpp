//
// Created by weicheng qian on 2020/5/14.
//

#ifndef A8_LINKEDIN_SPIDER_HPP
#define A8_LINKEDIN_SPIDER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "../model/entities.hpp"
#include "rapidxml/rapidxml.hpp"
#include "../service/online_resource.hpp"

using namespace rapidxml_a8;

namespace a8 {
    enum SearchEngine {
        Local,
        Google,
        GoogleCustomSearch,
        Bing,
        Edison,
    };
    enum SearchPlace {
        INTITLE,
        INTEXT
    };
    enum ProfileVersion {
        Normal = 0, // 0,
        Tip = 1, // organization from discover
        Public = 2 // public domain
    };
    typedef struct {
        SearchPlace place;
        std::string name;
        std::string organization;
        std::string title;
        std::string html;
        int version;
    } SearchCase;

    typedef struct {
        std::string name;
        std::string email;
        std::string organization;
        std::string organizationSource;//db,domain,tip
        std::string title;
        std::string owner;
    } LinkedInQueryParam;

    class LinkedInSpider {
    public:
        LinkedInSpider();

        LinkedInSpider(SearchEngine searchEngine);

        LinkedInProfile FetchLinkedInProfile(LinkedInQueryParam queryParam, const int curl_timeout = 8L);

        bool ParseLinkedInInfo(const SearchCase &searchCase, LinkedInProfile &profile);

        bool ParseLinkedInInfoFromJson(const SearchCase &searchCase, LinkedInProfile &profile);

        void UploadLinkedInReportAsync(const LinkedInQueryParam &queryParam, const LinkedInProfile &linkedInProfile,
                                       const std::string &queryStr);

        bool MatchOrganization(const std::string &organizationIntitle, const std::string &organization2Search);

        bool MatchName(const std::string &searchResultTitle, const std::string &name, std::vector<std::string> &segs);

        bool MatchDescription(const SearchCase &searchCase, const std::string &description);

        std::string FetchOrganization(const std::string &email);

        std::string FindDescription(const SearchCase &searchCase, const long start);

        static std::string BuildQuery(const SearchCase &searchCase);

    private:

        bool ParseLinkedInInfoViaRegex(const SearchCase &searchCase, LinkedInProfile &profile);

        bool ParseLinkedInInfoFromXML(const SearchCase &searchCase, LinkedInProfile &profile);

    private:
        SearchEngine searchEngine;
        std::regex linkedinURLRegex;
        std::regex linkedinURLRegex2;
    };
}  // namespace a8

#endif // A8_LINKEDIN_SPIDER_HPP
