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
        ${SFML_INCLUDE_DIRS} 
        ${VCPKG_SOURCE_DIR}/installed/x86-windows-static/include

)

# linking
target_link_libraries(${PROJECT_NAME}
    #${SFML_LIBRARIES}
    ${VCPKG_SOURCE_DIR}/installed/x86-windows-static/lib/sfml-system-s.lib
    ${VCPKG_SOURCE_DIR}/installed/x86-windows-static/lib/sfml-graphics-s.lib
    ${VCPKG_SOURCE_DIR}/installed/x86-windows-static/lib/sfml-window-s.lib
    #${SFML_DEPENDENCIES}
    ${OPENGL_LIBRARIES}
    FLAC
    Vorbis
    #jet-live
    #${GTK3_LIBRARIES}
)

# cotire speedup
#set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "../include/${PROJECT_NAME}/stdafx.hpp")
#cotire(${PROJECT_NAME})

# add tests
#add_subdirectory(tests)
