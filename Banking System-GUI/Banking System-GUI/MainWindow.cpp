#include <sstream>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <atlbase.h>
#include <stdio.h>
#include <WinUser.h>


#include "resource.h"
#include "resource1.h"
#include "System.h"

// Global variables


// Show All Accounts

LRESULT CALLBACK Dialog_Show_Accounts_Procedure(HWND, UINT, WPARAM, LPARAM);

void Register_Show_Accounts_Dialog_Class(HINSTANCE);
void Display_Show_Accounts_Dialog(const HWND, LPCSTR, LPCSTR, LPCSTR);


// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Banking System GUI");
TCHAR WMessage;

void AddMenu(HWND);
HMENU hMENU;
HINSTANCE hInst;

// Open Account Dialog Controls

HWND hEditAccountFirstName;
HWND hEditAccountLastName;
HWND hEditAccountBalance;

// Close Account Dialog Controls

HWND hCloseAccountNumber;

// Deposit Dialog Controls

HWND hDepositAccountNumber;
HWND hDepositAmountMoney;

// Withdraw Dialog Controls

HWND hWithdrawAccountNumber;
HWND hWithdrawAmountMoney;

// Balance Enquiry (ID)

HWND hBalanceEnquiryID;

// balance Enquiry (Number)

HWND hBalanceEnquiryNO;

// All Accounts

LRESULT CALLBACK Dialog_Show_Accounts_Procedure(HWND, UINT, WPARAM, LPARAM);

