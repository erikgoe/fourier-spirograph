#include "fft/stdafx.hpp"
#include "fft/Base.hpp"
#include "fft/Framework.hpp"

#ifdef SFML_SYSTEM_LINUX
#define NOC_FILE_DIALOG_GTK
#elif defined SFML_SYSTEM_WINDOWS
#define NOC_FILE_DIALOG_WIN32
#elif defined SFML_SYSTEM_MACOS
#define NOC_FILE_DIALOG_OSX
#endif

#define NOC_FILE_DIALOG_IMPLEMENTATION
#include "noc/noc_file_dialog.h"

#define NANOSVG_IMPLEMENTATION // Expands implementation
#include "nanosvg/src/nanosvg.h"

void updateView( sf::View &view, const float &zoom_factor, const sf::Vector2f &window_size, const sf::Vector2f &center ) {
    view = sf::View( center, window_size );
    view.zoom( zoom_factor );
}

struct DragData {
    sf::Vector2f initialStart;
    sf::Vector2f dragStart;
    bool pre_dragging = false;
    bool dragging = false;
};

int main() {
    // Resources
    sf::RenderWindow window( sf::VideoMode( 1200, 800 ), "fft spirograph", sf::Style::Default,
                             sf::ContextSettings( 0, 0, 8, 3, 0, 0, true ) );
    window.setVerticalSyncEnabled( true );
    fft::Framework fw( [&]() { window.close(); } );
    sf::Clock timer;
    sf::View view = window.getDefaultView();
    float zoom_factor = 1.0;
    sf::Vector2f window_size = sf::Vector2f( window.getSize() );
    sf::Vector2f view_center = sf::Vector2f( window.getSize() ) * 0.5f;
    DragData drag_data;
    bool valid_pressed = false;

    fw.init();
    fw.evt_update_window_size( sf::Vector2f( window.getSize() ) );
    ImGui::SFML::Init( window );

    // Main Loop
    while ( window.isOpen() ) {
        // Calculate delta time
        auto delta_time = timer.restart();

        // Event handling
        sf::Event evt;
        while ( window.pollEvent( evt ) ) {
            ImGui::SFML::ProcessEvent( evt );
            bool not_on_gui = !ImGui::IsAnyItemHovered() && !ImGui::IsAnyWindowHovered();
            bool not_key_insert_gui = !ImGui::IsAnyItemActive();

            if ( evt.type == sf::Event::Closed ) {
                window.close();
            } else if ( evt.type == sf::Event::MouseButtonPressed ) {
                if ( not_on_gui ) {
                    valid_pressed = true;
                    sf::Vector2f in_Screen =
                        window.mapPixelToCoords( sf::Vector2i( evt.mouseButton.x, evt.mouseButton.y ) );
                    if ( evt.mouseButton.button == sf::Mouse::Button::Left ) {
                        fw.evt_mouse_pri_press( in_Screen );
                    } else if ( evt.mouseButton.button == sf::Mouse::Button::Right ) {
                            drag_data.pre_dragging = true;
                            drag_data.dragStart = sf::Vector2f( evt.mouseButton.x, evt.mouseButton.y );
                            drag_data.initialStart = drag_data.dragStart;
                    }
                }
            } else if ( evt.type == sf::Event::MouseButtonReleased ) {
                if ( not_on_gui && valid_pressed ) {
                    sf::Vector2f in_Screen =
                        window.mapPixelToCoords( sf::Vector2i( evt.mouseButton.x, evt.mouseButton.y ) );
                    if ( evt.mouseButton.button == sf::Mouse::Button::Left ) {
                        fw.evt_mouse_pri_release( in_Screen );
                    } else if ( evt.mouseButton.button == sf::Mouse::Button::Right ) {
                        if ( !drag_data.dragging )
                            fw.evt_mouse_sec_release( in_Screen );
                    }
                }
                valid_pressed = false;
                drag_data.dragging = false;
                drag_data.pre_dragging = false;
            } else if ( evt.type == sf::Event::MouseMoved ) {
                sf::Vector2f in_Screen = window.mapPixelToCoords( sf::Vector2i( evt.mouseMove.x, evt.mouseMove.y ) );
                fw.evt_update_cursor_pos( in_Screen );

                // Dragging
                if ( drag_data.pre_dragging ) {
                    sf::Vector2f windowCoords( evt.mouseMove.x, evt.mouseMove.y );
                    view_center += ( drag_data.dragStart - windowCoords ) * zoom_factor;
                    drag_data.dragStart = windowCoords;
                    updateView( view, zoom_factor, window_size, view_center );
                    window.setView( view );

                    // Dragging threshold
                    sf::Vector2f drag_distance = drag_data.initialStart - windowCoords;
                    if ( drag_distance.x * drag_distance.x + drag_distance.y * drag_distance.y > 16 ) // 4 px ^2
                        drag_data.dragging = true;
                }
            } else if ( evt.type == sf::Event::Resized ) {
                window_size = sf::Vector2f( evt.size.width, evt.size.height );
                updateView( view, zoom_factor, window_size, view_center );
                window.setView( view );
                fw.evt_update_window_size( window_size );
            } else if ( evt.type == sf::Event::MouseWheelScrolled ) {
                if ( not_on_gui ) {
                    sf::Vector2f mouse_coords( evt.mouseWheelScroll.x, evt.mouseWheelScroll.y );
                    mouse_coords -= window_size * 0.5f;
                    zoom_factor *= std::pow( 1.1f, -evt.mouseWheelScroll.delta );
                    view_center += mouse_coords * zoom_factor * 0.1f * ( evt.mouseWheelScroll.delta < 0 ? -1.f : 1.f );
                    updateView( view, zoom_factor, window_size, view_center );
                    window.setView( view );
                }
            } else if ( evt.type == sf::Event::KeyReleased ) {
                if ( not_key_insert_gui ) {
                    if ( evt.key.control ) {
                        if ( evt.key.shift ) {
                            fw.evt_key_shift_ctrl_release( evt.key.code );
                        } else {
                            fw.evt_key_ctrl_release( evt.key.code );
                        }
                    } else {
                        if ( evt.key.shift ) {
                            fw.evt_key_shift_release( evt.key.code );
                        } else {
                            fw.evt_key_release( evt.key.code );
                        }
                    }
                }
            }
        }

        // Updating
        ImGui::SFML::Update( window, delta_time );
        fw.update( delta_time );
        ImGui::EndFrame();

        // Rendering
        window.clear( sf::Color( 127, 127, 127 ) );

        fw.render( window );
        ImGui::SFML::Render( window );

        window.display();
    }

    // Cleanup
    ImGui::SFML::Shutdown();
    fw.terminate();

    return 0;
}
