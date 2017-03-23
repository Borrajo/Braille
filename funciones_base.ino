//ESTAS FUNCIONES SON BASE Y NO DEBEN SER MODIFICADAS.

unsigned long leerSPI()
{
  unsigned long valor = 0;
  SPI.setBitOrder(MSBFIRST);
  digitalWrite(SSB,LOW);
  for(int i = 0 ; i < BYTES; i++)
  {  
    valor += (unsigned long)(SPI.transfer(0x00)) << 8*i; // = (Byte1 * << 8*0) + (Byte2 * 8*1) + (Byte3 * 8*2)
  }
  digitalWrite(SSB,HIGH);
  return valor;  
}

/*
void escribirSPI(unsigned long num)
{
  byte dato;
  SPI.setBitOrder(MSBFIRST);
  digitalWrite(SSL,LOW);
  //Descomponemos el numero en sus bytes para enviarlos de a uno.
  //al final de la funcion num siempre valdrá 0.
  for(int i = 0 ; i < BYTES; i++)
  { 
    dato = num%256;
    num /= 256; 
    SPI.transfer(dato);
  }
  digitalWrite(SSL,HIGH);  
} 
*/