void Display_Show_Accounts_Dialog(HWND);
void Register_Show_Accounts_Dialog_Class(HINSTANCE);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    DialogOpenAccountProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DialogCloseAccountProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    OnAccount(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ClseAccount(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    DialogDepositProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DialogWithdrawProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    DialogBalanceEnquiryIDProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DialogBalanceEnquiryNOProcedure(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    DialogBalanceEnquiryProcedure(HWND, UINT, WPARAM, LPARAM);
// Forward declarations of functions included in this code module:
void RegisterOpenAccountDialogClass(HINSTANCE);
void DisplayOpenAccountDialog(HWND hDlg);
void RegisterCloseAccountDialogClass(HINSTANCE);
void DisplayCloseAccountDialog(HWND hDlg);

void RegisterDepositDialogClass(HINSTANCE);
void DisplayDepositDialog(HWND);
void RegisterWithdrawDialogClass(HINSTANCE);
void DisplayWithdrawDialog(HWND);

void RegisterBalanceEnquiryIDDialogClass(HINSTANCE);
void DisplayBalanceEnquiryIDDialog(HWND);
void RegisterBalanceEnquiryNODialogClass(HINSTANCE);
void DisplayBalanceEnquiryNODialog(HWND);

void RegisterBalanceEnquiryDialogClass(HINSTANCE);
void DisplayBalanceEnquiryDialog(const HWND, LPCSTR, LPCSTR, LPCSTR);



int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    
    
	
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    RegisterOpenAccountDialogClass(hInst);
    RegisterCloseAccountDialogClass(hInst);
	
    RegisterDepositDialogClass(hInst);
    RegisterWithdrawDialogClass(hInst);

    RegisterBalanceEnquiryIDDialogClass(hInst);
    RegisterBalanceEnquiryNODialogClass(hInst);
    Register_Show_Accounts_Dialog_Class(hInst);
    //RegisterBalanceEnquiryDialogClass(hInst);
    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindow explained:
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1000, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = L"Welcome To Banking System GUI Version Alpha 1.0.1\n\n\n";
    TCHAR greeting2[] = L"Go to File > Open Account to Open an Account";
    TCHAR greeting3[] = L"Go to File > Close Account to Close an Account";
    TCHAR greeting4[] = L"For More Tutorials, Go to https://github.com/Poom1016/BankingSystemGUI/Tutorials/";
    std::string myUrl = "https://poom1016.github.io/Banking-System-Website/tutorials.html";
    std::string myUrl2 = "https://github.com/Poom1016/BankingSystemGUI/";
    std::string myUrl3 = "https://poom1016.github.io/Banking-System-Website/index.html";
    
    switch (message)
    {

    case WM_COMMAND:

	    switch (wParam)
	    {
        case 11:
            system(std::string("start " + myUrl3).c_str());
            break;
        case 12:
            MessageBox(NULL, L"https://github.com/Poom1016/BankingSystemGUI/", L"Gitbub Link",MB_RIGHT);
	    	system(std::string("start " + myUrl2).c_str());
            break;
        case 13:
            DestroyWindow(hWnd);
            break;
        case 21:
            DisplayOpenAccountDialog(hWnd);
            break;
        case 22:
            DisplayCloseAccountDialog(hWnd);
            break;
        case 31:
            DisplayDepositDialog(hWnd);
            break;
        case 32:
            DisplayWithdrawDialog(hWnd);
            break;
        case 41:
            Display_Show_Accounts_Dialog(hWnd);
            break;
        case 51:
            DisplayBalanceEnquiryIDDialog(hWnd);
            break;
        case 52:
            DisplayBalanceEnquiryNODialog(hWnd);
            break;
        case 81:
            
            system(std::string("start " + myUrl).c_str());
                break;
        case 91:
            DialogBoxW(hInst, MAKEINTRESOURCE(IDABORT), NULL, About);
            break;
        case 92:
           DialogBoxW(hInst, MAKEINTRESOURCE(AboutCreator), NULL, About);
            break;
	    }
    	
        break;
    	
    case WM_CREATE:
        AddMenu(hWnd);
        break;
    	
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        TextOut(hdc, 5, 60, greeting2, _tcslen(greeting2));
        TextOut(hdc, 5, 90, greeting3, _tcslen(greeting3));
        TextOut(hdc, 5, 150, greeting4, _tcslen(greeting4));
        // End application-specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

void AddMenu(HWND hWND)
{
    hMENU = CreateMenu();

    HMENU hBSMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hEditMenu = CreateMenu();
    HMENU hShowMenu = CreateMenu();
    HMENU hShowBEMenu = CreateMenu();
    HMENU hViewMenu = CreateMenu();
    HMENU hViewNo = CreateMenu();
    HMENU hHelpMenu = CreateMenu();
    HMENU hHelpAMenu = CreateMenu();

	AppendMenu(hMENU,MF_POPUP,(UINT_PTR)hBSMenu,L"    Banking System    ");

		//AppendMenu(hBSMenu, MF_STRING, 11, L"Preferences");
		AppendMenu(hBSMenu, MF_STRING, 11, L"Website");
        AppendMenu(hBSMenu, MF_STRING, 12, L"Github Link");
        AppendMenu(hBSMenu, MF_STRING, 13, L"Quit");
	
    AppendMenu(hMENU, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

		AppendMenu(hFileMenu, MF_STRING, 21, L"Open Account");
		AppendMenu(hFileMenu, MF_STRING, 22, L"Close Account");
	
    AppendMenu(hMENU, MF_POPUP, (UINT_PTR)hEditMenu, L"Edit");
	
		AppendMenu(hEditMenu, MF_STRING, 31, L"Deposit");
        AppendMenu(hEditMenu, MF_STRING, 32, L"Withdraw");
	
    AppendMenu(hMENU, MF_POPUP, (UINT_PTR)hShowMenu, L"View");

    AppendMenu(hShowMenu, MF_STRING, 41, L"All Accounts");
    AppendMenu(hShowMenu, MF_POPUP, (UINT_PTR)hShowBEMenu, L"Balance Enquiry");

		AppendMenu(hShowBEMenu, MF_STRING, 51, L"Give ID");
        AppendMenu(hShowBEMenu, MF_STRING, 52, L"Give Account Number");

	
    AppendMenu(hMENU, MF_POPUP, (UINT_PTR)hHelpMenu, L"Help");

		AppendMenu(hHelpMenu, MF_STRING, 81, L"Tutorials");
		AppendMenu(hHelpMenu, MF_POPUP, (UINT_PTR)hHelpAMenu, L"About");

			AppendMenu(hHelpAMenu, MF_STRING, 91, L"About");
			AppendMenu(hHelpAMenu, MF_STRING, 92, L"About Creator");

    SetMenu(hWND, hMENU);
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        switch(LOWORD(wParam))
        {
        case CloseButton:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        }
    	
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    }
	
    return (INT_PTR)FALSE;
}



INT_PTR CALLBACK ClseAccount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    int VALUE;
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case CloseButton:
            DestroyWindow(hDlg);
            return TRUE;
            break;

        case OkButton:

            System Bank;
            BankAccount Account;
            std::string FNAME;
            std::string LNAME;
            long INPUT = DELETEACCOUNTNO;
            std::string RESULT = "Account Deleted";

            VALUE = MessageBoxA(hDlg, "Do you want to Delete this Account?", "Close Account", MB_YESNO);
        	if(VALUE == IDYES)
        	{
                Bank.CloseAccount(INPUT);
                MessageBoxA(hDlg, RESULT.c_str(), "Account Deleted", MB_OK);
        	}

            DestroyWindow(hDlg);
            return TRUE;
            break;
        }


        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    }

    return (INT_PTR)FALSE;
}

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

LRESULT CALLBACK DialogOpenAccountProcedure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
    	switch(wParam)
    	{
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        case 2:
            System Bank;
            BankAccount Account;

            int Length1 = GetWindowTextLength(hEditAccountFirstName);
            int Length2 = GetWindowTextLength(hEditAccountLastName);
    		
			std::string FIRSTNAMETEXTINPUTOPENACCOUNT;
            LPSTR STRING1 = const_cast<char*>(FIRSTNAMETEXTINPUTOPENACCOUNT.c_str());
            int a_size = sizeof(FIRSTNAMETEXTINPUTOPENACCOUNT) / sizeof(char);
            GetWindowTextA(hEditAccountFirstName, STRING1, Length1+1);
            std::string SFIRSTNAMETEXTINPUTOPENACCOUNT = convertToString(STRING1, Length1+1);

            std::string LASTNAMETEXTINPUTOPENACCOUNT;
    		LPSTR STRING2 = const_cast<char*>(LASTNAMETEXTINPUTOPENACCOUNT.c_str());
            int b_size = sizeof(LASTNAMETEXTINPUTOPENACCOUNT) / sizeof(char);
            GetWindowTextA(hEditAccountLastName, STRING2, Length2+1);
            std::string SLASTNAMETEXTINPUTOPENACCOUNT = convertToString(STRING2, Length2+1);

            char BALANCETEXTINPUTOPENACCOUNT[64];
            
            GetWindowTextA(hEditAccountBalance, BALANCETEXTINPUTOPENACCOUNT, 64);
            float SBALANCETEXTINPUTOPENACCOUNT = (float)atof(BALANCETEXTINPUTOPENACCOUNT);

            Account = Bank.OpenAccount(SFIRSTNAMETEXTINPUTOPENACCOUNT, SLASTNAMETEXTINPUTOPENACCOUNT, SBALANCETEXTINPUTOPENACCOUNT);
            long AccNO = Account.GetAccountNumber();
            long AccID = AccNO * 9 + 1000;
            std::string ACCOUNTNO = std::to_string(AccNO);
            std::string ACCOUNTID = std::to_string(AccID);
            std::string INTRO = "Account Number: ";
            std::string PRINT = INTRO + ACCOUNTNO + "\n" + "Account ID: " + ACCOUNTID;
            
            MessageBoxA(hDlg, PRINT.c_str(), "Account Created", MB_OK);

            DestroyWindow(hDlg);
            return TRUE;
    		
            break;
    	}
    	
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
    }
}

