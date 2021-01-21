//
// Created by weicheng qian on 2020/3/27.
//

#ifndef A8_GMAIL_PARSER_HPP
#define A8_GMAIL_PARSER_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace a8 {
    class GmailParser {
    public:
        static void
        ParseMessage(const nlohmann::json &message, std::vector<nlohmann::json> &htmlParts,
                     std::vector<nlohmann::json> &inlineAttachments, std::vector<nlohmann::json> &attachments);

        static void
        ParseMessage2(const std::string &response, std::vector<nlohmann::json> &htmlParts,
                      std::vector<nlohmann::json> &inlineAttachments, std::vector<nlohmann::json> &attachments);

        static void Test();

    private:
        static void
        ParsePart(const std::string &partID, nlohmann::json part, std::vector<nlohmann::json> &htmlParts,
                  std::vector<nlohmann::json> &inlineAttachments, std::vector<nlohmann::json> &attachments);

        static bool PartContainsMimeType(const nlohmann::json part, std::string targetMimeType);

        static bool IsInlinePart(const nlohmann::json &part, bool strict);

        static bool IsTextPart(const nlohmann::json &part);

        static bool IsImagePart(const nlohmann::json &part);
    };
} // namespace a8

#endif //A8_GMAIL_PARSER_HPP
