#include "global.h"

/**
 * @brief 
 * SYNTAX: R <- CROSS relation_name relation_name
 */
bool syntacticParseCROSS()
{
    logger.log("syntacticParseCROSS");
    if (tokenizedQuery.size() != 5)
    {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }
    parsedQuery.queryType = CROSS;
    parsedQuery.crossResultRelationName = tokenizedQuery[0];
    parsedQuery.crossFirstRelationName = tokenizedQuery[3];
    parsedQuery.crossSecondRelationName = tokenizedQuery[4];
    return true;
}

bool semanticParseCROSS()
{
    logger.log("semanticParseCROSS");
    //Both tables must exist and resultant table shouldn't
    if (tableCatalogue.isTable(parsedQuery.crossResultRelationName))
    {
        cout << "SEMANTIC ERROR: Resultant relation already exists" << endl;
        return false;
    }

    if (!tableCatalogue.isTable(parsedQuery.crossFirstRelationName) || !tableCatalogue.isTable(parsedQuery.crossSecondRelationName))
    {
        cout << "SEMANTIC ERROR: Cross relations don't exist" << endl;
        return false;
    }
    return true;
}

void executeCROSS()
{
    logger.log("executeCROSS");

    Table table1 = *(tableCatalogue.getTable(parsedQuery.crossFirstRelationName));
    Table table2 = *(tableCatalogue.getTable(parsedQuery.crossSecondRelationName));

    vector<string> columns;

    //If both tables are the same i.e. CROSS a a, then names are indexed as a1 and a2
    if(table1.tableName == table2.tableName){
        parsedQuery.crossFirstRelationName += "1";
        parsedQuery.crossSecondRelationName += "2";
    }

    //Creating list of column names
    for (int columnCounter = 0; columnCounter < table1.columnCount; columnCounter++)
    {
        string columnName = table1.columns[columnCounter];
        if (table2.isColumn(columnName))
        {
            columnName = parsedQuery.crossFirstRelationName + "_" + columnName;
        }
        columns.emplace_back(columnName);
    }

    for (int columnCounter = 0; columnCounter < table2.columnCount; columnCounter++)
    {
        string columnName = table2.columns[columnCounter];
        if (table1.isColumn(columnName))
        {
            columnName = parsedQuery.crossSecondRelationName + "_" + columnName;
        }
        columns.emplace_back(columnName);
    }

    Table *resultantTable = new Table(parsedQuery.crossResultRelationName, columns);\

    Cursor cursor1 = table1.getCursor();
    Cursor cursor2 = table2.getCursor();

    vector<int> row1 = cursor1.getNext();
    vector<int> row2;
    vector<int> resultantRow;
    resultantRow.reserve(resultantTable->columnCount);

    while (!row1.empty())
    {

        cursor2 = table2.getCursor();
        row2 = cursor2.getNext();
        while (!row2.empty())
        {
            resultantRow = row1;
            resultantRow.insert(resultantRow.end(), row2.begin(), row2.end());
            resultantTable->writeRow<int>(resultantRow);
            row2 = cursor2.getNext();
        }
        row1 = cursor1.getNext();
    }
    resultantTable->blockify();
    tableCatalogue.insertTable(resultantTable);
    return;
}