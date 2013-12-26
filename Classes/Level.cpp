/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Level.cpp
 * $Id: Level.cpp v 1.0 2013-12-26 10:11:14 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 17:22:59 $
 * @brief
 *
 ******************************************************************/

#include "Level.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

Level::Level(int level) {
    m_level = level;
    m_locked = true;
    m_passCountRecord = 0;
    resetProgress();
}

Level::~Level() {
}

void Level::clearQuestions() {
    m_questions.clear();
}

void Level::addQuestion(Question q) {
    m_questions.push_back(q);
}

void Level::resetProgress() {
    m_passCount = 0;
    m_failCount = 0;
    m_progress = 0;
}

void Level::resetRecord() {
    m_passCountRecord = 0;
    m_locked = true;
}

void Level::initRecord(const LevelRecord& record) {
    if (record.level != m_level)
        return;

    m_passCountRecord = record.passCount;
    m_locked = record.locked;
}

LevelRecord Level::record() const {
    LevelRecord lr;
    lr.level = m_level;
    lr.locked = m_locked;
    lr.passCount = m_passCountRecord;
}

bool Level::fail() const {
    return m_failCount >= questionCount() / 2;
}

void Level::passCurrentQuestion() {
    m_passCount++;
    if (m_passCount > m_passCountRecord)
        m_passCountRecord = m_passCount;
}

void Level::failCurrentQuestion() {
    m_failCount++;
}

Question Level::nextQuesion() {
    if (currentProgress() >= questionCount())
        return Question();

    return m_questions[m_progress++];
}

Question Level::prevQuesion() {
    if (currentProgress() < 0)
        return Question();

    return m_questions[m_progress--];
}

void Level::shuffleQuestion() {
    srandom(time(NULL));
    int count = questionCount();
    for (int i = 0; i < count; i++) {
        int pos = random() % count;
        if (pos != i)
            swap(m_questions[i], m_questions[pos]);
    }
}

int Level::evaluateStars(int passCount) const {
    int count = questionCount();
    if (passCount >= count) {
        return 3;
    }
    else if (passCount >= (count - 2) ) {
        return 2;
    }
    else if (pass(passCount)) {
        return 1;
    }

    return 0;
}

bool Level::pass(int passCount) const {
    return passCount > questionCount();
}

