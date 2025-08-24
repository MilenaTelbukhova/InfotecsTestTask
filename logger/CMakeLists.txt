add_library(LoggerLib SHARED logger.cpp)

target_include_directories(LoggerLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(LoggerLib PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

