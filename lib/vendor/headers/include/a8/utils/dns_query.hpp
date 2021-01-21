//
// Created by weicheng qian on 2020/3/22.
//

#ifndef A8_DNS_QUERY_HPP
#define A8_DNS_QUERY_HPP

#include <vector>
#include <map>
#include <iostream>
#include <string>

class DNSQuery {
public:
    static std::vector<std::string> Query(const std::string &domain, const std::string &queryType);

    static int
    QueryWithoutCache(const std::string &domain, const std::string &queryType, std::vector<std::string> &result);

    static std::map<std::string, std::vector<std::string>>
    Query(const std::vector<std::string> domains, const std::string &queryType);

    static std::vector<std::string> QueryIP(const std::string &domain, int ipv = 4);
};


#endif //A8_DNS_QUERY_HPP
