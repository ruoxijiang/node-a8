//
// Created by bumblebee on 1/19/21.
//

#ifndef A8_NODE_ADDON_H
#define A8_NODE_ADDON_H

#include <a8/a8.h>
#include <a8/email_security/email_security.hpp>
#include <a8/spider/linkedin_spider.hpp>
#include <napi.h>

enum commands {
    NODE_HEADER_CHECK = 0,
    NODE_EMAIL_CHECK = 1,
    NODE_LINKED_PROFILE_FETCH = 2,
    NODE_SPAM_CHECK = 3
};

class NodeCheckCB : public a8::CheckCB {
public:
    NodeCheckCB(const Napi::AsyncProgressQueueWorker<a8::OnlineResult>::ExecutionProgress &progress);

    virtual void OnResult(std::shared_ptr<a8::OnlineResult> result);

    ~NodeCheckCB();

private:
    const Napi::AsyncProgressQueueWorker<a8::OnlineResult>::ExecutionProgress &progress;
};

class NodeAddon : public Napi::AsyncProgressQueueWorker<a8::OnlineResult> {
public:
    NodeAddon(Napi::Function &okCallback, Napi::Function &errorCallback, Napi::Function &progressCallback, int command,
              int max_wait_seconds);

    virtual ~NodeAddon();

    void ParseJSHeaders(const Napi::Array &headers);

    a8::HeaderItem JSToHeaderItem(const Napi::Object &header);

    void ParseJSExtCheckInfo(const Napi::Object &checkInfo);

    void ParseJSEmailInfo(const Napi::Object &emailInfo);

    void ParseJSEmailAddress(const Napi::String &emailAddress);

    void ParseJSReplyTo(const Napi::String &replyTo);

    void ParseJSLinkedInQueryParam(const Napi::Object &linkedInQueryParam);


    void Execute(const ExecutionProgress &progress);

    void OnOK();

    void OnError(const Napi::Error &error);

    void OnProgress(const a8::OnlineResult *onlineResult, size_t count);

private:
    void CheckEmail();

    void CheckHeader();

    void FetchLinkedInProfile();

    void SpamCheck(const Napi::AsyncProgressQueueWorker<a8::OnlineResult>::ExecutionProgress &progress);

    void CheckResultToJS(const a8::CheckResult &checkResult, Napi::Object &ret);

    void OnlineResultToJS(const a8::OnlineResult &result, Napi::Object &ret);

    void LinkedInProfileToJS(const a8::LinkedInProfile &profile, Napi::Object &ret);


    int command = 0;
    int max_wait_seconds = 90;
    const int totalSpamChecks = 70;
    a8::CheckResult output_CheckResult;
    a8::LinkedInProfile output_LinkedInProfile;
    a8::EmailInfo input_EmailInfo;
    std::string input_emailAddress;
    std::string input_ReplyTo;
    a8::ExtCheckInfo input_ExtraInfo;
    a8::LinkedInQueryParam input_LinkedInQueryParam;
    std::vector<a8::HeaderItem> input_Headers;
    Napi::FunctionReference progressCallback;
    Napi::FunctionReference errorCallback;
    int output_simpleCheckResult = 0;
    int spamCheckInCBCount = 0;
};

#endif //A8_NODE_ADDON_H
