#include "Adafruit_VL53L0X.h"

float senal = 0;
float senalANT = 0;
float alfa = 0.25;
float EMA = 0;  

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);


  while (! Serial) {
    delay(1);
  }
  
  Serial.println("----- VL53L0X -----");
  if (!lox.begin()) {
    Serial.println(F("error de inicializacion"));
    while(1);
  }
  
  Serial.println(F("VL53L0X ejemplo rango\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Leyendo distancia ... ");
  lox.rangingTest(&measure, false); 

  if (measure.RangeStatus != 4) {  
    senalANT = senal;
    senal = measure.RangeMilliMeter;
    
    EMA = filtroEMA(measure.RangeMilliMeter, alfa, senalANT);
    Serial.print("Distancia  (mm): "); Serial.println(EMA);
  } else {
    Serial.println(" fuera de rango ");
  }
    
  delay(100);
}

float filtroEMA(float senal, float alfa, float senalANT){
  EMA = alfa*senal + (1 - alfa)*senalANT;
  return EMA;
}
