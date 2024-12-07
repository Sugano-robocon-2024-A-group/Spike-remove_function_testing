#include "spike.h"

// 中央値を計算する関数
float calculateMedian(int values[], int size) {
    int sortedValues[size];
    memcpy(sortedValues, values, size * sizeof(int));
    std::sort(sortedValues, sortedValues + size);

    if (size % 2 == 0) {
        return (sortedValues[size / 2 - 1] + sortedValues[size / 2]) / 2.0;
    } else {
        return sortedValues[size / 2];
    }
}

// スパイク除去関数
int removeSpike(int newValue, int samples[], int& sampleIndex, int threshold) {
    samples[sampleIndex] = newValue;
    sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;

    float median = calculateMedian(samples, NUM_SAMPLES);
    if (abs(newValue - median) > threshold) {
        return static_cast<int>(median); // スパイクを中央値に置換
    }
    return newValue; // スパイクでない場合はそのまま
}
