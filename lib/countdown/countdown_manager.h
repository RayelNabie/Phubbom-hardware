#ifndef COUNTDOWN_MANAGER_H
#define COUNTDOWN_MANAGER_H

class CountdownManager {
private:
  unsigned long startTime  = 0;
  unsigned long lastToggle = 0;
  bool active     = false;
  bool pulseState = false;

  unsigned long halfPeriod() const;

public:
  static int phaseForElapsed(unsigned long elapsed);
  static unsigned long halfPeriodForPhase(int phase);

  void start();
  bool isActive() const;
  void stop();
  void update();
};

#endif
