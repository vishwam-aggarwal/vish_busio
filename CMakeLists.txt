add_library( vish_busio
    vish_busio.h
    vish_busio.cpp
    )

add_subdirectory(vish_i2cdev)

target_link_libraries(vish_busio
    pico_stdlib
    vish_i2cdev
)

target_include_directories(vish_busio PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")