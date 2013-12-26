/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: DBUtil.cpp
 * $Id: DBUtil.cpp v 1.0 2013-12-26 18:35:29 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 19:36:04 $
 * @brief
 *
 ******************************************************************/

#include "DBUtil.h"
#include <sqlite/sqlite3.h>

sqlite3 *pDB = NULL;
char* errMsg = NULL; // error message
int result = SQLITE_OK; // result of sqlite command

int isExistedCallback(void* para, int n_column, char** column_value, char** column_name) {
    bool* isExisted_= (bool*)para;
    *isExisted_ = (**column_value) != '0';
    return 0;
}

int countCallBack(void* para, int n_column, char** column_value, char** column_name) {
    int* count = (int*)para;
    *count = n_column;
    return 0;
}

int queryCallBack(void* para, int column, char** value, char** name) {
    if (!para)
        return 0;

    DBUtilSender* sender = (DBUtilSender*)para;
    sender->queryCallBack(column, value, name);
    return 0;
}

bool DBUtil::openDB(const char* db) {
    if (pDB != NULL)
        closeDB();

    result = sqlite3_open(db, &pDB);
    return result == SQLITE_OK;
}

void DBUtil::closeDB() {
    if (pDB)
        sqlite3_close(pDB);
    pDB = NULL;
}

bool DBUtil::tableExist(string name) {
    if (pDB != NULL) {
        bool tableIsExisted;
        string sql = "select count(type) from sqlite_master where type='table' and name ='"+name+"'";
        result = sqlite3_exec(pDB, sql.c_str(), isExistedCallback, &tableIsExisted, &errMsg);
        return tableIsExisted;
    }
    return false;
}

bool DBUtil::createTable(string sql, string name) {
    if (!tableExist(name)) {
        result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
        return result == SQLITE_OK;
    }
    errMsg = "table already exist";
    return false;
}

bool DBUtil::deleteTable(string name) {
    if (tableExist(name)) {
        string sql = "drop table "+name;
        result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
        return result == SQLITE_OK;
    }
    return true;
}

bool DBUtil::query(string sql, DBUtilSender* pSender) {
    result = sqlite3_exec(pDB, sql.c_str(), queryCallBack, pSender, &errMsg);
    return result == SQLITE_OK;
}

int DBUtil::count(string sql) {
    int count = 0;
    result = sqlite3_exec(pDB, sql.c_str(), countCallBack, &count, &errMsg);
    return count;
}

string DBUtil::errorMessage() {
    return string(errMsg);
}

int DBUtil::resultCode() {
    return result;
}

