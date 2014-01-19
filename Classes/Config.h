/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Config.h
 * $Id: Config.h v 1.0 2013-12-26 14:31:47 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2013-12-27 17:42:34 $
 * @brief
 *
 ******************************************************************/

#ifndef __CONFIG_H_
#define __CONFIG_H_

#define DESIGNED_WIDTH      640
#define DESIGNED_HEIGHT     1067

#define MAX_STAR_COUNT      3
#define MAX_SEASON          10
#define MAX_AVATAR_COUNT    5

#define MIN_MOVE_GAP        3

#define MAP_HEIGHT          1540
#define MAP_CLOUD_SPPED     100
#define MAP_MAX_LEVEL       20
#define LEVEL_PER_MAP       10
#define LEVELNODE_WIDTH     105
#define LEVELNODE_HEIGHT    74

#define MAX_SEASON_LEVEL    24
#define MAX_LEVEL_QUESTION_COUNT    10

#define QUESTIONLAYER_CONTENT_WIDTH     581
#define QUESTIONLAYER_CONTENT_HEIGHT    350
#define QUESTIONLAYER_TITLE_WIDTH       520
#define QUESTIONLAYER_TITLE_HEIGHT      210
#define QUESTIONLAYER_TITLE_SIZE        40

#define OPTIONLAYER_CONTENT_WIDTH   581
#define OPTIONLAYER_CONTENT_HEIGHT  150
#define OPTIONLAYER_SPACING         0
#define OPTION_TEXT_SIZE            28

inline float abs(float a) {
    return a > 0 ? a : -a;
}

#endif // __CONFIG_H_
