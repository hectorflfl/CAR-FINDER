/*
 * UART_TERMINAL.h
 *
 *  Created on: Apr 7, 2018
 *      Author: carlo
 */

#ifndef UART_TERMINAL_H_
#define UART_TERMINAL_H_



#define LETTER_B 0xb
#define LETTER_C 0xc
#define LETTER_D 0xd
#define LETTER_E 0xe
#define LETTER_F 0xf

typedef enum{
			ASCII_LETTER_A = 97,
			ASCII_LETTER_B = 98,
			ASCII_LETTER_C = 99,
			ASCII_LETTER_D = 100,
			ASCII_LETTER_E = 101,
			ASCII_LETTER_F = 102,
			ASCII_LETTER_a = 65,
			ASCII_LETTER_b = 66,
			ASCII_LETTER_c = 67,
			ASCII_LETTER_d = 68,
			ASCII_LETTER_e = 69,
			ASCII_LETTER_f = 70

}Letters;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is used for read the memory
 	 \param[in] void
 	 \return void
 */
void showmemory();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function show the default menu
 	 \param[in] void
 	 \return void
 */
void show_menu(void);
/*
const uint8 array55[]={
													 "/ymNMNmy/`"
"shhh`             shhh`                            `dMMMmhdMMMN/"
"dMMM`             dMMN`                            +MMMo   -NMMM-"
"dMMM`             dMMN`                            oMMM:    oMMMs "
"dMMM`             dMMN`                            oMMM:    oMMMs "
"dMMM`             dMMN`        `:+syyys+:`         oMMM:   -NMMM-         ./osyyyo/- `oss/"
"dMMM`             dMMN`      /hMMMMMMMMMMMd+.      oMMM: .oNMMM+       .omMMMMMMMMMMNhMMMy "
"dMMM+/////////////mMMN`    -mMMMMds+++sdMMMMMNdyo+/hMMMdmMMMMd-       oNMMMNho++oymMMMMMMy "
"dMMMMMMMMMMMMMMMMMMMMN`   :MMMMs.       .sMMMMMMMMMMMMMMMMms-        yMMMm/`       :dMMMMy "
"dMMMo+++++++++++++mMMN`  `NMMM+           +MMMM+ossdMMMs:`          /MMMN.          `hMMMy "
"dMMM`             dMMN`  -MMMm`            NMMM:   oMMM:            yMMMs            /MMMy "
"dMMM`             dMMN`  .MMMN.           .MMMM.   oMMM:            oMMMh            oMMMy "
"dMMM`             dMMN`   sMMMm-         .mMMMy    oMMM:            sMMMMs`         +MMMMy "
"dMMM`             dMMN`   `yMMMMy/.` `./yMMMMy`    oMMM:         .+dMMMMMMNo:`  `-+dMMMMMN:"
"dMMM`             dMMN`     :dMMMMMMMMMMMMMd/  -mmmNMMMNmmmmmmmNMMMMMd-oNMMMMMMMMMMMMNyNMMMNy"
"hNNN`             hNNN`       .+hmNMMMNmho-    :NNNNNNNNNNNNNNNNmhy+.    :sdNMMMMNdy/` `/ydNh"
};
*/

#endif /* UART_TERMINAL_H_ */
