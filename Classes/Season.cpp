/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Season.cpp
 * $Id: Season.cpp v 1.0 2013-12-26 13:36:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 14:35:17 $
 * @brief
 *
 ******************************************************************/

#include "Season.h"
#include "Question.h"

#define LEVEL_QUESTION_MAX_COUNT    10

string g_SeasonTitles[Season::MaxSeason] = {
    "第一期灵水村上",
    "第二期灵水村下",
    "第三期沙漠上",
    "第四期沙漠下",
    "第五期云南水乡上",
    "第六期云南水乡下",
    "第七期烟台海岛上",
    "第八期烟台海岛下",
    "第九期白寺村上",
    "第十期白寺村下"
};

QuestionSet* g_SeasonQuestions[Season::MaxSeason] = {
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

Season::Season(Season::SeasonType type)
    : m_type(type)
    , m_title(g_SeasonTitles[type])
{
    initLevels();
}

Season::~Season() {
    clearLevelData();
}

void Season::initLevels() {
    QuestionSet* q = g_SeasonQuestions[m_type];
    int qCount = q->count();
    int levelCount = qCount / LEVEL_QUESTION_MAX_COUNT+1;
    for (int i = 0; i < levelCount; i++) {
        Level* level = new Level(i+1);
        int start = i * LEVEL_QUESTION_MAX_COUNT;
        int end = start + LEVEL_QUESTION_MAX_COUNT;
        for ( int j = start; j < end && j < qCount; j++) {
            level->addQuestion(q->question(j));
        }
        m_levels.push_back(level);
    }
}

void Season::initRecord(const SeasonRecord& record) {
}

int Season::starCount() const {
    int count = 0;
    for (int i = levelCount() - 1; i >= 0; i--) {
        count += m_levels[i]->starCount();
    }
    return count;
}

bool Season::pass() const {
    return m_levels[levelCount()-1]->hasPassedOnce();
}

Level* Season::level(int index) {
    if (index >= 0 && index < levelCount())
        return m_levels[index];
    return NULL;
}

void Season::clearLevelData() {
    for (int i = levelCount() - 1; i >= 0; i--) {
        delete m_levels[i];
    }
    m_levels.clear();
}
