#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

// 定义温湿度传感器引脚
#define ONE_WIRE_BUS_PIN 2

// 实例化OneWire和DallasTemperature对象
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

// 定义Zigbee模块的串口引脚
#define ZIGBEE_RX_PIN 3
#define ZIGBEE_TX_PIN 4

// 实例化Zigbee模块的软串口对象
SoftwareSerial zigbeeSerial(ZIGBEE_RX_PIN, ZIGBEE_TX_PIN);

Void setup() {
  Serial.begin(9600);
  zigbeeSerial.begin(9600);
  sensors.begin();
}

Void loop() {
  // 读取温湿度数据
  sensors.requestTemperatures();  // 请求温度数据
  Float temperature = sensors.getTempCByIndex(0);  // 获取温度值
  Float humidity = sensors.getHumidity();

  // 打印温湿度数据
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // 将温湿度数据发送给物联网网关
  sendDataToGateway(temperature, humidity);

  delay(5000);
}

Void sendDataToGateway(float temperature, float humidity) {
  // 将温湿度数据转换为字节数组
  Byte data[8];
  memcpy(data, &temperature, sizeof(temperature));
memcpy(data+sizeof(temperature),&humidity,sizeof(humidity));
  // 发送数据到物联网网关
  For (int I = 0; I < sizeof(data); i++) {
    zigbeeSerial.write(data[i]);
  }
}