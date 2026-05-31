#ifndef CONFIG_H
#define CONFIG_H

// Feature flags — comment out om component uit te zetten
//#define FEATURE_AUDIO
//#define FEATURE_MOTOR
#define FEATURE_LED
#define FEATURE_COUNTDOWN
#define FEATURE_DFPLAYER

constexpr int BUTTON_PIN = 2;
constexpr int BUZZER_PIN = 3;
constexpr int MOTOR_PIN = 6;
constexpr int LED_PIN   = 10;

// DFPlayer Mini UART pins
constexpr int DFPLAYER_TX_PIN = 20;
constexpr int DFPLAYER_RX_PIN = 21;

#endif
