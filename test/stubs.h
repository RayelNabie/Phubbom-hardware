#pragma once
#include <cstdint>
#include <vector>
#include <tuple>

// Arduino constants
#define HIGH 1
#define LOW  0
#define OUTPUT       1
#define INPUT_PULLUP 2

// Controllable globals — tests set deze om hardware te simuleren
extern unsigned long                                           g_millis;
extern int                                                     g_digitalReadReturn;
extern std::vector<std::pair<int,int>>                         g_digitalWrites;
extern std::vector<std::pair<int,int>>                         g_analogWrites;
extern std::vector<std::tuple<int,unsigned int,unsigned long>> g_tones;

// Arduino hardware stubs — tracken wat er wordt aangeroepen
inline unsigned long millis()                                 { return g_millis; }
inline int           digitalRead(int)                         { return g_digitalReadReturn; }
inline void          digitalWrite(int pin, int val)           { g_digitalWrites.push_back({pin, val}); }
inline void          analogWrite(int pin, int val)            { g_analogWrites.push_back({pin, val}); }
inline void          pinMode(int, int)                        {}
inline void          delay(unsigned long)                     {}
inline void          tone(int p, unsigned int f, unsigned long d = 0) { g_tones.push_back({p, f, d}); }
inline void          noTone(int)                              {}

struct SerialClass {
    template<typename T> void println(T) {}
    template<typename T> void print(T) {}
    void begin(unsigned long) {}
};
extern SerialClass Serial;
