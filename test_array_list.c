#include "array_list.c"

int main(void) {
    // Struct Test
    a_test t[] = {{.a = 3}, {.a = 2}, {.a = 1}};
    array_list *t_list = init_list(3, compare_test);
    add_value(t_list, &t);
    add_value(t_list, &t[1]);
    add_value(t_list, &t[2]);
  
    printf("before qsort: "); walk(t_list, show_test);
    qsort(t_list->values, t_list->len, sizeof(void*), t_list->compare);
    printf("\nafter qsort: "); walk(t_list, show_test);
    printf("\nminimum: %d\n",((a_test*) t_list->minimum)->a);
    printf("maximum: %d\n",((a_test*) t_list->maximum)->a);
  
    // Int test
    int i[] = {5,4,3,2,1};
    array_list *i_list = init_list(5, compare_int);
    add_value(i_list, &i);
    add_value(i_list, &i[1]);
    add_value(i_list, &i[2]);
    add_value(i_list, &i[3]);
    add_value(i_list, &i[4]);
    
    printf("\nbefore qsort: "); walk(i_list, show_int);
    qsort(i_list->values, i_list->len, sizeof(void*), i_list->compare);
    printf("\nafter qsort: "); walk(i_list, show_int);
    printf("\nminimum: %d\n",((a_test*) i_list->minimum)->a);
    printf("maximum: %d\n",((a_test*) i_list->maximum)->a);
  
    return  EXIT_SUCCESS;
  }