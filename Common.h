
#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>
#include <TeensyThreads.h>
#include <ArduinoQueue.h>
#include <TimeLib.h>

#define GPS_SERIAL Serial1
#define  GROUND_XBEE_SERIAL Serial7
#define PAYLOAD_XBEE_SERIAL Serial8

namespace Common
{
  static elapsedMillis milli;
  const unsigned long TELEMETRY_DELAY = 1000; // 1hz

  const byte VOLTAGE_PIN = 23;
  const byte BMP_SCL = 24;
  const byte BMP_SDA = 25;
  const byte PARA_SERVO_PIN = 41;
  const byte CAMERA_PIN = 3;
  const byte AUDIO_BEACON_PIN = 2;

  const float SEA_LEVEL = 1014.6f;

  static bool SIM_ACTIVATE = false;
  static bool SIM_ENABLE = false;
  static int SIM_PRESSURE = 0;
  const static uint16_t TEAM_ID = 1051;
  const static uint16_t LEAP_SECONDS = 18;

  static uint16_t BA_ADDR = 0;
  static uint16_t PC_ADDR = 4;
  static uint16_t ST_ADDR = 6;

  static float EE_BASE_ALTITUDE = 0;
  static uint16_t EE_PACKET_COUNT = 0;

  static String lastCMD = "None";

  struct GPS_Data
  {
    uint16_t hours;
    uint16_t minutes;
    uint16_t seconds;
    uint16_t milliseconds;
    float latitude;
    float longitude;
    float altitude;
    byte sats;
  };

  struct Sensor_Data
  {
    float vbat;
    float altitude;
    float temperature;
  };

  static int millisecond()
  {
    if (milli >= 1000)
      milli -= 1000;
    return milli;
  }

  static void build_packet(String& packet, const String& state, const String& tp_released, const GPS_Data &gps, const Sensor_Data &sensors)
  {
    packet = String(TEAM_ID) + ","; //0
    packet += String(hour()) + ":" + String(minute()) + ":" + String(second()) + "." + String(millisecond()) + ",";
    packet += String(EE_PACKET_COUNT) + ",";
    if (SIM_ACTIVATE && SIM_ENABLE)
      packet += "S,";
    else
      packet += "F,";
    packet += tp_released + ",";
    packet += String(sensors.altitude) + ","; 
    packet += String(sensors.temperature) + ",";
    packet += String(sensors.vbat) + ",";
    packet += String(gps.hours) + ":" + String(gps.minutes) + ":" + String(gps.seconds) + "." + String(gps.milliseconds) + ",";
    packet += String(gps.latitude) + ","; 
    packet += String(gps.longitude) + ","; 
    packet += String(gps.altitude) + ",";  
    packet += String(gps.sats) + ",";
    packet += state + ",";
    packet += lastCMD;
  }
}
#endif
