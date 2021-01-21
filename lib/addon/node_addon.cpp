//
// Created by bumblebee on 1/19/21.
//

#include "node_addon.h"
#include <a8/a8.h>
#include <a8/email_security/email_security.hpp>
#include <napi.h>
#include <thread>
#include <chrono>

using namespace a8;
using namespace Napi;
using namespace std;

NodeCheckCB::NodeCheckCB(const Napi::AsyncProgressQueueWorker<a8::OnlineResult>::ExecutionProgress &progress)
        : progress(progress) {}

NodeCheckCB::~NodeCheckCB() {}

void NodeCheckCB::OnResult(std::shared_ptr<OnlineResult> result) {
    if (result) {
        this->progress.Send(result.get(), 1);
    } else {
        OnlineResult *tmp;
        tmp->code = 1;
        tmp->type = "runtimeError";
        this->progress.Send(tmp, 1);
        delete tmp;
        tmp = nullptr;
    }
//    if (result->type == "dbl" || result->type == "dbl2") {
//        this->dbl2Count++;
//        return;
//    } else if (result->type == "dbl-info") {
//        printf("Domain: %s\tCode:%i\n", result->domain.c_str(), result->code);
//        this->progress.Send(result.get(), 1);
//        return;
//    }
//    printf("Sending progress result\n");
//    printf("%i\ttype:%s\tdomain:%s\tcode:%i\n", this->dbl2Count, result->type.c_str(), result->domain.c_str(),
//           result->code);
//    for (auto item:result->results) {
//        printf("item:%s\n", item.c_str());
//    }
}


NodeAddon::NodeAddon(Function &okCallback, Function &errorCallback, Function &progressCallback, int command,
                     int max_wait_seconds)
        : AsyncProgressQueueWorker(okCallback), command(command), max_wait_seconds(max_wait_seconds) {
    this->errorCallback.Reset(errorCallback, 1);
    this->progressCallback.Reset(progressCallback, 1);
}

NodeAddon::~NodeAddon() {}

void NodeAddon::ParseJSHeaders(const Napi::Array &headers) {
    this->input_Headers.clear();
    for (int i = 0; i < headers.Length(); i++) {
        this->input_Headers.emplace_back(JSToHeaderItem(headers.Get(i).As<Object>()));
    }
}

HeaderItem NodeAddon::JSToHeaderItem(const Object &header) {
    HeaderItem ret;
    if (header.Has("type")) {
        ret.type = header.Get("type").As<Number>();
    }
    if (header.Has("header")) {
        ret.header = header.Get("header").As<String>();
    }
    if (ret.type == 0 && header.Has("value")) {
        ret.value = header.Get("value").As<String>();
    } else if (ret.type == 1 && header.Has("values")) {
        vector<string> values;
        Array tmp = header.Get("values").As<Array>();
        for (int i = 0; i < tmp.Length(); i++) {
            values.emplace_back(tmp.Get(i).As<String>());
        }
        ret.values = values;
    }
    return ret;
}

void NodeAddon::ParseJSExtCheckInfo(const Object &checkInfo) {
    this->input_ExtraInfo.isColleague = false;
    this->input_ExtraInfo.isStrange = false;
    this->input_ExtraInfo.isWellKnownProvider = false;
    if (checkInfo.Has("isStrange")) {
        this->input_ExtraInfo.isStrange = checkInfo.Get("isStrange").As<Boolean>();
    }
    if (checkInfo.Has("isColleague")) {
        this->input_ExtraInfo.isColleague = checkInfo.Get("isColleague").As<Boolean>();
    }
    if (checkInfo.Has("isWellKnownProvider")) {
        this->input_ExtraInfo.isWellKnownProvider = checkInfo.Get("isWellKnownProvider").As<Boolean>();
    }
}

void NodeAddon::ParseJSEmailInfo(const Object &emailInfo) {
    this->input_EmailInfo.owner = "";
    this->input_EmailInfo.body = "";
    this->input_EmailInfo.identify = "";
    this->input_EmailInfo.label = 0;
    this->input_EmailInfo.src = "";
    this->input_EmailInfo.imapHeaders.clear();
    if (emailInfo.Has("owner")) {
        this->input_EmailInfo.owner = emailInfo.Get("owner").As<String>();
    }
    if (emailInfo.Has("identify")) {
        this->input_EmailInfo.identify = emailInfo.Get("identify").As<String>();
    }
    if (emailInfo.Has("src")) {
        this->input_EmailInfo.src = emailInfo.Get("src").As<String>();
    }
    if (emailInfo.Has("label")) {
        this->input_EmailInfo.label = emailInfo.Get("label").As<Number>();
    }
    if (emailInfo.Has("body")) {
        this->input_EmailInfo.body = emailInfo.Get("body").As<String>();
    }
    if (emailInfo.Has("imapHeaders")) {
        Array headers = emailInfo.Get("imapHeaders").As<Array>();
        for (int i = 0; i < headers.Length(); i++) {
            this->input_EmailInfo.imapHeaders.emplace_back(this->JSToHeaderItem(headers.Get(i).As<Object>()));
        }
    }
}

