#pragma once

#include <functional>

namespace hacksim {

// Interactive htop simulation
// Returns when user presses 'q'
void run_htop(std::function<bool()> should_exit);

} // namespace hacksim
