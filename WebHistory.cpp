#include "WebHistory.hpp"

WebHistory::WebHistory()
{
    // Does nothing.
}

WebHistory::WebHistory(std::string historyText)
{
	// history = url timestamp | url timestamp | url timestamp...
    // urls are string and timestamps are non-negative integers.
    std::string delimiter = " | ";

	std::string tabInfo;
    std::string url;
    std::string timestamp;
    size_t pos = 0;

    while (true)
	{
        pos = historyText.find(delimiter);

        bool breakTheLoop = (pos == std::string::npos);

        tabInfo = historyText.substr(0, pos);
        historyText.erase(0, pos + delimiter.length());

        pos = tabInfo.find(" ");
        
        url = tabInfo.substr(0, pos);
        timestamp = tabInfo.substr(pos + 1, tabInfo.length() - pos);

		Node<Tab> *newPage = new Node<Tab>(Tab(url, std::atoi(timestamp.c_str())), NULL, NULL);
        insertInOrder(newPage);

        if (breakTheLoop)
		{
			break;
		}
    }
}

void WebHistory::printHistory()
{
	std::cout << "Your web history:" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
	if (history.getHead()->next == history.getTail())
	{
		std::cout << "History is empty." << std::endl;
		std::cout << std::endl;
	}
	else
	{
		Node<Tab> *node = history.getFirstNode();
		
		while (node != history.getTail())
		{
		    std::cout << "Page: " << node->element.getUrl() << std::endl;
			std::cout << "Last Visited: " << node->element.getTimestamp() << std::endl;
			std::cout << std::endl;
		    node = node->next;
		}
	}
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

WebHistory::WebHistory(std::string url, int timestamp)
{
	Node<Tab> *head = history.getHead();
	Node<Tab> *tail = history.getTail();
	Node<Tab> *newPage = new Node<Tab>(Tab(url,timestamp), head, tail);
	head->next = newPage;
	tail->prev = newPage;
	head->prev = NULL;
	tail->next = NULL;
}

WebHistory::~WebHistory()
{

}

void WebHistory::insertInOrder(Node<Tab> *newPage)
{
	Node<Tab> *head = history.getHead();
	Node<Tab> *tail = history.getTail();
	Node<Tab> *current = head->next;

	while((current!= NULL) && (current!=tail) && ((newPage->element.getTimestamp()) < (current->element.getTimestamp()))){
		current = current->next;
	}

	newPage->prev = current->prev;
	newPage->next = current;
	current->prev->next = newPage;
	current->prev = newPage;
}

void WebHistory::goToPage(std::string url, int timestamp)
{
	Node<Tab> *newPage = new Node<Tab>();
	newPage->element.setUrl(url);
	newPage->element.setTimestamp(timestamp);
	insertInOrder(newPage);
}

void WebHistory::clearHistory()
{
	history.removeAllNodes();
}

void WebHistory::clearHistory(int timestamp)
{
	Node<Tab> *head = history.getHead();
	Node<Tab> *tail = history.getTail();
	Node<Tab> *current = head->next;
	while(current->element.getTimestamp() > timestamp && current!=tail){
		current=current->next;
	}
	while (current!=tail){
		Node<Tab> *temp = current->next;
		history.removeNode(current);
		current = temp;
	}
}

WebHistory WebHistory::operator+(const WebHistory &rhs) const
{		
	WebHistory newhist;
	Node<Tab> *current = history.getHead()->next;
	while(current!=history.getTail()){
		newhist.goToPage(current->element.getUrl(), current->element.getTimestamp());
		current = current->next;
	}

	Node<Tab> *current1 = rhs.history.getHead()->next;
	while(current1!=rhs.history.getTail()){
		newhist.goToPage(current1->element.getUrl(), current1->element.getTimestamp());
		current1 = current1->next;
	}
	return newhist;
}


int WebHistory::timesVisited(std::string pageName)
{
	Node<Tab> *head = history.getHead();
	Node<Tab> *tail = history.getTail();
	Node<Tab> *current = head->next;
	int i = 0;
	while(current!=tail){
		if(current->element.getWebSite() == pageName){
			i++;
		}
		current = current->next;
	}
	return i;
}

std::string WebHistory::mostVisited()
{
	Node<Tab> *head = history.getHead();
	Node<Tab> *tail = history.getTail();
	Node<Tab> *current = head->next;
	Node<Tab> *most = current;
	Node<Tab> *temp = current->next;
	if(current!=tail){
		while(temp!=NULL && temp!=tail){
			if(timesVisited(temp->element.getWebSite()) > timesVisited(most->element.getWebSite())){
				most = temp;
			}
			temp = temp->next;
		}
	}
	return most->element.getWebSite();
}