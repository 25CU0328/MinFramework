#pragma once

#include <windows.h>

enum class KeyCode
{
    // ----- アルファベットキー -----
    A = 'A',
    B = 'B',
    C = 'C',
    D = 'D',
    E = 'E',
    F = 'F',
    G = 'G',
    H = 'H',
    I = 'I',
    J = 'J',
    K = 'K',
    L = 'L',
    M = 'M',
    N = 'N',
    O = 'O',
    P = 'P',
    Q = 'Q',
    R = 'R',
    S = 'S',
    T = 'T',
    U = 'U',
    V = 'V',
    W = 'W',
    X = 'X',
    Y = 'Y',
    Z = 'Z',

    // ----- メインキーボードの数字キー -----
    Num0 = '0',
    Num1 = '1',
    Num2 = '2',
    Num3 = '3',
    Num4 = '4',
    Num5 = '5',
    Num6 = '6',
    Num7 = '7',
    Num8 = '8',
    Num9 = '9',

    // --- システム・コントロールキー (System & Control Keys) ---
    Backspace = VK_BACK,  
    Tab = VK_TAB, 
    Clear = VK_CLEAR, 
    Enter = VK_RETURN, 
    Shift = VK_SHIFT, 
    Control = VK_CONTROL, 
    Alt = VK_MENU, 
    Pause = VK_PAUSE, 
    CapsLock = VK_CAPITAL, 
    Escape = VK_ESCAPE, 
    Space = VK_SPACE,  

    // --- ナビゲーション -----
    PageUp = VK_PRIOR, 
    PageDown = VK_NEXT,
    End = VK_END,
    Home = VK_HOME, 
    
    Select = VK_SELECT,  
    Print = VK_PRINT, 
    Execute = VK_EXECUTE, 
    PrintScreen = VK_SNAPSHOT,
    Insert = VK_INSERT,
    Delete = VK_DELETE, 
    Help = VK_HELP, 
    
    // ----- 矢印キー -----
    ArrowLeft = VK_LEFT,  
    ArrowUp = VK_UP,
    ArrowRight = VK_RIGHT,
    ArrowDown = VK_DOWN,

    // --- テンキー (Numeric Keypad) ---
    Numpad0 = VK_NUMPAD0, 
    Numpad1 = VK_NUMPAD1, 
    Numpad2 = VK_NUMPAD2, 
    Numpad3 = VK_NUMPAD3, 
    Numpad4 = VK_NUMPAD4, 
    Numpad5 = VK_NUMPAD5, 
    Numpad6 = VK_NUMPAD6, 
    Numpad7 = VK_NUMPAD7, 
    Numpad8 = VK_NUMPAD8, 
    Numpad9 = VK_NUMPAD9, 
    Multiply = VK_MULTIPLY,   
    Add = VK_ADD,   
    Separator = VK_SEPARATOR,  
    Subtract = VK_SUBTRACT,   
    Decimal = VK_DECIMAL, 
    Divide = VK_DIVIDE, 

    // --- ファンクションキー (Function Keys) ---
    F1 = VK_F1,     
    F2 = VK_F2,     
    F3 = VK_F3, 
    F4 = VK_F4,
    F5 = VK_F5,
    F6 = VK_F6, 
    F7 = VK_F7,   
    F8 = VK_F8,    
    F9 = VK_F9, 
    F10 = VK_F10, 
    F11 = VK_F11, 
    F12 = VK_F12, 

    // --- ロックキー (Lock Keys) ---
    NumLock = 0x90,  // VK_NUMLOCK
    ScrollLock = 0x91,  // VK_SCROLL

    // --- 修飾キー (Left/Right Modifier Keys) ---
    LShift = VK_LSHIFT,      // VK_LSHIFT
    RShift = VK_RSHIFT,      // VK_RSHIFT
    LControl = VK_LCONTROL,    // VK_LCONTROL
    RControl = VK_RCONTROL,    // VK_RCONTROL
    LAlt = VK_LMENU,        // VK_LMENU (左Alt)
    RAlt = VK_RMENU,        // VK_RMENU (右Alt)
};