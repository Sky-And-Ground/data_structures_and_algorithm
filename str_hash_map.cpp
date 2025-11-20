#include <iostream>
#include <string>
#include <list>
#include <array>
#include <optional>
#include <cstdint>
#include <cstddef>

struct StrPair {
    std::string key;
    std::string value;

    StrPair(const std::string& _key, const std::string& _value) 
        : key{ _key }, value{ _value } 
    {}
};

class StrHashMap {
    static constexpr uint32_t bucket_size = 101;

    std::array<std::list<StrPair>, bucket_size> bucket;
    size_t len;

    bool find_pos(const std::string& key, std::list<StrPair>::iterator& result) {
        auto hashval = std::hash<std::string>{}(key) % bucket_size;
        auto& str_pair_list = bucket[hashval];

        for (auto iter = str_pair_list.begin(); iter != str_pair_list.end(); ++iter) {
            if (iter->key == key) {
                result = iter;
                return true;
            }
        }

        return false;
    }
public:
    StrHashMap() : len{ 0 } {}

    void put(const std::string& key, const std::string& value) {
        std::list<StrPair>::iterator iter;
        
        if (find_pos(key, iter)) {
            iter->value = value;
        }
        else {
            auto hashval = std::hash<std::string>{}(key) % bucket_size;
            bucket[hashval].emplace_back(key, value);
            ++len;
        }
    }

    void del(const std::string& key) {
        std::list<StrPair>::iterator iter;

        if (find_pos(key, iter)) {
            auto hashval = std::hash<std::string>{}(key) % bucket_size;
            bucket[hashval].erase(iter);
            --len;
        }
    }

    bool contains(const std::string& key) {
        std::list<StrPair>::iterator iter;
        return find_pos(key, iter);
    }

    std::optional<std::string> get(const std::string& key) {
        std::list<StrPair>::iterator iter;
    
        if (find_pos(key, iter)) {
            return iter->value;
        }
        else {
            return std::nullopt;
        }
    }
};

int main() {
    StrHashMap map;
    map.put("fenny", "I love you");

    auto result = map.get("fenny");
    if (result) {
        std::cout << result.value() << "\n";
    }

    return 0;
}
