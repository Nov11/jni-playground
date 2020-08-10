#include "../include/pkg_HelloJNI.h"
#include <iostream>

using namespace std;

JNIEXPORT void JNICALL Java_pkg_HelloJNI_sayHello
        (JNIEnv *env, jobject thisObject) {
    std::cout << "Hello from C++ !!" << std::endl;
}

JNIEXPORT jlong JNICALL Java_pkg_HelloJNI_sumIntegers
        (JNIEnv *env, jobject thisObject, jint first, jint second) {
    std::cout << "C++: The numbers received are : " << first << " and " << second << std::endl;
    return (long) first + (long) second;
}

JNIEXPORT jstring JNICALL Java_pkg_HelloJNI_sayHelloToMe
        (JNIEnv *env, jobject thisObject, jstring name, jboolean isFemale) {
    const char *nameCharPointer = env->GetStringUTFChars(name, NULL);
    std::string title;
    if (isFemale) {
        title = "Ms. ";
    } else {
        title = "Mr. ";
    }

    std::string fullName = title + nameCharPointer;
    return env->NewStringUTF(fullName.c_str());
}

JNIEXPORT jobject JNICALL Java_pkg_HelloJNI_createUser
        (JNIEnv *env, jobject thisObject, jstring name, jdouble balance) {

    // Create the object of the class UserData
    jclass userDataClass = env->FindClass("pkg/UserData");
    jobject newUserData = env->AllocObject(userDataClass);

    // Get the UserData fields to be set
    jfieldID nameField = env->GetFieldID(userDataClass, "name", "Ljava/lang/String;");
    jfieldID balanceField = env->GetFieldID(userDataClass, "balance", "D");

    env->SetObjectField(newUserData, nameField, name);
    env->SetDoubleField(newUserData, balanceField, balance);

    return newUserData;
}

JNIEXPORT jstring JNICALL Java_pkg_HelloJNI_printUserData
        (JNIEnv *env, jobject thisObject, jobject userData) {

    // Find the id of the Java method to be called
    jclass userDataClass = env->GetObjectClass(userData);
    jmethodID methodId = env->GetMethodID(userDataClass, "getUserInfo", "()Ljava/lang/String;");

    jstring result = (jstring) env->CallObjectMethod(userData, methodId);
    return result;
}

JNIEXPORT jobjectArray JNICALL Java_pkg_HelloJNI_search
        (JNIEnv *env, jobject thisObject, jobjectArray arrayOfDoubleArray, jint count) {
    int nq = env->GetArrayLength(arrayOfDoubleArray);
    if (nq == 0) {
        return nullptr;
    }
    auto firstArray = (jdoubleArray) env->GetObjectArrayElement(arrayOfDoubleArray, 0);
    int d = env->GetArrayLength(firstArray);

    double *matrix = new double[nq * d];

    for (int i = 0; i < nq; i++) {
        auto tmp = (jdoubleArray) env->GetObjectArrayElement(arrayOfDoubleArray, i);
        jboolean isCopy = false;
        jdouble *array = env->GetDoubleArrayElements(tmp, &isCopy);
        for (int j = 0; j < d; j++) {
            matrix[i * d + j] = array[j];
        }
        env->ReleaseDoubleArrayElements(tmp, array, JNI_ABORT);
    }

    for (int i = 0; i < nq; i++) {
        for (int j = 0; j < d; j++) {
            cout << matrix[i * d + j] << " ";
        }
        cout << endl;
    }


    jclass dd = env->FindClass("[[D");
    jobjectArray result = env->NewObjectArray(2, dd, nullptr);
    for (int outer = 0; outer < 2; outer++) {
        jobjectArray middle = env->NewObjectArray(nq, env->FindClass("[D"), nullptr);
        double *ptr = matrix;
        for (int i = 0; i < nq; i++) {
            jdoubleArray inner = env->NewDoubleArray(d);
            env->SetDoubleArrayRegion(inner, 0, d, ptr);
            ptr += d;
            env->SetObjectArrayElement(middle, i, inner);
        }
        env->SetObjectArrayElement(result, outer, middle);
    }

    delete[] matrix;
    return result;
}