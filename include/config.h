#ifndef CONFIG_H
#define CONFIG_H

// Feature flags — comment out om component uit te zetten
#define FEATURE_AUDIO
#define FEATURE_MOTOR
#define FEATURE_LED
#define FEATURE_COUNTDOWN

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 3;
const int MOTOR_PIN  = 1;
const int LED_R_PIN  = 8;
const int LED_G_PIN  = 9;
const int LED_B_PIN  = 10;

#endif
