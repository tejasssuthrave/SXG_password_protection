#include "Enclave_t.h"
#include <string.h>
#include <sgx_tcrypto.h>

#define PASSWORD "SuperSecretPassword"

void ecall_check_password(const char* password) {
    if (strcmp(password, PASSWORD) == 0) {
        ocall_print("Password is correct!");
    } else {
        ocall_print("Password is incorrect!");
    }
}
