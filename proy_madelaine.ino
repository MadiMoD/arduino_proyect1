#include <SoftwareSerial.h>
#include <Servo.h>

  int dirmotor1=11; //motores
  int cambio1=9;
  int dirmotor2=10;
  int cambio2=6;
  
  int duracion,distancia;   //sensor ultrasonido
  const int EchoPin = 7;
  const int TriggerPin = 8;
  
  
Servo myservo;
//SoftwareSerial bluethoo(2,3);
SoftwareSerial bluethoo(0,1);
void giraizquierda()
{
   
  digitalWrite(dirmotor1,LOW);
  digitalWrite(cambio1,HIGH);
  digitalWrite(dirmotor2,HIGH);
  digitalWrite(cambio2,LOW);
    
}

void giraderecha()
{
  
  digitalWrite(dirmotor1,LOW);
  digitalWrite(cambio1,HIGH);
  digitalWrite(dirmotor2,HIGH);
  digitalWrite(cambio2,LOW);

}
void adelante()
{
    
  digitalWrite(dirmotor1,HIGH);
  digitalWrite(dirmotor2,HIGH);
  digitalWrite(cambio1,HIGH);
  digitalWrite(cambio2,HIGH);
  
}

void retrocede()
{
  //Serial.println("RETROCEDE1");
  digitalWrite(dirmotor1,HIGH); 
  digitalWrite(cambio1,LOW);
  //Serial.println("RETROCEDE2");
  digitalWrite(dirmotor2,HIGH); 
  digitalWrite(cambio2,LOW);
  //delay(500);
}

void parar()
{
  digitalWrite(dirmotor1,LOW);
  digitalWrite(dirmotor2,LOW);
  digitalWrite(cambio1,LOW);
  digitalWrite(cambio2,LOW);
}


int ping(int TriggerPin, int EchoPin) 
{
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH)
   ;  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

int ping1(int TriggerPin1, int EchoPin1) 
{
   long duration, distanceCm;
   
   digitalWrite(TriggerPin1, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin1, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin1, LOW);
   
   duration = pulseIn(EchoPin1, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

void setup() 
{
  // put your setup code here, to run once:
  pinMode(dirmotor1,OUTPUT);
  pinMode(dirmotor2,OUTPUT);
  pinMode(cambio1,OUTPUT);
  pinMode(cambio2,OUTPUT);
   
  Serial.begin(9600);
  //bluethoo.begin(9600);

  //  pinMode(LedPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
 
  myservo.attach(5);

}

void servo2()
{
  for (int pos = 0; pos <= 180; pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (int pos = 180; pos >= 0; pos -= 1) 
  { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
  
  


void loop()
{
 /*
  digitalWrite(TriggerPin,HIGH);
            delay(0.01);
             digitalWrite(TriggerPin, LOW);
     
     duracion = pulseIn(EchoPin, HIGH);          // Lee el tiempo del Echo
     distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
     delay(10); 
     
     if (distancia <= 15 && distancia >=2){
        parar();
        delay (200);
        retrocede();
        delay(500); 
        }
     else{                             // Si no hay obstaculos se desplaza al frente  
         adelante();
     }*/
   int cm = ping(TriggerPin, EchoPin);
    Serial.println(cm);
    servo2();
    
    while (cm<30)
    {
      
        parar();
        retrocede();
       
      break;
    }  


    if (bluethoo.available()>0)
    {
      Serial.println("LOCK");    
    char op= bluethoo.read();
  
    switch (op)
    {
      case 'A':
                adelante();
                Serial.println(op);
                break;
                
      case 'B':
                retrocede();
                Serial.println(op);
                break;          
      case 'C':
                giraderecha();
                Serial.println(op);
                break;
      case 'D': 
                giraizquierda();
                Serial.println(op);
                break;

      case 'F':
            parar();
            Serial.println(op);
            break;

       case 'G':
            digitalWrite(TriggerPin,HIGH);
            delay(0.01);
             digitalWrite(TriggerPin, LOW);
     
     duracion = pulseIn(EchoPin, HIGH);          // Lee el tiempo del Echo
     distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
     delay(10); 
     
     if (distancia <= 15 && distancia >=2){    // si la distancia es menor de 15cm
        
        /*digitalWrite(dirmotor1, LOW);             // Parar los motores por 200 mili segundos
        digitalWrite(dirmotor2, LOW); 
        digitalWrite(cambio1, LOW);    
        digitalWrite(cambio2, LOW); 
        delay (200);*/
        parar;
        delay (200);
        
        /*analogWrite(dirmotor1, HIGH);          // Reversa durante 500 mili segundos
        analogWrite(dirmotor2, HIGH); */
        retrocede();
        delay(500);           
        
        /*analogWrite(derB, 0);            // Girar durante 600 milisegundos   
        analogWrite(izqB, 0); 
        analogWrite(derA, 0);  
        analogWrite(izqA, vel);  
        delay(600);
        
     }
     else{                             // Si no hay obstaculos se desplaza al frente  
         adelante();
     }*/
      default:
                parar();
                break;
    }
   }
    }
   //adelante();
    //delay (1000);
}
