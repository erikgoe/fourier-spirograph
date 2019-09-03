#include "fft/stdafx.hpp"
#include "fft/Framework.hpp"
#include "fft/GUI.hpp"
#include "fft/HotReload.hpp"
#include "fft/DFT.hpp"
//#include "jet/live/Live.hpp"

namespace fft {
Framework::Framework( std::function<void()> quit_callback ) {
    this->quit_callback = quit_callback;
}

void Framework::init() {
#if ENABLE_HOT_RELOAD
    // Hot reload
    jet_live = std::make_shared<jet::Live>( std::make_unique<HotReloadLogger>( *this ) );
#endif

    gui = std::make_shared<GUI>( *this );

    // Reload the system
    reload();
}
void Framework::terminate() {
    prepare_reload();
}

void Framework::evt_update_window_size( const sf::Vector2f &size ) {
    screen_size = size;
}

void Framework::evt_update_cursor_pos( const sf::Vector2f &in_screen_pos ) {}
bool Framework::evt_mouse_pri_press( const sf::Vector2f &in_screen_pos ) {
    return false;
}
bool Framework::evt_mouse_pri_release( const sf::Vector2f &in_screen_pos ) {
    return false;
}
bool Framework::evt_mouse_sec_press( const sf::Vector2f &in_screen_pos ) {
    return false;
}
bool Framework::evt_mouse_sec_release( const sf::Vector2f &in_screen_pos ) {
    return false;
}
void Framework::evt_key_release( const sf::Keyboard::Key &key ) {}
void Framework::evt_key_ctrl_release( const sf::Keyboard::Key &key ) {
#if ENABLE_HOT_RELOAD
    if ( key == sf::Keyboard::R ) {
        jet_live->tryReload();
        jet_reloading = true;
    }
#endif
}
void Framework::evt_key_shift_release( const sf::Keyboard::Key &key ) {}
void Framework::evt_key_shift_ctrl_release( const sf::Keyboard::Key &key ) {}


void Framework::update( sf::Time &delta_time ) {
#if ENABLE_HOT_RELOAD
    // Hot reload
    jet_live->update();
#endif

    timer_sec += delta_time.asSeconds();

    // Simulation
    spirograph_nodes.resize( spirograph_values.size() );
    for ( int iteration = 0; iteration < simulation_iterations; iteration++ ) {
        sf::Vector2f last;
        for ( int i = 0; i < spirograph_values.size(); i++ ) {
            spirograph_values[i] *= std::pow<float, float>(
                M_E, Complex( 0, M_PI * rotation_speed * ( ( i + 1 ) / 2 ) * ( i % 2 ? 1 : -1 ) ) );
            last += sf::Vector2f( spirograph_values[i].real(), spirograph_values[i].imag() );
            spirograph_nodes[i] = last;
        }
        graph_result.push_back( last );
    }

    // Thread
    ++calc_offset_ctr;

    // GUI
    gui->layout_gui( delta_time.asSeconds() );
}
void Framework::thread_run() {
    while ( thread_should_run ) {
        if ( calc_offset_ctr >= 2 ) {
            calc_offset_ctr = 0;

            // Heavy calculations

        } else
            sf::sleep( sf::milliseconds( 10 ) );
    }
}
void Framework::render( sf::RenderTarget &target ) {
    // Raw data
    if ( draw_raw ) {
        sf::VertexArray va1( sf::PrimitiveType::LinesStrip, raw_image.size() );
        sf::VertexArray va2( sf::PrimitiveType::Points, raw_image.size() );
        for ( size_t i = 0; i < raw_image.size(); i++ ) {
            va1[i] = sf::Vertex( raw_image[i], sf::Color( 255, 255, 255, 180 ) );
            va2[i] = va1[i];
            va2[i].color = sf::Color::Magenta;
        }
        target.draw( va1 );
        target.draw( va2 );
    }

    // Resulting graph
    if ( draw_graph ) {
        sf::VertexArray va( sf::PrimitiveType::LinesStrip, graph_result.size() );
        sf::Vector2f last;
        for ( size_t i = 0; i < graph_result.size(); i++ ) {
            va[i] = sf::Vertex( graph_result[i], sf::Color::Green );
        }
        target.draw( va );
    }

    // Spirograph
    if ( draw_compass ) {
        sf::VertexArray va( sf::PrimitiveType::LinesStrip, spirograph_nodes.size() + 1 );
        for ( size_t i = 0; i < spirograph_nodes.size(); i++ ) {
            va[i + 1] = sf::Vertex( spirograph_nodes[i], sf::Color( 200, 200, 50, 150 ) );
        }
        if ( spirograph_nodes.size() > 0 )
            va[0].color = va[1].color;
        target.draw( va );
    }
}

void Framework::reload() {
    // Initialize stuff

    // Start thread
    calc_offset_ctr = 0;
    thread_should_run = true;
    thread = std::make_shared<std::thread>( &Framework::thread_run, this );
}
void Framework::prepare_reload() {
    thread_should_run = false;
    thread->join();
}
} // namespace fft
