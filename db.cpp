#include "db.h"
#include <SQLiteCpp/SQLiteCpp.h>

std::optional<int> getCountMarkedFeatures(const std::string &db_path)
{
    try
    {
        // Open a database file
        SQLite::Database db(db_path);

        // Return count of all entries from the marked_feature table
        return db.execAndGet("SELECT COUNT(*) FROM marked_feature");
    }
    catch (std::exception &e)
    {
        std::cout << "exception: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<std::map<std::string, int>> getCountByMarkedFeaturesType(const std::string &db_path)
{
    try
    {
        // Open a database file
        SQLite::Database db(db_path);

        // Compile a SQL query
        SQLite::Statement query(db, "SELECT feature_type, COUNT(*) FROM marked_feature GROUP BY feature_type;");

        // Loop to execute the query step by step, to get rows of result
        std::map<std::string, int> group_counts;
        while (query.executeStep())
        {
            // Demonstrate how to get some typed column value
            int type = query.getColumn(0);
            int count = query.getColumn(1);
            group_counts.insert(std::make_pair(std::to_string(type), count));
        }

        return group_counts;
    }
    catch (std::exception &e)
    {
        std::cout << "exception: " << e.what() << std::endl;
        return std::nullopt;
    }
}