void RegisterOpenAccountDialogClass(HINSTANCE hInst)
{
    WNDCLASSW OpenAccountDialog = { 0 };

    OpenAccountDialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    OpenAccountDialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    OpenAccountDialog.hInstance = hInst;
    OpenAccountDialog.lpszClassName = L"Open Account";
    OpenAccountDialog.lpfnWndProc = DialogOpenAccountProcedure;

    RegisterClassW(&OpenAccountDialog);
}

void DisplayOpenAccountDialog(HWND hWnd)
{
	
    HWND hDlg = CreateWindowW(L"Open Account", L"Open Account", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 400, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Close", WS_CHILD | WS_VISIBLE, 500, 320, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Create Account", WS_CHILD | WS_VISIBLE, 370, 320, 120, 30, hDlg, (HMENU)2, NULL, NULL);

    CreateWindowW(L"Static", L"Account First Name:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST , 10, 10, 150, 50, hDlg, NULL, NULL, NULL);
    hEditAccountFirstName = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 35, 540, 20, hDlg, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Account Last Name:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST , 10, 70, 150, 50, hDlg, NULL, NULL, NULL);
    hEditAccountLastName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 10, 95, 540, 20, hDlg, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Account Balance:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST , 10, 130, 150, 50, hDlg, NULL, NULL, NULL);
    hEditAccountBalance  = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 10, 155, 540, 20, hDlg, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"*Note - Max Character per box is 64 characters", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 225, 350, 50, hDlg, NULL, NULL, NULL);
	
}

