#include <vector>
#include <cmath>
#include <assert.h>

float relU(float x) {
    return x > 0 ? x : 0;
}

float relUDeriv(float x) {
    return x > 0 ? 1 : 0;
}

float leakyRelU(float x, float a = 0.01) {
    return  x > 0 ? x : a * x;
}

float leakyRelUDeriv(float x, float a = 0.01) {
    return x > 0 ? 1 : a;
}

float meanSquaredError(const std::vector<float> &output, const std::vector<float> &actual) {
    assert(output.size() == actual.size());
    float loss = 0;
    for (size_t i = 0; i < output.size(); ++i) {
        loss += pow(output[i] - actual[i], 2);
    }
    loss /= output.size();
    return loss;
}



std::vector<float> softMax(const std::vector<float> &input) {
    std::vector<float> v;
    float sum = 0;
    for (const float &i : input) {
        v.push_back(exp(i));
        sum += v.back();
    }
    for (float &i : v) {
        i /= sum;
    }
    return v;
}

std::vector<std::vector<float>> softMaxDeriv(const std::vector<float> &input) {
    size_t n = input.size();
    std::vector<std::vector<float>> jMatrix(n, std::vector<float>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                jMatrix[i][j] = input[i] * (1 - input[i]);
            } else {
                jMatrix[i][j] = -input[i] * input[j];
            }
        }
    }
    return jMatrix;
}