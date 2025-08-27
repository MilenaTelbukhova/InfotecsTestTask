#include "baselogger.h"

BaseLogger::BaseLogger(){}
void BaseLogger::SetImportanceLevel(ImportanceLevel importanceLevel) {
    std::lock_guard<std::mutex> lg(Importance.Mutex);
    this->Importance.value = importanceLevel;
};
BaseLogger::BaseLogger(ImportanceLevel importance): Importance(importance){};

ImportanceLevel BaseLogger::GetImportanceLevel() { return Importance.value; };

BaseLogger::~BaseLogger() = default;