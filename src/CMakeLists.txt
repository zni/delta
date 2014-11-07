include_directories(${delta_SOURCE_DIR}/src)
link_directories(/usr/lib)

add_executable(delta main.cpp bullets.cpp enemies.cpp player.cpp)
target_link_libraries(delta sfml-graphics sfml-window sfml-system)
 
