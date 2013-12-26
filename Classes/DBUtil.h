/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: DBUtil.h
 * $Id: DBUtil.h v 1.0 2013-12-26 18:18:28 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 19:36:38 $
 * @brief
 *
 ******************************************************************/

#ifndef __DBUTIL__H_
#define __DBUTIL__H_

#include <string>

using namespace std;

class DBUtilSender {
public:
    DBUtilSender() { };
    virtual ~DBUtilSender() { }
    virtual void queryCallBack(int column, char** value, char** name) { }
};

class DBUtil {
public:
    static bool openDB(const char* db);
    static void closeDB();
    static bool tableExist(string name);
    static bool createTable(string name, string sql);
    static bool deleteTable(string name);
    static bool query(string sql, DBUtilSender* pSender);
    static int count(string sql);

    static string errorMessage();
    static int resultCode();
};

#endif // __DBUTIL__H_
