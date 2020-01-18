# from hashlib import sha256
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256

Hash = None
binary = None


def calculate_sha2_over_binary():
    # Function / thread to read the next 256 bytes from file and Hash and append to list
    global binary
    global Hash
    stringchunk = binary.read(256)
    local_hash = (SHA256.new(stringchunk).hexdigest())
    if Hash is None:
        Hash = local_hash
    else:
        Hash = SHA256.new(str(Hash).lower().encode("utf-8") + str(local_hash).lower().encode("utf-8")).hexdigest()
        # local_hash_string = local_hash_string + Hash_string
        # hash_oid = SHA256.new(local_hash_string)
        # Hash_string = str(SHA256.new(local_hash_string).hexdigest()).lower().encode("utf-8")


def main():
    global binary
    binary = open('MERGED_APPL_CMAC_PADDED.bin', mode='rb')
    Blockhash = open('Finalbockhash.bin', mode='wb')
    hashes = 0
    while hashes < 16127:
        calculate_sha2_over_binary()
        hashes = hashes + 1
    print(str(Hash).lower().encode("utf-8"))
    Blockhash.write(str(Hash).lower().encode("utf-8"))
    Blockhash.close()
    privatekey = RSA.import_key(open('RSA_privateEnc_key.pem').read(), passphrase="VisteonSecurityVIP")
    # h = SHA256.new(b'To be signed')
    # signer1 = pkcs1_15.new(privatekey)
    # signature1 = signer1.sign(h)
    # print(signature1)
    signer = pkcs1_15.new(privatekey)
    signature = signer.sign(str(Hash).lower().encode("utf-8"))
    # signature = pkcs1_15.new(privatekey).sign(Hash_string)
    # Blockhash.write()
    # Blockhash.close()
    binary.close()


if __name__ == '__main__':
    main()
