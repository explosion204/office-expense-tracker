#include "computeunit.h"

void ComputeUnit::buildPieChart(std::vector<std::pair<QString, int> >)
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");
    PyRun_SimpleString("from pie_chart import pie_plot");
    Py_Finalize();
}

void ComputeUnit::test()
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");
    PyRun_SimpleString("import pie_chart");
    Py_Finalize();
}
