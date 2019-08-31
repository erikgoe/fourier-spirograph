#pragma once
#include "fft/Base.hpp"
#include "jet/live/Live.hpp"

// Declare jet-live Live class
namespace jet {
class Live;
}

namespace fft {
/// Manages the application in the virtual space
class Framework {
    sf::Vector2f screen_size; // save the size of the screen

    // Time
    float timer_sec = 0; /// general timer in seconds
    float select_start_time = 0; /// used for selection animation

    // GUI
    std::shared_ptr<GUI> gui;

    // Callbacks
    std::function<void()> quit_callback;

    // Simulation data

    // Thread data
    std::atomic_int calc_offset_ctr;
    std::shared_ptr<std::thread> thread;
    std::atomic_bool thread_should_run;


#if ENABLE_HOT_RELOAD
    // Code hot reload
    std::shared_ptr<jet::Live> jet_live;
    std::array<String, 128> jet_log;
    size_t jet_log_offset = 0;
    int jet_log_level = static_cast<int>( jet::LogSeverity::kInfo );
    bool jet_reloading = false;
#endif

public:
    Framework( std::function<void()> quit_callback );

    void init();
    void terminate();

    void evt_update_window_size( const sf::Vector2f &size ); /// Must also be called directly after initialization
    void evt_update_cursor_pos( const sf::Vector2f &in_screen_pos );
    bool evt_mouse_pri_press( const sf::Vector2f &in_screen_pos );
    bool evt_mouse_pri_release( const sf::Vector2f &in_screen_pos );
    bool evt_mouse_sec_press( const sf::Vector2f &in_screen_pos );
    bool evt_mouse_sec_release( const sf::Vector2f &in_screen_pos );
    void evt_key_release( const sf::Keyboard::Key &key );
    void evt_key_ctrl_release( const sf::Keyboard::Key &key );
    void evt_key_shift_release( const sf::Keyboard::Key &key );
    void evt_key_shift_ctrl_release( const sf::Keyboard::Key &key );

    void update( sf::Time &delta_time );

    /// Thread to update the fft
    void thread_run();

    void render( sf::RenderTarget &target );

#if ENABLE_HOT_RELOAD
    /// Is called when a hot reload occurs
    void reload();

    /// Is called to prepare a hot reload
    void prepare_reload();
#endif

    friend class HotReloadLogger;
    friend class GUI;
};
} // namespace fft