LRESULT CALLBACK DialogCloseAccountProcedure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        case 2:
            System Bank;
            BankAccount Account;
            char BALANCETEXTINPUTCLOSEACCOUNT[64];
            int VALUE;
            VALUE = MessageBoxA(hDlg, "Do you want to close this Account?", "Close Account", MB_YESNO | MB_ICONEXCLAMATION);

            if(VALUE == IDYES)
            {
                
                GetWindowTextA(hCloseAccountNumber, BALANCETEXTINPUTCLOSEACCOUNT, 64);
                float SBALANCETEXTINPUTOPENACCOUNT = (float)atof(BALANCETEXTINPUTCLOSEACCOUNT);
                Bank.CloseAccount(SBALANCETEXTINPUTOPENACCOUNT);
                MessageBoxA(hDlg, "Account Closed", "Close Account", MB_YESNO | MB_ICONINFORMATION);
            }

            DestroyWindow(hDlg);
            return TRUE;

            break;
        }

        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
    }
}

void RegisterCloseAccountDialogClass(HINSTANCE hInst)
{
    WNDCLASSW CloseAccountDialog = { 0 };  

    CloseAccountDialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    CloseAccountDialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    CloseAccountDialog.hInstance = hInst;
    CloseAccountDialog.lpszClassName = L"Close Account";
    CloseAccountDialog.lpfnWndProc = DialogCloseAccountProcedure;

    RegisterClassW(&CloseAccountDialog);
}

void DisplayCloseAccountDialog(HWND hWnd)
{

    HWND hDlg = CreateWindowW(L"Close Account", L"Close Account", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 200, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Close", WS_CHILD | WS_VISIBLE, 500, 120, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Close Account", WS_CHILD | WS_VISIBLE, 370, 120, 120, 30, hDlg, (HMENU)2, NULL, NULL);

    CreateWindowW(L"Static", L"Account Number:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 150, 50, hDlg, NULL, NULL, NULL);
    hCloseAccountNumber = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 35, 540, 20, hDlg, NULL, NULL, NULL);


}

//std::string operator+(const std::string& cs, const float& rhs);

LRESULT CALLBACK DialogDepositProcedure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        case 2:
            System Bank;
            BankAccount Account;
            char ACCOUNTNOTEXTINPUTDEPOSITMONEY[64];
            char MONEYTEXTINPUTDEPOSITMONEY[64];
            
            GetWindowTextA(hDepositAccountNumber, ACCOUNTNOTEXTINPUTDEPOSITMONEY, 64);
            float SACCOUNTNOTEXTINPUTDEPOSITMONEY = (float)atof(ACCOUNTNOTEXTINPUTDEPOSITMONEY);

            GetWindowTextA(hDepositAmountMoney, MONEYTEXTINPUTDEPOSITMONEY, 64);
            float SMONEYTEXTINPUTDEPOSITMONEY = (float)atof(MONEYTEXTINPUTDEPOSITMONEY);
        	
            Account = Bank.Deposit(SACCOUNTNOTEXTINPUTDEPOSITMONEY, SMONEYTEXTINPUTDEPOSITMONEY);
        	
            float MSGBALANCE = Account.GetBalance();
            std::string SMSGBALANCE = std::to_string(MSGBALANCE);

            long MSGACCNUMBER = Account.GetAccountNumber();
            std::string SMSGACCNUMBER = std::to_string(MSGACCNUMBER);

            std::string MSG = "Current Balance for account Number " + SMSGACCNUMBER + " is: $" + SMSGBALANCE;
            
            MessageBoxA(hDlg, MSG.c_str(), "Deposited", MB_OK);
        	
            DestroyWindow(hDlg);
            return TRUE;

            break;
        }

        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
    }
}

void RegisterDepositDialogClass(HINSTANCE hInst)
{
    WNDCLASSW DepositDialog = { 0 };

    DepositDialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    DepositDialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    DepositDialog.hInstance = hInst;
    DepositDialog.lpszClassName = L"Deposit";
    DepositDialog.lpfnWndProc = DialogDepositProcedure;

    RegisterClassW(&DepositDialog);
}

