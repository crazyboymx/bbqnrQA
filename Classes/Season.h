/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Season.h
 * $Id: Season.h v 1.0 2013-12-26 11:03:41 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 16:58:54 $
 * @brief
 *
 ******************************************************************/

#ifndef __SEASON_H__
#define __SEASON_H__

#include "Level.h"
#include "Record.h"
#include <map>
#include <string>

using namespace std;

class Season {
public:
    enum SeasonId {
        Season_1,
        Season_2,
        Season_3,
        Season_4,
        Season_5,
        Season_6,
        Season_7,
        Season_8,
        Season_9,
        Season_10,
        MaxSeason
    };
    static int seasonCount() { return MaxSeason; }

    Season(SeasonId id);
    virtual ~Season();

    void initLevels();
    void initRecord(const SeasonRecord& record);
    SeasonRecord record() const;

    string title() const { return m_title; }
    int levelCount() const { return m_levels.size(); }
    int starCount() const;
    bool pass() const;
    Level* level(int index);

    void unlock() { m_locked = false; }
    bool locked() const { return m_locked; }

private:
    void clearLevelData();

private:
    SeasonId m_id;
    bool m_locked;

    string m_title;
    map<int, Level*> m_levels;
};

#endif // __SEASON_H__
