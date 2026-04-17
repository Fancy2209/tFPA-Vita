/*
 * Copyright (C) 2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/**
 * @file  patch.c
 * @brief Patching some of the .so internal functions or bridging them to native
 *        for better compatibility.
 */

#include <stdbool.h>
#include <stdint.h>
#include <kubridge.h>
#include <so_util/so_util.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern so_module so_mod;

static bool didHack = false;
bool _ZNK13CMenuGameMode15WantConsoleMenuEv_hook(void* this)
{
    if(didHack) return *(int *)(this + 0x44) == 9;
    
    //sceClibPrintf("CMenuGameMode::WantsConsoleMenu()\n");
    int *menuState = (int *)(this + 0x44);
    if(*menuState == 6)
    {
        sceClibPrintf("Trying to Force In Game\n");
        // basic_string<>[8], basic_string is each 8
        void (*make_std_string)(void* this, const char* string);
        make_std_string = (typeof(make_std_string))so_symbol(&so_mod, "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEE11AllocatorIdIcLN10IAllocator10ESubSystemE20EEEC2INS_9nullptr_tEEEPKc");

        void (*CMainGameMode_SetNextLevel)(void* levelName, bool a2, bool a3, bool a4, bool a5);
        CMainGameMode_SetNextLevel = (typeof(CMainGameMode_SetNextLevel))so_symbol(&so_mod, "_ZN13CMainGameMode12SetNextLevelERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEE11AllocatorIdIcLN10IAllocator10ESubSystemE20EEEEbbbb");

        void (*CMenuGameMode_SetMenuState)(void* this, int state);
        CMenuGameMode_SetMenuState = (typeof(CMenuGameMode_SetMenuState))so_symbol(&so_mod, "_ZN13CMenuGameMode12SetMenuStateENS_10EMenuStateE");

        unsigned char abStack_28[12*8];
        make_std_string((void*)&abStack_28, "INTRO_LEVEL");
        CMainGameMode_SetNextLevel(&abStack_28, false, false, false, false);
        CMenuGameMode_SetMenuState(this, 10);
        didHack = true;
    }
    return *menuState == 9;
}


void CBird_Done_hook(void* this) {
    if(this == NULL) return; 

    void** obj = *(void*** )((uintptr_t)this + 0x218);

    if (obj)
    {
        void (**vtable)() = *(void (***)())obj;
        if (vtable && vtable[3])   // 0xC / 4 = index 3
            vtable[3]();

        *(void**)((uintptr_t)this + 0x218) = NULL;
    }

    void(*CEnemy_Done)(void*) = (typeof(CEnemy_Done))so_symbol(&so_mod, "_ZN6CEnemy4DoneEv");
    CEnemy_Done(this);
}


so_hook ccontrol_fade_hook;
void Engine_GUI_CControl_Fade_hook(void *this, float arg1, float arg2)
{
    if(this == NULL) return;
#ifdef USE_KUBRIDGE
    SO_CONTINUE(typeof(&Engine_GUI_CControl_Fade_hook), &ccontrol_fade_hook, this, arg1, arg2);

#endif
}

void so_patch(void) {
    // TODO: There's definetely something wrong... The UI should work
    // The game is also throwing Unhandled SISGEV like crazy on Vita3K
    hook_addr((uintptr_t)so_symbol(&so_mod, "_ZNK13CMenuGameMode15WantConsoleMenuEv"), (uintptr_t)&_ZNK13CMenuGameMode15WantConsoleMenuEv_hook);
    hook_addr((uintptr_t)so_symbol(&so_mod, "_ZN5CBird4DoneEv"), (uintptr_t)&CBird_Done_hook);
    hook_addr((uintptr_t)so_symbol(&so_mod, "_ZN3GUI8CControl4FadeEff"), (uintptr_t)&Engine_GUI_CControl_Fade_hook);
}