volatile int NumPulsos,NumPulsos2; //variable para la cantidad de pulsos recibidos
int PinSensor = 2;
int PinSensor2 = 3;//Sensor conectado en el pin 2
float factor_conversion=65; //para convertir de frecuencia a caudal


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(PinSensor, INPUT); 
  attachInterrupt(0,ContarPulsos,RISING);
  pinMode(PinSensor2, INPUT); 
  attachInterrupt(1,ContarPulsos2,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
float frecuencia=ObtenerFrecuencia(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  float caudal_L_h=caudal_L_m*60; //calculamos el caudal en L/h
/*float frecuencia2=ObtenerFrecuencia2(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m2=frecuencia2/factor_conversion; //calculamos el caudal en L/m
  float caudal_L_h2=caudal_L_m2*60;*/
  //-----Enviamos por el puerto serie---------------
  Serial.print ("FrecuenciaPulsos: "); 
  Serial.print (frecuencia,0); 
  Serial.print ("Hz\tCaudal: "); 
  Serial.print (caudal_L_m,3); 
  Serial.print (" L/m\t"); 
   Serial.print (caudal_L_h,3); 
  Serial.println ("L/h");
  /*  Serial.print ("FrecuenciaPulsos 2: "); 
  Serial.print (frecuencia2,0); 
  Serial.print ("Hz\tCaudal 2 : "); 
  Serial.print (caudal_L_m2,3); 
  Serial.print (" L/m\t 2"); 
   Serial.print (caudal_L_h2,3); 
  Serial.println ("L/h 2");  */
}

int ObtenerFrecuencia() 
{
  int frecuencia;
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  frecuencia=NumPulsos; //Hz(pulsos por segundo)
  return frecuencia;
}
int ObtenerFrecuencia2() 
{
  int frecuencia2;
  NumPulsos2 = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  frecuencia2=NumPulsos2; //Hz(pulsos por segundo)
  return frecuencia2;
}

//---Función que se ejecuta en interrupción---------------
void ContarPulsos ()
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
} 
void ContarPulsos2 ()
{ 
  NumPulsos2++;  //incrementamos la variable de pulsos
} 
