#include "config_manager.h"
#include <fstream>
#include <regex>
#include <sstream>

namespace {
std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool number(const std::string& text, const std::string& key, double& value) {
    std::regex pattern("\"" + key + "\"\\s*:\\s*(-?[0-9]+(?:\\.[0-9]+)?)");
    std::smatch match;
    if (!std::regex_search(text, match, pattern)) return false;
    value = std::stod(match[1].str());
    return true;
}

bool integer(const std::string& text, const std::string& key, int& value) {
    double v = 0;
    if (!number(text, key, v)) return false;
    value = static_cast<int>(v);
    return true;
}

bool string_value(const std::string& text, const std::string& key, std::string& value) {
    std::regex pattern("\"" + key + "\"\\s*:\\s*\"([^\"]*)\"");
    std::smatch match;
    if (!std::regex_search(text, match, pattern)) return false;
    value = match[1].str();
    return true;
}
}

bool load_config(const std::string& path, AppConfig& config) {
    const std::string text = read_file(path);
    if (text.empty()) return false;

    double value = 0;
    if (number(text, "period_us", value)) config.task.period_us = static_cast<long>(value);
    integer(text, "iterations", config.task.iterations);
    if (number(text, "deadline_us", value)) config.task.deadline_us = static_cast<long>(value);
    string_value(text, "scheduler", config.task.scheduler.policy);
    integer(text, "priority", config.task.scheduler.priority);
    integer(text, "cpu", config.cpu);
    string_value(text, "csv_output", config.csv_output);

    return config.task.period_us > 0 && config.task.iterations > 0;
}
