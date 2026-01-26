/*
 * common_define.h
 *
 *  Created on: 2019年10月26日
 *      Author: master
 */

#ifndef SRC_CFG_PRINTF_H_
#define SRC_CFG_PRINTF_H_

#include <stdio.h>
#include <errno.h>


//#define DEBUG_PRINT(fmt, args ...)     printf("XML parse debug: " #fmt "\n", ##args)
#define DEBUG_PRINT()


//#define DEBUG_PRINT_FILE_LINE() printf("%s:%d\n", __FILE__, __LINE__)

//#define DEBUG_PRINT_FUNC_LINE() printf("%s:%d\n", __FUNCTION__, __LINE__)
#define DEBUG_PRINT_FUNC_LINE() 

#define ERROR_PRINT(fmt, args ...) printf("XML parse error: " #fmt "\n", ##args);

#define WARNING_PRINT(fmt, args ...) printf("XML parse warning: " #fmt "\n", ##args);

#define INFO_PRINT(fmt, args...) printf("XML parse: " #fmt "\n", ##args);




#endif /* SRC_PRINTF_DEFINE_H_ */
