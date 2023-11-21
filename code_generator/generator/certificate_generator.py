import subprocess
import os

def generate_certificate():
    # Step 1: Generate Certificate and Private Key
    subprocess.run(["openssl", "req", "-x509", "-newkey", "rsa:2048", "-keyout", "key.pem", "-out", "cert.pem", "-days", "365", "-nodes", "-subj", "/CN=example.com"])

    # Step 2: Read Certificate and Key
    with open("cert.pem", "rb") as f:
        cert_data = f.read()
    with open("key.pem", "rb") as f:
        key_data = f.read()

    # Step 3: Convert to uint8_t Arrays in String Format
    def to_uint8_string(binary_data):
        return ", ".join(str(b) for b in binary_data)

    cert_array_str = to_uint8_string(cert_data)
    key_array_str = to_uint8_string(key_data)

    # Step 4: Create the Final String
    final_str = f"uint8_t certificate[] = {{{cert_array_str}}};\nuint8_t private_key[] = {{{key_array_str}}};"

    # Deleting the generated files
    os.remove("cert.pem")
    os.remove("key.pem")

    return final_str

