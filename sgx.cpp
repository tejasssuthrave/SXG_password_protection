#include <stdio.h>
#include <string.h>
#include <sgx_urts.h>
#include "Enclave_u.h"

#define ENCLAVE_FILE "enclave.signed.so"
#define PASSWORD "SuperSecretPassword"

void ocall_print(const char* str) {
    printf("%s\n", str);
}

void print_error_message(sgx_status_t ret) {
    switch(ret) {
        case SGX_ERROR_UNEXPECTED:
            printf("Unexpected error occurred.\n");
            break;
        case SGX_ERROR_INVALID_PARAMETER:
            printf("Invalid parameter.\n");
            break;
        case SGX_ERROR_OUT_OF_MEMORY:
            printf("Out of memory.\n");
            break;
        case SGX_ERROR_ENCLAVE_LOST:
            printf("Power transition occurred.\n");
            break;
        case SGX_ERROR_INVALID_ENCLAVE:
            printf("Invalid enclave image.\n");
            break;
        case SGX_ERROR_INVALID_ENCLAVE_ID:
            printf("Invalid enclave identification.\n");
            break;
        case SGX_ERROR_INVALID_SIGNATURE:
            printf("Invalid enclave signature.\n");
            break;
        case SGX_ERROR_OUT_OF_EPC:
            printf("Out of EPC memory.\n");
            break;
        case SGX_ERROR_NO_DEVICE:
            printf("SGX device not available.\n");
            break;
        case SGX_ERROR_MEMORY_MAP_CONFLICT:
            printf("Memory map conflicted.\n");
            break;
        case SGX_ERROR_INVALID_METADATA:
            printf("Invalid enclave metadata.\n");
            break;
        case SGX_ERROR_DEVICE_BUSY:
            printf("SGX device was busy.\n");
            break;
        case SGX_ERROR_INVALID_VERSION:
            printf("Enclave version was invalid.\n");
            break;
        case SGX_ERROR_INVALID_ATTRIBUTE:
            printf("Enclave was not authorized.\n");
            break;
        case SGX_ERROR_ENCLAVE_FILE_ACCESS:
            printf("Can't open enclave file.\n");
            break;
        case SGX_ERROR_NDEBUG_ENCLAVE:
            printf("The enclave is signed as product enclave, and can not be created as debuggable enclave.\n");
            break;
        case SGX_ERROR_SERVICE_UNAVAILABLE:
            printf("SGX service unavailable.\n");
            break;
        case SGX_ERROR_SERVICE_TIMEOUT:
            printf("SGX service timeout.\n");
            break;
        case SGX_ERROR_SERVICE_INVALID_PRIVILEGE:
            printf("The request requires a privilege that is not held by the client.\n");
            break;
        default:
            printf("Error code is %d.\n", ret);
            break;
    }
}

int main() {
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, NULL, NULL, &eid, NULL);
    if (ret != SGX_SUCCESS) {
        print_error_message(ret);
        return -1;
    }

    const char* password = "SuperSecretPassword";
    ret = ecall_check_password(eid, password);
    if (ret != SGX_SUCCESS) {
        print_error_message(ret);
        sgx_destroy_enclave(eid);
        return -1;
    }

    sgx_destroy_enclave(eid);
    return 0;
}
