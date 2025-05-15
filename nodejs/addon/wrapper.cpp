#include <napi.h>
#include <iostream>

#include "../../src/neuralnetwork/neuralnetwork.hpp"

Napi::Number Add(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::cout << "Inside Add function" << std::endl;

    int result = 1 + 1;
    return Napi::Number::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("add", Napi::Function::New(env, Add));
    return exports;
}


