#include "repgen.h"
#include <filesystem>
#include <inja/inja.hpp>
#include <fstream>
#include "db.h"
#include <iostream>

std::string repgen::generateAnomaliesSummary(std::string dbFile)
{
    // Fetch count of all entries from the marked_feature table
    auto count = getCountMarkedFeatures(dbFile);
    auto countsByType = getCountByMarkedFeaturesType(dbFile);

    if (!count || !countsByType)
    {
        return R"(\documentclass{article}
        \begin{document}
        \begin{center}
        Error fetching data from database
        \end{center}
        \end{document})";
        "Error fetching data from database";
    }

    nlohmann::json data;
    data["totalAnomalies"] = *count;
    data["metalAnomalies"] = (*countsByType)["0"];
    data["geometryAnomalies"] = (*countsByType)["1"];
    data["laminationInclusions"] = (*countsByType)["2"];

    // LaTeX template with placeholders
    std::string latexTemplate = R"(\documentclass{article}
    \begin{document}
    \begin{center}
    \begin{tabular}{|l | r|} 
    \hline
    \multicolumn{2}{|c|}{SUMMARY OF ANOMALIES} \\
    \hline
    Total number of anomalies & {{ totalAnomalies }} \\ 
    \hline
    Number of metal loss anomalies & {{ metalAnomalies }} \\
    \hline
    Number of geometry anomalies & {{ geometryAnomalies }} \\
    \hline
    Number of laminations and inclusions & {{ laminationInclusions }} \\
    \hline
    \end{tabular}
    \end{center}
    \end{document})";

    return inja::render(latexTemplate, data);
}

bool repgen::writeTexFile(std::string content, std::string texFileName)
{
    // Write the output to a .tex file
    std::ofstream texFile(texFileName);
    if (!texFile)
    {
        return false;
    }
    texFile << content;
    texFile.close();
    return true;
}

bool repgen::compileToPdf(std::string content, std::string pdfFileName)
{
    // Replace the .pdf extension with .tex using std::filesystem
    std::filesystem::path pdfPath(pdfFileName);

    // Create a new path with .tex extension
    std::filesystem::path texFileName = pdfPath.replace_extension(".tex");

    // Write the LaTeX content to the .tex file
    if (!writeTexFile(content, texFileName.string()))
    {
        return false;
    }

    // Compile LaTeX to PDF using the generated .tex file
    std::string command = "pdflatex " + texFileName.string();
    system(command.c_str());

    return true; // Add return statement to indicate success
}
