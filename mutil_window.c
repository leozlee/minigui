//
// Created by leo on 9/7/17.
//

/*MINIGUi   sample mitwindows*/

#include <stdio.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#define IDC_BUTTON1                102   //��ť
#define IDC_BUTTON2                103   //��ť
#define IDC_BUTTON3                104   //��ť
#define IDC_BUTTON4                105   //��ť
#define IDC_FANHUI                 106   //��ť
#define IDC_MAINMENU               107   //�˵�

static char *hello_str = "Hello MiniGUI!";

static HWND hMainWnd; //���ھ��

static DLGTEMPLATE Dlgweihu= //DLGTEMPLATE �Ի���ģ��
        {
                WS_BORDER | WS_CAPTION,
                WS_EX_NONE,
                0, 0, 320, 240,
                "ϵͳά��",
                0, 0,
                2, NULL,
                0
        };static CTRLDATA Ctrlweihu[] = //�Ի����е��������
        {
                {
                        "button",
                        WS_VISIBLE | WS_TABSTOP | WS_GROUP,
                        200, 150, 50, 30,
                        IDC_FANHUI,
                        "����",
                        0
                },   {
                        "button",
                        WS_VISIBLE | WS_TABSTOP | WS_GROUP,
                        20, 150, 50, 30,
                        IDC_MAINMENU,
                        "���˵�",
                        0
                },

        };//=====================================================�ص�����==DialogBoxProc3

static int DialogBoxProc3 (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case MSG_INITDIALOG:
            return 1;
        case MSG_COMMAND:
        {
            int id = LOWORD (wParam);
            int code = HIWORD (wParam);
            switch (wParam)
            {
                case IDC_MAINMENU:
                    // if (id==IDC_MAINMENU && code==BN_CLICKED)
                    if (id == IDC_MAINMENU && code == BN_DBLCLK)
                        // if (id==IDC_MAINMENU && code==BN_PUSHED)
                    {
                        SetWindowText(hDlg,"Hello world!");
                    }
                    break;
                case IDC_FANHUI:
                case IDOK:
                case IDCANCEL:
                    EndDialog (hDlg, wParam);//�����Ի���
                    break;
            }

            break;
        }
    }
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}
//=====================================================================

static void testDialogBox3 (HWND hWnd)
{
    Dlgweihu.controls = Ctrlweihu; /*dialog   controls */

    DialogBoxIndirectParam (&Dlgweihu, hWnd, DialogBoxProc3, 0L);
}
//�±��ǵڶ������ڵĴ���******************************************************************

static HWND hMainWnd1 = HWND_INVALID;

static int InitOrderProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)   //�ڶ���������Ϣ
{

    switch (message) {
        case MSG_CREATE:
            CreateWindow (CTRL_BUTTON,
                          "�����ϼ�����",
                          WS_CHILD | BS_PUSHBUTTON | BS_CHECKED | WS_VISIBLE,
                          IDC_BUTTON3, /*button 3*/
                          10, 70, 80, 20, hWnd, 0);

            CreateWindow (CTRL_BUTTON,
                          "������������",
                          WS_CHILD | BS_PUSHBUTTON | BS_CHECKED | WS_VISIBLE,
                          IDC_BUTTON4, /*Button 4 */
                          100, 70, 80, 20, hWnd, 0);
            break;

        case MSG_COMMAND:
        {//-----------------Event
            int id    = LOWORD(wParam);
            int code = HIWORD(wParam);
            char buffer [256];
            sprintf (buffer, "ID: %d, Code: %x", id, code);
            switch (id)
            {
                case (IDC_BUTTON3):
                    SendMessage (hWnd, MSG_CLOSE, 0, 0);
                    break;
                case (IDC_BUTTON4):
                    if(code == BN_CLICKED)

                    {
                        testDialogBox3 (hWnd);
                    }
                    break;
                default:
                    break;
            }
        }
            break;

        case MSG_DESTROY:
            DestroyAllControls (hWnd);
            hMainWnd1 = HWND_INVALID;
            return 0;

        case MSG_CLOSE:
            DestroyMainWindow (hWnd);
            MainWindowCleanup (hWnd);
            return 0;
    }
    return DefaultMainWinProc (hWnd, message, wParam, lParam);
}
//=============================================================================

