cmake_minimum_required (VERSION 3.5)

# add files
set(INCLUDE_DIR ../include/${PROJECT_NAME}/)
add_executable(${PROJECT_NAME}
../dep/imgui/imgui.cpp
../dep/imgui/imgui_draw.cpp
../dep/imgui/imgui_widgets.cpp
../dep/imgui/imgui_demo.cpp
../dep/imgui/misc/cpp/imgui_stdlib.cpp
../dep/imgui-sfml/imgui-SFML.cpp

    stdafx.cpp
    main.cpp
    Base.cpp
    Framework.cpp
    GUI.cpp
    Vectorize.cpp
    DFT.cpp
    
)

# includes
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../dep/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/../dep/imgui-sfml
        ${CMAKE_CURRENT_SOURCE_DIR}/../dep/jet-live/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../dep
        ${GTK3_INCLUDE_DIRS}

        if(MSVC)
        ${SFML_PATH}/include 
        endif()

)

# linking
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window

    if(UNIX)
    GL
    else()
    opengl32
    endif()
    
    FLAC
    Vorbis
    
    if(ENABLE_JET_LIVE)
    jet-live
    endif()
    
    if(UNIX)
    ${GTK3_LIBRARIES}
    endif()
)

# cotire speedup
if(ENABLE_COTIRE)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "../include/${PROJECT_NAME}/stdafx.hpp")
cotire(${PROJECT_NAME})
endif()

# add tests
#add_subdirectory(tests)
