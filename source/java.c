#include <falso_jni/FalsoJNI.h>
#include <falso_jni/FalsoJNI_Impl.h>
#include <falso_jni/FalsoJNI_Logger.h>
#include <stdbool.h>
#include <string.h>
#include <psp2/kernel/clib.h>
#include "utils/trophies.h"

/*
 * JNI Methods
*/

struct { const char* achievementID; int trophyID; } trophyMap[11] = {
	{ "CgkI2ILYlYUPEAIQFQ",  0 }, // "Obsessed"
	{ "CgkI2ILYlYUPEAIQFw",  1 }, // "Big Brother"
	{ "CgkI2ILYlYUPEAIQGg",  2 }, // "Better than the developers"
	{ "CgkI2ILYlYUPEAIQGw",  3 }, // "Fancy Fashion"
	{ "CgkI2ILYlYUPEAIQGA",  4 }, // "Squiggle Hunter"
	{ "CgkI2ILYlYUPEAIQHg",  5 }, // "Paparazzi"
	{ "CgkI2ILYlYUPEAIQFg",  6 }, // "Fancy Fanboy"
	{ "CgkI2ILYlYUPEAIQHA",  7 }, // "Storyteller"
	{ "CgkI2ILYlYUPEAIQGQ",  8 }, // "The Olympian"
	{ "CgkI2ILYlYUPEAIQHQ",  9 }, // "The Newbie"
	{ "CgkI2ILYlYUPEAIQHw", 10 }, // "The Juggler"
};

void unlockAchievement(jmethodID id, va_list args) {
	jstring _cheevo = va_arg(args, jstring);
	const char* cheevo = (char *)jni->GetStringUTFChars(&jni, _cheevo, NULL);
	sceClibPrintf("unlockAchievement(%s)\n", (char *)cheevo);
		for(size_t i = 0; i < 11; i++) {
		if(strcmp(cheevo, trophyMap[i].achievementID) == 0) {
			trophies_unlock(trophyMap[i].trophyID);
			break;
		}
	}
	jni->ReleaseStringUTFChars(&jni, _cheevo, (char *)cheevo);
}

void jniVNoop(jmethodID id, va_list args) { // V (ret type) is a void
    // noop
}

jboolean jniZRet0(jmethodID id, va_list args) { // Z (ret type) is a bool
    return false;
}

jboolean jniZRet1(jmethodID id, va_list args) { // Z (ret type) is a bool
    return true;
}

jint getPreferencesInt(jmethodID id, va_list args) {
	jstring _pref = va_arg(args, jstring);
	const char* pref = jni->GetStringUTFChars(&jni, _pref, NULL);
	jint defaultValue = va_arg(args, jint);
	sceClibPrintf("%s\n", (char *)pref);
	jni->ReleaseStringUTFChars(&jni, _pref, (char *)pref);
	// TODO: Is this used for more fhan FANCY_PANTS_EXPLICIT_SIGNOUT?
	return defaultValue;
}

NameToMethodID nameToMethodId[] = {
	{ 100, "showLoadingDialog",  METHOD_TYPE_VOID },
	{ 101, "hideLoadingDialog",  METHOD_TYPE_VOID },
	{ 102, "consumeReward",      METHOD_TYPE_VOID },
	{ 103, "getShowSignIn",      METHOD_TYPE_BOOLEAN },

	{ 104, "isPremiumUnlocked",  METHOD_TYPE_BOOLEAN },
	{ 105, "isWorld1Unlocked",   METHOD_TYPE_BOOLEAN },
	{ 106, "isWorld2Unlocked",   METHOD_TYPE_BOOLEAN },
	{ 107, "isWardrobeUnlocked", METHOD_TYPE_BOOLEAN },
	{ 108, "isRewardReady",      METHOD_TYPE_BOOLEAN },

    { 109, "getPreferencesInt",  METHOD_TYPE_INT },

	{ 110, "unlockAchievement", METHOD_TYPE_VOID },
	{ 111, "showAchievements", METHOD_TYPE_VOID },

};

MethodsBoolean methodsBoolean[] = {
	{ 103, jniZRet0 }, // getShowSignIn

	{ 104, jniZRet0 }, // isPremiumUnlocked
	{ 105, jniZRet0 }, // isWorld1Unlocked
	{ 106, jniZRet0 }, // isWorld2Unlocked
	{ 107, jniZRet0 }, // isWardrobeUnlocked
	{ 108, jniZRet1 }, // isRewardReady
};
MethodsByte methodsByte[] = {};
MethodsChar methodsChar[] = {};
MethodsDouble methodsDouble[] = {};
MethodsFloat methodsFloat[] = {};
MethodsInt methodsInt[] = {
    { 109, getPreferencesInt }
};
MethodsLong methodsLong[] = {};
MethodsObject methodsObject[] = {};
MethodsShort methodsShort[] = {};
MethodsVoid methodsVoid[] = {
	{ 100, jniVNoop },
	{ 101, jniVNoop },
	{ 102, jniVNoop },
	{ 110, unlockAchievement },
	{ 111, jniVNoop },
};

/*
 * JNI Fields
*/

// System-wide constant that applications sometimes request
// https://developer.android.com/reference/android/content/Context.html#WINDOW_SERVICE
char WINDOW_SERVICE[] = "window";

// System-wide constant that's often used to determine Android version
// https://developer.android.com/reference/android/os/Build.VERSION.html#SDK_INT
// Possible values: https://developer.android.com/reference/android/os/Build.VERSION_CODES
const int SDK_INT = 19; // Android 4.4 / KitKat

NameToFieldID nameToFieldId[] = {
		{ 0, "WINDOW_SERVICE", FIELD_TYPE_OBJECT }, 
		{ 1, "SDK_INT", FIELD_TYPE_INT },
};

FieldsBoolean fieldsBoolean[] = {};
FieldsByte fieldsByte[] = {};
FieldsChar fieldsChar[] = {};
FieldsDouble fieldsDouble[] = {};
FieldsFloat fieldsFloat[] = {};
FieldsInt fieldsInt[] = {
		{ 1, SDK_INT },
};
FieldsObject fieldsObject[] = {
		{ 0, WINDOW_SERVICE },
};
FieldsLong fieldsLong[] = {};
FieldsShort fieldsShort[] = {};

__FALSOJNI_IMPL_CONTAINER_SIZES
