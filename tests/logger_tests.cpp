#include <gtest/gtest.h>
#include <logger/logger.h>
#include <regex>
#include <logger/util.h>

TEST(ParserTests, MainScenarios) {
    std::pair<ImportanceLevel, std::string> input [] = { 
        {ImportanceLevel::info, "DEBUG Memory used: 256MB"},
        {ImportanceLevel::info, "INFO database connection has been established"},
        {ImportanceLevel::warn, "INFOdatabase connection has been established"},
        {ImportanceLevel::warn, " INFOdatabase connection has been established"},
        {ImportanceLevel::debug, "INFO DEBUG database connection has been established"},
        {ImportanceLevel::error, "Can not open file /app/config.yaml"},
        {ImportanceLevel::info, "short"},
        {ImportanceLevel::info, "    database connection has been established"},
        {ImportanceLevel::debug, "      "}
     };
     std::pair<ImportanceLevel, std::string> output [] = {
        {ImportanceLevel::debug, "Memory used: 256MB"},
        {ImportanceLevel::info, "database connection has been established"},
        {ImportanceLevel::warn, "INFOdatabase connection has been established"},
        {ImportanceLevel::warn, "INFOdatabase connection has been established"},
        {ImportanceLevel:: info, "DEBUG database connection has been established"},
        {ImportanceLevel::error, "Can not open file /app/config.yaml"},
        {ImportanceLevel::info, "short"},
        {ImportanceLevel::info, "database connection has been established"},
        {ImportanceLevel::debug, ""}

     };

     for (size_t i = 0; i < std::size(input); i++) {
        auto parse = MessageParse::ParseCommand(input[i].first, input[i].second);
        ASSERT_EQ(parse, output[i]);
     }
}

TEST (LoggerTests, FileOpen) {
   std::filesystem::path path = "./test.txt";
   std::string log = "Memory used: 256MB";

   Logger logger(path, ImportanceLevel::debug);
   auto err = logger.Log(ImportanceLevel::debug, log);
   std::string fileContent;
   std::getline(std::ifstream{path}, fileContent);
   std::regex line_pattern("[A-Za-z]{3} \\d{1,2} \\d{2}:\\d{2}:\\d{2} \\d{4} \\[[A-Za-z]{4,5}\\] ?");
   ASSERT_TRUE(std::regex_search(fileContent, line_pattern));
   size_t find = fileContent.find(log);
   ASSERT_TRUE(find != std::string::npos);
   ASSERT_EQ(find, fileContent.size() - log.size());
}

TEST (LoggerTests, LowImportance) {
   std::filesystem::path path = "./test.txt";
   std::string log = "Memory used: 256MB";

   Logger logger(path, ImportanceLevel::error);
   auto err = logger.Log(ImportanceLevel::debug, log);
   ASSERT_FALSE(err.has_value());
   std::string fileContent;
   std::getline(std::ifstream{path}, fileContent);
   ASSERT_TRUE(fileContent.size() == 0);
}

TEST (LoggerTests, DeletedFile) {
   std::filesystem::path path = "./test.txt";
   std::string log = "Memory used: 256MB";

   Logger logger(path, ImportanceLevel::debug);
   remove(path);
   auto err = logger.Log(ImportanceLevel::debug, log);
   ASSERT_EQ("Can not open journal\n", err.value().Message);
}