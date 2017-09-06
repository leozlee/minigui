cmake_minimum_required(VERSION 2.8.4)
project(minigui_demo)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(minigui_demo ${SOURCE_FILES})


set(HELLO_WORLD_SOURCE_FILES helloworld.c)
add_executable(hello_world ${HELLO_WORLD_SOURCE_FILES})
target_link_libraries(hello_world -lminigui_ths -lpng -ljpeg -lpthread -lmgncs -lmgplus -lmgutils -ldl)

set(INPUT_SOURCE_FILES input.c)
add_executable(input ${INPUT_SOURCE_FILES})
target_link_libraries(input -lminigui_ths -lpng -ljpeg -lpthread -lmgncs -lmgplus -lmgutils -ldl -lmgi -lfreetype)

set(MAIN_WINDOW_SOURCE_FILES iconview.c)
add_executable(main_window ${MAIN_WINDOW_SOURCE_FILES})
target_link_libraries(main_window -lminigui_ths -lpng -ljpeg -lpthread -lmgncs -lmgplus -lmgutils -ldl -lmgi -lfreetype)