cmake_minimum_required(VERSION 3.20)

project(CodeKnight LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(raylib CONFIG REQUIRED)

add_executable(CodeKnight
    src/main.c
    src/entities/blocks.c
    src/entities/coins.c
    src/entities/enemies.c
    src/entities/player.c
    src/entities/weapons.c
    src/game_atributes/game.c
    src/game_atributes/gameWindow.c
    src/interface/menu.c
    src/interface/pause.c
    src/resources/resourceManager.c
    src/resources/save.c
    src/world_logic/collisions.c
    src/world_logic/gameLobby.c
    src/world_logic/gameWorld.c
)

target_include_directories(CodeKnight PRIVATE 
    include
    include/entities
    include/game_atributes
    include/interface
    include/resources
    include/world_logic
)

target_link_libraries(CodeKnight PRIVATE
    raylib
)

if(MSVC)
    target_compile_options(CodeKnight PRIVATE /W4)
else()
    target_compile_options(CodeKnight PRIVATE -Wall -Wextra)
endif()