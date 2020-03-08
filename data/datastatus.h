#ifndef DATAMANIPULATIONACTION_H
#define DATAMANIPULATIONACTION_H

#include <QString>

enum DataStatus
{
    CREATED = 0, MODIFIED = 1, DELETED = 2, VALIDATED = 3
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
            default:
                break;
        }
        return "VALIDATED";
    }

    static DataStatus stringToDataStatus(QString string)
    {
        if (!string.compare("CREATED"))
            return CREATED;
        if (!string.compare("MODIFIED"))
            return MODIFIED;
        if (!string.compare("DELETED"))
            return DELETED;
        return VALIDATED;
    }
};

#endif // DATAMANIPULATIONACTION_H
