
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef struct tree{
    struct tree *p;
    struct tree *r;
    struct tree *l;
    int v;
    unsigned int h;

}Tree;

Tree* newnode(int num);
void adicionar(Tree **R, int v);
void update(Tree* n);
int max(int num1, int num2);
void p1(Tree *x);
void tprint( Tree* x);



int main (void) {

    Tree *raiz = NULL;
    adicionar(&raiz, 10);
    adicionar(&raiz, 5);
    tprint(raiz);

    
}


void adicionar(Tree **R, int v){

    struct tree *f;
    struct tree *p;
    Tree *w = newnode(v);

    if(*R == NULL){
        *R = w;
    }else{

        p = *R;

        while(p != NULL){
            f = p;

            if(p->v == v){
                return;
            }
            else if(p->v > w->v){
                p = p->l;
            }else{
                p = p->r;
            }
        }

        w->p = f;

        if(w->v < f->v){
            f->l = w;
        }else{
            f->r = w;
        }

        update(f);
    }
} 



void update(Tree* n){


    
}

void p1(Tree *x){
    
    Tree *y = x->r;
    Tree *b = y->l;

    if(x->p != NULL){
        if(x->p->r == x){
            x->p->r = y;
        }else{
            x->p->l = y;
        }
    }
    y->p = x->p;

    x->p = y;
    y->l = x;
    b->p = x;
    x->r = b;
}



Tree* newnode(int num){

    Tree* a = (Tree*)malloc(sizeof(Tree));

    a->v = num;
    a->l = NULL;
    a->r = NULL;
    a->h = 0;
    return a;

}

int max(int num1, int num2){

    int maior;
    
    (num1 > num2) ? (maior = num1) : (num2 > maior);

    return maior;

}

void tprint( Tree* x){
    if(x != NULL){
        tprint(x->l);
        printf("%p %d %p %p \n", x , x->v, x->l, x->r);
        tprint(x->r);
    }
}