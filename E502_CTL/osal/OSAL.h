#ifndef OSAL_H
#define OSAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "data_type.h"
#include "stm8s.h"



/*********************************************************************
 * FUNCTIONS
 */

/*** Task Synchronization  ***/

  /*
   * Set a Task Event
   */
  extern u8 osal_set_event( u8 task_id, u16 event_flag );


  /*
   * Clear a Task Event
   */
  extern u8 osal_clear_event( u8 task_id, u16 event_flag );


/*** Task Management  ***/

  /*
   * One Pass Through the OSAL Processing Loop
   */
  extern void osal_run_system( void );

#ifdef __cplusplus
}
#endif

#endif /* OSAL_H */
