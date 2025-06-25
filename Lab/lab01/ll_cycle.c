#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node* hare, *tortoise;
    hare = tortoise = head;
    while (hare && hare->next) {
        hare = hare->next->next;
        tortoise = tortoise->next;
        if (hare == tortoise) {
            return 1;    
        }
    }
    return 0;
}
