/*4つのモーターに適応させる*/
/*
#include <Arduino.h>

#define NUM_SAMPLES 10
#define NUM_MOTORS 4

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
int removeSpike(int newValue, int *samples, int threshold, int motorIndex) {
    static int sampleIndices[NUM_MOTORS] = {0};

    // Add new value to the samples array for the specific motor
    samples[sampleIndices[motorIndex]] = newValue;
    sampleIndices[motorIndex] = (sampleIndices[motorIndex] + 1) % NUM_SAMPLES;

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

    int encoderSamples[NUM_MOTORS][NUM_SAMPLES] = {0}; // Arrays to store the last NUM_SAMPLES encoder values for each motor
    int threshold = 50; // Example threshold for spike detection ここで、閾値変更です。（閾値）

    // Simulated input loop
    for (int i = 0; i < 20; i++) {
        for (int motor = 0; motor < NUM_MOTORS; motor++) {
            int encoderValue = random(100, 500); // Simulate encoder value for each motor
            if (i == 10 && motor == 2) {
                encoderValue = 2000; // Simulate a spike for motor 2
            }

            int filteredValue = removeSpike(encoderValue, encoderSamples[motor], threshold, motor);

            Serial.print("Motor ");
            Serial.print(motor);
            Serial.print(" Raw: ");
            Serial.print(encoderValue);
            Serial.print(" Filtered: ");
            Serial.println(filteredValue);
        }
        delay(200);
    }
}

void loop() {
    // Implementation for continuous operation would go here
}
*/
