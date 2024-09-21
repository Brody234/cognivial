#include <napi.h>
#include <iostream>

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

NODE_API_MODULE(cogninet, Init)



//Activations
#include <iostream>

#include "../src/neuralnetwork/activation/baseactivation.hpp"
#include "../src/neuralnetwork/activation/leakyreluactivation.hpp"
#include "../src/neuralnetwork/activation/linearactivation.hpp"
#include "../src/neuralnetwork/activation/preluactivation.hpp"
#include "../src/neuralnetwork/activation/reluactivation.hpp"
#include "../src/neuralnetwork/activation/sigmoidactivation.hpp"
#include "../src/neuralnetwork/activation/softmaxactivation.hpp"
#include "../src/neuralnetwork/activation/stepactivation.hpp"

//Layer
#include "../src/neuralnetwork/layer/layerlite.hpp"

//Loss
#include "../src/neuralnetwork/loss/baseloss.hpp"
#include "../src/neuralnetwork/loss/bceloss.hpp"
#include "../src/neuralnetwork/loss/cceloss.hpp"
#include "../src/neuralnetwork/loss/mseloss.hpp"
#include "../src/neuralnetwork/loss/maeloss.hpp"

//Optimizers
#include "../src/neuralnetwork/optimizer/baseoptimizer.hpp"
#include "../src/neuralnetwork/optimizer/randomoptimizer.hpp"
#include "../src/neuralnetwork/optimizer/sgdoptimizer.hpp"

//Managers
#include "../src/neuralnetwork/statemanager/netmanager.hpp"
#include "../src/neuralnetwork/statemanager/linkedmanager.hpp"

//Test Data
#include "../src/neuralnetwork/testdata/dataset.hpp"
#include "../src/neuralnetwork/testdata/generatedata.hpp"
#include "../src/neuralnetwork/testdata/generatenumbers.hpp"
#include "../src/neuralnetwork/testdata/viewer.hpp"

//Utilities
#include "../src/neuralnetwork/utilities/matrixutility.hpp"
#include "../src/neuralnetwork/utilities/networkutility.hpp"
#include "../src/neuralnetwork/utilities/vectorutility.hpp"

// Simple function that adds 1 + 1