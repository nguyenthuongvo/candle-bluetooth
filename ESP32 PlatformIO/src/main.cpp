/*Program to use GATT service on ESP32 to send Battery Level
 * ESP32 works as server - Mobile as client
 * Program by: B.Aswinth Raj
 * Dated on: 13-10-2018
 * Website: www.circuitdigest.com
 */

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h> //Library to use BLE as server
#include <BLE2902.h> 

bool _BLEClientConnected = false;

BLEServer* pServer = NULL;

// Optional Services
#define BatteryService BLEUUID((uint16_t)0x180F) 
BLECharacteristic BatteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_READ  | BLECharacteristic::PROPERTY_WRITE  | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));


// CandleService
#define CandleService BLEUUID((uint16_t)0xFF02) 
BLECharacteristic DeviceNameCharacteristic(BLEUUID((uint16_t)0xFFFF), BLECharacteristic::PROPERTY_READ  | BLECharacteristic::PROPERTY_WRITE  | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor DeviceNameDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic ColorCharacteristic(BLEUUID((uint16_t)0xFFFC), BLECharacteristic::PROPERTY_READ  | BLECharacteristic::PROPERTY_WRITE  | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor ColorDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic EffectCharacteristic(BLEUUID((uint16_t)0xFFFB), BLECharacteristic::PROPERTY_READ  | BLECharacteristic::PROPERTY_WRITE  | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor EffectDescriptor(BLEUUID((uint16_t)0x2901));

// End services


class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      _BLEClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      _BLEClientConnected = false;
    }
};

class DeviceNameCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
      std::string value = characteristic->getValue();

      if (value.length() > 0) {
        Serial.print("Device Name: ");

        for (int i = 0; i < value.length(); i++) {
          Serial.print(value[i]);
          if (i < value.length() - 1) Serial.print(",");
        }

        Serial.println("");
      }
    }
};

class ColorCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
      std::string value = characteristic->getValue();

      if (value.length() > 0) {
        Serial.print("Color: ");

        for (int i = 0; i < value.length(); i++) {
          Serial.print((uint8_t)value[i]);
          if (i < value.length() - 1) Serial.print(",");
        }

        Serial.println("");
      }
    }
};

class EffecctCharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
      std::string value = characteristic->getValue();

      if (value.length() > 0) {
        Serial.print("Effect: ");

        for (int i = 0; i < value.length(); i++) {
          Serial.print((uint8_t)value[i]);
          if (i < value.length() - 1) Serial.print(",");
        }

        Serial.println("");
      }
    }
};


void InitBLE() {
  BLEDevice::init("BLE Battery");
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pBatteryService = pServer->createService(BatteryService);
  
  pBatteryService->addCharacteristic(&BatteryLevelCharacteristic);
  BatteryLevelDescriptor.setValue("Percentage 0 - 100");
  BatteryLevelCharacteristic.addDescriptor(&BatteryLevelDescriptor);
  BatteryLevelCharacteristic.addDescriptor(new BLE2902());

  pServer->getAdvertising()->addServiceUUID(BatteryService);
  pBatteryService->start();

  // End the BLE Service



  // Create the BLE Service
  BLEService *pCandleService = pServer->createService(CandleService);

  // Create BLE Characteristics

  // DeviceName
  pCandleService ->addCharacteristic(&DeviceNameCharacteristic);
  DeviceNameDescriptor.setValue("Change device name");
  DeviceNameCharacteristic.addDescriptor(&DeviceNameDescriptor);
  DeviceNameCharacteristic.addDescriptor(new BLE2902());
  DeviceNameCharacteristic.setCallbacks(new DeviceNameCharacteristicCallbacks());
  pServer->getAdvertising()->addServiceUUID(CandleService);

  // Color
  pCandleService ->addCharacteristic(&ColorCharacteristic);
  ColorDescriptor.setValue("Set color bulb");
  ColorCharacteristic.addDescriptor(&ColorDescriptor);
  ColorCharacteristic.addDescriptor(new BLE2902());
  ColorCharacteristic.setCallbacks(new ColorCharacteristicCallbacks());
  pServer->getAdvertising()->addServiceUUID(CandleService);

  // Effect
  pCandleService ->addCharacteristic(&EffectCharacteristic);
  EffectDescriptor.setValue("Set effect bulb");
  EffectCharacteristic.addDescriptor(&EffectDescriptor);
  EffectCharacteristic.addDescriptor(new BLE2902());
  EffectCharacteristic.setCallbacks(new EffecctCharacteristicCallbacks());
  pServer->getAdvertising()->addServiceUUID(CandleService);

  //
  pCandleService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  _BLEClientConnected = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Battery Level Indicator - BLE");
  InitBLE();
}


uint8_t level = 57;
  
void loop() {

    delay(1000);
    if (_BLEClientConnected == false) {
      Serial.println("ESP32 start adverising....");
      pServer->getAdvertising()->start();
    }
    

}