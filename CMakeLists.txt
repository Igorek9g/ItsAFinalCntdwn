cmake_minimum_required(VERSION 3.6)
set(NAME ItsAFinalCntdwn)
project(${NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH /home/student/geant4/geant4-install)

option(WITH_GEANT4_UIVIS "Build project with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(${NAME} main.cc ${sources} ${headers} include/Run.hh include/RunAct.hh src/Run.cc src/RunAct.cc include/Mes.hh src/Mes.cc)
target_link_libraries(${NAME} ${Geant4_LIBRARIES})


set(FSCRIPTS
        init_vis.mac
        vis.mac
        )

foreach(_script ${FSCRIPTS})
    configure_file(
            ${PROJECT_SOURCE_DIR}/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach()
