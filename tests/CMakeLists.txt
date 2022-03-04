
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

#-----Adding Source Files-----#
file(GLOB sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/input/*.c"
    )
list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.c")


#-----Adding Cpp Files-----#
file(GLOB tests "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM tests "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
  target_link_libraries("${name}_tests" gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
