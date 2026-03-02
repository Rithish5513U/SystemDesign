#include <bits/stdc++.h>
using namespace std;

class EmailSubscribeList{
public:
	static map<string, unordered_map<string, void (*)(string email, string event, string data)>> subscribers;
	
	static void subscribe(string event, string email, void (*subscriber)(string email, string event, string data)){
		subscribers[event][email] = subscriber;
	}
	
	static void publish(string event, string data){
		if(subscribers.find(event) != subscribers.end()){
			for(auto& [email, subscriber] : subscribers[event]){
				subscriber(email, event, data);
			}
		}
	}
};

map<string, unordered_map<string, void (*)(string email, string event, string data)>> EmailSubscribeList::subscribers;

class NewsLetterNotification{
public:
	// This is the part after the event is occurred
	static void handleEvent(string email, string event, string data=""){
		if(event == "RecievedNewsLetter"){
			cout << "Email to " << email << "\n";
			cout << data;
		}
	}
};

class NewsLetterPostService{
public:
	// This is the place where the event is triggerred
	static void postEvent(string event, string data = ""){
		EmailSubscribeList::publish(event, data);
	}
};

int main(){
	EmailSubscribeList::subscribe("RecievedNewsLetter", "rithish.satish@gmail.com", NewsLetterNotification::handleEvent);
	
	NewsLetterPostService newsLetterPostService;
	
	newsLetterPostService.postEvent("RecievedNewsLetter", "Hi bro! I think it is working fine\n");
	
	return 0;
}
