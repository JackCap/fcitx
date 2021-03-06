/***************************************************************************
 *   Copyright (C) 2002~2005 by Yuking                                     *
 *   yuking_net@sohu.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/
#ifndef _TABLE_H
#define _TABLE_H

#include "fcitx/configfile.h"
#include "fcitx/ime.h"
#include "fcitx-utils/utarray.h"
#include "tabledict.h"
#include "fcitx/candidate.h"

struct _FcitxInstance;

typedef union _CANDWORD {
    AUTOPHRASE     *autoPhrase;
    RECORD         *record;
    int             iFHIndex;
} CANDWORD;

typedef enum _CANDTYPE {
    CT_NORMAL = 0,
    CT_AUTOPHRASE,
    CT_REMIND,
    CT_FH
} CANDTYPE;

typedef struct _TABLECANDWORD {
    CANDTYPE        flag;   //指示该候选字/词是自动组的词还是正常的字/词
    CANDWORD        candWord;
} TABLECANDWORD;

typedef struct _FcitxTableState {
    UT_array* table; /* 码表 */

    char            iTableIMIndex;
    char            iTableCount;

    char            iCurrentTableLoaded;
    RECORD         *pCurCandRecord; //Records current cand word selected, to update the hit-frequency information

    RECORD_INDEX   *recordIndex;

    char            strTableRemindSource[PHRASE_MAX_LENGTH * UTF8_MAX_LENGTH + 1];

    boolean            bIsTableDelPhrase;
    FcitxHotkey         hkTableDelPhrase[HOT_KEY_COUNT];
    boolean            bIsTableAdjustOrder;
    FcitxHotkey         hkTableAdjustOrder[HOT_KEY_COUNT];
    boolean            bIsTableAddPhrase;
    FcitxHotkey         hkTableAddPhrase[HOT_KEY_COUNT];

    char            iTableNewPhraseHZCount;

    boolean            bTablePhraseTips;

    ADJUSTORDER     PYBaseOrder;
    boolean         isSavingTableDic;

    struct _FcitxInstance* owner;
    struct _FcitxAddon* pyaddon;
    FcitxCandidateWordCommitCallback pygetcandword;
} FcitxTableState;

void            LoadTableInfo(FcitxTableState* tbl);
boolean TableInit(void* arg);
void            SaveTableIM(void* arg);

INPUT_RETURN_VALUE DoTableInput(void* arg, FcitxKeySym sym, unsigned int state);
INPUT_RETURN_VALUE TableGetCandWords(void* arg);
void TableAddCandWord(RECORD * record, TABLECANDWORD* tableCandWord);
void            TableAddAutoCandWord(TableMetaData* table, short int which, TABLECANDWORD* tableCandWord);
INPUT_RETURN_VALUE TableGetRemindCandWords(TableMetaData* table);
void TableAddRemindCandWord(RECORD * record, TABLECANDWORD* tableCandWord);
INPUT_RETURN_VALUE TableGetFHCandWords(TableMetaData* table);
INPUT_RETURN_VALUE TableGetPinyinCandWords(TableMetaData* table);
void            TableResetStatus(void* arg);
INPUT_RETURN_VALUE TableGetRemindCandWord(void* arg, TABLECANDWORD* tableCandWord);
INPUT_RETURN_VALUE TableGetFHCandWord(TableMetaData* table, TABLECANDWORD* tableCandWord);
void TableAdjustOrderByIndex(TableMetaData* table, TABLECANDWORD* tableCandWord);
void            TableDelPhraseByIndex(TableMetaData* table, TABLECANDWORD* tableCandWord);
void            TableCreateNewPhrase(TableMetaData* table);
INPUT_RETURN_VALUE _TableGetCandWord(TableMetaData* table, TABLECANDWORD* tableCandWord, boolean _bRemind);
INPUT_RETURN_VALUE TableGetCandWord(void* arg, FcitxCandidateWord* candWord);
boolean            TablePhraseTips(void* arg);
void            TableSetCandWordsFlag(TableMetaData* table, int iCount, boolean flag);

void            UpdateHZLastInput(TableMetaData* table, char* str);

FcitxConfigFileDesc *GetTableConfigDesc();

#endif

// kate: indent-mode cstyle; space-indent on; indent-width 0;
