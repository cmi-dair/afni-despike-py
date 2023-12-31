#include "afniheaders.h"

/*------------------------------------------------------------------------
   Compute the median of an array of floats.  Will rearrange (partially
   sort) the array in the process.  The algorithm is based on Quicksort,
   where we only keep the partition that has the middle element.
   For large n, this is faster than finishing the whole sort.
--------------------------------------------------------------------------*/

/* macro for median-of-3 */

#undef  MED3
#define MED3(a,b,c) ( (a < b) ? ( (a > c) ? a : (b > c) ? c : b )  \
                              : ( (b > c) ? b : (a > c) ? c : a ) )

/* macro for swap (duh) */

#undef  SWAP
#define SWAP(x,y) (temp=(x),(x)=(y),(y)=temp)

float qmed_float( int n , float * ar )
{
   register int i , j ;           /* scanning indices */
   register float temp , pivot ;  /* holding places */
   register float * a = ar ;

   int left , right , mid , nodd ;

   switch( n ){
      case 1: return ar[0] ;
      case 2: return 0.5*(ar[0]+ar[1]) ;
      case 3: return MED3( ar[0] , ar[1] , ar[2] ) ;
   }

   left = 0 ; right = n-1 ; mid = n/2 ; nodd = ((n & 1) != 0) ;

   /* loop while the subarray is at least 3 long */

   while( right-left > 1  ){  /* work on subarray from left -> right */

      i = ( left + right ) / 2 ;   /* middle of subarray */

      /* sort the left, middle, and right a[]'s */

      if( a[left] > a[i]     ) SWAP( a[left]  , a[i]     ) ;
      if( a[left] > a[right] ) SWAP( a[left]  , a[right] ) ;
      if( a[i] > a[right]    ) SWAP( a[right] , a[i]     ) ;

      pivot = a[i] ;                 /* a[i] is the median-of-3 pivot! */
      a[i]  = a[right] ;

      i = left ;                     /* initialize scanning */
      j = right ;

      /*----- partition:  move elements bigger than pivot up and elements
                          smaller than pivot down, scanning in from ends -----*/

      do{
        for( ; a[++i] < pivot ; ) ;  /* scan i up,   until a[i] >= pivot */
        for( ; a[--j] > pivot ; ) ;  /* scan j down, until a[j] <= pivot */

        if( j <= i ) break ;         /* if j meets i, quit */

        SWAP( a[i] , a[j] ) ;
      } while( 1 ) ;

      /*----- at this point, the array is partitioned -----*/

      a[right] = a[i] ;           /* restore the pivot */
      a[i]     = pivot ;

      if( i == mid ){             /* good luck */
         if( nodd ) return pivot ;   /* exact middle of array */

         temp = a[left] ;            /* must find next largest element below */
         for( j=left+1 ; j < i ; j++ )
            if( a[j] > temp ) temp = a[j] ;

         return 0.5*(pivot+temp) ;   /* return average */
      }

      if( i <  mid ) left  = i ; /* throw away bottom partition */
      else           right = i ; /* throw away top partition    */

   }  /* end of while sub-array is long */

   return (nodd) ? a[mid] : 0.5*(a[mid]+a[mid-1]) ;
}

#undef MED3
#undef SWAP