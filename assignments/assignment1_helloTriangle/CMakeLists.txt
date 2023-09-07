#Hello Triangle example

file(
 GLOB_RECURSE HELLOTRIANGLE_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE HELLOTRIANGLE_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this assignment2_sunset's asset folder to bin when it is built
add_custom_target(copyAssetsA1 ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/Shaders/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders/)

install(FILES ${HELLOTRIANGLE_INC} DESTINATION include/assignment1_helloTriangle)
add_executable(assignment1_helloTriangle ${HELLOTRIANGLE_SRC} ${HELLOTRIANGLE_INC} ${HELLOTRIANGLE_ASSETS})
target_link_libraries(assignment1_helloTriangle PUBLIC core IMGUI)
target_include_directories(assignment1_helloTriangle PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})
add_dependencies(assignment1_helloTriangle copyAssetsA1)