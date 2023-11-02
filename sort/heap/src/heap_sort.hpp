// heap_sort.hpp: templates, prototypes, etc
//

#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <utility>
#include <assert.h>


template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& coll)
{
    os << '{' ;
    for (const auto& e : coll)   os << " " << e ;
    return os << " }"  ;
}


// calculate indexes in the compareHeap
static inline size_t _sh_ind_parent(size_t i) { return i >> 1 ; }             // of the parent
static inline size_t _sh_ind_lc(size_t i)     { return i << 1 ; }             //        left child
static inline size_t _sh_ind_rc(size_t i)     { return (i << 1) + 1 ; }       //        right ...
static inline size_t _sh_ind_next()           { return 1 ; }                  // next to be poped-out
static inline size_t _sh_access_ind(size_t i) { assert(i > 0) ; return i - 1 ; }     // maps [Heap] index to array[]


template <typename Collection, typename Compare = std::less<typename Collection::value_type>>
void  _sh_heapify_down(size_t ind, size_t size, Collection& coll, Compare compare)   // parent -> compareChild
{
   for (size_t cleft, cright ; (cleft = _sh_ind_lc(ind)) <= size ; ) {        // Heap leaves: placed left-wards
      decltype(auto) curr = coll[_sh_access_ind(ind)] ;                       // the current element: reference expected

      // define the child to compare (if compare(left, right))
      if ((cright = _sh_ind_rc(ind)) > size)  ind = cleft ;                   // left child only
      else   {
         // std::cout << "\n> compare " << cleft << '(' << coll[_sh_access_ind(cleft)] << ") and "
         //           << cright << '(' << coll[_sh_access_ind(cright)] << ')' ;
         ind = compare(coll[_sh_access_ind(cleft)], coll[_sh_access_ind(cright)])
               ? cright : cleft ;                                             //  !compare()
      }
      decltype(auto)   comp_child = coll[_sh_access_ind(ind)] ;               // reference to the child expected
      if (compare(curr, comp_child))   std::swap(curr, comp_child) ;          // parent (!compares) OK to _comp_child
      else                             break ;                                // 'ind' already set to the chosen leaf
   }
   return ;
} // _sh_heapify_down()


// sort a Container with Container::reference operator[] ()
//    instead of RandomIterators (just for a change)
//    used members of Container
template <typename Collection, typename Compare = std::less<typename Collection::value_type>>
void  sortHeap(Collection& coll)
{
    // build a ! compareHeap
   try {
      size_t   size = coll.size() ;
      if (size < 2)   return ;                                                // nothing to sort

      Compare compare ;

      // build a Heap: indexes in [1, size]. use _sh_access_ind() to match container indexes [0, size-1]
      for (size_t ind = _sh_ind_parent(size) ; ind > 0 ; --ind) {             // build a compareHeap ;
         _sh_heapify_down(ind, size, coll, compare) ;
      } // a compareHeap is built in the Collection

      for ( ; size > 2 ; ) {                                                  // simulate heap.pop() for all
         std::swap(coll[_sh_access_ind(_sh_ind_next())], coll[_sh_access_ind(size--)]) ;
         _sh_heapify_down(_sh_ind_next(), size, coll, compare) ;
      }
      std::swap(coll[0], coll[1]) ;
   } catch (...) { throw ; }

   return ;
}


#endif // HEAP_SORT_HPP
