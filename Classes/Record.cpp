/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Record.cpp
 * $Id: Record.cpp v 1.0 2013-12-26 14:33:02 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 18:37:27 $
 * @brief
 *
 ******************************************************************/

#include "Record.h"
#include <cocos2d.h>
#include <cstdio>

//USING_NS_CC;

Record* Record::m_instance = NULL;

Record* Record::instance() {
    if (m_instance == NULL)
        m_instance = new Record();
    return m_instance;
}

void Record::load() {
    string dbPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath() + "save.db";
    //cocos2d::CCLog("dbPath: %s", dbPath.c_str());
    FILE* fp = fopen(dbPath.c_str(), "rb");
    if (fp == NULL)
        return;

    int count, levelCnt;
    LevelRecord lr;
    fread(&this->m_totalPass, sizeof(uint32_t), 1, fp);
    fread(&this->m_totalFail, sizeof(uint32_t), 1, fp);
    fread(&count, sizeof(uint32_t), 1, fp);
    for (int i = 0; i < count; ++i) {
        SeasonRecord sr;
        fread(&sr.seasonId, sizeof(uint32_t), 1, fp);
        fread(&sr.locked, sizeof(bool), 1, fp);
        fread(&levelCnt, sizeof(uint32_t), 1, fp);
        for (int j = 0; j < levelCnt; ++j) {
            fread(&lr, sizeof(LevelRecord), 1, fp);
            sr.record.push_back(lr);
        }
        addSeasonRecord(sr);
    }
    fclose(fp);
}

void Record::save() {
    string dbPath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath() + "save.db";
    //cocos2d::CCLog("dbPath: %s", dbPath.c_str());
    FILE* fp = fopen(dbPath.c_str(), "wb");
    if (fp == NULL)
        return;

    int count = m_record.size();
    fwrite(&this->m_totalPass, sizeof(uint32_t), 1, fp);
    fwrite(&this->m_totalFail, sizeof(uint32_t), 1, fp);
    fwrite(&count, sizeof(uint32_t), 1, fp);
    map<int, SeasonRecord>::iterator pos = m_record.begin();
    for (; pos != m_record.end(); ++pos) {
        fwrite(&(pos->second.seasonId), sizeof(uint32_t), 1, fp);
        fwrite(&(pos->second.locked), sizeof(bool), 1, fp);
        int levelCnt = pos->second.record.size();
        fwrite(&levelCnt, sizeof(uint32_t), 1, fp);
        for (int i = 0; i < levelCnt; ++i) {
            fwrite(&(pos->second.record[i]), sizeof(LevelRecord), 1, fp);
        }
    }
    fclose(fp);
}

void Record::addSeasonRecord(const SeasonRecord& record) {
    m_record[record.seasonId] = record;
}

SeasonRecord* Record::seasonRecord(int id) {
    if (m_record.find(id) != m_record.end())
        return &m_record[id];
    return NULL;
}

