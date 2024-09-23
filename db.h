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

auto initStorage(const std::string &db_path)
{
    return make_storage(db_path,
                        make_table("marked_feature",
                                   make_column("id", &MarkedFeature::id, primary_key().autoincrement()),
                                   make_column("dist0", &MarkedFeature::dist0),
                                   make_column("angle0", &MarkedFeature::angle0),
                                   make_column("dist1", &MarkedFeature::dist1),
                                   make_column("angle1", &MarkedFeature::angle1),
                                   make_column("feature_type", &MarkedFeature::feature_type),
                                   make_column("note", &MarkedFeature::note),
                                   make_column("is_cluster", &MarkedFeature::is_cluster)));
}