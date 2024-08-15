#ifndef GENERATENUMBERS_H
#define GENERATENUMBERS_H

float** createDeterministicFloat4x4(){
    float** testdata = new float*[4];
    for (int i = 0; i < 4; ++i) {
        testdata[i] = new float[4];
    }

    testdata[0][0] = -0.9f; testdata[0][1] = -0.5f; testdata[0][2] = 0.0f; testdata[0][3] = 0.2f;
    testdata[1][0] = 0.4f;  testdata[1][1] = -0.3f; testdata[1][2] = 0.7f; testdata[1][3] = -0.8f;
    testdata[2][0] = 0.6f;  testdata[2][1] = -0.1f; testdata[2][2] = -0.7f; testdata[2][3] = 0.9f;
    testdata[3][0] = -0.2f; testdata[3][1] = 0.8f;  testdata[3][2] = -0.4f; testdata[3][3] = 0.1f;
    return testdata;
}

float** createDeterministicFloat4x3(){
    float** testdata = new float*[4];
    for (int i = 0; i < 4; ++i) {
        testdata[i] = new float[3];
    }

    testdata[0][0] = -0.9f; testdata[0][1] = -0.5f; testdata[0][2] = 0.0f;
    testdata[1][0] = 0.4f;  testdata[1][1] = -0.3f; testdata[1][2] = 0.7f;
    testdata[2][0] = 0.6f;  testdata[2][1] = -0.1f; testdata[2][2] = -0.7f;
    testdata[3][0] = -0.2f; testdata[3][1] = 0.8f;  testdata[3][2] = -0.4f;

    return testdata;
}

float** createDeterministicFloat3x4(){
    float** testdata = new float*[4];
    for (int i = 0; i < 4; ++i) {
        testdata[i] = new float[3];
    }

    testdata[0][0] = -0.9f; testdata[0][1] = -0.5f; testdata[0][2] = 0.0f; testdata[0][3] = 0.2f;
    testdata[1][0] = 0.4f;  testdata[1][1] = -0.3f; testdata[1][2] = 0.7f; testdata[1][3] = -0.8f;
    testdata[2][0] = 0.6f;  testdata[2][1] = -0.1f; testdata[2][2] = -0.7f; testdata[2][3] = 0.9f;
    return testdata;
}

#endif