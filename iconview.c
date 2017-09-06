/*
** $Id: iconview.c 741 2009-03-31 07:16:18Z weiym $
**
** iconview.c: Sample program for MiniGUI Programming Guide
**      Usage of ICONVIEW control.
**
** Copyright (C) 2004 ~ 2007 Feynman Software.
**
** License: GPL
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define _LANG_ZHCN

#ifdef _LANG_ZHCN
#include "iconview_res_cn.h"
#elif defined _LANG_ZHTW
#include "iconview_res_tw.h"
#else
#include "iconview_res_en.h"
#endif

#define IDC_ICONVIEW                100
#define IDC_BT                       200
#define IDC_BT2                      300
#define IDC_BT3                      400
#define IDC_BT4                      500

#define IDC_ADD                     600
#define IDC_DELETE                  601


#define ICON_NUM    8

#define BUTTON_WIDTH    60
#define BUTTON_HEIGHT   60


static HWND hIconView;

static BITMAP myicons [ICON_NUM];

static const char* iconfiles[ICON_NUM] =
{
		"./res/acroread.png",
		"./res/icons.png",
		"./res/looknfeel.png",
		"./res/package_games.png",
		"./res/tux.png",
		"./res/xemacs.png",
		"./res/gimp.png",
		"./res/kpilot.png"
};

static const char *iconlabels[ICON_NUM] =
{
    "录像检索",
    "录像设置",
    "功能设置",
    "系统信息",
    "车辆管理",
    "显示设置",
    "密码管理",
    "退   出"
};

#if 0
static void myDrawItem (HWND hWnd, GHANDLE hsvi, HDC hdc, RECT *rcDraw)
{
    const PBITMAP pbmp = (PBITMAP)iconview_get_item_bitmap (hsvi);
    const char *label = (const char*)iconview_get_item_label (hsvi);
    
    SetBkMode (hdc, BM_TRANSPARENT);
    SetTextColor (hdc, PIXEL_black);

    if (iconview_is_item_hilight(hWnd, hsvi)) {
        SetBrushColor (hdc, PIXEL_blue);
    }
    else {
        SetBrushColor (hdc, PIXEL_lightwhite);
    }
    FillBox (hdc, rcDraw->left, rcDraw->top, RECTWP(rcDraw), RECTHP(rcDraw));
    SetBkColor (hdc, PIXEL_blue);
    
    if (label) {
        RECT rcTxt = *rcDraw;
        rcTxt.top = rcTxt.bottom - GetWindowFont (hWnd)->size * 2;
        rcTxt.left = rcTxt.left - (GetWindowFont (hWnd)->size) + 2;

        DrawText (hdc, label, -1, &rcTxt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }
    FillBoxWithBitmap (hdc, rcDraw->left, rcDraw->top, 0, 0, pbmp);
}
#endif

static int BookProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    case MSG_INITDIALOG:
    {
        IVITEMINFO ivii;
        static int i = 0, j = 0;

        hIconView = GetDlgItem (hDlg, IDC_ICONVIEW);
        SetWindowBkColor (hIconView, PIXEL_lightwhite);
        //SendMessage (hIconView, IVM_SETITEMDRAW, 0, (LPARAM)myDrawItem);
        SendMessage (hIconView, IVM_SETITEMSIZE, 55, 65);
        //SendMessage (hIconView, IVM_SETITEMSIZE, 35, 35);
        for (j = 0; j < 3; j ++) {
            for (i = 0; i < TABLESIZE(myicons); i++) {
                memset (&ivii, 0, sizeof(IVITEMINFO));
                ivii.bmp = &myicons[i];
                ivii.nItem = 12 * j + i;
                ivii.label = iconlabels[i];
                ivii.addData = (DWORD)iconlabels[i];
                SendMessage (hIconView, IVM_ADDITEM, 0, (LPARAM)&ivii);
            }
        }
        break;
    }

    case MSG_COMMAND:
    {
        int id = LOWORD (wParam);
        int code = HIWORD (wParam);

        switch (id) {
        case IDC_ICONVIEW:
            if (code == IVN_CLICKED) {
                int sel;
                sel = SendMessage (hIconView, IVM_GETCURSEL, 0, 0);
            }
            break;
        case IDC_ADD:
        {
            IVITEMINFO ivii;
            char buff [10];
            int idx;
            int count = SendMessage (hIconView, IVM_GETITEMCOUNT, 0, 0);
            
            sprintf (buff, "NewIcon%i", count);
            memset (&ivii, 0, sizeof (IVITEMINFO));
            ivii.bmp = &myicons [0];
            ivii.nItem = count;
            ivii.label = buff;
            ivii.addData = (DWORD)"NewIcon";

            idx = SendMessage (hIconView, IVM_ADDITEM, 0, (LPARAM)&ivii);
            SendMessage (hIconView, IVM_SETCURSEL, idx, 1);
            break;
        }

        case IDC_DELETE:
        {
            int sel = SendMessage (hIconView, IVM_GETCURSEL, 0, 0);
            int count = SendMessage (hIconView, IVM_GETITEMCOUNT, 0, 0);
            char *label = NULL;

            if (sel >= 0){
                label = (char *) SendMessage (hIconView, IVM_GETITEMADDDATA, sel, 0); 
                SendMessage (hIconView, IVM_DELITEM, sel, 0);
                if (sel == count - 1)
                    sel --;
                SendMessage (hIconView, IVM_SETCURSEL, sel, 1);
            }
            break;
        }

        } /* end command switch */
        break;
    }

    case MSG_KEYDOWN:
        if (wParam == SCANCODE_REMOVE) {
            int cursel = SendMessage (hIconView, IVM_GETCURSEL, 0, 0);
            
            if (cursel >= 0){
                SendMessage (hIconView, IVM_DELITEM, cursel, 0);
                SendMessage (hIconView, IVM_SETCURSEL, cursel, 0);
            }
        }
        break;

    case MSG_CLOSE:
    {
        EndDialog (hDlg, 0);
        return 0;
    }

    } /* end switch */

    return DefaultDialogProc (hDlg, message, wParam, lParam);
}


