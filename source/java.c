#include <falso_jni/FalsoJNI.h>
#include <falso_jni/FalsoJNI_Impl.h>
#include <falso_jni/FalsoJNI_Logger.h>
#include <stdbool.h>

/*
 * JNI Methods
*/


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
	jint defaultValue = va_arg(args, jstring);
	sceClibPrintf("%s\n", pref);
	jni->ReleaseStringUTFChars(&jni, _pref, pref);
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

};

MethodsBoolean methodsBoolean[] = {
	{ 103, jniZRet0 },
	{ 104, jniZRet1 },
	{ 105, jniZRet1 },
	{ 106, jniZRet1 },
	{ 107, jniZRet1 },
	{ 108, jniZRet1 },
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
