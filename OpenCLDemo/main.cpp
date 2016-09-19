//
//  main.cpp
//  OpenCLDemo
//
//  Created by ioan on 19.09.2016.
//  Copyright © 2016 Ioan Chera. All rights reserved.
//

#include <OpenCL/OpenCL.h>

#include <stdio.h>

#include <string>
#include <vector>

struct ErrorException
{
    cl_int result;
};

static void checkError(cl_int result)
{
    if(result != CL_SUCCESS)
        throw ErrorException{.result = result};
}

static void getPlatformInfo(cl_platform_id platformId, cl_platform_info paramName, std::string &result)
{
    size_t size = 0;
    checkError(clGetPlatformInfo(platformId, paramName, 0, nullptr, &size));
    result.resize(size);
    checkError(clGetPlatformInfo(platformId, paramName, size, const_cast<char *>(result.data()), nullptr));
}

static void printPlatformInfo(cl_platform_id platformId)
{
    std::string info;
    getPlatformInfo(platformId, CL_PLATFORM_PROFILE, info);
    printf("Profile   : %s\n", info.c_str());
    getPlatformInfo(platformId, CL_PLATFORM_VERSION, info);
    printf("Version   : %s\n", info.c_str());
    getPlatformInfo(platformId, CL_PLATFORM_NAME, info);
    printf("Name      : %s\n", info.c_str());
    getPlatformInfo(platformId, CL_PLATFORM_VENDOR, info);
    printf("Vendor    : %s\n", info.c_str());
    getPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS, info);
    printf("Extensions: %s\n", info.c_str());
}

static void getDeviceInfo(cl_device_id deviceId, cl_device_info paramName, std::string &result)
{
    size_t size = 0;
    checkError(clGetDeviceInfo(deviceId, paramName, 0, nullptr, &size));
    result.resize(size);
    checkError(clGetDeviceInfo(deviceId, paramName, size, const_cast<char *>(result.data()), nullptr));
}

