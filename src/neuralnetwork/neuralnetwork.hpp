#pragma once

// Activations
#include "activation/baseactivation.hpp"
#include "activation/leakyreluactivation.hpp"
#include "activation/linearactivation.hpp"
#include "activation/preluactivation.hpp"
#include "activation/reluactivation.hpp"
#include "activation/sigmoidactivation.hpp"
#include "activation/softmaxactivation.hpp"
#include "activation/stepactivation.hpp"

// Layer
#include "layer/layerlite.hpp"

// Losses
#include "loss/baseloss.hpp"
#include "loss/bceloss.hpp"
#include "loss/cceloss.hpp"
#include "loss/mseloss.hpp"
#include "loss/maeloss.hpp"

// Optimizers
#include "optimizer/baseoptimizer.hpp"
#include "optimizer/randomoptimizer.hpp"
#include "optimizer/sgdoptimizer.hpp"

// Managers
#include "statemanager/netmanager.hpp"
#include "statemanager/linkedmanager.hpp"

// Test Data
#include "testdata/dataset.hpp"
#include "testdata/generatedata.hpp"
#include "testdata/generatenumbers.hpp"
#include "testdata/viewer.hpp"

// Utilities
#include "utilities/matrixutility.hpp"
#include "utilities/networkutility.hpp"
#include "utilities/vectorutility.hpp"