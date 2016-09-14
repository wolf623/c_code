
#ifndef __CASA_G_TREE_H__
#define __CASA_G_TREE_H__

#include <pthread.h>
#include "glib/glib.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _CGtree
{
        GTree *tree;
        ///pthread_mutex_t lock;
        pthread_rwlock_t rw_lock; // bug 33188
} CGtree;

//#define  casa_g_tree_nnodes(_CGtree) g_tree_nnodes((_CGtree)->tree)
int  casa_g_tree_nnodes(CGtree * _CGtree) ;
/**
 * casa_g_tree_has_more_nodes:
 * @tree: a #CGtree.
 * 
 * check if the #CGtree contains at least min_cnt nodes
 * 
 * Return value: TRUE if nnodes > min_cnt, else FALSE.
 **/
gboolean
casa_g_tree_has_more_nodes (CGtree * ctree, int min_cnt);

int  casa_g_tree_new(CGtree *ctree, GCompareFunc key_compare_func);
void casa_g_tree_destroy(CGtree *ctree);
void casa_g_tree_insert(CGtree *ctree, gpointer key, gpointer value);
void casa_g_tree_remove(CGtree *ctree, gconstpointer key);
void casa_g_tree_traverse(CGtree *ctree, GTraverseFunc traverse_func,
       GTraverseType traverse_type, gpointer user_data);
gpointer casa_g_tree_lookup(CGtree *ctree, gconstpointer key);

/**
  * none-recursive version of g_tree lookup
  **/
gpointer
casa_g_tree_lookup_next (CGtree    *ctree,
	       gpointer  key);

/**
 * g_tree_lookup_next:
 * @tree: a #GTree. 
 * @key: the key to look up.
 * 
 * Gets the value corresponding to the next node of the specified key.
 * Since a #GTree is automatically balanced as key/value pairs are added, 
 * key lookup is very fast. * 
 *
 * Return value: the value corresponding to the next node of the specified key,
 * or %NULL if the next node was not found.
 * 
 **/    
gpointer
casa_g_tree_lookup_nr (CGtree    *ctree,
               gpointer  key);

/**
 * g_tree_lookup_nlt:
 * @tree: a #GTree. 
 * @key: the key to look up.
 * 
 * Gets the value corresponding to the node which key is not less than the 
 * specified key. Since a #GTree is automatically balanced as key/value pairs are added, 
 * key lookup is very fast. * 
 *
 * Return value: the value corresponding to the node which key is not less 
 * than the specified key, or %NULL if the next node was not found.
 * 
 **/
gpointer
casa_g_tree_lookup_nlt (CGtree    *ctree,
	       gpointer  key);

#ifdef  __cplusplus
}
#endif


#endif /* __CASA_G_TREE_H__ */

