set(LOGGER_BASE
    ${CMAKE_CURRENT_SOURCE_DIR}/baselogger/baselogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/baselogger/baselogger.h
)

set(LOGGER_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/filelogger/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filelogger/logger.h
)

set(LOGGER_UTIL
    ${CMAKE_CURRENT_SOURCE_DIR}/util/util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util/util.h
    ${CMAKE_CURRENT_SOURCE_DIR}/util/error.h
)


if (SHARED)
    add_library(LoggerLib SHARED ${LOGGER_BASE} ${LOGGER_FILE} ${LOGGER_UTIL} ${LOGGER_ERROR})
else()
    add_library(LoggerLib STATIC ${LOGGER_BASE} ${LOGGER_FILE} ${LOGGER_UTIL} ${LOGGER_ERROR})
endif()

target_include_directories(LoggerLib PUBLIC 
    ${PROJECT_SOURCE_DIR}
)

set_target_properties(LoggerLib PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

