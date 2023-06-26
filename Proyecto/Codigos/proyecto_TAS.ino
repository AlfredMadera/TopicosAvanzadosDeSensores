#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <Adafruit_MPL3115A2.h>
#include <LiquidCrystal.h>

Adafruit_VL53L0X lidar = Adafruit_VL53L0X();
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
const int rs = 12, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float senal = 0;
float senalANT = 0;
float alfa = 0.25;
float EMA = 0;  

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  delay(500);

  Serial.println("MPL3115A2");
  if (!baro.begin()) {
    Serial.println("error de inicialización");
    return;
  }

  Serial.println("VL53L0X");
  if (!lidar.begin(0x30)) {
    Serial.println(F("error de inicialización"));
    while(1);
  }

  baro.setSeaPressure(1013.26);
}

void loop(){
  readLidar();
  readTemp();
}
void readLidar(){
  VL53L0X_RangingMeasurementData_t measure;  
  lidar.rangingTest(&measure, false); 
  lcd.setCursor(0, 0);
  if (measure.RangeStatus != 4) {  
    senalANT = senal;
    senal = measure.RangeMilliMeter;
    EMA = filtroEMA(senal, alfa, senalANT);
    //Serial.println("-----------------");
    lcd.print("Dist: "); lcd.print(EMA); lcd.print(" mm");
  } else {
    //Serial.println("-----------------");
    lcd.println("Fuera de rango");
  }
  delay(100);
}

void readTemp(){
  float temperature = baro.getTemperature();
  //Serial.println("-----------------");
  lcd.setCursor(0, 1);
  lcd.print("Temp: "); lcd.print(temperature); lcd.println(" C");
  delay(100);
}

float filtroEMA(float senal, float alfa, float senalANT){
  EMA = alfa*senal + (1 - alfa)*senalANT;
  return EMA;
}

/*
#include <Wire.h>
#include <VL53L0X.h>
#define VL53L0X_I2C_ADDR 0x29 
#define MPL3115A2_I2C_ADDR 0x60

#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro;

VL53L0X lidar;

void setup() {
  Serial.begin(9600);
  while (! Serial) delay(1); 
  Wire.begin();
}



void loop() {
  readLidar();

}

int readLidar(int address){
  Wire.beginTransmission(VL53L0X_I2C_ADDR);
  lidar.init();
  lidar.setTimeout(500);
  lidar.startContinuous(); 
  int distance = lidar.readRangeContinuousMillimeters();
  Serial.println(distance);
  Wire.endTransmission(VL53L0X_I2C_ADDR);
  Wire.flush();
}

void readTemp(){

}
*/