static void InitCreateInfoTWO (PMAINWINCREATE pCreateInfo)
{
    pCreateInfo->dwStyle = WS_CHILD | WS_BORDER | WS_VISIBLE | WS_CAPTION;
    pCreateInfo->dwExStyle = WS_EX_NONE;
    pCreateInfo->spCaption = "�ڶ�������";
    pCreateInfo->hMenu = 0;
    pCreateInfo->hCursor = GetSystemCursor(1);
    pCreateInfo->hIcon = 0;
    pCreateInfo->MainWindowProc = InitOrderProc; //����ص�����
    pCreateInfo->lx = 0;
    pCreateInfo->ty = 0;
    pCreateInfo->rx = 320;
    pCreateInfo->by = 240;
    pCreateInfo->iBkColor = COLOR_lightwhite;
    pCreateInfo->dwAddData = 0;
    pCreateInfo->hHosting = hMainWnd;
}
//=============================================================================
void orderdesk (HWND hwnd)
{
    MAINWINCREATE CreateInfo2; //�½�һ������

    InitCreateInfoTWO (&CreateInfo2);
    hMainWnd1 = CreateMainWindow (&CreateInfo2);//��������

    if (hMainWnd1 != HWND_INVALID)
    {
        ShowWindow (hMainWnd1, SW_SHOWNORMAL); //��ʾ����
        return;
    }
}
//=====================================================================================
//************************************************************************�����ڻص�����
static int HelloWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    RECT rc;
    switch (message) {

        case MSG_CREATE:
            CreateWindow (CTRL_BUTTON,//============CTRL_BUTTON ��ť
                          "�ڶ�������",
                          WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                          IDC_BUTTON1,//=========================��ťID=IDC_BUTTON1
                          10, 70, 80, 20, hWnd, 0);

            CreateWindow (CTRL_BUTTON,//============CTRL_BUTTON ��ť
                          "�ر�",
                          WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                          IDC_BUTTON2,//=========================��ťID=IDC_BUTTON2
                          100, 70, 80, 20, hWnd, 0);
            break;

        case MSG_COMMAND:
        {
            int id    = LOWORD(wParam);//��
            int code = HIWORD(wParam);//��
            //printf ("Notification from buttons: ID: %d, Code: %x\n", id, code);
            switch (id)
            {

                case IDC_BUTTON1:
                    printf ("opendisk: ID: %d, Code: %x\n", id, code);
                    orderdesk(hWnd);   //======================================��������
                    break;

                case IDC_BUTTON2:
                    SendMessage (hWnd, MSG_CLOSE, 0, 0L);//������Ϣ
                    break;
                default:
                    break;
            }
            break;
        }
            break;



        case MSG_PAINT://��
            hdc = BeginPaint (hWnd);
            GetClientRect (hWnd, &rc);
            DrawText (hdc, hello_str, -1, &rc, DT_LEFT);
            EndPaint (hWnd, hdc);

            break;

        case MSG_CLOSE:
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            break;
    }


    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}
//===========================================================================������


static void InitCreateInfo (PMAINWINCREATE pCreateInfo)
{

    pCreateInfo->dwStyle = WS_CAPTION|WS_BORDER|WS_SYSMENU;
    pCreateInfo->dwExStyle = WS_EX_NONE;
    pCreateInfo->spCaption = "���ǵ�һ������";
    pCreateInfo->hMenu = 0;
    pCreateInfo->hCursor = GetSystemCursor (0);
    pCreateInfo->hIcon = 0;
    pCreateInfo->MainWindowProc = HelloWinProc;//���ڻص�����
    pCreateInfo->lx = 0;
    pCreateInfo->ty = 0;
    pCreateInfo->rx = 320;
    pCreateInfo->by = 240;
    pCreateInfo->iBkColor = COLOR_lightwhite;
    pCreateInfo->dwAddData = 0;
    pCreateInfo->hHosting = HWND_DESKTOP;//======1
}//========================================================================

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    MAINWINCREATE CreateInfo;

#ifdef _LITE_VERSION
    SetDesktopRect(0, 0, 1024, 768);
#endif


    InitCreateInfo (&CreateInfo);

    hMainWnd = CreateMainWindow (&CreateInfo);
    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);
    printf ("The main window showed.\n");
//==================================================================
    while (GetMessage(&Msg, hMainWnd))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup (hMainWnd);


    return 0;
}
#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif

