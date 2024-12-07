#include <Arduino.h>
#include <CAN.h>

// setupReceiver関数: 受信の初期設定
void setupReceiver() {
  // 受信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Receiver Initialized");
}

// setupSender関数: 送信の初期設定
void setupSender() {
  // 送信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Sender Initialized");
}

// sendPacket関数: CANメッセージを送信する
/*
void sendPacket(int PS4_Circle) {
  // 通常パケットの送信
  Serial.print("Sending packet ... ");
  
  // CANパケットを送信。ID: 0x12
  CAN.beginPacket(0x12);
  Serial.print("Sending 1 ");
  CAN.write(static_cast<uint8_t>(PS4_Circle));
  CAN.endPacket();  // 送信終了
  
  Serial.println("done");

}*/

// receivePacket関数: CANメッセージを受信し、内容を表示する
void receivePacket(uint32_t &id, int16_t *data, uint16_t &length) 
//void receivePacket(uint32_t id, int16_t *data, uint16_t &length, volatile int encoderCount)
{
  delay(10); 
  int packetSize = CAN.parsePacket();  // 受信したパケットのサイズを取得

  if (packetSize>0) {  // パケットが受信された場合
    Serial.print("Received \n");

  /*  for (int i = 0; i < length; i++) {
      //data[i] = (int)CAN.read();uint16_t
      //data[i] = (uint16_t)CAN.read();
 uint8_t byte = CAN.read();  // 1 バイト読み取る
  data[i] = static_cast<uint16_t>(byte);  
  data[i] = CAN.read();  // 1バイトずつデータをそのまま格納*/

  for (int i = 0; i < 4; i++) {
      // 3バイトずつ受け取ってuint16_tに変換
      //uint8_t link = CAN.read();
      int8_t highByte = CAN.read();  // 上位バイト
      //Serial.print(highByte);
      int8_t lowByte = CAN.read();   // 下位バイト
      //Serial.print(lowByte);

      // 受け取った2バイトを結合してuint16_tにする
      data[i] = static_cast<uint16_t>(highByte << 8 | lowByte);
      /*if(link>2){
        data[i]=-data[i];
        }*/

      // int16_tに符号をつける
      //int16_t signedData = static_cast<int16_t>(data[i]);

      // デバッグ用に受信した値を表示
      Serial.print("Data[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(data[i]);
    }

    //data[3] = 1; 

    /*// 拡張パケットの場合
    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    // RTRパケットの場合
    if (CAN.packetRtr()) {
      Serial.print("RTR ");
    }*/

    // パケットIDを表示
    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    // RTRパケットの場合、要求された長さを表示
    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      // 通常パケットの場合、受信データの長さを表示
      Serial.print(" and length ");
      Serial.println(packetSize);

      // データをシリアルに表示
      while (CAN.available()) {
        Serial.print((uint16_t)CAN.read());//⇒こいつで100って出てる。

    id = CAN.packetId();        // CAN IDを取得
    length = CAN.packetDlc();   // データ長を取得

    //Serial.println();
    

        
      //}
      //Serial.println();
    }
    //Serial.println();
  }
}
}

/*#include <Arduino.h>
#include <CAN.h>
#include "tuushin.h"

// setupReceiver関数: 受信の初期設定
void setupReceiver() {
  // 受信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Receiver Initialized");
}

// setupSender関数: 送信の初期設定
void setupSender() {
  // 送信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Sender Initialized");
}

// sendPacket関数: CANメッセージを送信する
/*void sendPacket(int PS4_Circle, int PS4_Triangle, int PS4_R1, int PS4_L1) {
  // 通常パケットの送信
  Serial.print("Sending packet ... ");
  
  // CANパケットを送信。ID: 0x12
  CAN.beginPacket(0x12);
  Serial.print("Sending");
  CAN.write(static_cast<uint8_t>(PS4_Circle));
  Serial.print("Sending 2");
  CAN.write(static_cast<uint8_t>(PS4_Triangle));
  Serial.print("Sending 3 ");
  CAN.write(static_cast<uint8_t>(PS4_R1));
  Serial.print("Sending 4 ");
  CAN.write(static_cast<uint8_t>(PS4_L1));
  CAN.endPacket();  // 送信終了

  //Serial.print(PS4_Circle);
  
  Serial.println("done");
}*/


// receivePacket関数: CANメッセージを受信し、内容を表示する
void receivePacket() {
  int packetSize = CAN.parsePacket();  // 受信したパケットのサイズを取得

  if (packetSize) {  // パケットが受信された場合
  
    Serial.print("Received ");

    // 拡張パケットの場合
    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    // RTRパケットの場合
    if (CAN.packetRtr()) {
      Serial.print("RTR ");
    }

    // パケットIDを表示
    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    // RTRパケットの場合、要求された長さを表示
    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      // 通常パケットの場合、受信データの長さを表示
      Serial.print(" and length ");
      Serial.println(packetSize);

      // データをシリアルに表示
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }
    Serial.println();
  }
}
