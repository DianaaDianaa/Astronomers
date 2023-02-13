#include "Star.h"

string Star::toStd()
{
    string RAstd = std::to_string(RA);
    string DecStd = std::to_string(Dec);
    string diameterStd = std::to_string(diameter);
    return name + " " + constellation + " " + RAstd + " " + DecStd + " " + diameterStd;
}
