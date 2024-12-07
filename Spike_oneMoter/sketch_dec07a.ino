#include <Arduino.h>

#define NUM_SAMPLES 10

//実装するときは、新しくファイル作る他ないね。　calculateMedian(samples, NUM_SAMPLES);
//　　　　　　　　　　　　　　　　　　　　　　removeSpike(encoderValue, encoderSamples, threshold);
//それで　samples　ん？Samples？配列読むの？

// Function to calculate the median of an array
int calculateMedian(int *values, size_t size) {
    int sortedValues[size];
    memcpy(sortedValues, values, size * sizeof(int));
    std::sort(sortedValues, sortedValues + size);
    if (size % 2 == 0) {
        return (sortedValues[size / 2 - 1] + sortedValues[size / 2]) / 2;
    } else {
        return sortedValues[size / 2];
    }
}

// Function to remove spikes from the encoder values
int removeSpike(int newValue, int *samples, int threshold) {
    static int sampleIndex = 0;
    
    // Add new value to the samples array
    samples[sampleIndex] = newValue;
    sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;

    // Calculate the median
    int median = calculateMedian(samples, NUM_SAMPLES);

    // Replace value if it deviates significantly from the median
    if (abs(newValue - median) > threshold) {
        return median;
    } else {
        return newValue;
    }
}

void setup() {
    Serial.begin(115200);
    
    int encoderSamples[NUM_SAMPLES] = {0}; // Array to store the last NUM_SAMPLES encoder values
    int threshold = 50; // Example threshold for spike detection
    
    // 入力ループのシミュレーション
    for (int i = 0; i < 20; i++) {
        int encoderValue = random(100, 500); // Simulate encoder value
        if (i == 10) {
            encoderValue = 2000; // Simulate a spike
        }

        int filteredValue = removeSpike(encoderValue, encoderSamples, threshold);
//過去10個のエンコーダ値を保存し、その中央値を計算します。新しい値がその中央値から一定の閾値を超える場合は、中央値に置き換えることでスパイクを除去します。
// NUM_SAMPLESと thresholdは用途に応じて調整可能

        Serial.print("Raw: ");
        Serial.print(encoderValue);
        Serial.print(" Filtered: ");
        Serial.println(filteredValue);

        delay(200);
    }
}

void loop() {
    // 連続運転のための実装はこちら
}
