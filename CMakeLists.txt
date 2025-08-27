cmake_minimum_required(VERSION 3.10)
project(MyProject)


add_subdirectory(logger)
add_subdirectory(bin)
add_subdirectory(statistic)

enable_testing()
add_subdirectory(tests)