void initSPI1(void){
  RPB8Rbits.RPB8R = 0b0011;    //assign SDO1 to B8
  RPB7Rbits.RPB7R = 0b0011;    //assign SS1 to B7
  SDI1Rbits.SDI1R = 0b0000;   //assign SDI1 to A1

  SPI1BUF;                   //clear rx buffer by reading from it
  SPI1BRG = 1;              //set clock frequency to 2 MHz
  SPI1STATbits.SPIROV = 0;  //clear overflow bit
  SPI1CONbits.MSTEN = 1;    //master enabled
  SPI1CONbits.MSSEN = 0;    //auto slave select diabled
  SPI1CONbits.ON = 1;       //turn on SPI1

  TRISBbits.TRISB7 = 0;     //set SSI pin (B7) as output
  LATBbits.LATB7 = 1;       //do not allow communication
}


char SPI1_IO(char write){
  LATBbits.LATB7 = 0;     //open communication
  SPI1BUF = write;        //send to buffer
  LATBbits.LATB7 = 1;     //close communication
}

setVoltage(char channel, char voltage){
  if(channel == 0)
  {
    int write = ((0b0111 << 8) || voltage) << 4;
    SPI1_IO(write);
  }else if(channel == 1){
    int write = ((0b1111 << 8) || voltage) << 4;
    SPI1_IO(write);
  }

}
