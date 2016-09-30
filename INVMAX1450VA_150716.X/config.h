/*****************************************************************************/
/*                                                                           */
/*                      INNERVE POWER SOLUTIONS                          */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Module name:         CONFIG.H                                             */
/*                                                                           */
/* Programmer:          Saikrishna Kashyap G                                 */
/*                                                                           */
/* Date:                2016-09-30                                           */
/*                                                                           */
/* Description:         Defines the product ID and release type of firmware  */
/*                                                                           */
/*****************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONFIG_HEADER_TEMPLATE_H
#define	CONFIG_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define VER_RELEASE             0
#define VER_PRE_RELEASE         1
#define VER_BETA                2
#define VER_ALFA                3

#define RELEASE_TYPE            VER_BETA

#define VERSION_MAJOR           1
#define VERSION_MINOR           2

// 1450VA or 1800VA
#define PRODUCT_ID_1450VA       1
#define PRODUCT_ID_1800VA       2


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

