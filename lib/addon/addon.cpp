//
// Created by weicheng qian on 2020/4/23.
//

#include "addon.hpp"
#include "node_addon.h"
#include <a8/a8.h>
#include <napi.h>

using namespace Napi;
using namespace a8;
using namespace std;

// Exposed nodejs methods
Value CheckHeader(const CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Number of parameters incorrect").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsArray()) {
        Napi::TypeError::New(env, "Parameter 'message_header' must be an array").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[1].IsObject()) {
        Napi::TypeError::New(env, "Parameter 'extraCheckInfo' must be an Object").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    Function onOk = info[2].As<Function>();
    Function onError = info[3].As<Function>();
    Function onProgress = info[4].As<Function>();
    NodeAddon *nodeAddon = new NodeAddon(onOk, onError, onProgress, NODE_HEADER_CHECK, 1);
    nodeAddon->ParseJSHeaders(info[0].As<Array>());
    nodeAddon->ParseJSExtCheckInfo(info[1].As<Object>());
    nodeAddon->Queue();
    return info.Env().Undefined();
}

Value CheckEmail(const CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Number of parameters incorrect").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "Parameter 'emailInfo' must be an array").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[1].IsObject()) {
        Napi::TypeError::New(env, "Parameter 'extraCheckInfo' must be an Object").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    Function onOk = info[2].As<Function>();
    Function onError = info[3].As<Function>();
    Function onProgress = info[4].As<Function>();
    NodeAddon *nodeAddon = new NodeAddon(onOk, onError, onProgress, NODE_EMAIL_CHECK, 1);
    nodeAddon->ParseJSEmailInfo(info[0].As<Object>());
    nodeAddon->ParseJSExtCheckInfo(info[1].As<Object>());
    nodeAddon->Queue();
    return info.Env().Undefined();
}

Value SpamCheck(const CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Number of parameters incorrect").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Parameter 'emailAddress' must be a string").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[1].IsString()) {
        Napi::TypeError::New(env, "Parameter 'replyTo' must be a string").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    String emailAddress = info[0].As<String>();
    String replyTo = info[1].As<String>();
    Function onOk = info[2].As<Function>();
    Function onError = info[3].As<Function>();
    Function onProgress = info[4].As<Function>();
    int max_wait_seconds = 90;
    if(info.Length() == 6 && info[5].IsNumber()){
        max_wait_seconds = info[5].As<Number>();
    }
    NodeAddon *nodeAddon = new NodeAddon(onOk, onError, onProgress, NODE_SPAM_CHECK, max_wait_seconds);
    nodeAddon->ParseJSReplyTo(replyTo);
    nodeAddon->ParseJSEmailAddress(emailAddress);
    nodeAddon->Queue();
    return info.Env().Undefined();
}

Value FetchLinkedInProfile(const CallbackInfo &info){
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Number of parameters incorrect").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsObject()) {
        Napi::TypeError::New(env, "Parameter 'linkedInProfile' must be an object").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    Function onOk = info[1].As<Function>();
    Function onError = info[2].As<Function>();
    Function onProgress = info[3].As<Function>();
    NodeAddon *nodeAddon = new NodeAddon(onOk, onError, onProgress, NODE_LINKED_PROFILE_FETCH, 1);
    nodeAddon->ParseJSLinkedInQueryParam(info[0].As<Object>());
    nodeAddon->Queue();
    return info.Env().Undefined();
}

Value Setup(const CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Number of parameters incorrect").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Parameter 'workingDir' must be a string").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[1].IsBoolean()) {
        Napi::TypeError::New(env, "Parameter 'isProduction' must be a boolean").
                ThrowAsJavaScriptException();
        return env.Null();
    }
    bool isProduction = info[1].As<Boolean>();
    if (isProduction) {
        RXApplication::Init(info[0].As<String>(), EnvProd);
    } else {
        RXApplication::Init(info[0].As<String>(), EnvStag);
    }
    return Number::New(env, 0);
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "setup"), Function::New(env, Setup));
    exports.Set(String::New(env, "checkHeader"), Function::New(env, CheckHeader));
    exports.Set(String::New(env, "checkEmail"), Function::New(env, CheckEmail));
    exports.Set(String::New(env, "spamCheck"), Function::New(env, SpamCheck));
    exports.Set(String::New(env, "fetchLinkedInProfile"), Function::New(env, FetchLinkedInProfile));
    return exports;
}

NODE_API_MODULE(addon, Init)