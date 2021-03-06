/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Season.cpp
 * $Id: Season.cpp v 1.0 2013-12-26 13:36:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 20:31:43 $
 * @brief
 *
 ******************************************************************/

#include "Config.h"
#include "Season.h"
#include "Question.h"
#include <cocos2d.h>

using namespace cocos2d;

string g_SeasonTitles[MAX_SEASON] = {
    "  第一期   灵水村上 ",
    "  第二期   灵水村下 ",
    "  第三期    沙漠上  ",
    "  第四期    沙漠下  ",
    "  第五期  云南水乡上",
    "  第六期  云南水乡下",
    "  第七期  烟台海岛上",
    "  第八期  烟台海岛下",
    "  第九期   白寺村上 ",
    "  第十期   白寺村下 "
};

QuestionSet* g_SeasonQuestions[MAX_SEASON] = {
    new QuestionSet(QuestionSet::LinShuiCun_1),
    new QuestionSet(QuestionSet::LinShuiCun_2),
    new QuestionSet(QuestionSet::ShaMo_1),
    new QuestionSet(QuestionSet::ShaMo_2),
    new QuestionSet(QuestionSet::YunNanShuiXiang_1),
    new QuestionSet(QuestionSet::YunNanShuiXiang_2),
    new QuestionSet(QuestionSet::YanTaiHaiDao_1),
    new QuestionSet(QuestionSet::YanTaiHaiDao_2),
    new QuestionSet(QuestionSet::BaiSiCun_1),
    new QuestionSet(QuestionSet::BaiSiCun_2)
};

Season::Season(Season::SeasonId id)
    : m_id(id)
    , m_title(g_SeasonTitles[id])
    , m_locked(true)
{
}

Season::~Season() {
    clearLevelData();
}

void Season::initLevels(int startLevel) {
    clearLevelData();

    QuestionSet* q = g_SeasonQuestions[m_id];
    int qCount = q->count();
    int levelCount = qCount / MAX_LEVEL_QUESTION_COUNT+ ((qCount % MAX_LEVEL_QUESTION_COUNT) ? 1 : 0);
    for (int i = 0; i < levelCount; i++) {
        Level* level = new Level(i+startLevel, m_id);
        int start = i * MAX_LEVEL_QUESTION_COUNT;
        int end = start + MAX_LEVEL_QUESTION_COUNT;
        for ( int j = start; j < end && j < qCount; j++) {
            level->addQuestion(q->question(j));
        }
        if (level->level() == 1)
            level->unlock();
        m_levels.insert(pair<int, Level*>(level->level(), level));
    }
}

void Season::initRecord(const SeasonRecord& record) {
    if (record.seasonId != m_id)
        return;

    m_locked = record.locked;

    LevelRecord lr;
    int count = record.record.size();
    for (int i = 0; i < count; i++) {
        lr = record.record[i];
        if (m_levels.find(lr.level) != m_levels.end()) {
            m_levels[lr.level]->initRecord(lr);
        }
    }
}

SeasonRecord Season::record() const {
    SeasonRecord sr;
    sr.seasonId = m_id;
    sr.locked = m_locked;

    map<int, Level*>::const_iterator pos = m_levels.begin();
    for (; pos != m_levels.end(); ++pos) {
        LevelRecord r = pos->second->record();
        sr.record.push_back(pos->second->record());
    }
    return sr;
}

int Season::starCount() const {
    int count = 0;
    map<int, Level*>::const_iterator pos = m_levels.begin();
    for (; pos != m_levels.end(); ++pos) {
        count += pos->second->starCount();
    }
    return count;
}

bool Season::pass() const {
    return m_levels.rbegin()->second->hasPassedOnce();
}

Level* Season::level(int index) {
    if (m_levels.find(index) != m_levels.end())
        return m_levels[index];
    return NULL;
}

void Season::clearLevelData() {
    map<int, Level*>::iterator pos = m_levels.begin();
    for (; pos != m_levels.end(); ++pos) {
        delete pos->second;
        pos->second = NULL;
    }
    m_levels.clear();
}
