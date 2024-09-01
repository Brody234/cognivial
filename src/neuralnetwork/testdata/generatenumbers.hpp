#ifndef GENERATENUMBERS_H
#define GENERATENUMBERS_H

template <typename NumType = float>
NumType** createDeterministicArray4x4(){
    NumType** testdata = new NumType*[4];
    for (int i = 0; i < 4; ++i) {
        testdata[i] = new NumType[4];
    }

    testdata[0][0] = -0.9f; testdata[0][1] = -0.5f; testdata[0][2] = 0.0f; testdata[0][3] = 0.2f;
    testdata[1][0] = 0.4f;  testdata[1][1] = -0.3f; testdata[1][2] = 0.7f; testdata[1][3] = -0.8f;
    testdata[2][0] = 0.6f;  testdata[2][1] = -0.1f; testdata[2][2] = -0.7f; testdata[2][3] = 0.9f;
    testdata[3][0] = -0.2f; testdata[3][1] = 0.8f;  testdata[3][2] = -0.4f; testdata[3][3] = 0.1f;
    return testdata;
}

template <typename NumType = float>
NumType** createDeterministicArray4x3(){
    NumType** testdata = new NumType*[4];
    for (int i = 0; i < 4; ++i) {
        testdata[i] = new NumType[3];
    }

    testdata[0][0] = -0.9f; testdata[0][1] = -0.5f; testdata[0][2] = 0.0f;
    testdata[1][0] = 0.4f;  testdata[1][1] = -0.3f; testdata[1][2] = 0.7f;
    testdata[2][0] = 0.6f;  testdata[2][1] = -0.1f; testdata[2][2] = -0.7f;
    testdata[3][0] = -0.2f; testdata[3][1] = 0.8f;  testdata[3][2] = -0.4f;

    return testdata;
}

template <typename NumType = float>
NumType** createDeterministicArray3x4(){
    NumType** testdata = new NumType*[4];
    for (int i = 0; i < 4; ++i) {
        testdata[i] = new NumType[3];
    }

    testdata[0][0] = -0.9f; testdata[0][1] = -0.5f; testdata[0][2] = 0.0f; testdata[0][3] = 0.2f;
    testdata[1][0] = 0.4f;  testdata[1][1] = -0.3f; testdata[1][2] = 0.7f; testdata[1][3] = -0.8f;
    testdata[2][0] = 0.6f;  testdata[2][1] = -0.1f; testdata[2][2] = -0.7f; testdata[2][3] = 0.9f;
    return testdata;
}

#endif