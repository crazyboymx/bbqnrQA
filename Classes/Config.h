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

#define DESIGNED_WIDTH      480
#define DESIGNED_HEIGHT     800

#define LEVELNODE_WIDTH     DESIGNED_WIDTH / 4
#define LEVELNODE_HEIGHT    LEVELNODE_WIDTH

#define MAX_SEASON_LEVEL    24
#define MAX_LEVEL_QUESTION_COUNT    10

#define GAMELAYER_QUESTION_WIDTH    DESIGNED_WIDTH - 60
#define GAMELAYER_QUESTION_HEIGHT   200
#define QUESTION_TEXT_SIZE          32

#define OPTIONLAYER_CONTENT_WIDTH   DESIGNED_WIDTH - 20
#define OPTIONLAYER_CONTENT_HEIGHT  100
#define OPTIONLAYER_SPACING         30
#define OPTION_TEXT_SIZE            24

#endif // __CONFIG_H_
