#include "fft/stdafx.hpp"
#include "fft/Base.hpp"
#include "fft/GUI.hpp"
#include "fft/Vectorize.hpp"
#include "fft/DFT.hpp"
#if ENABLE_HOT_RELOAD
#include "jet/live/Live.hpp"
#endif
#include "noc/noc_file_dialog.h"

namespace fft {

void GUI::layout_gui( float delta_time ) {
    layout_controller();
    layout_hot_reload();

    // Info
    ImGui::Begin( "Info" );
    ImGui::Text( String( "FPS: " + to_string( 1.f / delta_time ) ).c_str() );
    ImGui::End();
}

void GUI::layout_controller() {
    ImGui::Begin( "Settings" );

    if ( ImGui::Button( "Open file" ) ) {
        auto path_c = noc_file_dialog_open( NOC_FILE_DIALOG_OPEN, nullptr, nullptr, nullptr );
        if ( path_c ) {
            fw.file_path = path_c;
            vectorize( fw.file_path, fw.raw_image, fw.interpolation_step );
            log( "Selected file " + fw.file_path );
        }
    }

    if ( ImGui::SliderInt( "Steps", &fw.interpolation_step, 2, 100 ) && !fw.file_path.empty() ) {
        vectorize( fw.file_path, fw.raw_image, fw.interpolation_step );
        fw.fourier_coeff.resize( fw.raw_image.size() );
    }
    ImGui::Text( ( "File vertex count: " + to_string( fw.raw_image.size() ) ).c_str() );

    ImGui::Spacing();
    int ff_c_size = fw.fourier_coeff.size();
    bool series_updated = false;
    if ( ImGui::SliderInt( "Series length", &ff_c_size, 0, fw.raw_image.size() ) ) {
        fw.fourier_coeff.resize( ff_c_size );
        series_updated = true;
    }
    if ( ImGui::Button( "Calculate fourier series" ) || ( fw.auto_update_series && series_updated ) ) {
        fft_series( fw.raw_image, fw.fourier_coeff );
        fw.spirograph_values = fw.fourier_coeff;
        fw.graph_result.clear();
    }
    ImGui::SameLine();
    ImGui::Checkbox( "Auto update", &fw.auto_update_series );

    ImGui::Spacing();
    ImGui::SliderFloat( "Spirograph speed", &fw.rotation_speed, 0, 0.01, "%.5f" );
    if ( ImGui::Button( "Clear graph" ) ) {
        fw.graph_result.clear();
    }
    ImGui::Text( ( "Graph vertex count: " + to_string( fw.graph_result.size() ) ).c_str() );

    ImGui::SliderInt( "Interaction count", &fw.simulation_iterations, 0, 100 );

    ImGui::Checkbox( "Draw original image", &fw.draw_raw );
    ImGui::Checkbox( "Draw graph", &fw.draw_graph );
    ImGui::Checkbox( "Draw ruler", &fw.draw_compass );

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
