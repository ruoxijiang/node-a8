//
// Created by weicheng qian on 2020/11/24.
//

#ifndef A8_EDISON_SERVICE_MANAGER_HPP
#define A8_EDISON_SERVICE_MANAGER_HPP

#include <iostream>
#include <string>

namespace a8 {
    class EdisonServiceManager {
    public:
        static std::string GetCrunchbaseOrganizationProxyURL();

        static std::string GetCrunchbaseDomainCheckBatchURL();

        static std::string GetEmailSMTPCheckURL();

        static std::string GetSecurityReportURL();

        static std::string GetSecurityCheckURL();

        static std::string GetFetchIMAPSettingsURL();

        static std::string GetLinkedInDiscoverReportURL();

        static std::string GetMultipleServiceBearer();

        static std::string GetAESPassword();

    private:
        static inline std::string GetHost();
    };
}

#endif //A8_EDISON_SERVICE_MANAGER_HPP
