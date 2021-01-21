//
// Created by weicheng qian on 2020/5/2.
//

#ifndef A8_EDI_CURL_HPP
#define A8_EDI_CURL_HPP

#include <map>
#include <vector>
#include <curl_header.h>
#include "curl_easy.h"
#include "curl_ios.h"
#include "curl_exception.h"
#include "curl_pair.h"
#include "curl_header.h"

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;
using curl::curl_pair;
using curl::curl_header;

namespace a8 {

    class EdiCurl {
    public:
        EdiCurl();

        EdiCurl(long timeout);

        ~EdiCurl();

        static void ConfigCURL(curl_easy &easy);

        void SetHeaders(const std::shared_ptr<std::map<std::string, std::string>> headers);

        void Escape(std::string &str);

        int GET(const std::string &url, std::string *response);

        int POST(const std::string &url, std::string *response);

        int POST(const std::string &url, const std::string &body, std::string *response);

        int EXEC(const std::string &url, std::string *response);

    private:
        std::unique_ptr<curl_easy> easy;
        std::shared_ptr<std::map<std::string, std::string>> headers;
    };
}

#endif //A8_EDI_CURL_HPP
