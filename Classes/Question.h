/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Question.h
 * $Id: Question.h v 1.0 2013-12-25 09:12:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-26 10:50:22 $
 * @brief
 *
 ******************************************************************/

#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <string>
#include <vector>

using namespace std;

struct Option {
    int     answer;
    string  opt_a;
    string  opt_b;
    string  opt_c;
    string  opt_d;

    string operator[] (int index) {
        if (index == 1)
            return opt_a;
        else if (index == 2)
            return opt_b;
        else if (index == 3)
            return opt_c;
        else if (index == 4)
            return opt_d;
        else
            return "";
    }
};

struct Question {
    int id;
    string question;
    Option option;
    bool valid;
    Question() : valid(false) { }
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
        BaiSiCun_2,
        MaxSubject
    };

    QuestionSet(Subject sub);

    Question question(int index);
    int count() const { return m_count;}
private:
    Subject m_subject;
    vector<Question> m_questions;
    int     m_count;
};

#endif //__QUESTION_H__