void DisplayDepositDialog(HWND hWnd)
{

    HWND hDlg = CreateWindowW(L"Deposit", L"Deposit", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 400, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Close", WS_CHILD | WS_VISIBLE, 500, 320, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Deposit Money", WS_CHILD | WS_VISIBLE, 370, 320, 120, 30, hDlg, (HMENU)2, NULL, NULL);

    CreateWindowW(L"Static", L"Account Number:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 150, 50, hDlg, NULL, NULL, NULL);
    hDepositAccountNumber = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 35, 540, 20, hDlg, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Amount of money to deposit($):", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 70, 200, 50, hDlg, NULL, NULL, NULL);
    hDepositAmountMoney = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 95, 540, 20, hDlg, NULL, NULL, NULL);


}

LRESULT CALLBACK DialogWithdrawProcedure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        case 2:
            System Bank;
            BankAccount Account;
            char ACCOUNTNOTEXTINPUTWITHDRAWMONEY[64];
            char MONEYTEXTINPUTWITHDRAWMONEY[64];

            GetWindowTextA(hWithdrawAccountNumber, ACCOUNTNOTEXTINPUTWITHDRAWMONEY, 64);
            float SACCOUNTNOTEXTINPUTWITHDRAWMONEY = (float)atof(ACCOUNTNOTEXTINPUTWITHDRAWMONEY);

            GetWindowTextA(hWithdrawAmountMoney, MONEYTEXTINPUTWITHDRAWMONEY, 64);
            float SMONEYTEXTINPUTWITHDRAWMONEY = (float)atof(MONEYTEXTINPUTWITHDRAWMONEY);

            Account = Bank.Withdraw(SACCOUNTNOTEXTINPUTWITHDRAWMONEY, SMONEYTEXTINPUTWITHDRAWMONEY);

            float MSGBALANCE = Account.GetBalance();
            std::string SMSGBALANCE = std::to_string(MSGBALANCE);

            long MSGACCNUMBER = Account.GetAccountNumber();
            std::string SMSGACCNUMBER = std::to_string(MSGACCNUMBER);

            std::string MSG = "Current Balance for account Number " + SMSGACCNUMBER + " is: $" + SMSGBALANCE;

            MessageBoxA(hDlg, MSG.c_str(), "Withdrawn", MB_OK);

            DestroyWindow(hDlg);
            return TRUE;

            break;
        }

        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
    }
}

void RegisterWithdrawDialogClass(HINSTANCE hInst)
{
    WNDCLASSW WithdrawDialog = { 0 };

    WithdrawDialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    WithdrawDialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    WithdrawDialog.hInstance = hInst;
    WithdrawDialog.lpszClassName = L"Withdraw";
    WithdrawDialog.lpfnWndProc = DialogWithdrawProcedure;

    RegisterClassW(&WithdrawDialog);
}

void DisplayWithdrawDialog(HWND hWnd)
{

    HWND hDlg = CreateWindowW(L"Withdraw", L"Withdraw", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 400, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Close", WS_CHILD | WS_VISIBLE, 500, 320, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Withdraw Money", WS_CHILD | WS_VISIBLE, 370, 320, 120, 30, hDlg, (HMENU)2, NULL, NULL);

    CreateWindowW(L"Static", L"Account Number:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 150, 50, hDlg, NULL, NULL, NULL);
    hWithdrawAccountNumber = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 35, 540, 20, hDlg, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Amount of money to withdraw($):", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 70, 250, 100, hDlg, NULL, NULL, NULL);
    hWithdrawAmountMoney = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 95, 540, 20, hDlg, NULL, NULL, NULL);


}








LRESULT CALLBACK DialogBalanceEnquiryIDProcedure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RegisterBalanceEnquiryDialogClass(hInst);
    UNREFERENCED_PARAMETER(lParam);
    
	switch(message)
	{
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
		switch(wParam)
		{
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        case 2:
            System Bank;
            BankAccount Account;
            char ACCOUNTIDTEXTINPUTBALANCEENQUIRY[64];

            GetWindowTextA(hBalanceEnquiryID, ACCOUNTIDTEXTINPUTBALANCEENQUIRY, 64);
            float SACCOUNTIDTEXTINPUTBALANCEENQUIRY = (float)atof(ACCOUNTIDTEXTINPUTBALANCEENQUIRY);

            float SACCOUNTNOTEXTINPUTBALANCEENQUIRY = (SACCOUNTIDTEXTINPUTBALANCEENQUIRY - 1000) / 9;

            Account = Bank.BalanceEnquiry(SACCOUNTNOTEXTINPUTBALANCEENQUIRY);

            std::string FNAME = "First Name: " + Account.GetFName();
            std::string LNAME = "Last Name: " + Account.GetLName();
            long BALANCE = Account.GetBalance();
            std::string SBALANCE = "Balance: $" + std::to_string(BALANCE);

            std::string MSG = FNAME  + LNAME +  SBALANCE;
            
            DisplayBalanceEnquiryDialog(hDlg, FNAME.c_str(), LNAME.c_str(), SBALANCE.c_str());
            MessageBoxA(hDlg, "Press OK to close  ", "Balance Enquiry", MB_OK);
            DestroyWindow(hDlg);
            return TRUE;
			
            break;
		}
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
	}
	
}

