#include <iostream>
#include <ostream>
#include <chrono>

namespace jgm {
  class Timer {
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::milliseconds ms;

  public:
    explicit Timer(bool run = false) { 
      if (run) reset();
    }

    void reset() {
      mStart = clock::now();
    }

    ms elapsed() const {
      return std::chrono::duration_cast<ms>(clock::now() - mStart);
    }

    template <typename T, typename Traits>
    friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& out, const Timer& timer) {
      std::cout << timer.elapsed().count() << '\n';
    }

  private:
    clock::time_point mStart;
  };
}

int main(int argc, char* args[]) {
  auto alot = 100000000;

  jgm::Timer timer{ true };
  double semicolonAvg,
    commaAvg;

  for (auto j = 0; j < 10; ++j) {
    // semicolon
    for (auto i = 0; i < alot; ++i) {
      auto a = 0;
      auto b = 1;
      auto c = 2;
      auto d = 3;
      auto f = 4;
    }
    auto semicolonElapsed = timer.elapsed();
    semicolonAvg += semicolonElapsed.count();

    timer.reset();

    // comma
    for (auto i = 0; i < alot; ++i) {
      auto a = 0,
        b = 1,
        c = 2,
        d = 3,
        f = 4;
    }
    auto commaElapsed = timer.elapsed();
    commaAvg += commaElapsed.count();
  }

  semicolonAvg /= 10;
  commaAvg /= 10;

  std::cout << ";: " << std::to_string(semicolonAvg) << "\n,: " << std::to_string(commaAvg) << '\n';

  return 0;
}
