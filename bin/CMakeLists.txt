add_executable(MyApp main.cpp)

target_link_libraries(MyApp PRIVATE LoggerLib)

target_include_directories(MyApp PRIVATE 
    ${PROJECT_SOURCE_DIR}/logger
)