void RegisterBalanceEnquiryIDDialogClass(HINSTANCE hInst)
{
    
    WNDCLASSW BalanceEnquiryIDDialog = { 0 };

    BalanceEnquiryIDDialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    BalanceEnquiryIDDialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    BalanceEnquiryIDDialog.hInstance = hInst;
    BalanceEnquiryIDDialog.lpszClassName = L"Balance Enquiry ID";
    BalanceEnquiryIDDialog.lpfnWndProc = DialogBalanceEnquiryIDProcedure;

    RegisterClassW(&BalanceEnquiryIDDialog);
}

void DisplayBalanceEnquiryIDDialog(HWND hWnd) 
{
    
    HWND hDlg = CreateWindowW(L"Balance Enquiry ID", L"Balance Enquiry (ID)", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 400, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Close", WS_CHILD | WS_VISIBLE, 500, 320, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Balance Enquiry", WS_CHILD | WS_VISIBLE, 370, 320, 120, 30, hDlg, (HMENU)2, NULL, NULL);

    CreateWindowW(L"Static", L"Account ID:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 150, 50, hDlg, NULL, NULL, NULL);
    hBalanceEnquiryID = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 35, 540, 20, hDlg, NULL, NULL, NULL);
}

LRESULT CALLBACK DialogBalanceEnquiryProcedure(const HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        }
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
    }

}

void RegisterBalanceEnquiryDialogClass(const HINSTANCE hInst)
{
    WNDCLASSW BalanceEnquiryDialog = { 0 };

    BalanceEnquiryDialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    BalanceEnquiryDialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    BalanceEnquiryDialog.hInstance = hInst;
    BalanceEnquiryDialog.lpszClassName = L"Balance Enquiry";
    BalanceEnquiryDialog.lpfnWndProc = DialogBalanceEnquiryProcedure;

    RegisterClassW(&BalanceEnquiryDialog);
}

void DisplayBalanceEnquiryDialog(const HWND hWnd, LPCSTR FNAME, LPCSTR LNAME, LPCSTR BALANCE)
{
    HWND hDlg = CreateWindowW(L"Balance Enquiry", L"Balance Enquiry", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 400, hWnd, NULL, NULL, NULL);

    //CreateWindowW(L"Button", L"OK", WS_CHILD | WS_VISIBLE, 500, 320, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowA("Static", FNAME, WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 300, 50, hDlg, NULL, NULL, NULL);
    CreateWindowA("Static", LNAME, WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 60, 300, 50, hDlg, NULL, NULL, NULL);
    CreateWindowA("Static", BALANCE, WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 110, 300, 50, hDlg, NULL, NULL, NULL);
	
    
}


LRESULT CALLBACK DialogBalanceEnquiryNOProcedure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RegisterBalanceEnquiryDialogClass(hInst);
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            DestroyWindow(hDlg);
            return TRUE;
            break;
        case 2:
            System Bank;
            BankAccount Account;
            char ACCOUNTIDTEXTINPUTBALANCEENQUIRY[64];

            GetWindowTextA(hBalanceEnquiryNO, ACCOUNTIDTEXTINPUTBALANCEENQUIRY, 64);
            float SACCOUNTIDTEXTINPUTBALANCEENQUIRY = (float)atof(ACCOUNTIDTEXTINPUTBALANCEENQUIRY);

            
            Account = Bank.BalanceEnquiry(SACCOUNTIDTEXTINPUTBALANCEENQUIRY);

            std::string FNAME = "First Name: " + Account.GetFName();
            std::string LNAME = "Last Name: " + Account.GetLName();
            long BALANCE = Account.GetBalance();
            std::string SBALANCE = "Balance: $" + std::to_string(BALANCE);

            std::string MSG = FNAME + LNAME + SBALANCE;

            DisplayBalanceEnquiryDialog(hDlg, FNAME.c_str(), LNAME.c_str(), SBALANCE.c_str());
            MessageBoxA(hDlg, "Press OK to close  ", "Balance Enquiry", MB_OK);
            DestroyWindow(hDlg);
            return TRUE;

            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hDlg);
        return TRUE;
        break;
    default:
        return DefWindowProc(hDlg, message, wParam, lParam);
    }

}

