#include <jni.h>
#include <iostream>
#include <string>
#include <time.h>

int main(int argc, char **argv) {
    using namespace std;
    JavaVM *jvm;                                                     // Pointer to the JVM (Java Virtual Machine)
    JNIEnv *env;                                                     // Pointer to native interface
    JavaVMInitArgs vm_args;                                          // Initialization arguments
    JavaVMOption *options = new JavaVMOption[1];                     // JVM invocation options
    options[0].optionString = "-Djava.class.path=../target/classes"; // where to find java .class
    vm_args.version = JNI_VERSION_1_6;                               // minimum Java version
    vm_args.nOptions = 1;                                            // number of options
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;                              // invalid options make the JVM init fail

    jint rc = JNI_CreateJavaVM(&jvm, (void **) &env, &vm_args);
    delete options;

    if (rc != JNI_OK) {
        exit(EXIT_FAILURE);
    }

    cout << "JVM load succeeded: Version ";
    jint ver = env->GetVersion();
    cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

    jclass main_class = env->FindClass("Main");

    if (main_class == nullptr) {
        cerr << "ERROR: class not found !";
    } else {
        jmethodID mid = env->GetStaticMethodID(main_class, "returnInteger", "()I");

        if (mid == nullptr) {
            cerr << "ERROR: method not found !" << endl;
        } else {
            clock_t tic = clock();

            int times = 1000000;
            for (int i = 0; i < times; ++i) {
                env->CallStaticVoidMethod(main_class, mid);
            }
            clock_t toc = clock();

            clock_t difference = toc - tic;
            double total_time = ((double) difference) / CLOCKS_PER_SEC;

            printf("Totaltime: %f s\n", total_time);
            printf("Per invocation: %g\n", total_time / times * 1000 * 1000000);
        }

        jvm->DestroyJavaVM();
    }
}