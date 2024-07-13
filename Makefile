SGX_SDK ?= /opt/intel/sgxsdk
SGX_MODE ?= HW
SGX_ARCH ?= x64
SGX_DEBUG ?= 1
SGX_PRERELEASE ?= 0

SGX_COMMON_FLAGS := -Wall -Wextra -Werror -Wno-unused-parameter

App_Name := app
Enclave_Name := enclave.so
Signed_Enclave_Name := enclave.signed.so

App_C_Files := App/App.cpp
App_Objects := $(App_C_Files:.cpp=.o)
App_Include_Paths := -I$(SGX_SDK)/include

Enclave_C_Files := Enclave/Enclave.cpp
Enclave_Objects := $(Enclave_C_Files:.cpp=.o)
Enclave_Include_Paths := -I$(SGX_SDK)/include -IEnclave

.PHONY: all clean

all: $(App_Name) $(Signed_Enclave_Name)

$(App_Name): $(App_Objects) $(Signed_Enclave_Name)
	@echo "LINK => $@"
	@$(CXX) $^ -o $@ $(SGX_COMMON_FLAGS) -L$(SGX_SDK)/lib64 -lsgx_urts -lsgx_uae_service

$(Signed_Enclave_Name): Enclave/Enclave.config.xml $(Enclave_Objects)
	@echo "SIGN => $@"
	@$(SGX_SDK)/bin/x64/sgx_sign sign -key Enclave/Enclave_private.pem -enclave $(Enclave_Name) -out $@ -config Enclave/Enclave.config.xml

Enclave/%.o: Enclave/%.cpp
	@echo "CXX => $@"
	@$(CXX) $< -o $@ -c $(SGX_COMMON_FLAGS) $(Enclave_Include_Paths)

App/%.o: App/%.cpp
	@echo "CXX => $@"
	@$(CXX) $< -o $@ -c $(SGX_COMMON_FLAGS) $(App_Include_Paths)

clean:
	@rm -f $(App_Objects) $(Enclave_Objects) $(App_Name) $(Signed_Enclave_Name)
