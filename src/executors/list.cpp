#include "global.h"
/**
 * @brief 
 * SYNTAX: LIST TABLES
 */
bool syntacticParseLIST()
{
    logger.log("syntacticParseLIST");
    if (tokenizedQuery.size() != 2 || tokenizedQuery[1] != "TABLES")
    {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }
    parsedQuery.queryType = LIST;
    return true;
}

bool semanticParseLIST()
{
    logger.log("semanticParseLIST");
    return true;
}

void executeLIST()
{
    logger.log("executeLIST");
    tableCatalogue.print();
}