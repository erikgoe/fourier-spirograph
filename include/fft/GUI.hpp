#pragma once
#include "fft/Base.hpp"
#include "fft/Framework.hpp"

namespace fft {
/// Encapsulates the layouting methods
class GUI {
    Framework &fw;

public:
    GUI( Framework &framework ) : fw( framework ) {}

    // Main method
    void layout_gui(float delta_time);

private:
    // Sub methods for layouting
    void layout_controller();
    void layout_hot_reload();
};
} // namespace fft
