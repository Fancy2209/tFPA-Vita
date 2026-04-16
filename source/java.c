#include <falso_jni/FalsoJNI.h>
#include <falso_jni/FalsoJNI_Impl.h>
#include <falso_jni/FalsoJNI_Logger.h>
#include <stdbool.h>

/*
 * JNI Methods
*/

NameToMethodID nameToMethodId[] = {
	{ 100, "showLoadingDialog", METHOD_TYPE_VOID },
	{ 101, "hideLoadingDialog", METHOD_TYPE_VOID },
	{ 102, "getShowSignIn", METHOD_TYPE_BOOLEAN },
	{ 103, "isPremiumUnlocked", METHOD_TYPE_BOOLEAN },
    { 104, "getPreferencesInt", METHOD_TYPE_INT },
};

void showLoadingDialog(jmethodID id, va_list args) { // V (ret type) is a void
    // noop
	sceClibPrintf("showLoadingDialog\n");
}

void hideLoadingDialog(jmethodID id, va_list args) { // V (ret type) is a void
    // noop
	sceClibPrintf("hideLoadingDialog\n");
}

jboolean getShowSignIn(jmethodID id, va_list args) { // Z (ret type) is a bool
    return false;
}

jboolean isPremiumUnlocked(jmethodID id, va_list args) { // Z (ret type) is a bool
    return true;
}

jint getPreferencesInt(jmethodID id, va_list args) {
	// TODO: Is this used for more fhan FANCY_PANTS_EXPLICIT_SIGNOUT?
	return 0;
}

MethodsBoolean methodsBoolean[] = {
	{ 102, getShowSignIn },
	{ 103, isPremiumUnlocked },
};
MethodsByte methodsByte[] = {};
MethodsChar methodsChar[] = {};
MethodsDouble methodsDouble[] = {};
MethodsFloat methodsFloat[] = {};
MethodsInt methodsInt[] = {
    { 104, getPreferencesInt }
};
MethodsLong methodsLong[] = {};
MethodsObject methodsObject[] = {};
MethodsShort methodsShort[] = {};
MethodsVoid methodsVoid[] = {
	{ 100, showLoadingDialog },
	{ 101, hideLoadingDialog },
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
