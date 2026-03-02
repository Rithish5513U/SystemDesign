#include <bits/stdc++.h>
using namespace std;

// It is the EventBus where all the events are stored so that subscribing and publishing can happen.
// The user can subscribe to an event and the publisher of the event can publish the event so that subscriber can recieve it.
class EmailSubscribeList{
public:
	// Map to store the event and the correspondent subscriber detail and the service they want
	// It is like for this event -> I need this particular service to happen
	static map<string, unordered_map<string, void (*)(string email, string event, string data)>> subscribers;

	// Function to subscribe to an event to attain the service wanted
	static void subscribe(string event, string email, void (*subscriber)(string email, string event, string data)){
		subscribers[event][email] = subscriber;
	}
	// The publisher triggers the event from this and the service will take place
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
	// This is the part after the trigger which the user opted for after the event
	static void handleEvent(string email, string event, string data=""){
		if(event == "RecievedNewsLetter"){
			cout << "Email to " << email << "\n";
			cout << data;
		}
	}
};

class NewsLetterPostService{
public:
	// This is the place where the event is triggerred by the publisher
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





/*
This is something like the user wants to achieve something when a particular event happenns.
In this following example, the subscriber wants the handleEvent to happen when the publisher triggers the postEvent.
So the subscriber first subscribes the RecievedNewsLetter event with the email with the handleEvent service to happen after the event is triggerred.
The publisher triggers the event and then all the subscribers will get their services to run after the trigger happenned.
This is the purpose of Event Driven Architecture, where the EventBroker handles all the events and services to be happenning after the event is triggerred
Here,
	EmailSubscribeList -> Event Broker
	NewsLetterPostService -> Event (Triggerring part)
	NewsLetterNotification -> Response for the event (Service)
*/
