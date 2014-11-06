/*
Model:AS-289R(Printer Shield)
Arduino UNO R3用 DTR制御無しサンプルコード
ナダ電子株式会社 特機課
NADA ELECTRONICS, LTD.
http://www.nada.co.jp
*/
 #include <string.h>

const int head_length = 4;
const int body_length = 256;
char head[head_length] = { 0x1D,0x78,0x48,0x01 };  //QRコード stat, stat, nz_reduction, length　//1D=29, 78=120, 48=72
 
void setup()
{
  Serial.begin(9600);
 
byte cmd_rev_prt[3] = { 0x1B, 0x49, 0x01 };
Serial.write(cmd_rev_prt,3);
  //{0x1B, 0x49, 0x01}; 
}
 
void loop()
{

   if(Serial.available()){	 

       //Make Body to Storage
        char body[body_length]; 
       //Reser all params
        for(int i=0; i<256; i++){ 
          body[i]=0;    
        }        
        //Listen Serial Message        	
        int gotCharNum = Serial.readBytesUntil('\n' , body, body_length);

	if(gotCharNum != 0){ //If received the new message

//                        Serial.println(gotCharNum);
                        //for(int i=0; i<body_length; i++) Serial.println((byte)body[i]);

		 	head[3]=gotCharNum; //Set the number of datalength

                        //Make STR for Merge
                        char str[256];
                        for(int i=0; i<256; i++){ 
                          str[i]=0;    
                        }

                        //Copy the head 
                        strcpy(str,(char*)head);
                        //Merge the body after it
                        strcat(str, body);

		 	// Serial.print(str);
		 	Serial.write((byte*)str, head_length+gotCharNum);
                        Serial.print("\r\r\r");  // 改行x6
                        Serial.println(body);
                        // Serial.print("\r\r\r\r\r\r");  // 改行x6
                        Serial.print("\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r");  // 改行x18
                        Serial.print("\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r");  // 改行x18
                        Serial.print("\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r");  // 改行x18


//                        Serial.println("in byte-----");
//                        for(int i=0; i< (head_length+gotCharNum); i++) Serial.println((byte)str[i]);
//                     
//                        Serial.println("in char-----");
//                        for(int i=0; i< (head_length+gotCharNum); i++) Serial.print(str[i]);
// 
//                        Serial.println("--Length----------");
//                        Serial.println(head_length+gotCharNum);

	}

  }
  





//  Serial.write(head, 8);
//  Serial.print("\r\r\r\r\r\r");  // 改行x6
 
  //delay(5000);  // 5sec
}
