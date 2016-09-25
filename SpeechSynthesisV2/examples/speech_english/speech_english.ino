#include <SpeechSynthesis.h>
void setup()
{
  Serial.begin(9600);
}
 byte ssr[500];//define a character string
void loop()
{ 
SpeechSynthesis.buf_init(ssr);//initialize the buff
SpeechSynthesis.English(ssr,4,"5");//volume in grade 5
SpeechSynthesis.English(ssr,6,"cooki");//"6" means synthesis in English; "cooki"is the content
SpeechSynthesis.English(ssr,4,"5");
SpeechSynthesis.English(ssr,6,"cooki Clock, reset and supply management");
SpeechSynthesis.English(ssr,2,"10");
SpeechSynthesis.English(ssr,6,"cooki Clock, reset and supply management");
SpeechSynthesis.English(ssr,2,"5");//speed of speaking: grade 5
SpeechSynthesis.English(ssr,5," ");//speed,volume,intomation are all set into default
SpeechSynthesis.English(ssr,6,"cooki Clock, reset and supply management");
SpeechSynthesis.Espeaking(0,19,4,ssr);//Executive commands above, "0" is synthesis command; "19" select speaker; "4" speech function  

 while(Serial.read()!=0x41)//waiting synthesis complete
  {}
 while(Serial.read()!=0x4F)//waiting play complete
  {}   
SpeechSynthesis.buf_init(ssr);
SpeechSynthesis.English(ssr,6,"hello cooki 123");
SpeechSynthesis.Espeaking(0,19,4,ssr);
  
   while(Serial.read()!=0x41)
  {}
 while(Serial.read()!=0x4F)
  {}   
SpeechSynthesis.buf_init(ssr);
SpeechSynthesis.English(ssr,6,"hello cooki 123");
SpeechSynthesis.Espeaking(0,19,7,ssr);
  
while(1);
  
}
