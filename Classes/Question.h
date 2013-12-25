/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Question.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-25 10:10:03 $
 * @brief
 *
 ******************************************************************/

#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <string>

using namespace std;

struct Option {
    int answer;
    string opt_a;
    string opt_b;
    string opt_c;
    string opt_d;
};

class QuestionSet {
public:
    enum Subject {
        LinShuiCun_1,
        LinShuiCun_2,
        ShaMo_1,
        ShaMo_2,
        YunNanShuiXiang_1,
        YunNanShuiXiang_2,
        YanTaiHaiDao_1,
        YanTaiHaiDao_2,
        BaiSiCun_1,
        BaiSiCun_2
    };

    QuestionSet(Subject sub);

    string question(int index);
    Option option(int index);
    int count() const { return m_count;}
private:
    Subject m_subject;
    string *m_questions;
    Option *m_options;
    int     m_count;
};

#endif //__QUESTION_H__
