#ifndef SPIKE_H
#define SPIKE_H

#include <Arduino.h>

constexpr int NUM_SAMPLES = 10; // 過去のサンプル数

// 関数プロトタイプ
float calculateMedian(int values[], int size);
int removeSpike(int newValue, int samples[], int& sampleIndex, int threshold);

#endif // SPIKE_HPP
