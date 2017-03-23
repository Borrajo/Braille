  /*
   *                                       *
   *  Utilizando el protocolo SPI se logra *                                     
   *  tomar el valor de los 8 botones  y   *
   *  obtener un numero resultante que es  *
   *  la combinacion de las teclas presio- *
   *  nadas                                *
   *                                       *
   *  Se Utiliza un Arduino Micro Pro      *
   *****************************************
   *            TECLADO BRAILLE            *
   *  Fecha:                    22/10/16   *       
   *                                       *
   *****************************************  
   */
  #include <SPI.h>
  #include <Keyboard.h>
  #define SSB 10 //Select Slave pin
  #define BYTES 1 //Cantidad de bytes (botones y luces)*8 
  
  /*  DEFINICION DE TECLAS NUEVAS AGREGADAS A LAS DE LA LIBRERIA DE ARDUINO */
 
  #define KEY_BACKSPACE  0xB2
  #define KEY_TAB        0xB3
  #define KEY_RETURN     0xB0
 
  #define KEY_DELETE     0xD4
  
  #define KEY_F8         0xC9
  #define KEY_F9         0xCA //
  
  #define NUMBER 135
  #define MAYUS 5
  
  // ARREGLOS PARA EL MAPEO del SPI --> CARACTER
  char charmap[256];
  char nummap[103];
 
void setup()
{
  inicializar();
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  Keyboard.begin();
  pinMode(SSB,OUTPUT);
  digitalWrite(SSB,HIGH);
  iniciarmapa();
}

void loop()
{
  //Leemos del puerto SPI
  unsigned long l = leerSPI();
  if(l != 0) //Si fue presionada una tecla
  {
    ObtenerTecla(l);
    //Una vez que ya sabemos con certeza que tecla se presionó, pasamos a ver cual es y actuar en consecuencia.
    switch (l) 
    {
    case NUMBER:  //Si se ha apretado el comando para escribir un numero, debemos leer nuevamente un caracter y este deberá corresponder a los numeros
      {
        leerDeTeclado(NUMBER,l);
      }
      break;
    case MAYUS:   //Si se ha apretado el comando para escribir una mayuscula, debemos leer un nuevo caracter y aplicarle la mayuscula en caso de que de una letra se trate.
      {
        leerDeTeclado(MAYUS,l);
      }
      break;
    default:
      { 
        //En cualquier otro caso escribimos la tecla leida del puerto SPI.
        Keyboard.write(charmap[l]);
      }
      break;
    }
  }
  delay(190);

}

unsigned long ObtenerTecla(unsigned letra)
{
  unsigned long l = letra;
  //Leemos 3 veces mas para eliminar errores.
    for(int i = 0; i < 5 ; i ++)
    {
      delay(12);

      unsigned long u = leerSPI();
      //Suponemos que cada vez que haya errorres será porqué los dedos no presionaron en el mismo instante las teclas.
      //Como cada tecla presionada siempre suma ( nunca resta al numero total) asumimos que el numero mayor será el correspondiente a la tecla deseada.
      if(u>l)
      {
        l = u ;
      }
    }
    Serial.println(l);
    return l;
}

void leerDeTeclado(unsigned long especial,char l)
{
  unsigned long r = l;
      //Leemos un nuevo caracter mientras no se presione ninguna tecla o el caracter leido sea igual al especial ( number o mayus) 
      while( r == especial || r == 0)
      {
        delay(190);    

        r = leerSPI();
        r = ObtenerTecla(r);
      }
      if(especial == NUMBER)
      {
        char c = nummap[r];
        Keyboard.write(c);
      }
      else
      {
        if(especial == MAYUS)
        {
            char c = charmap[r]-32; 
            Keyboard.write(c); //32 es la Distancia desde la 'a' a la 'A', de esta manera mostramos las Mayusculas
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
  charmap[160]='k';
  charmap[224]='l';
  charmap[164]='m';
  charmap[166]='n';
  charmap[103]='ñ';//ñ
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
  charmap[132]='/';
  charmap[194]='!';
  charmap[66]='-';
  charmap[130]='*';
  charmap[97]='(';
  charmap[134]=')';
  charmap[129]='_';
  charmap[10]= KEY_F8; //IMPRIMIR
  charmap[9]=KEY_F9; //ESCUCHAR
  charmap[8]=' ';
  charmap[24]=KEY_RETURN;
  charmap[16]=KEY_BACKSPACE;
}

void inicializar()
{
  for(int i = 0 ; i<256 ; i++)
  {
    charmap[i]= '\0';
    nummap[i]= '\0';
  }
}
 
 // Funcion substitutiva de la funcion delay()
void delayMs(unsigned int ms)
{
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}
 
