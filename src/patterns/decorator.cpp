// Подробнее в https://refactoring.guru/ru/design-patterns/decorator

#include <string>
#include <iostream>

class Logger {
public:
    virtual void log(const std::string &message) = 0;
};

class StdOutLogger : public Logger {
public:
    void log(const std::string &message) override {
        std::cout << message << std::endl;
    }
};

class LoggerDecorator : public Logger {
protected:
    Logger *logger;
public:
    explicit LoggerDecorator(Logger *logger) : logger(logger) {}
};

class RedLogger : public LoggerDecorator {
public:
    explicit RedLogger(Logger *logger) : LoggerDecorator(logger) {}

    void log(const std::string &message) override {
        std::string redMessage = "\033[31m" + message + "\033[0m";
        logger->log(redMessage);
    }
};

class StarLogger : public LoggerDecorator {
public:
    explicit StarLogger(Logger *logger) : LoggerDecorator(logger) {}

    void log(const std::string &message) override {
        std::string starMessage = "*" + message + "*";
        logger->log(starMessage);
    }
};

int main() {
    StdOutLogger stdOutLogger;
    stdOutLogger.log("simple message");
    RedLogger redLogger(&stdOutLogger);
    redLogger.log("red message");
    StarLogger starRedLogger(&redLogger);
    starRedLogger.log("star red message");
    stdOutLogger.log("another simple message");
    StarLogger starLogger(&stdOutLogger);
    starLogger.log("star message");
    return 0;
}
