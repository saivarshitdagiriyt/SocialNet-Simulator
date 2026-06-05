#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP
#include <string>
using namespace std;

class User;

struct FriendNode {
    User* user;
    FriendNode(User* u){
        user = u;
    }
};

struct PostNode {
    string content;
    time_t timestamp;
    PostNode(const string& c, time_t t){
        content = c;
        timestamp = t;
    }
};

struct SuggestionNode {
    User* user;
    int mutualFriendCount;
    SuggestionNode(User* u, int count){
        user = u;
        mutualFriendCount = count;
    }
};

#endif
