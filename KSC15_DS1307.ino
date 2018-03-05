//read and write the DS1307.Using the serial port to display the current time.
#include <Wire.h>
  
int bcd2bin(int temp){ //BCD  to decimal
	int a=temp, b=0,c;
	while(a>=16){
			a=a-16;
			b=b+10;
			c=a+b;
			temp=c;
	}
	return temp;
}

int bin_to_bcd(int temp){ //decimal to BCD
	int a=temp,b=0,c;
	while(a>=10){
			a=a-10;
			b=b+16;
			c=a+b;
			temp=c;
	}
	return temp;
}

void setup () {
    Serial.begin(9600);
    Wire.begin();
}
 
void loop () {
  uint8_t seconds = 0;//Initialization 7 fev 2018 à minuit pile
  uint8_t minutes = 0;
  uint8_t hours = 0;
  uint8_t week = 1;
  uint8_t days = 7;
  uint8_t months = 2;
  uint16_t Year = 18;
  /*
  //DS1307 write the initial time
  Wire.beginTransmission(0x68);
	  Wire.write(0);
	  Wire.requestFrom(0x68, 7);
	  Wire.write(bin_to_bcd(seconds));
	  Wire.write(bin_to_bcd(minutes));
	  Wire.write(bin_to_bcd(hours));
	  Wire.write(bin_to_bcd(week));
	  Wire.write(bin_to_bcd(days));
	  Wire.write(bin_to_bcd(months));
	  Wire.write(bin_to_bcd(Year));	
  Wire.endTransmission();
  */
  
  Wire.beginTransmission(0x68);//Send the address of DS1307
		Wire.write(0);//Sending address	
  Wire.endTransmission();//The end of the IIC communication
  
  Wire.requestFrom(0x68, 7);//IIC communication is started, you can continue to access another address (address auto increase) and the number of visits
	  seconds = bcd2bin(Wire.read());//read time
	  minutes = bcd2bin(Wire.read());
	  hours = bcd2bin(Wire.read());
	  week = Wire.read();
	  days = bcd2bin(Wire.read());
	  months = bcd2bin(Wire.read());
	  Year = bcd2bin(Wire.read()) + 2000;
  Wire.endTransmission();
  
  
  Serial.print(Year, DEC);//Serial display time
  Serial.print('/');
  Serial.print(months, DEC);
  Serial.print('/');
  Serial.print(days, DEC);
  Serial.print(' ');
  Serial.print(hours, DEC);
  Serial.print(':');
  Serial.print(minutes, DEC);
  Serial.print(':');
  Serial.print(seconds, DEC);
  Serial.println();
  Serial.print(" week: ");
  Serial.print(week, DEC);
  Serial.println();
  
  delay(5000);
}
