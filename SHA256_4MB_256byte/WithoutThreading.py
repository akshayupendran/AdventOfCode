from hashlib import sha256

md_list = []
binary = None


def calculate_sha2_over_binary():
    # Function / thread to read the next 256 bytes from file and Hash and append to list
    global binary
    array = binary.read(256)
    md_list.append(sha256(array).hexdigest())


def main():
    global binary
    binary = open('Hello.bin', mode='rb')
    hashes = 0
    while hashes < 16384:
        calculate_sha2_over_binary()
        hashes = hashes + 1
        if hashes > 1:
            print("Current Hash is %x:"%(md_list[hashes]))
            print("Previous Hash is %x:"%(md_list[hashes-1]))
            print("Current counter is %d", hashes)
    # print(*md_list, sep=", ")


if __name__ == '__main__':
    main()
