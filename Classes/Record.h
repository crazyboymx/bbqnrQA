/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Record.h
 * $Id: Record.h v 1.0 2013-12-26 14:31:47 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 21:44:04 $
 * @brief
 *
 ******************************************************************/

#ifndef __RECORD_H_
#define __RECORD_H_

#include <vector>
#include <map>

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
    SeasonRecord()
        : seasonId(-1)
        , locked(true)
    {
    }
};

class Record {
public:
    static Record* instance();
    virtual ~Record() { }

    void load();
    void save();
    void addSeasonRecord(const SeasonRecord& record);
    SeasonRecord* seasonRecord(int id);

protected:
    Record() { }
    Record(const Record&) { }

private:
    map<int, SeasonRecord> m_record;
    static Record* m_instance;
};

#endif // __RECORD_H_
