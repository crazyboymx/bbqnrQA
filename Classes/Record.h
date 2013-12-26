/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Record.h
 * $Id: Record.h v 1.0 2013-12-26 14:31:47 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 19:36:58 $
 * @brief
 *
 ******************************************************************/

#ifndef __RECORD_H_
#define __RECORD_H_

#include <vector>
#include <map>
#include "DBUtil.h"

using namespace std;

struct LevelRecord {
    int level;
    int passCount;
    bool locked;
};

struct SeasonRecord {
    int seasonId;
    bool locked;
    vector<LevelRecord> record;
};

class Record : private DBUtilSender {
public:
    Record() { };
    virtual ~Record() { }

    void load();
    void save();
    void setSeasonRecord(const SeasonRecord& record);

private:
    virtual void queryCallBack(int column, char** value, char** name);

private:
    map<int, SeasonRecord> m_record;
};

#endif // __RECORD_H_
