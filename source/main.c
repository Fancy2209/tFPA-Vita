#include "utils/init.h"
#include "utils/glutil.h"
#include "utils/logger.h"

#include <psp2/kernel/threadmgr.h>

#include <falso_jni/FalsoJNI.h>
#include <AFakeNative/AFakeNative.h>
#include <so_util/so_util.h>

#include <AFakeNative/utils/controls.h>

int _newlib_heap_size_user = 256 * 1024 * 1024;

#ifdef USE_SCELIBC_IO
int sceLibcHeapSize = 4 * 1024 * 1024;
#endif

so_module so_mod;

int crasher(unsigned int argc, void *argv) {
  uint32_t *null_ptr = NULL;
  for (;;) {
    SceCtrlData pad;
    sceCtrlPeekBufferPositive(0, &pad, 1);
    if (pad.buttons & SCE_CTRL_SELECT) *null_ptr = 0;
    sceKernelDelayThread(100);
  }
}

int main() {
	SceUID crasher_thread = sceKernelCreateThread("crasher", crasher, 0x40, 0x1000, 0, 0, NULL);
    sceKernelStartThread(crasher_thread, 0, NULL);

    soloader_init_all();

    int (*ANativeActivity_onCreate)(ANativeActivity *activity, void *savedState,
									size_t savedStateSize) = (void *) so_symbol(&so_mod, "ANativeActivity_onCreate");

	ANativeActivity *activity = ANativeActivity_create();
	l_success("Created NativeActivity object");

	ANativeActivity_onCreate(activity, NULL, 0);
	l_success("ANativeActivity_onCreate() passed");

	AInputQueue *aInputQueue = AInputQueue_create();
	activity->callbacks->onInputQueueCreated(activity, aInputQueue);
	l_success("onInputQueueCreated() passed");

	ANativeWindow *aNativeWindow = ANativeWindow_create();
	activity->callbacks->onNativeWindowCreated(activity, aNativeWindow);
	l_success("onNativeWindowCreated() passed");

	activity->callbacks->onWindowFocusChanged(activity, 1);
	l_success("onWindowFocusChanged() passed");

	activity->callbacks->onStart(activity);
	l_success("onStart() passed");

	activity->callbacks->onResume(activity);
	l_success("onStart() passed");

    sceKernelExitDeleteThread(0);
}
