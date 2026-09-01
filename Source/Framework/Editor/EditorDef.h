#pragma once

// Editor関連の#defineを定義する
#if defined(EDITOR) || defined(__INTELLISENSE__)
#define EDITOR_DEF
#endif