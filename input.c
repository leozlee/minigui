//
// Created by leo on 9/6/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <mgi/mgi.h>

#define IDC_BASE 20000
#ifndef IDC_STATIC
#define IDC_STATIC 21000
#endif
#define IDC_EDT_ADDR 21100

HWND g_hIMEWnd = 0UL;

static DLGTEMPLATE s_DlgBox_DlgPing =
		{
				WS_BORDER | WS_CAPTION,
				WS_EX_NONE,
				200, 225, 400, 180,
				"Ping",
				0, 0,
				4,
				NULL,
				0
		};

static CTRLDATA s_DlgCtrl_DlgPing[] =
		{
				{
						"button",
						WS_VISIBLE | WS_TABSTOP ,
						47, 91, 100, 28,
						IDOK,
						"确定",
						0
				},
				{
						"button",
						WS_VISIBLE | WS_TABSTOP ,
						217, 91, 100, 28,
						IDCANCEL,
						"取消",
						0
				},
				{
						"sledit",
						WS_VISIBLE | WS_TABSTOP | WS_BORDER,
						127, 40, 199, 30,
						IDC_EDT_ADDR,
						"",
						0
				},
				{
						"static",
						WS_VISIBLE | WS_TABSTOP ,
						42, 42, 70, 34,
						IDC_STATIC,
						"IP地址",
						0
				},
		};

static HWND sk_ime_hwnd;
static BOOL g_ime_opened = FALSE;
static void edit_notif_proc(HWND hDlg, int id, int nc, DWORD add_data)
{
	IME_TARGET_INFO ime_t_info;
	//edit控件的消息处理函数中打印caret的位置
	GetIMETargetInfo(&ime_t_info);
	printf("ime_t_info.ptCaret: (%d, %d)\n", ime_t_info.ptCaret.x, ime_t_info.ptCaret.y);
}

void notify_ime_status(BOOL opened)
{
	g_ime_opened = opened;
}

static int DialogBox_DlgPing_Proc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			g_hIMEWnd  = hDlg;
			SetNotificationCallback (GetDlgItem (hDlg, IDC_EDT_ADDR), edit_notif_proc);
			sk_ime_hwnd = mgiCreateSoftKeypad(notify_ime_status);
			SetFocusChild(GetDlgItem(hDlg, IDC_EDT_ADDR));
			//SetIMEStatus(IME_STATUS_AUTOTRACK, TRUE);
			SetIMEStatus(IME_STATUS_ENCODING, IME_ENCODING_LOCAL);
			SetIMEStatus(IME_STATUS_ENABLED, TRUE);
			return 1;
		case MSG_CLOSE:
			EndDialog(hDlg, IDCANCEL);
			break;
	}

	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

int MiniGUIMain(int args, const char* arg[])
{
	s_DlgBox_DlgPing.controls = s_DlgCtrl_DlgPing;

	SetDefaultWindowElementRenderer("skin");

	DialogBoxIndirectParam(&s_DlgBox_DlgPing, HWND_DESKTOP, DialogBox_DlgPing_Proc, 0);
	return 0;
}