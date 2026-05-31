#ifndef COUNTDOWN_MANAGER_H
#define COUNTDOWN_MANAGER_H

class CountdownManager {
private:
  unsigned long startTime  = 0;
  unsigned long lastToggle = 0;
  bool active     = false;
  bool pulseState = false;
  unsigned long duration_ms = DurationMs;

  unsigned long halfPeriod() const;

public:
  static constexpr unsigned long DurationMs = 30000;
  static constexpr unsigned long PhaseMs    = 10000;

  static int phaseForElapsed(unsigned long elapsed);
  static unsigned long halfPeriodForPhase(int phase);
  static unsigned long duration();

  void start();
  void start(unsigned long customDuration);
  bool isActive() const;
  void stop();
  void update();
};

#endif
