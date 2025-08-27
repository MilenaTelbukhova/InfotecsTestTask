option(SHARED "Собрать библиотеку динамически" OFF)

if (SHARED)
    add_library(LoggerLib SHARED logger.cpp, baselogger.cpp)
    target_include_directories(LoggerLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
else()
    add_library(LoggerLib STATIC logger.cpp logger.h error.h baselogger.cpp baselogger.h)
endif()

set_target_properties(LoggerLib PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

