  #include <SPI.h>
  #include "Keyboard.h"
 // #define DATAout 51
 // #define CLK 52
 // #define DATAin 50
  #define SSB 4 //Select Slave Button
  #define SSL 2 //Select Slave Led
  #define BYTES 1 //Cantidad de bytes (botones y luces)*8 
  #define KEY_BACKSPACE 178
  #define KEY_RETURN 176
  #define NUMBER 135
  #define MAYUS 5
  char charmap[256];
  char nummap[256];
 
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(SSB,OUTPUT);
  pinMode(SSL,OUTPUT);
  digitalWrite(SSB,HIGH);
  digitalWrite(SSL,HIGH); 
  Keyboard.begin();
  iniciarmapa();
}

void loop()
{
  unsigned long l = leerSPI();
  if(l != 0)
  {
    switch (l) 
    {
    case NUMBER:
      leerDeTeclado(NUMBER);
      break;
    case MAYUS:
      leerDeTeclado(MAYUS);
      break;
    default: 
    //IMPRIME LA TECLA
     Keyboard.print(charmap[l]);
     Serial.println(charmap[l]);
     char c = charmap[l];
     Serial1.println(c);
    break;
    }
  }
  delay(210);
}

void leerDeTeclado(int especial)
{
  unsigned long r = l;
      while( r == especial || r == 0)
      {
        delay(200);
        r = leerSPI();
      }
      if(especial == NUMBER)
      {
        Keyboard.print(nummap[r]);
        escribirSPI(0);
        Serial1.println(nummap[r]);

      }
      if(especial == MAYUS)
      {
        Keyboard.print(charmap[r]-32);
        escribirSPI(0);
        Serial1.println(charmap[r]-32);

      }
    }
}

void iniciarmapa()
{
  nummap[32]='1';
  nummap[96]='2';
  nummap[36]='3';
  nummap[38]='4';
  nummap[34]='5';
  nummap[100]='6';
  nummap[102]='7';
  nummap[98]='8';
  nummap[68]='9';
  nummap[70]='0';
  charmap[32]='a';
  charmap[96]='b';
  charmap[36]='c';
  charmap[38]='d';
  charmap[34]='e';
  charmap[100]='f';
  charmap[102]='g';
  charmap[98]='h';
  charmap[68]='i';
  charmap[70]='j';
  charmap[162]='k';
  charmap[224]='l';
  charmap[164]='m';
  charmap[166]='n';
  charmap[103]='ñ';
  charmap[162]='o';
  charmap[228]='p';
  charmap[230]='q';
  charmap[226]='r';
  charmap[196]='s';
  charmap[198]='t';
  charmap[161]='u';
  charmap[225]='v';
  charmap[71]='w';
  charmap[165]='x';
  charmap[167]='y';
  charmap[163]='z';
  charmap[128]='.';
  charmap[64]=',';
  charmap[65]='?';
  charmap[192]=';';
  charmap[67]=':';
  charmap[132]='/';
  charmap[194]='!';
  charmap[66]='-';
  charmap[130]='*';
  charmap[193]='"';
  charmap[97]='(';
  charmap[134]=')';
  charmap[101]='ü';
  charmap[199]='ú';
  charmap[133]='ó';
  charmap[131]='í';
  charmap[197]='é';
  charmap[227]='á';
  charmap[229]='&';
  charmap[129]='_';
  charmap[24]=KEY_RETURN;
  charmap[16]=KEY_BACKSPACE;
}

