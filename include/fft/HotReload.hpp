#pragma once

#include "fft/Base.hpp"
#include "fft/Framework.hpp"

namespace fft {
#if ENABLE_HOT_RELOAD
/// Manages logs of the hot reload framework
class HotReloadLogger : public jet::ILiveListener {
    Framework& fw;

public:
    HotReloadLogger( Framework& framework ) : fw( framework ) {}
    
    void onLog( jet::LogSeverity serverity, const String& str ) override {
        if ( static_cast<int>( serverity ) >= fw.jet_log_level ) {
            ++fw.jet_log_offset %= fw.jet_log.size();
            fw.jet_log[fw.jet_log_offset] = str;
        }
    }

    void onCodePreLoad() override { fw.prepare_reload(); }

    void onCodePostLoad() override { fw.reload(); }
};
#endif
} // namespace fft
