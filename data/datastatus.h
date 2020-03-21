#ifndef DATAMANIPULATIONACTION_H
#define DATAMANIPULATIONACTION_H

#include <QString>

enum DataStatus
{
    CREATED = 0, MODIFIED = 1, DELETED = 2
};

class DataStatusTools
{
public:
    static QString dataStatusToString(DataStatus status)
    {
        switch (status)
        {
            case CREATED:
                return "CREATED";
            case MODIFIED:
                return "MODIFIED";
            case DELETED:
                return "DELETED";
        }
    }

    static DataStatus stringToDataStatus(QString string)
    {
        if (!string.compare("CREATED"))
            return CREATED;
        if (!string.compare("MODIFIED"))
            return MODIFIED;
        if (!string.compare("DELETED"))
            return DELETED;
        throw std::invalid_argument("invalid argument");
    }
};

#endif // DATAMANIPULATIONACTION_H
