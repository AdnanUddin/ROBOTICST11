#ifndef _SERIAL_H_
#define _SERIAL_H_

#define BAUD 2400
#define NINE 0     /* Use 9bit communication? FALSE=8bit */

#define DIVIDER 51
#define HIGH_SPEED 0

#if NINE == 1
#define NINE_BITS 0x40
#else
#define NINE_BITS 0
#endif

#if HIGH_SPEED == 1
#define SPEED 0x4
#else
#define SPEED 0
#endif

#if defined(_16F87) || defined(_16F88)
	#define RX_PIN TRISB2
	#define TX_PIN TRISB5
#else
	#define RX_PIN TRISC7
	#define TX_PIN TRISC6
#endif
/**
 * @brief Intializes the communcations on USART.
 * @retval None
 */
void init_comms(void);

/**
 * @brief Writes a char to the USART
 * @param char The character to be written
 * @retval None
 */
void putch(unsigned char);

/**
 * @brief Gets a char from the USART
 * @retval Char from the USART
 */
unsigned char getch(void);

/**
 * @brief Echos the character pulled from the USART
 * @retval Returns the character
 */
unsigned char getche(void);

#endif
