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
#include <unistd.h>

extern so_module so_mod;
/*
so_hook init_game_so_hook;

void _ZN6Engine11CRasterizer6SetFVFEj_hook(void* this, uint32_t a1)
{
    sceClibPrintf("Engine::CRasterizer::SetFVF this %p a1 %u\n", this, a1);
    
    if (this == NULL) {
        // if this is null we're fucked
        void** Engine_CRasterizer_s_pRef = so_symbol(&so_mod, "_ZN6Engine11CRasterizer6s_pRefE");
        sceClibPrintf("*Engine::CRasterizer::s_pRef %p", *Engine_CRasterizer_s_pRef);
        if(*Engine_CRasterizer_s_pRef == NULL)
        {
            sceClibPrintf("we're fucked\n");

            void* sInitParams = calloc(1, 0x38);
            ((void(*)(void*))(so_symbol(&so_mod, "_ZN11SInitParamsC2Ev")))(sInitParams);
            sceClibPrintf("new SInitParams() called\n");

            sceClibPrintf("Calling Engine::CRasterizer::StaticInit(%p)\n", sInitParams);
            bool result = ((bool(*)(void*))(so_symbol(&so_mod, "_ZN6Engine11CRasterizer10StaticInitERKNS_13SRasterParamsE")))(sInitParams);
            sceClibPrintf("Engine::CRasterizer::StaticInit(%p) returned %i\n", sInitParams, (int)result);
            if(!result)
            {
                sceClibPrintf("we're really fucked\n");
                exit(1);
                while(true)
                {
                    usleep(1000);
                }
            } else {
                sceClibPrintf("WOHOO\n");
                sceClibPrintf("*Engine::CRasterizer::s_pRef %p", *Engine_CRasterizer_s_pRef);
            }
        }
    }
    
    typeof(&_ZN6Engine11CRasterizer6SetFVFEj_hook) fun = so_symbol(&so_mod, "_ZN6Engine11CRasterizer8SetFVFHWEj");
    fun(this, a1);
    
    return;
}
*/

void so_patch(void) {
    // Sample hook
    //hook_addr((uintptr_t)so_symbol(&so_mod, "_ZN6Engine11CRasterizer6SetFVFEj"), (uintptr_t)&_ZN6Engine11CRasterizer6SetFVFEj_hook);
}