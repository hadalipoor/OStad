def parse_partition_table(filename):
    with open(filename, 'rb') as f:
        data = f.read()

    print("Type | SubType | Start Address | Size | Label")
    print("------------------------------------------------")

    for i in range(0, len(data), 32):  # Each partition entry is 32 bytes
        entry = data[i:i+32]
        if len(entry) < 32:
            break

        # Extract fields from the partition entry
        type_ = entry[0]
        subtype = entry[1]
        offset = int.from_bytes(entry[4:8], 'little')
        size = int.from_bytes(entry[8:12], 'little')
        
        try:
            label = entry[16:32].decode('utf-8').rstrip('\x00')
        except UnicodeDecodeError:
            label = entry[16:32].hex()

        print(f"{type_:02x}   | {subtype:02x}     | {offset:08x}    | {size:08x} | {label}")

parse_partition_table("elevatorControl.ino.partitions.bin")
