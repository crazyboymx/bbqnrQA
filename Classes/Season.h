/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Season.h
 * $Id: Season.h v 1.0 2013-12-26 11:03:41 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 14:36:26 $
 * @brief
 *
 ******************************************************************/

#ifndef __SEASON_H__
#define __SEASON_H__

#include "Level.h"
#include "Record.h"
#include <vector>
#include <string>

using namespace std;

class Season {
public:
    enum SeasonType {
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

    Season(SeasonType type);
    virtual ~Season();

    void initLevels();
    void initRecord(const SeasonRecord& record);

    string title() const { return m_title; }
    int levelCount() const { return m_levels.size(); }
    int starCount() const;
    bool pass() const;
    Level* level(int index);

private:
    void clearLevelData();

private:
    SeasonType m_type;
    string m_title;
    vector<Level*> m_levels;
};

#endif // __SEASON_H__
