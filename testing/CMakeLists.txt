
include_directories("${PROJECT_SOURCE_DIR}/include")

#-----Adding Source Files-----#
file(GLOB sources 
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/input/*.c"
    )
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")


#-----Adding Cpp Files-----#
file(GLOB tests "${PROJECT_SOURCE_DIR}/testing/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/testing/main.cpp")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "${PROJECT_SOURCE_DIR}/testing/main.cpp")
  target_link_libraries("${name}_tests" gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
