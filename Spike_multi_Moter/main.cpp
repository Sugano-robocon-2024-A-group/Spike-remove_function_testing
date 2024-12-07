#include <Arduino.h>
#include "spike.h"

constexpr int NUM_MOTORS = 4; // モーターの数
constexpr int THRESHOLD = 50; // スパイク除去の閾値

int encoderSamples[NUM_MOTORS][NUM_SAMPLES] = {}; // 各モーターのエンコーダ値配列
int sampleIndices[NUM_MOTORS] = {}; // 各モーターのサンプルインデックス

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Spike removal test for 4 motors");
}

void loop() {
    for (int motor = 0; motor < NUM_MOTORS; motor++) {
        int encoderValue = analogRead(motor); // モーターごとに仮のエンコーダ値を取得
        int filteredValue = removeSpike(encoderValue, encoderSamples[motor], sampleIndices[motor], THRESHOLD);

        Serial.print("Motor ");
        Serial.print(motor);
        Serial.print(": Original = ");
        Serial.print(encoderValue);
        Serial.print(", Filtered = ");
        Serial.println(filteredValue);
    }

    delay(100); // デモ用に少し待機
}
