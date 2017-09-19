#include <stdlib.h>
#include <stdio.h>
#include "bigint.h"

struct BigInt{
	unsigned int digit;
	struct BigInt *next;
	struct BigInt *prev;
};



static bigint *head_insert(bigint **head, bigint **tail, unsigned long int val);
static bigint *tail_insert(bigint **head, bigint **tail, unsigned long int val);
static void make_circular(bigint *head, bigint *tail);
static bigint *make_straigth(bigint *head);
static unsigned long int get_length(bigint *head, bigint *tail);
static void destroy_bigint(bigint *head);
static int is_circular(bigint *head);
static int is_straigth(bigint *head);


/*
 * Converts the unsigned long int x into the bigint representation. 
 */
bigint *int2bigint(unsigned long int x){
	bigint *head_ptr = NULL;
	bigint *tail_ptr = NULL;
	do{
		tail_insert(&head_ptr, &tail_ptr, x%10);
	}while(x/=10);
	make_circular(head_ptr, tail_ptr);
	return head_ptr;

}
/*
 * Converts string representation of a positive integer number into
 * the bigint representation.
 * i
 * Returns a pointer to the bigint structure or NULL if the conversion 
 * cannot be performed.
 */
bigint *str2bigint(char *str){
	bigint *head_ptr = NULL;
	bigint *tail_ptr = NULL;
	while(*str != '\0'){
		//printf("%d\n", (*str)-48);
		if ((*str) >= 48 && (*str) <= 57) {
			head_insert(&head_ptr, &tail_ptr, (*str)-48);
			//printf("testa = %d\n", head_ptr -> digit);
			//update_reference(head_insert(&head_ptr, (*str)-48 ), &head_ptr, &tail_ptr );
		}else{
			clear(&head_ptr);
			return NULL;
		}
		str++;
	}

	make_circular(head_ptr, tail_ptr);

	//if (tail_ptr -> next == head_ptr && head_ptr -> prev == tail_ptr) printf("è circolare\n");

	//è ancora a nullo
	return head_ptr;


}
/*
 * Converts a bigint number into a (printable) string.
 *
 * Returns a pointer to the first character of the string or NULL if 
 * the conversion cannot be performed.
 */
char *bigint2str(bigint *num){
	char *string;
	bigint *head_ptr = num;
	bigint *tail_ptr = num->prev;
	bigint *iter = head_ptr -> prev;
	unsigned long int index = 0;
	unsigned long int num_size = get_length(head_ptr, tail_ptr);

	string = (char*)calloc(num_size+1, sizeof(char));

	//printf("dimensione = %d\n", num_size);
	//printf("testa = %d, coda = %d\n", head_ptr->digit, tail_ptr->digit);
	for (index = num_size; index > 0; index--){
		//printf("index = %d\n", index);
		string[index-1] = (iter -> digit)+48;
		//printf("string[%d] = %c\n",index, string[index]);
		iter = iter -> prev;
	}
	
	return string;
}

/*
 * Returns the sum of the two input numbers or NULL if the operation 
 * cannot be performed.

 non mette la cifra più significativa se i due numeri hanno lunghezze diverse
 */
bigint *sum(bigint *num1, bigint *num2){
	bigint *num1_head = num1, *num2_head = num2;
	bigint *num1_tail = num1->prev, *num2_tail = num2->prev;
	unsigned short int add1, add2, carry = 0;
	bigint *sum_head = NULL;
	bigint *sum_tail = NULL;

	
	make_straigth(num1);
	make_straigth(num2);
	do{
		add1 = (num1 != NULL) ? num1 -> digit : 0;
		add2 = (num2 != NULL) ? num2 -> digit : 0;
		head_insert(&sum_head, &sum_tail, (add1 + add2 + carry)%10 );
		if (num1 != NULL) num1 = num1 -> next;
		if (num2 != NULL) num2 = num2 -> next;
		carry = (add1 + add2 + carry)/10;

		add1 = (num1 != NULL) ? num1 -> digit : 0;
		add2 = (num2 != NULL) ? num2 -> digit : 0;

	}while( add1 ||  add2 || carry);

	make_circular(num1_head, num1_tail);
	make_circular(num2_head, num2_tail);
	make_circular(sum_head, sum_tail);
	return sum_head;
}

/*
*Destroys hte bigint data structure
recives the pointer to the head of the structur
*/
void clear(bigint **num){
	
	if (is_circular(*num)) make_straigth(*num);
	
	bigint *temp = *num;
	destroy_bigint(temp);
	
	num = NULL;

}


static bigint *head_insert(bigint **head, bigint **tail, unsigned long int val){
	bigint *new = (bigint*)malloc(sizeof(bigint));

	//new diverrà la nuova testa
	new -> digit = val;
	new -> prev = NULL; //prima non ha nulla
	new -> next = *head; //dopo ha il resto del corpo


	if (*head != NULL){
		(*head)->prev = new;
	}else {
		*tail = new;
		tail = &new;
	}
 	//il precendente della testa è il nuovo nodo
	//printf("test aggiornamento prev testa\n");

	*head = new;
	head = &new; //aggiorno la reference della testa
	return new;
}

static bigint *tail_insert(bigint **head, bigint **tail, unsigned long int val){
	bigint *new = (bigint*)malloc(sizeof(bigint));

	new -> digit = val;
	new -> prev = *tail;
	new -> next = NULL;

	if (*tail != NULL){
		(*tail)->next = new;
	}else{
		*head = new;
		head = &new;
	}

	*tail = new;
	tail = &new;
	return new;
}



/*devo rendere circolar una lista "stesa"*/
static void make_circular(bigint *head, bigint *tail){
	head -> prev = tail;
	tail -> next = head;
}

static unsigned long int get_length(bigint *head_ptr, bigint *tail_ptr){
	unsigned long int size = 1;
	while (head_ptr != tail_ptr){
		size++;
		head_ptr = head_ptr -> next;
	}
	return size;
}

static bigint *make_straigth(bigint *head){
	bigint *tail = head -> prev;

	head -> prev = NULL;
	tail -> next = NULL;

	return tail;

}

static void destroy_bigint(bigint *head_ptr){
	if (head_ptr != NULL){
		destroy_bigint(head_ptr->next);
		free(head_ptr);
		head_ptr = NULL;
	}
}


static int is_circular(bigint *head){
	return head->prev != NULL;
}

static int is_straigth(bigint *head){
	return head->prev == NULL;
}
