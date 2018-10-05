class LRUCache:
    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.capacity = capacity
        self.data = {}
        self.nodes = {}  # key: (prev, next)
        self.least_recent_key = -1
        self.most_recent_key = -1

    def update_chain(self, key):
        if key == self.least_recent_key and self.nodes[self.least_recent_key][1] >= 0:
            self.least_recent_key = self.nodes[self.least_recent_key][1]
        elif self.least_recent_key < 0:
            self.least_recent_key = key

        if key != self.most_recent_key:
            if key in self.nodes:
                left_key = self.nodes[key][0]
                right_key = self.nodes[key][1]
                if left_key >= 0:
                    self.nodes[left_key][1] = right_key
                    if right_key >= 0:
                        self.nodes[right_key][0] = left_key
                else:
                    self.nodes[right_key][0] = -1

            if self.most_recent_key >= 0:
                self.nodes[self.most_recent_key][1] = key

            self.nodes[key] = [self.most_recent_key, -1]
            self.most_recent_key = key

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        if key not in self.data:
            return -1

        self.update_chain(key)

        return self.data[key]

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """
        self.data[key] = value
        self.update_chain(key)

        if len(self.data) > self.capacity and self.least_recent_key >= 0:
            victim = self.least_recent_key
            self.least_recent_key = self.nodes[victim][1]
            self.data.pop(victim, None)


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)

'''
def debug_output():
    print("cache = ", lru.data)
    print()


def print_chain(lru_cache):
    print("MOST = %d, LEAST = %d" % (lru_cache.most_recent_key, lru_cache.least_recent_key))
    if lru_cache.least_recent_key < 0:
        print("NO CHAIN")
    else:
        chain = "LEAST → %d" % lru_cache.least_recent_key
        nk = lru_cache.nodes[lru_cache.least_recent_key][1]
        while nk >= 0:
            chain += " → %d" % nk
            nk = lru_cache.nodes[nk][1]
        chain += " → MOST"
        print(chain)


lru = LRUCache(2)
lru.get(2)
lru.get(2)
lru.put(2, 6)
lru.get(1)
lru.put(1, 5)
lru.put(1, 2)
lru.get(1)
lru.get(2)
'''
