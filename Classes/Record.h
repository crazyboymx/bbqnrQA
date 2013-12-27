/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Record.h
 * $Id: Record.h v 1.0 2013-12-26 14:31:47 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:42:34 $
 * @brief
 *
 ******************************************************************/

#ifndef __RECORD_H_
#define __RECORD_H_

#include <vector>
#include <map>

using namespace std;

struct Config {
    bool mute;
    bool bgMusic;
};

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
    void incTotalPass() { m_totalPass++; }
    void incTotalFail() { m_totalFail++; }
    void addSeasonRecord(const SeasonRecord& record);
    SeasonRecord* seasonRecord(int id);

protected:
    Record() : m_totalPass(0), m_totalFail(0) { }
    Record(const Record&) { }

private:
    Config m_config;
    map<int, SeasonRecord> m_record;
    int m_totalPass;
    int m_totalFail;
    static Record* m_instance;
};

#endif // __RECORD_H_