void NodeAddon::ParseJSEmailAddress(const Napi::String &emailAddress) {
    this->input_emailAddress = emailAddress;
}

void NodeAddon::ParseJSReplyTo(const Napi::String &replyTo) {
    this->input_ReplyTo = replyTo;
}

void NodeAddon::ParseJSLinkedInQueryParam(const Napi::Object &linkedInQueryParam) {
    if (linkedInQueryParam.Has("name")) {
        this->input_LinkedInQueryParam.name = linkedInQueryParam.Get("name").As<String>();
    }
    if (linkedInQueryParam.Has("email")) {
        this->input_LinkedInQueryParam.email = linkedInQueryParam.Get("email").As<String>();
    }
    if (linkedInQueryParam.Has("organization")) {
        this->input_LinkedInQueryParam.organization = linkedInQueryParam.Get("organization").As<String>();
    }
    if (linkedInQueryParam.Has("organizationSource")) {
        this->input_LinkedInQueryParam.organizationSource = linkedInQueryParam.Get("organizationSource").As<String>();
    }
    if (linkedInQueryParam.Has("title")) {
        this->input_LinkedInQueryParam.title = linkedInQueryParam.Get("title").As<String>();
    }
    if (linkedInQueryParam.Has("owner")) {
        this->input_LinkedInQueryParam.owner = linkedInQueryParam.Get("owner").As<String>();
    }
}

void NodeAddon::CheckResultToJS(const CheckResult &checkResult, Object &ret) {
    ret.Set(String::New(Env(), "sentVia"), String::New(Env(), checkResult.sentVia));
    ret.Set(String::New(Env(), "spfPass"), Number::New(Env(), checkResult.spfPass));
    ret.Set(String::New(Env(), "dkimPass"), Number::New(Env(), checkResult.dkimPass));
    ret.Set(String::New(Env(), "dmarcPass"), Number::New(Env(), checkResult.dmarcPass));
    ret.Set(String::New(Env(), "sentViaPass"), Number::New(Env(), checkResult.sentViaPass));
    ret.Set(String::New(Env(), "smtpPass"), Number::New(Env(), checkResult.smtpPass));
    ret.Set(String::New(Env(), "spamPass"), Number::New(Env(), checkResult.spamPass));
    ret.Set(String::New(Env(), "bodyPass"), Number::New(Env(), checkResult.bodyPass));
}

void NodeAddon::OnlineResultToJS(const a8::OnlineResult &result, Object &ret) {
    ret.Set(String::New(Env(), "type"), String::New(Env(), result.type));
    ret.Set(String::New(Env(), "domain"), String::New(Env(), result.domain));
    ret.Set(String::New(Env(), "code"), Number::New(Env(), result.code));
    Array results = Array::New(Env());
    for (int i = 0; i < result.results.size(); i++) {
        results.Set(i, String::New(Env(), result.results[i]));
    }
    ret.Set(String::New(Env(), "results"), results);
}

void NodeAddon::LinkedInProfileToJS(const a8::LinkedInProfile &profile, Napi::Object &ret) {
    ret.Set(String::New(Env(), "id"), Number::New(Env(), profile.id));
    ret.Set(String::New(Env(), "code"), Number::New(Env(), profile.code));
    ret.Set(String::New(Env(), "version"), Number::New(Env(), profile.version));
    ret.Set(String::New(Env(), "source"), Number::New(Env(), profile.source));
    ret.Set(String::New(Env(), "email"), String::New(Env(), profile.email));
    ret.Set(String::New(Env(), "name"), String::New(Env(), profile.name));
    ret.Set(String::New(Env(), "title"), String::New(Env(), profile.title));
    ret.Set(String::New(Env(), "linkedin"), String::New(Env(), profile.linkedin));
    ret.Set(String::New(Env(), "updateTime"), Number::New(Env(), profile.updateTime));
}

