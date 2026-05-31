#ifndef CONFIG_H
#define CONFIG_H

// Feature flags — comment out om component uit te zetten
#define FEATURE_AUDIO
#define FEATURE_MOTOR
#define FEATURE_LED
#define FEATURE_COUNTDOWN

constexpr int BUTTON_PIN = 2;
constexpr int BUZZER_PIN = 3;
constexpr int MOTOR_PIN = 1;
constexpr int LED_PIN   = 10;

#endif
