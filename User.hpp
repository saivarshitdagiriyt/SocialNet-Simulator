#ifndef USER_HPP
#define USER_HPP
#include <string>
#include "AVLTree.hpp"
#include "DataStructures.hpp"
#include "Comparators.hpp"
using namespace std;

class User {
public:
    string username;
    CustomAVLTree<FriendNode, FriendComparator> friends;
    CustomAVLTree<PostNode, PostComparator> posts;
    User(const string& name){
        username = name;
    }

    void addFriend(User* friendUser){
        FriendNode friendNode(friendUser);
        friends.insert(friendNode);
    }

    void addPost(const string& content, time_t timestamp){
        PostNode post(content, timestamp);
        posts.insert(post);
    }
};

inline bool FriendComparator::compare(const FriendNode& a, const FriendNode& b){
    return a.user->username < b.user->username;
}

inline bool SuggestionComparator::compare(const SuggestionNode& a, const SuggestionNode& b){
    if(a.mutualFriendCount != b.mutualFriendCount){
        return a.mutualFriendCount > b.mutualFriendCount;
    }
    return a.user->username < b.user->username;
}

#endif
