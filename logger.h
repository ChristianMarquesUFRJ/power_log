#pragma once

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

const int sck   =   14;
const int miso  =   2;
const int mosi  =   15;
const int cs    =   13;

void setup_log();
void readFile(fs::FS &fs, const char *path);
void writeFile(fs::FS &fs, const char *path, const char *message);
void appendFile(fs::FS &fs, const char *path, String message);
String get_message(unsigned long time, float voltage, float current, float power);