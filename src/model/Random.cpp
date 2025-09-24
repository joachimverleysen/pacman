//
// Created by joachimverleysen on 1/4/25.
//
#include <exception>
#include <iostream>
#include <stdexcept>
#include "Random.h"

bool Random::decide(float chance) {
    if (chance < 0.0f || chance > 1.0f) {
        throw std::invalid_argument("Chance must be between 0 and 1");
    }
    float random_value = getFloat(0, 1);
    return random_value <= chance;
}

int Random::makeWeightedDecision(const std::vector<float>& weights) {
    if (weights.empty()) {
        throw std::invalid_argument("Weight list can't be empty.");
    }

    float totalWeight = 0.0f;
    for (float weight : weights) {
        if (weight < 0) {
            throw std::invalid_argument("Weights must be positive.");
        }
        totalWeight += weight;
    }


    float randomValue = getFloat(0, totalWeight);

    for (size_t i = 0; i < weights.size(); ++i) {
        randomValue -= weights[i];
        if (randomValue <= 0) {
            return i;   // Return index corresponding to weight in vector
        }
    }

    throw std::runtime_error("No selection made, check input parameters.");

}

float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    auto val = distribution(generator);
    if (std::isnan(val)) {
        std::cerr << "invalid random num" << std::endl;
        // throw std::logic_error("invalid random num");
		}

    return distribution(generator);
}
