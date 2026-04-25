#include <condition_variable>
#include <functional>
#include <mutex>

using namespace std;

class H2O {
  private:
    int h_slots;
    int o_slots;
    int used;
    mutex m;
    condition_variable cv;

  public:
    H2O() : h_slots(2), o_slots(1), used(0) {
    }

    void hydrogen(function<void()> releaseHydrogen) {
      unique_lock<mutex> lk(m);
      cv.wait(lk, [this] { return h_slots > 0; });

      // releaseHydrogen() outputs "H". Do not change or remove this line.
      releaseHydrogen();

      --h_slots;
      ++used;

      if (used == 3) {
        h_slots = 2;
        o_slots = 1;
        used = 0;
      }
      cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
      unique_lock<mutex> lk(m);
      cv.wait(lk, [this] { return o_slots > 0; });

      // releaseOxygen() outputs "O". Do not change or remove this line.
      releaseOxygen();

      --o_slots;
      ++used;

      if (used == 3) {
        h_slots = 2;
        o_slots = 1;
        used = 0;
      }
      cv.notify_all();
    }
};
