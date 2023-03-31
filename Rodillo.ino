                                                                                                                                                                                                           /*
 * Micro usado= Arduino nano
 * 
 * Sensor infrarrojo E18-d80nk
 * Antihorario el tornillo par acortar distancia de senso 
   Pin definiciones:
                    Marron-> positivo
                    Negro ---- señal D5
                    Azul-> negativo
                    
 *Encoder Rotativo KY-040
 *PIN SW = D3
 *PIN DT = D2 
 *PIN CLK = D5
 *
 *PANTALLA LCD I2C 16X2
 *PIN SCL = A5
 *PIN SDA = A4
 *
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int A = 2;       
int B = 4;       
int btn = 3;
int sensor = 5;

int ANTERIOR ;    // almacena valor anterior de la variable POSICION
int POSICION ; // variable POSICION con valor inicial de 50 y definida
int tiempo;
 

byte bar1[8] =
{
  B11100,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11100
};
byte bar2[8] =
{
  B00111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B00111
};
byte bar3[8] =
{
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte bar4[8] =
{
  B11110,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11100
};
byte bar5[8] =
{
  B01111,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B00111
};
byte bar6[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte bar7[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00111,
  B01111
};
byte bar8[8] =
{
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

   
            
                        
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
      
  pinMode(A, INPUT);    // A como entrada
  pinMode(B, INPUT);    // B como entrada
  pinMode(btn, INPUT_PULLUP);    // Entrada con resistencia Pullup para el Switch del encoder
  pinMode(sensor, INPUT_PULLUP);    // Entrada con resistencia Pullup para el Switch del encoder
  lcd.setCursor(0,0);
  // assignes each segment a write number
      lcd.createChar(1, bar1);
      lcd.createChar(2, bar2);
      lcd.createChar(3, bar3);
      lcd.createChar(4, bar4);
      lcd.createChar(5, bar5);
      lcd.createChar(6, bar6);
      lcd.createChar(7, bar7);
      lcd.createChar(8, bar8);                 

  Serial.begin(9600);   // incializacion de comunicacion serie a 9600 bps

  attachInterrupt(digitalPinToInterrupt(A), encoder, LOW);// interrupcion sobre pin A con
                // funcion ISR encoder y modo LOW
  Serial.println("Listo");  // imprime en monitor serial Listo

  byte unidad = EEPROM.read(1);
  byte decena = EEPROM.read(2);

   tiempo=(unidad)+(decena*10);

  ANTERIOR=tiempo;  POSICION=tiempo ; compocicion();
 
   
}


void loop() 
{
  
  if (POSICION != ANTERIOR) 
  { // si el valor de POSICION es distinto de ANTERIOR
    Serial.println(POSICION); // imprime valor de POSICION
    compocicion();
    ANTERIOR = POSICION ; // asigna a ANTERIOR el valor actualizado de POSICION
  }

    if (digitalRead(btn) == LOW)
          {
            while (!digitalRead(btn)){lcd.setCursor(9,0); lcd.print("RODILLO"); lcd.setCursor(11,1); lcd.print("ON"); }
            delay(10);
            lcd.setCursor(9,0); lcd.print("       "); lcd.setCursor(11,1); lcd.print("  ");
          }


    if ( digitalRead(sensor) != LOW)
          {
            while (digitalRead(sensor)){ lcd.setCursor(9,0); lcd.print("SENSOR"); lcd.setCursor(11,1); lcd.print("ON");}
            delay(10);
            lcd.setCursor(9,0); lcd.print("      "); lcd.setCursor(11,1); lcd.print("  ");
          }
}

void encoder()  {
  static unsigned long ultimaInterrupcion = 0;  // variable static con ultimo valor de
            // tiempo de interrupcion
  unsigned long tiempoInterrupcion = millis();  // variable almacena valor de func. millis

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {  // rutina antirebote desestima
              // pulsos menores a 5 mseg.
    if (digitalRead(B) == HIGH)     // si B es HIGH, sentido horario
    {
      POSICION--; 
       // incrementa POSICION en 1
    }
    else {          // si B es LOW, senti anti horario
      POSICION++; 
            // decrementa POSICION en 1
    }
    POSICION = min(99, max(0, POSICION)); 
    ultimaInterrupcion = tiempoInterrupcion;  // guarda valor actualizado del tiempo
  }           // de la interrupcion en variable static
}

void compocicion()
{
  int aux;
  int centena = POSICION / 100;
  aux = POSICION % 100;
  byte decena = aux / 10;
  byte unidad = aux % 10;

  lcd.clear();
  printNumber(decena, 0);
  printNumber(unidad, 4);


  EEPROM.write(1, unidad);
  EEPROM.write(2, decena);

}

//---------------------------------------------------------------------------------------------
void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }
}
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom4(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}
//---------------------------------------------------------------------------------------------
