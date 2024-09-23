#include "db.h"

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

int getCountMarkedFeatures(const std::string &db_path)
{
    // Read Database, initialize storage with ORM mappings
    auto storage = initStorage(db_path);

    // Fetch count of all entries from the marked_feature table
    return storage.count<MarkedFeature>();
}

std::map<std::string, int> getCountByMarkedFeaturesType(const std::string &db_path)
{
    // Read Database, initialize storage with ORM mappings
    auto storage = initStorage(db_path);

    // Perform the query: SELECT COUNT(*), feature_type FROM marked_feature GROUP BY feature_type
    auto results = storage.select(columns(count(&MarkedFeature::id), &MarkedFeature::feature_type),
                                  group_by(&MarkedFeature::feature_type));

    // Print the results
    return {{"0", std::get<0>(results[0])},
            {"1", std::get<0>(results[1])},
            {"2", std::get<0>(results[2])}};
}