#include <iostream>
#include <string>
#include <map>
#include <optional>

std::optional<int> getCountMarkedFeatures(const std::string &db_path);

std::optional<std::map<std::string, int>> getCountByMarkedFeaturesType(const std::string &db_path);