static void printDeviceInfo(cl_device_id deviceId)
{
    cl_device_type deviceType;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_TYPE, sizeof(deviceType), &deviceType, nullptr));
    printf("Type: ");
    switch(deviceType)
    {
        case CL_DEVICE_TYPE_CPU:
            puts("CPU");
            break;
        case CL_DEVICE_TYPE_GPU:
            puts("GPU");
            break;
        case CL_DEVICE_TYPE_ACCELERATOR:
            puts("Accelerator");
            break;
        case CL_DEVICE_TYPE_DEFAULT:
            puts("Default");
            break;
        case CL_DEVICE_TYPE_CUSTOM:
            puts("Custom");
            break;
        default:
            printf("Unknown (%d)\n", (int)deviceType);
            break;
    }
    cl_uint uintValue;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_VENDOR_ID, sizeof(uintValue), &uintValue, nullptr));
    printf("Vendor id: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(uintValue), &uintValue, nullptr));
    printf("Max compute units: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(uintValue), &uintValue, nullptr));
    printf("Max work item dimensions: %u\n", uintValue);

    std::vector<size_t> sizes(uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WORK_ITEM_SIZES, uintValue * sizeof(size_t), sizes.data(), nullptr));
    printf("Max work item sizes: (");
    for(size_t size : sizes)
        printf("%zu, ", size);
    puts(")");

    size_t sizeValue;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(sizeValue), &sizeValue, nullptr));
    printf("Max work group size: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width char: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width short: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width int: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width long: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width float: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width double: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, sizeof(uintValue), &uintValue, nullptr));
    printf("Preferred vector width half: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width char: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width short: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width int: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width long: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width float: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width double: %u\n", uintValue);
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, sizeof(uintValue), &uintValue, nullptr));
    printf("Native vector width half: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(uintValue), &uintValue, nullptr));
    printf("Max clock frequency: %u MHz\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_ADDRESS_BITS, sizeof(uintValue), &uintValue, nullptr));
    printf("Address bits: %u\n", uintValue);

    cl_ulong ulongValue;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(ulongValue), &ulongValue, nullptr));
    printf("Max mem alloc size: %llu\n", ulongValue);

    cl_bool boolValue;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE_SUPPORT, sizeof(boolValue), &boolValue, nullptr));
    printf("Image support? %u\n", boolValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(uintValue), &uintValue, nullptr));
    printf("Max read image args: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(uintValue), &uintValue, nullptr));
    printf("Max write image args: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(sizeValue), &sizeValue, nullptr));
    printf("2D image max width: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(sizeValue), &sizeValue, nullptr));
    printf("2D image max height: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(sizeValue), &sizeValue, nullptr));
    printf("3D image max width: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(sizeValue), &sizeValue, nullptr));
    printf("3D image max height: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(sizeValue), &sizeValue, nullptr));
    printf("3D image max depth: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, sizeof(sizeValue), &sizeValue, nullptr));
    printf("Image max buffer size: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, sizeof(sizeValue), &sizeValue, nullptr));
    printf("Image max array size: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_SAMPLERS, sizeof(uintValue), &uintValue, nullptr));
    printf("Max samplers: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(sizeValue), &sizeValue, nullptr));
    printf("Max parameter size: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MEM_BASE_ADDR_ALIGN, sizeof(uintValue), &uintValue, nullptr));
    printf("Mem base addr align: %u\n", uintValue);

    cl_device_fp_config fpConfig;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_SINGLE_FP_CONFIG, sizeof(fpConfig), &fpConfig, nullptr));
    puts("Single FP config:");
    if(fpConfig & CL_FP_DENORM)
        puts("\tdenorm");
    if(fpConfig & CL_FP_INF_NAN)
        puts("\tinf nan");
    if(fpConfig & CL_FP_ROUND_TO_NEAREST)
        puts("\tround to nearest");
    if(fpConfig & CL_FP_ROUND_TO_ZERO)
        puts("\tround to zero");
    if(fpConfig & CL_FP_ROUND_TO_INF)
        puts("\tround to inf");
    if(fpConfig & CL_FP_FMA)
        puts("\tFMA");
    if(fpConfig & CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT)
        puts("\tcorrectly rounded divide sqrt");
    if(fpConfig & CL_FP_SOFT_FLOAT)
        puts("\tsoft float");

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(fpConfig), &fpConfig, nullptr));
    puts("Double FP config:");
    if(fpConfig & CL_FP_DENORM)
        puts("\tdenorm");
    if(fpConfig & CL_FP_INF_NAN)
        puts("\tinf nan");
    if(fpConfig & CL_FP_ROUND_TO_NEAREST)
        puts("\tround to nearest");
    if(fpConfig & CL_FP_ROUND_TO_ZERO)
        puts("\tround to zero");
    if(fpConfig & CL_FP_ROUND_TO_INF)
        puts("\tround to inf");
    if(fpConfig & CL_FP_FMA)
        puts("\tFMA");
    if(fpConfig & CL_FP_SOFT_FLOAT)
        puts("\tsoft float");

    cl_device_mem_cache_type cacheType;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, sizeof(cacheType), &cacheType, nullptr));
    printf("Global mem cache type: ");
    switch (cacheType) {
        case CL_NONE:
            puts("none");
            break;
        case CL_READ_ONLY_CACHE:
            puts("read only");
            break;
        case CL_READ_WRITE_CACHE:
            puts("read/write");
            break;
        default:
            puts("unknown");
            break;
    }
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(uintValue), &uintValue, nullptr));
    printf("Global mem cacheline size: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(ulongValue), &ulongValue, nullptr));
    printf("Global mem cache size: %llu\n", ulongValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(ulongValue), &ulongValue, nullptr));
    printf("Global mem size: %llu\n", ulongValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(ulongValue), &ulongValue, nullptr));
    printf("Max constant buffer size: %llu\n", ulongValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(uintValue), &uintValue, nullptr));
    printf("Max constant args: %u\n", uintValue);

    cl_device_local_mem_type memtype;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_LOCAL_MEM_TYPE, sizeof(memtype), &memtype, nullptr));
    switch(memtype)
    {
        case CL_NONE:
            puts("none");
            break;
        case CL_LOCAL:
            puts("local");
            break;
        case CL_GLOBAL:
            puts("global");
            break;
        default:
            puts("unknown");
            break;
    }

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(ulongValue), &ulongValue, nullptr));
    printf("Local mem size: %llu\n", ulongValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(boolValue), &boolValue, nullptr));
    printf("Error correction support? %u\n", boolValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_HOST_UNIFIED_MEMORY, sizeof(boolValue), &boolValue, nullptr));
    printf("Host unified memory? %u\n", boolValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PROFILING_TIMER_RESOLUTION, sizeof(sizeValue), &sizeValue, nullptr));
    printf("Profiling timer resolution: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_ENDIAN_LITTLE, sizeof(boolValue), &boolValue, nullptr));
    printf("Little endian? %u\n", boolValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_AVAILABLE, sizeof(boolValue), &boolValue, nullptr));
    printf("Available? %u\n", boolValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_COMPILER_AVAILABLE, sizeof(boolValue), &boolValue, nullptr));
    printf("Compiler available? %u\n", boolValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_LINKER_AVAILABLE, sizeof(boolValue), &boolValue, nullptr));
    printf("Linker available? %u\n", boolValue);

    cl_device_exec_capabilities caps;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_EXECUTION_CAPABILITIES, sizeof(caps), &caps, nullptr));
    printf("Execution capabilities: ");
    if(caps & CL_EXEC_KERNEL)
        printf("kernel ");
    if(caps & CL_EXEC_NATIVE_KERNEL)
        printf("native-kernel");
    puts("");

    cl_command_queue_properties props;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_QUEUE_PROPERTIES, sizeof(props), &props, nullptr));
    printf("Queue properties: ");
    if(props & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
        printf("out-of-order-exec-mode-enable ");
    if(props & CL_QUEUE_PROFILING_ENABLE)
        printf("profiling-enable");
    puts("");

    std::string str;
    getDeviceInfo(deviceId, CL_DEVICE_BUILT_IN_KERNELS, str);
    printf("Build-in kernels: %s\n", str.c_str());

    cl_platform_id pid;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PLATFORM, sizeof(pid), &pid, nullptr));
    printf("Platform: ");
    printPlatformInfo(pid);

    getDeviceInfo(deviceId, CL_DEVICE_NAME, str);
    printf("Name: %s\n", str.c_str());
    getDeviceInfo(deviceId, CL_DEVICE_VENDOR, str);
    printf("Vendor: %s\n", str.c_str());
    getDeviceInfo(deviceId, CL_DRIVER_VERSION, str);
    printf("Driver version: %s\n", str.c_str());
    getDeviceInfo(deviceId, CL_DEVICE_PROFILE, str);
    printf("Profile: %s\n", str.c_str());
    getDeviceInfo(deviceId, CL_DEVICE_VERSION, str);
    printf("Device version: %s\n", str.c_str());
    getDeviceInfo(deviceId, CL_DEVICE_OPENCL_C_VERSION, str);
    printf("OpenCL C version: %s\n", str.c_str());
    getDeviceInfo(deviceId, CL_DEVICE_EXTENSIONS, str);
    printf("Extensions: %s\n", str.c_str());

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PRINTF_BUFFER_SIZE, sizeof(sizeValue), &sizeValue, nullptr));
    printf("printf buffer size: %zu\n", sizeValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PREFERRED_INTEROP_USER_SYNC, sizeof(boolValue), &boolValue, nullptr));
    printf("Preferred interop user sync? %u\n", boolValue);

    cl_device_id did;
    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PARENT_DEVICE, sizeof(did), &did, nullptr));
    printf("Parent device: %p (this is %p)\n", did, deviceId);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_PARTITION_MAX_SUB_DEVICES, sizeof(uintValue), &uintValue, nullptr));
    printf("Partition max sub devices: %u\n", uintValue);

    checkError(clGetDeviceInfo(deviceId, CL_DEVICE_REFERENCE_COUNT, sizeof(uintValue), &uintValue, nullptr));
    printf("Reference count: %u\n", uintValue);

}

int main(int argc, const char * argv[])
{
    try
    {
        cl_uint numPlatformIds = 0;
        checkError(clGetPlatformIDs(0, nullptr, &numPlatformIds));
        std::vector<cl_platform_id> platformIds(numPlatformIds);
        checkError(clGetPlatformIDs(numPlatformIds, platformIds.data(), nullptr));
        for(auto platformId : platformIds)
            printPlatformInfo(platformId);
        cl_platform_id platformId = platformIds[0];
        cl_uint numDeviceIds = 0;
        checkError(clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDeviceIds));
        std::vector<cl_device_id> deviceIds(numDeviceIds);
        checkError(clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, numDeviceIds, deviceIds.data(), nullptr));
        for(cl_uint i = 0; i < numDeviceIds; ++i)
        {
            printf("Device %u:\n", (unsigned)i);
            printDeviceInfo(deviceIds[i]);
        }

    }
    catch(const ErrorException &e)
    {
        fprintf(stderr, "OpenCL error: %u\n", (unsigned)e.result);
    }

    return 0;
}
