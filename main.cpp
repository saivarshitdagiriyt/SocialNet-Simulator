#include <iostream>
#include <string>
#include "Graph.hpp"

using namespace std;

void printHelp(){
    cout << endl << "--- SocialNet Simulator Help ---" << endl;
    cout << "ADD_USER <username>                        - Adds a new user to the network." << endl;
    cout << "ADD_FRIEND <username1> <username2>         - Establishes friendship between two users." << endl;
    cout << "LIST_FRIENDS <username>                    - Lists all friends of a user alphabetically." << endl;
    cout << "SUGGEST_FRIENDS <username> <N>             - Recommends up to N friends-of-friends." << endl;
    cout << "DEGREES_OF_SEPARATION <username1> <username2> - Finds shortest friendship path." << endl;
    cout << "ADD_POST <username> \"<content>\"            - Adds a post for the user." << endl;
    cout << "OUTPUT_POSTS <username> <N>                - Shows N most recent posts." << endl;
    cout << "HELP                                       - Shows this help message." << endl;
    cout << "EXIT                                       - Exits the program." << endl;
    cout << "-----------------------------------" << endl;
}

int main(){
    SocialNetworkGraph graph;
    string line;
    
    cout << "Welcome to the SocialNet Simulator!";
    printHelp();
    
    while(true){
        cout << endl << "> ";
        if(!getline(cin, line)){
            break;
        }
        
        size_t start = line.find_first_not_of(" \t\r\n");
        if(start == string::npos){
            continue;
        }
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);
        
        if(line.empty()){
            continue;
        }
        
        if(line == "EXIT"){
            cout << "Exiting SocialNet Simulator. Goodbye!" << endl;
            break;
        }
        
        if(line.find("ADD_USER ") == 0){
            string username = line.substr(9);
            if(username.empty()){
                cout << "Error: Usage: ADD_USER <username>" << endl;
                continue;
            }
            graph.addUser(username);
        }
        else if(line.find("ADD_FRIEND ") == 0){
            string rest = line.substr(11);
            size_t spacePos = rest.find(' ');
            
            if(spacePos == string::npos){
                cout << "Error: Usage: ADD_FRIEND <username1> <username2>\n";
                continue;
            }
            
            string username1 = rest.substr(0, spacePos);
            string username2 = rest.substr(spacePos + 1);
            
            if(username1.empty() || username2.empty()){
                cout << "Error: Usernames cannot be empty\n";
                continue;
            }
            
            graph.addFriend(username1, username2);
        }
        else if(line.find("LIST_FRIENDS ") == 0){
            string username = line.substr(13);
            if(username.empty()){
                cout << "Error: Usage: LIST_FRIENDS <username>" << endl;
                continue;
            }
            graph.listFriends(username);
        }
        else if(line.find("ADD_POST ") == 0){
            string rest = line.substr(9);
            
            size_t firstQuote = rest.find('"');
            if(firstQuote == string::npos){
                cout << "Error: Post content must be enclosed in quotes\n";
                continue;
            }
            
            string username = rest.substr(0, firstQuote);
            while(!username.empty() && username[username.length()-1] == ' '){
                username.pop_back();
            }
            
            if(username.empty()){
                cout << "Error: Username cannot be empty\n";
                continue;
            }
            
            size_t lastQuote = rest.rfind('"');
            if(lastQuote == firstQuote){
                cout << "Error: Post content must be enclosed in quotes\n";
                continue;
            }
            
            string content = rest.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            graph.addPost(username, content);
        }
        else if(line.find("OUTPUT_POSTS ") == 0){
            string rest = line.substr(13);
            size_t spacePos = rest.find(' ');
            
            if(spacePos == string::npos){
                cout << "Error: Usage: OUTPUT_POSTS <username> <N>" << endl;
                continue;
            }
            
            string username = rest.substr(0, spacePos);
            string nStr = rest.substr(spacePos + 1);
            
            if(username.empty() || nStr.empty()){
                cout << "Error: Username and number cannot be empty" << endl;
                continue;
            }
            
            try{
                size_t pos = 0;
                int n = stoi(nStr, &pos);
                if(pos != nStr.length()){
                    cout << "Error: Number must be an integer" << endl;
                    continue;
                }
                if(n < -1){
                    cout << "Error: N must be -1 or a positive integer" << endl;
                    continue;
                }
                graph.outputPosts(username, n);
            }catch(...){
                cout << "Error: Number must be an integer" << endl;
            }
        }
        else if(line.find("SUGGEST_FRIENDS ") == 0){
            string rest = line.substr(16);
            size_t spacePos = rest.find(' ');
            
            if(spacePos == string::npos){
                cout << "Error: Usage: SUGGEST_FRIENDS <username> <N>" << endl;
                continue;
            }
            
            string username = rest.substr(0, spacePos);
            string nStr = rest.substr(spacePos + 1);
            
            if(username.empty() || nStr.empty()){
                cout << "Error: Username and number cannot be empty" << endl;
                continue;
            }
            
            try{
                size_t pos = 0;
                int n = stoi(nStr, &pos);
                if(pos != nStr.length()){
                    cout << "Error: Number must be an integer" << endl;
                    continue;
                }
                if(n < -1){
                    cout << "Error: N must be -1 or a non-negative integer" << endl;
                    continue;
                }
                graph.suggestFriends(username, n);
            }catch(...){
                cout << "Error: Number must be an integer" << endl;
            }
        }
        else if(line.find("DEGREES_OF_SEPARATION ") == 0){
            string rest = line.substr(22);
            size_t spacePos = rest.find(' ');
            
            if(spacePos == string::npos){
                cout << "Error: Usage: DEGREES_OF_SEPARATION <username1> <username2>" << endl;
                continue;
            }
            
            string username1 = rest.substr(0, spacePos);
            string username2 = rest.substr(spacePos + 1);
            
            if(username1.empty() || username2.empty()){
                cout << "Error: Usernames cannot be empty" << endl;
                continue;
            }
            
            graph.degreesOfSeparation(username1, username2);
        }
        else if(line == "HELP"){
            printHelp();
        }
        else{
            cout << "Error: Unknown command '" << line << "'. Type HELP for a list of commands." << endl;
        }
    }
    
    return 0;
}
