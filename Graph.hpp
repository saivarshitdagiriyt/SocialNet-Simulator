#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <ctime>
#include "User.hpp"
#include "AVLTree.hpp"
#include "Comparators.hpp"
using namespace std;

string toLower(const string& str){
    string result = str;
    for(size_t i = 0; i < result.length(); i++){
        if(result[i] >= 'A' && result[i] <= 'Z'){
            result[i] = result[i] - 'A' + 'a';
        }
    }
    return result;
}

string timestampToString(time_t timestamp){
    string timeStr = ctime(&timestamp);
    if(!timeStr.empty() && timeStr[timeStr.length() - 1] == '\n'){
        timeStr.pop_back();
    }
    return timeStr;
}

class SocialNetworkGraph {
private:
    unordered_map<string, User*> users;

public:
    ~SocialNetworkGraph(){
        for(auto& pair : users){
            delete pair.second;
        }
    }

    void addUser(const string& username){
        string lowerUsername = toLower(username);
        if(users.find(lowerUsername) != users.end()){
            cout << "Error: Username already exists" << endl;
            return;
        }
        User* newUser = new User(lowerUsername);
        users[lowerUsername] = newUser;
        cout << "User " << lowerUsername << " added successfully" << endl;
    }

    void addFriend(const string& username1, const string& username2){
        string lower1 = toLower(username1);
        string lower2 = toLower(username2);
        if(users.find(lower1) == users.end()){
            cout << "Error: User " << lower1 << " not found" << endl;
            return;
        }
        if(users.find(lower2) == users.end()){
            cout << "Error: User " << lower2 << " not found" << endl;
            return;
        }
        if(lower1 == lower2){
            cout << "Error: Cannot add self as friend" << endl;
            return;
        }
        User* user1 = users[lower1];
        User* user2 = users[lower2];
        FriendNode checkNode(user2);
        if(user1->friends.contains(checkNode)){
            cout << "Error: Users are already friends" << endl;
            return;
        }
        user1->addFriend(user2);
        user2->addFriend(user1);
        cout << "Friendship between " << lower1 << " and " << lower2 << " established" << endl;
    }

    void listFriends(const string& username){
        string lowerUsername = toLower(username);
        if(users.find(lowerUsername) == users.end()){
            cout << "Error: User " << lowerUsername << " not found" << endl;
            return;
        }
        User* user = users[lowerUsername];
        vector<FriendNode> friendsList = user->friends.getElements();
        if(friendsList.empty()){
            cout << lowerUsername << " has no friends yet" << endl;
            return;
        }
        cout << "Friends of " << lowerUsername << ":" << endl;
        for(const auto& friendNode : friendsList){
            cout << friendNode.user->username << endl;
        }
    }

    void suggestFriends(const string& username, int n){
        string lowerUsername = toLower(username);
        if(users.find(lowerUsername) == users.end()){
            cout << "Error: User " << lowerUsername << " not found" << endl;
            return;
        }
        if(n < -1){
            cout << "Error: N must be -1 or a non-negative integer" << endl;
            return;
        }
        User* user = users[lowerUsername];
        vector<FriendNode> directFriends = user->friends.getElements();
        unordered_map<string, int> mutualFriendCount;
        for(const auto& friendNode : directFriends){
            User* friendUser = friendNode.user;
            vector<FriendNode> friendsOfFriend = friendUser->friends.getElements();
            for(const auto& fofNode : friendsOfFriend){
                User* fofUser = fofNode.user;
                if(fofUser->username == lowerUsername){
                    continue;
                }
                FriendNode checkNode(fofUser);
                if(user->friends.contains(checkNode)){
                    continue;
                }
                mutualFriendCount[fofUser->username]++;
            }
        }
        if(mutualFriendCount.empty()){
            cout << "No friend suggestions for " << lowerUsername << endl;
            return;
        }
        CustomAVLTree<SuggestionNode, SuggestionComparator> suggestions;
        for(const auto& pair : mutualFriendCount){
            User* suggestedUser = users[pair.first];
            SuggestionNode suggestion(suggestedUser, pair.second);
            suggestions.insert(suggestion);
        }
        vector<SuggestionNode> suggestionList = suggestions.getElements(n);
        cout << "Friend suggestions for " << lowerUsername << ":\n";
        for(const auto& suggestion : suggestionList){
            cout << suggestion.user->username << " (Mutual friends: " 
                 << suggestion.mutualFriendCount << ")\n";
        }
    }
    void degreesOfSeparation(const string& username1, const string& username2){
        string lower1 = toLower(username1);
        string lower2 = toLower(username2);
        if(users.find(lower1) == users.end()){
            cout << "Error: User " << lower1 << " not found" << endl;
            return;
        }
        if(users.find(lower2) == users.end()){
            cout << "Error: User " << lower2 << " not found" << endl;
            return;
        }
        if(lower1 == lower2){
            cout << "0" << endl;
            return;
        }
        User* startUser = users[lower1];
        User* endUser = users[lower2];
        unordered_map<string, int> distance;
        unordered_map<string, string> parent;
        queue<User*> q;
        q.push(startUser);
        distance[startUser->username] = 0;
        parent[startUser->username] = "";
        bool found = false;
        while(!q.empty()){
            User* current = q.front();
            q.pop();
            if(current->username == endUser->username){
                found = true;
                break;
            }
            vector<FriendNode> friendsList = current->friends.getElements();
            for(const auto& friendNode : friendsList){
                User* friendUser = friendNode.user;
                if(distance.find(friendUser->username) == distance.end()){
                    distance[friendUser->username] = distance[current->username] + 1;
                    parent[friendUser->username] = current->username;
                    q.push(friendUser);
                }
            }
        }

        if(!found){
            cout << "-1\n";
            return;
        }
        cout << distance[endUser->username] << "\n";
    }

    void addPost(const string& username, const string& content){
        string lowerUsername = toLower(username);

        if(users.find(lowerUsername) == users.end()){
            cout << "Error: User " << lowerUsername << " not found" << endl;
            return;
        }

        User* user = users[lowerUsername];
        time_t timestamp = time(nullptr);
        
        string lowerContent = toLower(content);
        user->addPost(lowerContent, timestamp);

        cout << "Post added for " << lowerUsername << endl;
    }

    void outputPosts(const string& username, int n){
        string lowerUsername = toLower(username);

        if(users.find(lowerUsername) == users.end()){
            cout << "Error: User " << lowerUsername << " not found" << endl;
            return;
        }

        if(n < -1){
            cout << "Error: N must be -1 or a non-negative integer" << endl;
            return;
        }

        User* user = users[lowerUsername];
        vector<PostNode> postsList = user->posts.getElements(n);

        if(postsList.empty()){
            cout << lowerUsername << " has no posts yet" << endl;
            return;
        }

        cout << "Posts by " << lowerUsername << ":" << endl;
        for(const auto& post : postsList){
            cout << "- \"" << post.content << "\" (" 
                 << timestampToString(post.timestamp) << ")" << endl;
        }
    }
};
#endif
