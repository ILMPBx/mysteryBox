#include <SpeechSynthesis.h>//加入语音合成库
void setup()
{
  Serial.begin(9600);//初始化串口
} 
byte sr[200];//定义一个缓存
byte d[]={0xB3,0xC9,0xB6,0xBC,0xBC,0xAB,0xC8,0xA4};//中文内容（GB2312）
void loop()
{  
SpeechSynthesis.buf_init(sr);//清空或者初始化缓存
SpeechSynthesis.Chinese_english(sr,d,sizeof(d),6,0);//编辑合成内容函数
SpeechSynthesis.Chinese_english(sr,0,0,7,"hello d f robot");//编辑合成内容函数
SpeechSynthesis.Chinese_english(sr,0,0,1,"26");//编辑合成内容函数
SpeechSynthesis.Chinese_english(sr,0,0,7," hello d f robot");//编辑合成内容函数
SpeechSynthesis.Chinese_english(sr,d,sizeof(d),6,0);//编辑合成内容函数
SpeechSynthesis.Speaking(0,0,7,sr);//开始将编辑好的内容转为语音内容
while(Serial.read()!=0x41)//等待语音合成完成
  {}
while(Serial.read()!=0x4F)//等待语音播放完成
  {}   
SpeechSynthesis.buf_init(sr);//清空或者初始化缓存
SpeechSynthesis.Chinese_english(sr,0,0,7,"hello d f robot");//编辑合成内容函数
SpeechSynthesis.Chinese_english(sr,d,sizeof(d),6,0);//编辑合成内容函数
SpeechSynthesis.Speaking(0,0,7,sr);//开始将编辑好的内容转为语音内容
while(1);
}