static CTRLDATA CtrlBook[] = //对话框中的组件数组
{
//   {
//      CTRL_ICONVIEW,
//      WS_BORDER | WS_CHILD | WS_VISIBLE,
//         10, 10, 290, 300,
//       IDC_ICONVIEW,
//        "",
//       0
//    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE | BS_ICON,
        30, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu1,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        140, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu2,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        250, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu3,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        360, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu4,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        30, 140, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu5,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        140, 140, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu6,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        250, 140, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu7,
        0
    },
    {
        CTRL_BUTTON,
        WS_CHILD | WS_VISIBLE,
        360, 140, BUTTON_WIDTH, BUTTON_HEIGHT,
        IDC_ADD,
        submenu8,
        0
    },
};

static DLGTEMPLATE DlgIcon =//DLGTEMPLATE 对话框模板
{
    WS_CAPTION | WS_DLGFRAME,      //样式
    WS_EX_NOCLOSEBOX,              //附加样式
    0, 0,480,272,                  //位置及大小
    capture,                       //标题
    0, 0,                          //图标及菜单？
    TABLESIZE(CtrlBook), CtrlBook,//控件的数量以及指针
    0                             //这个默认为0
};




//函数入口
int MiniGUIMain (int argc, const char* argv[])
{
    int i;

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "iconview" , 0 , 0);
#endif
    
    for (i=0; i<TABLESIZE(myicons); i++) {
        LoadBitmap(HDC_SCREEN, &myicons[i], iconfiles[i]);
    }

    DialogBoxIndirectParam (&DlgIcon, HWND_DESKTOP, BookProc, 0L);//创建窗口的函数
    //描述对话窗口的结构体，主窗口的句柄，回调函数，第二信息参数
    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