void NodeAddon::CheckEmail() {
    PhishingChecker phishingChecker;
    phishingChecker.CheckEmail(this->input_EmailInfo, this->input_ExtraInfo, this->output_CheckResult);
}

void NodeAddon::CheckHeader() {
    PhishingChecker phishingChecker;
    printf("Checking headers\n");
    const auto interMediateResult = phishingChecker.CheckHeader(this->input_Headers);
    printf("Simplifying result\n");
    this->output_simpleCheckResult = phishingChecker.CheckResultSimplify(interMediateResult, this->input_ExtraInfo);
}

void NodeAddon::FetchLinkedInProfile() {
    LinkedInSpider linkedIn;
    printf("Fetching LinkedInProfile\n");
    this->output_LinkedInProfile = linkedIn.FetchLinkedInProfile(this->input_LinkedInQueryParam);
    printf("LinkedInProfile fetched\n");
}

void NodeAddon::SpamCheck(const Napi::AsyncProgressQueueWorker<a8::OnlineResult>::ExecutionProgress &progress) {
    PhishingChecker checker;
    auto cb = std::make_shared<NodeCheckCB>(progress);
    int retries = 0;
    checker.CheckAsync(this->input_emailAddress, this->input_ReplyTo, cb);
    this->spamCheckInCBCount = 0;
    printf("Entering spamCheck loop, max wait %i\n", this->max_wait_seconds);
    while (this->spamCheckInCBCount < this->totalSpamChecks && (retries < this->max_wait_seconds)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        retries++;
    }
    if (retries >= this->max_wait_seconds) {
        SetError("Max wait periods exceeded.");
    }
    this->spamCheckInCBCount = 0;
    printf("SpamCheck loop exited\n");
}

void NodeAddon::Execute(const ExecutionProgress &progress) {
    if (this->command == NODE_HEADER_CHECK) {
        printf("Executing CheckHeader\n");
        CheckHeader();
    } else if (this->command == NODE_EMAIL_CHECK) {
        printf("Executing CheckEmail\n");
        CheckEmail();
    } else if (this->command == NODE_SPAM_CHECK) {
        printf("Executing SpamCheck\n");
        SpamCheck(progress);
    } else if (this->command == NODE_LINKED_PROFILE_FETCH) {
        printf("Executing FetchLinkedInProfile\n");
        FetchLinkedInProfile();
    }
    printf("Execute done\n");
}

void NodeAddon::OnOK() {
    HandleScope scope(Env());
    if (this->command == NODE_EMAIL_CHECK) {
        printf("Results returned for Email Check\n");
        Object result = Object::New(Env());
        CheckResultToJS(this->output_CheckResult, result);
        printf("Sending data to JS for Email CHeck\n");
        Callback().Call({result});
    } else if (this->command == NODE_HEADER_CHECK) {
        printf("Header Check result %i\n", this->output_simpleCheckResult);
        Callback().Call({Number::New(Env(), this->output_simpleCheckResult)});
    } else if (this->command == NODE_SPAM_CHECK) {
        printf("SpamCheck complete\n");
        Callback().Call({Env().Null()});
    } else if (this->command == NODE_LINKED_PROFILE_FETCH) {
        printf("Fetch LinkedinProfile complete\n");
        Object result = Object::New(Env());
        LinkedInProfileToJS(this->output_LinkedInProfile, result);
        Callback().Call({result});
    }
}

void NodeAddon::OnError(const Error &error) {
    printf("On Error\n");
    HandleScope scope(Env());
    if (!this->errorCallback.IsEmpty()) {
        // Call our onErrorCallback in javascript with the error message
        this->errorCallback.Call(Receiver().Value(), {String::New(Env(), error.Message())});
    }
}

void NodeAddon::OnProgress(const a8::OnlineResult *onlineResult, size_t count) {
    HandleScope scope(Env());
    if(onlineResult == nullptr || this->command !=NODE_SPAM_CHECK){
        return;
    }
    this->spamCheckInCBCount++;
    if (!this->progressCallback.IsEmpty()) {
        Object ret = Object::New(Env());
        ret.Set(String::New(Env(), "currentCBCount"), Number::New(Env(), this->spamCheckInCBCount));
        ret.Set(String::New(Env(), "total"), Number::New(Env(), this->totalSpamChecks));
        OnlineResultToJS(*onlineResult, ret);
        this->progressCallback.Call(Receiver().Value(), {ret});
    }
    if (this->spamCheckInCBCount >= this->totalSpamChecks) {
        printf("Spam check progress indicates finished\n");
    }

}