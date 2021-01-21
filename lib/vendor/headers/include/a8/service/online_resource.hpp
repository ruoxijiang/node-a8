//
// Created by weicheng qian on 2020/4/18.
//

#ifndef A8_ONLINE_RESOURCE_HPP
#define A8_ONLINE_RESOURCE_HPP

#include <iostream>
#include <string>
#include "../rx_application.hpp"
#include "../email_security/email_security.hpp"
#include "../model/entities.hpp"

namespace a8 {

    class OnlineResource {
    public:
        static OrganizationInfo FetchOrganizationInfo(const std::string &domain);

        static std::vector<OrganizationInfo>
        FetchOrganizationInfo(const std::vector<std::string> &domains, bool fullmode = false);

        static VendorEmail FetchVendorEmail(const std::string &email);

        static void UploadEmailInfoAsync(const EmailInfo &emailInfo);

        static void UploadIMAPSMTPSettingAsync(const std::string &domain, const IMAPSMTPSetting &setting);

        static IMAPSMTPSetting DownloadIMAPSMTPSetting(const std::string &domain);
    };
}


#endif //A8_ONLINE_RESOURCE_HPP
