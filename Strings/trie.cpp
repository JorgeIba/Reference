struct node{
	bool endWord;
	int count;
	int children[TAM_ALPHA];
};

node Trie[SUM];
int size = 1;

void push(string str){
	int act = 0;
	for(int i = 0; i<str.size();++i){
		if(Trie[act].children[str[i]-'a'] != 0){
			act = Trie[act].children[str[i]-'a'];
		}
		else{
			Trie[act].children[str[i]-'a'] = size++;
			act = Trie[act].children[str[i]-'a'];
		}
	}
	Trie[act].endWord = true;
	Trie[act].count++;
}

bool searchWord(string str){
	bool possible = true;
	int act = 0;
	for(int i = 0; i < str.size(); ++i){
		if(Trie[act].children[str[i]-'a'] != 0)
			act = Trie[act].children[str[i]-'a'];
		else
			possible = false;
	}
	return Trie[act].endWord && possible;
}