void RegisterBalanceEnquiryNODialogClass(HINSTANCE hInst)
{

    WNDCLASSW BalanceEnquiryNODialog = { 0 };

    BalanceEnquiryNODialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    BalanceEnquiryNODialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    BalanceEnquiryNODialog.hInstance = hInst;
    BalanceEnquiryNODialog.lpszClassName = L"Balance Enquiry NO";
    BalanceEnquiryNODialog.lpfnWndProc = DialogBalanceEnquiryNOProcedure;

    RegisterClassW(&BalanceEnquiryNODialog);
}

auto DisplayBalanceEnquiryNODialog(HWND hWnd) -> void
{

    HWND hDlg = CreateWindowW(L"Balance Enquiry NO", L"Balance Enquiry", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 400, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Close", WS_CHILD | WS_VISIBLE, 500, 320, 70, 30, hDlg, (HMENU)1, NULL, NULL);
    CreateWindowW(L"Button", L"Balance Enquiry", WS_CHILD | WS_VISIBLE, 370, 320, 120, 30, hDlg, (HMENU)2, NULL, NULL);

    CreateWindowW(L"Static", L"Account Number:", WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 150, 50, hDlg, NULL, NULL, NULL);
    hBalanceEnquiryNO = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 35, 540, 20, hDlg, NULL, NULL, NULL);
}



LRESULT CALLBACK Dialog_Show_Accounts_Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

	switch(message)
	{
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        return TRUE;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void Register_Show_Accounts_Dialog_Class(HINSTANCE hInst)
{
    WNDCLASSW Show_All_Account_Dialog = { 0 };

    Show_All_Account_Dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    Show_All_Account_Dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    Show_All_Account_Dialog.hInstance = hInst;
    Show_All_Account_Dialog.lpszClassName = L"Show All Account";
    Show_All_Account_Dialog.lpfnWndProc = Dialog_Show_Accounts_Procedure;

    RegisterClassW(&Show_All_Account_Dialog);
}

void Display_Show_Accounts_Dialog(const HWND hWnd)
{
    int ACCNUMBER;
    int OLDACCNUMBER = 0;
    float BALANCE;
    std::ifstream infile;
    std::string FNAME;
    std::string LNAME;
    std::string MESSAGE = "";
    infile.open("System.data");
	if(!infile)
	{
        MessageBoxA(hWnd, "std::ifstream Error: Cannot open File", "Error", MB_OK | MB_ICONERROR);
	}
    else
    {
        while (!infile.eof())
        {
        	
            infile >> ACCNUMBER;
            infile >> FNAME;
            infile >> LNAME;
            infile >> BALANCE;

        	if(!ACCNUMBER == OLDACCNUMBER)
        	{
                FNAME.erase(std::find(FNAME.begin(), FNAME.end(), '\0'), FNAME.end());
                LNAME.erase(std::find(LNAME.begin(), LNAME.end(), '\0'), LNAME.end());

                MESSAGE = MESSAGE + "Account Number: " + std::to_string(ACCNUMBER) + "\nFirst Name: " + FNAME + "\nLast Name: " + LNAME + "\nBalance: " + std::to_string(BALANCE) + "\n\n";
        	}
            OLDACCNUMBER = ACCNUMBER;
            
        } 
        infile.close();
        //MESSAGE.erase(std::find(MESSAGE.begin(), MESSAGE.end(), '\0'), MESSAGE.end());
       // MESSAGE = MESSAGE + "\0";
        HWND hWind = CreateWindowA("Show All Account", "All Accounts", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_VSCROLL, 500, 500, 600, 400, hWnd, 0, 0, 0);

        CreateWindowA("Static", MESSAGE.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHTJUST, 10, 10, 1000, 1000, hWind, NULL, NULL, NULL);
    }
	
	
}