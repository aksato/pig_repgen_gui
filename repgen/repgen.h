#ifndef REPGEN_H
#define REPGEN_H

#include <string>

namespace repgen {
std::string generateAnomaliesSummary(std::string name);
bool writeTexFile(std::string content, std::string texFileName);
bool compileToPdf(std::string content, std::string pdfFileName);
}

#endif // REPGEN_H
