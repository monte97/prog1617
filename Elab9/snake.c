#include "snake.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

static unsigned int rows;
static unsigned int cols;

/*
salva i valori della dimensione della griglia di gioco e inizializza RNG
*/
static void init_libVale(unsigned int r, unsigned int c, unsigned int rand_seed);

/*dice se la lista è vuota*/
static int is_empty(struct snake *s);

/*compara due nodi*/
static int compare_nodes(struct snake *s1, struct snake *s2);

/*inserisce una nuova testa nella lista*/
static void head_insert(struct snake **s, struct position p);

/*rimuove la coda*/
static void tail_remove(struct snake *s);

/*ritorna la posizione aggiornata dal movimento*/
static struct position update_position(struct position p, enum direction d);

/*scorre la la lista e ritorna la coda*/
static struct snake* get_tail(struct snake *s);

struct snake *snake_create(unsigned int rows, unsigned int cols){
	init_libVale(rows, cols, time(NULL));
	static struct snake *s;

	s = (struct snake*) malloc(sizeof(struct snake));

	s->i = rand()%rows;
	s->j = rand()%cols;
	s->prev = NULL;
	s->next = NULL;

	return s;
}


/*
 * Destroys the snake data structure.
 */
void snake_kill(struct snake *s){
	if (!is_empty(s)){
		snake_kill(s->next);
		free(s);
		s = NULL;
	}
}
/*
 * Returns the (position of the) snake's head.
 */
struct position snake_head(struct snake *s){
	struct position p;

	p.i = s->i;
	p.j = s->j;

	return p;

}
/*
 * Returns the (position of the) i-th part of the snake body.
 * 
 * Position 0 is equivalento the snake's head. If the snake
 * is shorter than i, the position returned is not defined. 
 */
struct position snake_body(struct snake *s, unsigned int i){
	unsigned int l_index = 0;
	struct position p;

	/*scorro la lista finché non arrivo al nodo che mi serve*/
	while (!is_empty(s) && l_index < i){
		s = s->next;
		l_index++;
	}

	/*per poi ritornarne le coordinate*/
	p.i = s->i;
	p.j = s->j;

	return p;
}
/*
 * Returns 1 if the snake crosses himself, 0 otherwise.
 */ 
int snake_knotted(struct snake *s){
	/*confrotnare la testa con ogni altro nodo del serpente*/
	struct snake *snake_head = s;

	s = s->next; /*dopo avere creto una copia della testa passo direttamete al successivo*/

	/*finchè la lista non è finita 
	effettuo il confronto della testa con l'attuale, se coincidono si stanno scontrando e ritorno uno
	passo al successivo

	se sono arrivato alla fine del ciclo posso uscire ritornando a 0
	*/
	while(!is_empty(s)){
		if (compare_nodes(snake_head, s)) return 1;
		s = s->next;
	}
	return 0;
}
/*
 * Moves the snake one step forward in the dir direction
 * into a toroidal world of size rows*cols.
 */
/*inserire una nuova testa con le coordinate aggiornate
 *rimuovere la vecchia coda
*/
void snake_move(struct snake **s, enum direction dir){
	struct position p = update_position(snake_head(*s), dir);
	head_insert(s, p);
	tail_remove(*s);
}
/*
 * Reverses the snake.
 *
 * The tail of the snake is now the new head.
 */
/*swappare i due puntatori aggiornando i vari campi*/
/*
costruire ricorsivamente una nuova lista?

*/
void snake_reverse(struct snake **s){
	struct snake *head = *s;
	struct snake *tail = get_tail(*s);
	struct snake *support;

	struct snake *iter;

	if ( head == tail ){} /*lungo 1*/
	else if (head -> next == tail){ /*lungo 2*/
		

		head -> prev = tail;
		tail -> next = head;

		head -> next = NULL;
		tail -> prev = NULL;

		*s = tail;
	}else{ /*lungo almeno 3*/
		/*
		devo invertire la lista
		
		1) setto la nuova testa come la coda
		2) scorro al contrario partendo dalla cosa
			aggiorno ogni puntatore a prev e next	
		*/
		
		iter = head;
		while (iter != NULL){
			/*scambio il puntatore al prev e al next*/
			support = iter -> next;
			iter -> next = iter -> prev;
			iter -> prev = support;

			iter = iter -> prev;

		}
		
		/*a questo punto sono sulla coda*/
		tail -> prev = NULL;
		head -> next = NULL;


		*s = tail; /*la referenza della testa è la coda*/
	}
	

}
/*
 * Increases the snake length.
 *
 * This is equivalent to:
 * - add a new head in the dir direction wrt the old head.
 */
/*come move ma non si rimuove la testa*/
void snake_increase(struct snake **s, enum direction dir){
	struct position p = update_position(snake_head(*s), dir);
	head_insert(s, p);
}
/*
 * Removes from the tail of the snake decrease_len parts.
 */
/*applico n volte la rimozione della coda*/
void snake_decrease(struct snake **s, unsigned int decrease_len){
	unsigned int i;

	for (i = 0; i < decrease_len; i++){
		tail_remove(*s);
	}
}


static void init_libVale(unsigned int r, unsigned int c, unsigned int rand_seed){
	rows = r;
	cols = c;

	srand(rand_seed);
}

static int is_empty(struct snake *s){
	return (s == NULL);
}

static int compare_nodes(struct snake *s1, struct snake *s2){
	return ((s1 -> i == s2 -> i && s1 -> j == s2 -> j));
}

static void head_insert(struct snake **s, struct position p){
	struct snake *new_node;

	new_node = (struct snake*)malloc(sizeof(struct snake));

	new_node->prev = NULL;
	new_node->next = *s;
	new_node->i = (p.i+rows)%rows;
	new_node->j = (p.j+cols)%cols;

	(*s)->prev = new_node;

	*s = new_node;
}


/*assumo che ci siano almeno due nodi nella struttura quando invoco*/
static void tail_remove(struct snake *s){
	struct snake *temp;

	s = get_tail(s);

	/*a questo punto sono posizionato sull'ultimo nodo*/

	temp = s; /*reference all'ultimo elemento*/

	/*torno al penultimo per aggiornare il puntatore a next*/
	s = s->prev;
	s->next = NULL;

	/*libero la memoria associata all'ulitmo nodo*/
	free (temp);
}

static struct position update_position(struct position p, enum direction d){
	switch (d){
		case UP:
			p.i--;
			break;

		case DOWN:
			p.i++;
			break;

		case LEFT:
			p.j--;
			break;

		case RIGHT:
			p.j++;
			break;
	}

	return p;
}


static struct snake* get_tail(struct snake *s){
	/*finché il nodo successivo all'attuale non è nullo*/
	while (s->next != NULL){
		s = s->next; /*passo al successivo*/
	}
	return s;
}