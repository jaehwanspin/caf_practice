file(GLOB sources ${CMAKE_CURRENT_LIST_DIR}/*)
list(REMOVE_ITEM sources ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt)

foreach(source ${sources})
    get_filename_component(exe ${source} NAME_WE)
    add_executable(${exe} ${exe}.cc)
    target_link_libaries(${exe} pthread ${CONAN_LIBS})
endforeach()