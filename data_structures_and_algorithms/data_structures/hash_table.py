from pprint import pprint


class HashTable:
    def __init__(self, size):
        self.size = size
        self.hash_table = self.create_buckets()

    def create_buckets(self):
        return [[] for _ in range(self.size)]

    # Insert values into hash map

    def set_val(self, key: str, val):
        # get the index from the key using the hash fn
        hashed_key = hash(key) % self.size
        # get the bucket corresponding index
        bucket = self.hash_table[hashed_key]

        found_key = False
        for i, record in enumerate(bucket):
            record_key, record_val = record

            # if the bucket has the same key as the key to be inserted:
            # update the key-value,
            # otherwise append the new key-value pair to the bucket
            if record_key == key:
                found_key = True
                break

        if found_key:
            bucket[i] = (key, val)
        else:
            bucket.append((key, val))

    def get_bucket(self, key):
        hashed_key = hash(key) % self.size
        return self.hash_table[hashed_key]

    def get_val(self, key):
        bucket = self.get_bucket(key)

        found_key = False
        for i, record in enumerate(bucket):
            record_key, record_val = record

            if record_key == key:
                found_key = True
                break

        if found_key:
            return record_val
        else:
            # raise KeyError(key)
            return None

    def del_val(self, key):
        bucket = self.get_bucket(key)

        found_key = False
        for i, record in enumerate(bucket):
            record_key, record_val = record

            if record_key == key:
                found_key = True
                break

        if found_key:
            return bucket.pop(i)
        else:
            raise KeyError(key)

    def __str__(self):
        return ''.join(str(item) for item in self.hash_table)

    __repr__ = __str__


# Test
ht = HashTable(4)
ht.set_val('one', 1)
ht.set_val('two', 2)
ht.set_val('three', 3)


pprint(ht.hash_table)
