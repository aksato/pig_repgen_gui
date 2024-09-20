#include "repgen.h"
#include <filesystem>
#include <inja/inja.hpp>
#include <fstream>

std::string repgen::generateAnomaliesSummary(std::string name) {
    nlohmann::json data;
    data["name"] = name;

    // LaTeX template with placeholders
    std::string latexTemplate = R"(\documentclass{article}
    \begin{document}
    Hello {{ name }}
    \end{document})";

    return inja::render(latexTemplate, data);
}

bool repgen::writeTexFile(std::string content, std::string texFileName) {
    // Write the output to a .tex file
    std::ofstream texFile(texFileName);
    if (!texFile) {
        return false;
    }
    texFile << content;
    texFile.close();
    return true;
}

bool repgen::compileToPdf(std::string content, std::string pdfFileName) {
    // Replace the .pdf extension with .tex using std::filesystem
    std::filesystem::path pdfPath(pdfFileName);

    // Create a new path with .tex extension
    std::filesystem::path texFileName = pdfPath.replace_extension(".tex");

    // Write the LaTeX content to the .tex file
    if (!writeTexFile(content, texFileName.string())) {
        return false;
    }

    // Compile LaTeX to PDF using the generated .tex file
    std::string command = "pdflatex " + texFileName.string();
    system(command.c_str());

    return true; // Add return statement to indicate success

}
