#ifndef COMPARATORS_HPP
#define COMPARATORS_HPP
#include "DataStructures.hpp"

class FriendComparator;
class PostComparator;
class SuggestionComparator;

class FriendComparator {
public:
    bool compare(const FriendNode& a, const FriendNode& b);
};

class PostComparator {
public:
    bool compare(const PostNode& a, const PostNode& b){
        return a.timestamp > b.timestamp;
    }
};

class SuggestionComparator {
public:
    bool compare(const SuggestionNode& a, const SuggestionNode& b);
};

#endif
