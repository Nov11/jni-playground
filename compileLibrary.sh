#!/bin/bash
#g++ -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -shared -fPIC ./jni/src/$FileNameWithoutExtension$.cpp $ProjectFileDir$
g++ -std=c++14 -fPIC -shared -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux ./jni/src/pkg_HelloJNI.cpp -o ./jni/out/library/libnative.so