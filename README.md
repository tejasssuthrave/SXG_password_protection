# SXG_password_protection
This repository contains a simple example of using Intel Software Guard Extensions (SGX) for password protection. The project demonstrates how to create an enclave to securely handle sensitive data and perform secure operations within the enclave.

Understanding the Approach:
Enclave Development: Your application's password handling logic will run inside an SGX enclave, a protected memory area isolated from the regular operating system. This ensures password confidentiality even with root access.
Password Storage: Don't store passwords in plain text within the enclave. Derive a strong encryption key from the user's password using a Key Derivation Function (KDF) like Argon2. Then, encrypt the actual password with the derived key using a secure algorithm like AES-256.
User Interaction:
Enrollment: During first use, prompt the user to create a password within the enclave. Derive the encryption key and store the encrypted password securely (e.g., sealed file).
Authentication: For subsequent logins, prompt the user for the password outside the enclave. Derive the encryption key again from the entered password. Inside the enclave, attempt to decrypt the stored encrypted password using the derived key. Successful decryption signifies a correct password.
