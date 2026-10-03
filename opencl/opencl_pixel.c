/*
 * SPDX-FileCopyrightText: 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "OpenCL-pixel"

#include <dlfcn.h>
#include <pthread.h>

#include <log/log.h>

static void* opencl_handle;
static pthread_once_t opencl_once = PTHREAD_ONCE_INIT;

static void open_opencl(void) {
    opencl_handle = dlopen("libOpenCL.so", RTLD_NOW | RTLD_LOCAL);
    if (opencl_handle == NULL) {
        ALOGE("Failed to load libOpenCL.so: %s", dlerror());
    }
}

void enableOpenCL(void) {
    pthread_once(&opencl_once, open_opencl);
}

void* loadOpenCLPointer(const char* name) {
    pthread_once(&opencl_once, open_opencl);
    if (opencl_handle == NULL) {
        return NULL;
    }
    return dlsym(opencl_handle, name);
}
