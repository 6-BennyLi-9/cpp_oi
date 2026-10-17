#include <cstdio>
#include <cstring>


class CharNode {
public:
	char value;
	CharNode *next;
	CharNode(){
		value = '\0';
		next = nullptr;
	}

	CharNode(char value){
		this->value = value;
		next = nullptr;
	}

	~CharNode(){
		if (next != nullptr){
			delete next;
		}
	}
};

class Integer {
private:
	CharNode *head,*end;
public:
	Integer(){
		head = new CharNode;
		end = head;
	}

	void readFromStream(){
		end = head;
		while(true){
			char cache;
			scanf("%c", &cache);
			if(cache == '\n'){
				break;
			}
			end -> value = cache;
			end -> next = new CharNode;
			end = end -> next;
		}
	}

	void printToStream(){
		CharNode *ptr = head;
		while (ptr != end){
			printf("%c", ptr -> value);
			ptr = ptr -> next;
		}
		
	}

	~Integer(){
		delete head;
		delete end;
	}
};

Integer n;

int main() {
    n.readFromStream();
	n.printToStream();
	return 0;
}
