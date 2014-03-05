struct set {
	int v1;
	int v2;
	int v;
	int w;
	struct set *next;
	struct set *rep;
};

struct set *head;

struct set *makeSet(int v1, int v2, int w) {
	struct set *tmp = (struct set *)malloc(sizeof(struct set *)));
	tmp->v1 = v1;
	tmp->v2 = v2;
	tmp->v = (v1>v2)?v1:v2;
	tmp->w = w;
	tmp->next = NULL;
	tmp->rep = NULL;

	return tmp;
}

int findRep(struct set *repRef) {
	if(repRef == NULL) {
		return -1;
	}

	return repRef->v;
}

struct set *union(struct set *repRef1, struct set *repRef2) {
	struct set *tmp;
	
	if((!repRef1) || (!repRef2)) {
		if((!repRef1) && (!repRef2)) {
			return NULL;
		}
		else if(!repRef1){
			return repRef2;
		}
		else {
			return repRef1;
		}
	}

	if(repRef1->v > repRef2->v) {
		tmp = repRef2;
		while(tmp) {
			tmp->rep = repRef1;
			tmp = tmp->next;
		}
		
		tmp = repRef1;

		while(tmp->next) {
			tmp = tmp->next;
		}
		
		tmp->next = repRef2;
		return repRef1;
	}
	else {
		tmp = repRef1;
		while(tmp) {
			tmp->rep = repRef2;
			tmp = tmp->next;
		}
		tmp = repRef2;
		while(tmp->next) {
			tmp = tmp->next;
		}

		tmp->next = repRef1;
		return repRef2;
	}
	return NULL;
}
