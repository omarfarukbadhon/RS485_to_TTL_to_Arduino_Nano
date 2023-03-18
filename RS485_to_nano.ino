// Omar Faruk Badhon
// Email: omarfarukbadhon@gmail.com 

#include <ModbusMaster.h> // decleare modbusmaster library 
    uint8_t result;
    uint16_t data[2];
    float reading;

#define MAX485_DE 3
#define MAX485_RE_NEG 2

ModbusMaster node; 

void preTransmission()
{ 
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
  //delay(500);
  }


void postTransmission()
{ 
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  //delay(500);
  }

void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);

//  init the receive mode 
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

//  modbus communication runs at 115200 baud
  Serial.begin(9600);

//  modbus slave ID 1
  node.begin(1, Serial);
//  callbacks allow us to configure the RS485 transceiver correctly
   node.preTransmission(preTransmission);
   node.postTransmission(postTransmission);
  
  }

void loop()
{

    result = node.readHoldingRegisters(1, 4);

    Serial.println(result, DEC);
  
    if (result == node.ku8MBSuccess) {
      Serial.print("Success, Received data: ");
      /*
      for (j = 0; j < 2; j++) {
        data[j] = node.getResponseBuffer(j);
        Serial.print(data[j], HEX);
        Serial.print(" ");
      }
      */
      data[0] = node.getResponseBuffer(0);
      data[1] = node.getResponseBuffer(1);
      reading = *((float *)data);

      Serial.println(reading);
      delay(1000);

      data[0] = node.getResponseBuffer(2);
      data[1] = node.getResponseBuffer(3);
      float temp = *((float *)data);

      Serial.println(temp);
    } else {
      Serial.print("Failed, Response Code: ");
      Serial.print(result, HEX);
      Serial.println("");
      delay(5000); 
    }
    delay(1000);
  }

  
