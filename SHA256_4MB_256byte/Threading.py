# Multi Threading Required for faster processing
from threading import Thread
# SHA256 is the hash Required
from hashlib import sha256

md_list = []
binary = None


def calculate_sha2_over_binary():
    # Threaded function will read the next 256 bytes from file and pass to SHA
    global binary
    array = binary.read(256)
    md_list.append(sha256(array).hexdigest())


def main():
    # This function is written with following expectations:
    # 1. Open a binary File. As we are opening the file in read binary, we do not need to provide an encoding argument.
    global binary
    binary = open('Hello.bin', mode='rb')
    # 2. Setup Multiprocessing -> Create a list of threads which we will start
    threads = []
    # 3. Create a loop to calculate 16384 hashes - use multi-threading
    number_of_threads = 0
    hashes = 0
    while hashes < 16384:
        while number_of_threads < 8:
            # 4. In Each Loop Step Start a thread
            # when the calculation is done, the result is stored in a global variable
            process = Thread(target=calculate_sha2_over_binary)
            process.start()
            threads.append(process)
            number_of_threads = number_of_threads + 1

        # We now pause execution on the main thread by 'joining' all of our started threads.
        # This ensures that each has finished processing the hash.
        for process in threads:
            process.join()
        hashes = hashes + 8

    print(*md_list, sep = ", ")


if __name__ == '__main__':
    main()
