#include "global.h"
/**
 * @brief 
 * SYNTAX: R <- PROJECT column_name1, ... FROM relation_name
 */
bool syntacticParsePROJECTION()
{
    logger.log("syntacticParsePROJECTION");
    if (tokenizedQuery.size() < 5 || *(tokenizedQuery.end() - 2) != "FROM")
    {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }
    parsedQuery.queryType = PROJECTION;
    parsedQuery.projectionResultRelationName = tokenizedQuery[0];
    parsedQuery.projectionRelationName = tokenizedQuery[tokenizedQuery.size() - 1];
    for (int i = 3; i < tokenizedQuery.size() - 2; i++)
        parsedQuery.projectionColumnList.emplace_back(tokenizedQuery[i]);
    return true;
}

bool semanticParsePROJECTION()
{
    logger.log("semanticParsePROJECTION");

    if (tableCatalogue.isTable(parsedQuery.projectionResultRelationName))
    {
        cout << "SEMANTIC ERROR: Resultant relation already exists" << endl;
        return false;
    }

    if (!tableCatalogue.isTable(parsedQuery.projectionRelationName))
    {
        cout << "SEMANTIC ERROR: Relation doesn't exist" << endl;
        return false;
    }

    Table table = *tableCatalogue.getTable(parsedQuery.projectionRelationName);
    for (auto col : parsedQuery.projectionColumnList)
    {
        if (!table.isColumn(col))
        {
            cout << "SEMANTIC ERROR: Column doesn't exist in relation";
            return false;
        }
    }
    return true;
}

void executePROJECTION()
{
    logger.log("executePROJECTION");
    Table* resultantTable = new Table(parsedQuery.projectionResultRelationName, parsedQuery.projectionColumnList);
    Table table = *tableCatalogue.getTable(parsedQuery.projectionRelationName);
    Cursor cursor = table.getCursor();
    vector<int> columnIndices;
    for (int columnCounter = 0; columnCounter < parsedQuery.projectionColumnList.size(); columnCounter++)
    {
        columnIndices.emplace_back(table.getColumnIndex(parsedQuery.projectionColumnList[columnCounter]));
    }
    vector<int> row = cursor.getNext();
    vector<int> resultantRow(columnIndices.size(), 0);

    while (!row.empty())
    {

        for (int columnCounter = 0; columnCounter < columnIndices.size(); columnCounter++)
        {
            resultantRow[columnCounter] = row[columnIndices[columnCounter]];
        }
        resultantTable->writeRow<int>(resultantRow);
        row = cursor.getNext();
    }
    resultantTable->blockify();
    tableCatalogue.insertTable(resultantTable);
    return;
}