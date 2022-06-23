#ifndef SIMD_TESTBED_UTILITIES_STOP_WATCH
#define SIMD_TESTBED_UTILITIES_STOP_WATCH

#include <chrono>

namespace sa::utilities {

class stop_watch
{
public:
    [[nodiscard]] auto elapsed() const noexcept -> double
    {
        auto const now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(now - start_).count();
    }

private:
    std::chrono::steady_clock::time_point start_ = std::chrono::steady_clock::now();
};

} // namespace st::utilities

#endif
