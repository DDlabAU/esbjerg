int lille = 1; //INTERRUPT #3
int ring = 0; //INTERRUPT #2
int lang = 2; //INTERRUPT #1
int pege = 3; //INTERRUPT #0
int tommel = 7; //INTERRUPT #4

byte databyte=0;
bool change=false;

void isr(void)
{
	change=true;
}

void setup()
{

Serial.begin(115200);

pinMode(lille,INPUT);
pinMode(ring,INPUT);
pinMode(lang,INPUT);
pinMode(pege,INPUT);
pinMode(tommel,INPUT);

//Attach ALL the interrupts to the same isr:
attachInterrupt(0, isr, CHANGE);
attachInterrupt(1, isr, CHANGE);
attachInterrupt(2, isr, CHANGE);
attachInterrupt(3, isr, CHANGE);
attachInterrupt(4, isr, CHANGE);


}

void loop()
{
	if(change) {

		//each of the lower four bits of the databyte represent a finger as so:
		//  0b000XXXXX
		//       /||||
		// tommel /|||
		//    pege /||
		//     lang /|
		//      ring /
		//      lille

		databyte = (!digitalRead(lille) << 0) | (!digitalRead(ring) << 1) | (!digitalRead(lang) << 2) | (!digitalRead(pege) << 3) | (!digitalRead(tommel) << 4);

/*		//debug:
		Serial.print("lillebyte: ");
		Serial.print(byte( (!digitalRead(lille)  << 0) & 0b11111),BIN);
		Serial.print(" ringbyte: ");
		Serial.print(byte( (!digitalRead(ring)   << 1) & 0b11111),BIN);
		Serial.print(" langbyte: ");
		Serial.print(byte( (!digitalRead(lang)   << 2) & 0b11111),BIN);
		Serial.print(" pegebyte: ");
		Serial.print(byte( (!digitalRead(pege)   << 3) & 0b11111),BIN);
		Serial.print(" tommelbyte: ");
		Serial.println(byte( (!digitalRead(tommel) << 4) & 0b11111),BIN);

		Serial.print("databyte: ");
		Serial.println(databyte,BIN);
*/

		Serial.write(databyte);
		Serial.write(13); //CR
		Serial.write(10); //NL

		change=false;
	}

}

