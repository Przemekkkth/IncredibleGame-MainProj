cmake_minimum_required(VERSION 3.28)
project(IncredibleGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
    src/AnimationComponent.h src/AnimationComponent.cpp
    src/AuxiliaryVariables.h src/AuxiliaryVariables.cpp

    src/Button.h src/Button.cpp
    src/BossLevel.h src/BossLevel.cpp
    src/BoundsChecking.h src/BoundsChecking.cpp

    src/CaveLevel.h src/CaveLevel.cpp
    src/Creature.h src/Creature.cpp

    src/Debug.h src/Debug.cpp

    src/Enemy.h src/Enemy.cpp

    src/Game.h src/Game.cpp
    src/GameResources.h src/GameResources.cpp
    src/GameState.h src/GameState.cpp
    src/Geometry.h src/Geometry.cpp

    src/Headers.h src/Headers.cpp
    src/HitboxComponent.h src/HitboxComponent.cpp

    src/Item.h src/Item.cpp

    src/Level.h src/Level.cpp

    src/MainMenuState.h src/MainMenuState.cpp
    src/MeleeWeapon.h src/MeleeWeapon.cpp
    src/MovementComponent.h src/MovementComponent.cpp

    src/ParkourValleyLevel.h src/ParkourValleyLevel.cpp
    src/PauseMenu.h src/PauseMenu.cpp
    src/PhysicsComponent.h src/PhysicsComponent.cpp
    src/Player.h src/Player.cpp
    src/PopUpText.h src/PopUpText.cpp

    src/RangeWeapon.h
    src/RangeWeapon.cpp

    src/State.h
    src/State.cpp

    src/Tile.h src/Tile.cpp
    src/TileMap.h src/TileMap.cpp

    src/ValleyLevel.h src/ValleyLevel.cpp

    src/main.cpp)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
