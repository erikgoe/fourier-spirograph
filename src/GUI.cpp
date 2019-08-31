#include "fft/stdafx.hpp"
#include "fft/Base.hpp"
#include "fft/GUI.hpp"
#include "jet/live/Live.hpp"
#include "noc/noc_file_dialog.h"

namespace fft {

void GUI::layout_gui( float delta_time ) {
    layout_controller();
    layout_hot_reload();

    // Info
    ImGui::Begin( "Info" );
    ImGui::Text( String( "FPS: " + to_string( 1.f / delta_time ) ).c_str() );
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void GUI::layout_controller() {
    ImGui::Begin( "Loader" );

    if ( ImGui::Button( "Open file" ) ) {
        auto path_c = noc_file_dialog_open( NOC_FILE_DIALOG_OPEN, nullptr, nullptr, nullptr );
        if ( path_c ) {
            log( "Selected file " + String( path_c ) );
        }
    }

    ImGui::End();
}

void GUI::layout_hot_reload() {
#if ENABLE_HOT_RELOAD
    // Code hot reload
    ImGui::Begin( "Hot reload log" );

    ImGui::Combo( "Log level", &fw.jet_log_level, "Debug\0Info\0Warning\0Error\0" );

    auto status = fw.jet_live->getStatus();
    bool ready = true;
    if ( !status.compilingFiles.empty() ) {
        if ( fw.jet_reloading ) {
            ImGui::Text( "Compiling (pending update)" );
        } else {
            ImGui::Text( "Compiling" );
        }
        for ( auto &s : status.compilingFiles ) {
            ImGui::TextDisabled( s.c_str() );
        }
        ready = false;
    }
    if ( !status.failedFiles.empty() ) {
        ImGui::TextColored( sf::Color::Red, "Failed" );
        for ( auto &s : status.failedFiles ) {
            ImGui::TextDisabled( s.c_str() );
        }
        ready = false;
        fw.jet_reloading = false;
    }
    if ( ready ) {
        if ( status.successfulFiles.empty() ) {
            fw.jet_reloading = false;
        }
        if ( fw.jet_reloading ) {
            ImGui::TextColored( sf::Color::Cyan, "Reloading" );
        } else {
            if ( status.successfulFiles.empty() ) {
                ImGui::TextColored( sf::Color::Green, "Ready" );
            } else {
                ImGui::TextColored( sf::Color::Green, "Ready (changes available)" );
            }
        }
    }
    ImGui::Separator();

    for ( size_t i = fw.jet_log_offset; i != ( fw.jet_log_offset + 1 ) % fw.jet_log.size(); ) {
        if ( fw.jet_log[i].empty() )
            break;
        ImGui::Text( fw.jet_log[i].c_str() );
        i--;
        if ( i >= fw.jet_log.size() )
            i = fw.jet_log.size() - 1;
    }
    ImGui::End();

#endif
}
} // namespace fft
