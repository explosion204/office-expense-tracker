#ifndef COMPUTEUNIT_H
#define COMPUTEUNIT_H

#include <QString>
#include <vector>
#pragma push_macro("slots")
#undef slots
#include <E:/Python/include/Python.h>
#pragma pop_macro("slots")
#include <stdio.h>

class ComputeUnit
{
public:
    static void buildPieChart(std::vector<std::pair<QString, int>>);
    static void test();
};

#endif // COMPUTEUNIT_H
