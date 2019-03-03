/*** Skullhouse Rock ("Impulse") ***/

/*
 * [File] SkullhouseRock.cpp
 * [Description] Robotic drummer with two arms with LED effects and audio input/output
 * [Author] Kevin K. Pho (926307943) <kevinpho@mit.edu>
 * [Author] Mario Leyva <mleyva@mit.edu>
 * [Author] Amaan Z. Malik
 * [Purpose] MakeMIT 2019
 */

// [Bug] Additional 20 millisecond drift (total per loop, not accumulating)





/*** Exports/Imports ***/
// [Purpose] Trigonometry calculations
#include <math.h>

// [Purpose] String manipulation
#include <string.h>

// [Purpose] Wi-Fi communications
#include <WiFi.h>

// [Purpose] SPI communications
#include <SPI.h>

// [Purpose] Bus communications
#include <Wire.h>

// [Purpose] Servo controls
#include <Servo.h>

// [Purpose] Framework stuff
#include "Helper.h"

// [Purpose] Processor
#include "ProcessorSystem.h"

// [Purpose] Text blinker
#include "TextSystem.h"

// [Purpose] Servo control
#include "ServoSystem.h"





/*** Systems Configuration ***/
ProcessorSystem mega2560 = ProcessorSystem();
ServoSystem leftShoulder = ServoSystem(2, 0);
ServoSystem rightShoulder = ServoSystem(3, 1);
ServoSystem leftArm = ServoSystem(4, 2);
ServoSystem rightArm = ServoSystem(5, 2);
ServoSystem leftElbow = ServoSystem(6, 3);
ServoSystem rightElbow = ServoSystem(7, 3);
// ServoSystem leftWrist = ContinuousSystem(8, 4);
// ServoSystem rightWrist = ContinuousSystem(9, 4);





/*** Main Function ***/
void setup() {
  mega2560.Main();
  leftShoulder.Main();
  rightShoulder.Main();
  leftArm.Main();
  rightArm.Main();
  leftElbow.Main();
  rightElbow.Main();
  // leftWrist.Main();
  // rightWrist.Main();
}





/*** Update Function ***/
void loop() {
  mega2560.Update();
  leftShoulder.Update();
  rightShoulder.Update();
  leftArm.Update();
  rightArm.Update();
  leftElbow.Update();
  rightElbow.Update();
  // leftWrist.Update();
  // rightWrist.Update();
}
