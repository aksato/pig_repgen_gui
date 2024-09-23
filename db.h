#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <string>

using namespace sqlite_orm;

struct MarkedFeature
{
    int id;           // Corresponds to "id" in the table (INTEGER PRIMARY KEY)
    double dist0;     // Corresponds to "dist0" in the table (REAL)
    double angle0;    // Corresponds to "angle0" in the table (REAL)
    double dist1;     // Corresponds to "dist1" in the table (REAL)
    double angle1;    // Corresponds to "angle1" in the table (REAL)
    int feature_type; // Corresponds to "feature_type" in the table (INTEGER)
    std::string note; // Corresponds to "note" in the table (TEXT)
    int is_cluster;   // Corresponds to "is_cluster" in the table (INTEGER)
};

int getCountMarkedFeatures(const std::string &db_path);

std::map<std::string, int> getCountByMarkedFeaturesType(const std::string &db_path);