/*-------------------------------------------
| Copyright(C) 2007 CHAUVIN-ARNOUX
---------------------------------------------
| Project:
| Project Manager:
| Source: dev_mkconf.c
| Path: X:\sources\kernel\config
| Authors:
| Plateform:
| Created:
| Revision/Date: $Revision: 1.14 $  $Date: 2007/12/03 11:29:39 $
| Description:
---------------------------------------------
| Historic:
---------------------------------------------
| Authors	| Date	| Comments
 -
---------------------------------------------*/


/*===========================================
Includes
=============================================*/
#include "kernel/core/kernelconf.h"
#include "kernel/fs/vfs/vfsdev.h"


/*===========================================
Global Declaration
=============================================*/


extern dev_map_t  dev_null_map;
extern dev_map_t  dev_proc_map;
extern dev_map_t  dev_cpufs_map;
extern dev_map_t  dev_pipe_map;
extern dev_map_t  dev_ppp_uip_map;
extern dev_map_t  dev_sock_map;
extern dev_map_t  dev_lm3s_cpu_map;
extern dev_map_t  dev_stm32f1xx_ijinus_073_board_map;
extern dev_map_t  dev_stm32f1xx_uart_s1_map;
extern dev_map_t  dev_stm32f1xx_uart_s2_map;
extern dev_map_t  dev_stm32f1xx_uart_s3_map;
extern dev_map_t  dev_cmsis_itm0_map;
extern dev_map_t  dev_os_debug_map;
extern dev_map_t  dev_stm32f1xx_spi_1_map;
extern dev_map_t  dev_spi_chip_select_map;
extern dev_map_t  dev_flash_nand_at45db_map;


pdev_map_t const dev_lst[]={
&dev_null_map,
&dev_proc_map,
&dev_cpufs_map,
&dev_pipe_map,
&dev_ppp_uip_map,
&dev_sock_map,
&dev_lm3s_cpu_map,
&dev_stm32f1xx_ijinus_073_board_map,
&dev_stm32f1xx_uart_s1_map,
&dev_stm32f1xx_uart_s2_map,
&dev_stm32f1xx_uart_s3_map,
&dev_cmsis_itm0_map,
&dev_os_debug_map,
&dev_stm32f1xx_spi_1_map,
&dev_spi_chip_select_map,
&dev_flash_nand_at45db_map
};

pdev_map_t const * pdev_lst=&dev_lst[0];
const char max_dev = sizeof(dev_lst)/sizeof(pdev_map_t);
/*===========================================
Implementation
=============================================*/


/*===========================================
End of Source dev_mkconf.c
=============================================*/
