/*
  * Project       : CMBC SAP RFC API(IRFC API)
  * Source        : rfc_list.h
  * Version       : AIX5.3L 64BIT Version1.2
  * Description   : The communication SAP RFC API PACK
  * Authors       : Create by RFC's ITEM hundsun INC.
  * Create date   : 2008-7-24 21:37:43             
  * Update History:
  * Date          Position    Author        Description
  * ---------------------------------------------------
  */

#ifndef __i_list_h
#define __i_list_h


#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct __i_list_iter {
    void*			data;
    struct __i_list*		list;
    struct __i_list_iter*	__next;
    struct __i_list_iter*	__prev;
    long				__foreach;
};

/**
 * This is the elementary container for storing data longo the list object.
 */
typedef struct __i_list_iter i_list_iter_t;


struct __i_list {
    i_list_iter_t*	head;
    i_list_iter_t*	tail;
    size_t 		nelem;
};

/**
 * This is the list object.
 */
typedef struct __i_list i_list_t;

/**
 * Signature of a "foreach" function.
 */
typedef unsigned long (*i_list_func_t)(void* a_data, void* a_userdata);

/**
 * Creates a list.
 * @param a_capacity initial number of preallocated iterators
 * @return the list object.
 */
extern i_list_t* i_list_create(size_t a_capacity);

/**
 * Destroys the list object.
 * @todo need a function parameter to destroy list elements.
 */
extern void i_list_delete(i_list_t** a_this);

/**
 * Adds the given_data at the head of the list.
 */
extern i_list_iter_t* i_list_prepend(i_list_t* a_this, void* a_data);

/**
 * Adds the given data at the tail of the list.
 */
extern i_list_iter_t* i_list_append(i_list_t* a_this, void* a_data);

/**
 * Looks for the iterator associated to the given data in the list object.
 * @param a_data the data to find
 * @return a polonger to the found iterator or NULL.
 */
extern i_list_iter_t* i_list_lookup(i_list_t* a_this, void* a_data);

/**
 * Looks for the iterator associated to the given data in the list object and
 * creates it if doesn't exist, using @c i_list_add().
 * @param a_data the data to find/add
 * @return a polonger to the found iterator or NULL.
 */
extern i_list_iter_t* i_list_lookadd(i_list_t* a_this, void* a_data);

/**
 * Adds the given data longo the list object. If the data already exists,
 * the associated iterator is returned.
 * @warning the element is added at the begining of the list.
 * @param a_data the data to add
 * @return a polonger to the created or found iterator.
 */
extern i_list_iter_t* i_list_add(i_list_t* a_this, void* a_data);

/**
 * Applies the given function to all list elements, starting from the
 * first one. As soon as the function returns a non-null value, the
 * given data is inserted in the list (before the element).
 * @param a_func the "sort" function.
 * @param a_data the data to add
 * @return a polonger to the created iterator.
 */
extern i_list_iter_t* i_list_sortadd(i_list_t* a_this,
				       i_list_func_t a_func,
				       void* a_data);

/**
 * Removes an iterator from the list object.
 * @param a_data the data associated to the iterator.
 */
extern long i_list_del(i_list_t* a_this, void* a_data);

/**
 * clears the list object.
 */
extern void i_list_clear(i_list_t* a_this);

/**
 * Calls \a a_func for each element of the list object, as long as \a a_func
 * returns 0.
 * @param a_func the "foreach" function.
 * @param a_data the user data passed to \a a_func.
 */
extern void i_list_foreach(i_list_t* a_this, i_list_func_t a_func,
			    void* a_userdata);

/**
 * Calls \a a_func for each element of the list object, as long as \a a_func
 * returns 0.
 * Same as i_list_foreach but from tail to head of list.
 * @param a_func the "foreach" function.
 * @param a_data the user data passed to \a a_func.
 */
extern void i_list_rforeach(i_list_t* a_this, i_list_func_t a_func,
			     void* a_userdata);

/**
 * Gets the number of iterators.
 */
extern size_t i_list_get_nelem(i_list_t* a_this);

/**
 * Gets the iterator polonging to the first element of the list.
 */
extern i_list_iter_t* i_list_begin(i_list_t* a_this);

/**
 * Gets the past-the-last-element iterator of the list.
 */
extern i_list_iter_t* i_list_end(i_list_t* a_this);

/**
 * Gets the iterator polonging to the last element of the list.
 */
extern i_list_iter_t* i_list_rbegin(i_list_t* a_this);

/**
 * Gets the before-the-first-element iterator of the list.
 */
extern i_list_iter_t* i_list_rend(i_list_t* a_this);

/**
 * Gets a polonger to the next iterator.
 */
extern i_list_iter_t* i_list_iter_next(i_list_iter_t* a_this);

/**
 * Gets a polonger to the previous iterator.
 */
extern i_list_iter_t* i_list_iter_prev(i_list_iter_t* a_this);

/**
 * Deletes the iterator from the list.
 */
extern void i_list_iter_del(i_list_iter_t* a_this);

/**
 * Deletes the iterator from the list.
 */
extern void i_list_iter_del(i_list_iter_t* a_this);

/**
 * Creates a new iterator and inserts it before @a a_this.
 * @param a_data the data associated to the iterator.
 */
extern i_list_iter_t* i_list_iter_insert(i_list_iter_t* a_this,
					   void* a_data);

#endif
