#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "mavlink_avoid_errors.h"
#include "uartfifo.h"
#include "open_tel_mavlink.h"
mavlink_system_t mavlink_system;
#define UART_TX_BUFFER_SIZE 255
#define UART_RX_BUFFER_SIZE 255
extern fifo_t uart_rx_fifo, uart_tx_fifo;
extern uint8_t uart_tx_buf[UART_TX_BUFFER_SIZE], uart_rx_buf[UART_RX_BUFFER_SIZE];
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();//延时初始化
	uart_init(115200);//串口初始化波特率为115200
	LED_Init();//初始化与LED连接的硬件接口
	fifo_init(&uart_tx_fifo, uart_tx_buf, UART_TX_BUFFER_SIZE);
	fifo_init(&uart_rx_fifo, uart_rx_buf, UART_RX_BUFFER_SIZE);
	mavlink_system.sysid = MAV_TYPE_GENERIC;
	mavlink_system.compid = MAV_AUTOPILOT_GENERIC;
	while(1)
	{
		mavlink_send_message(0, MSG_HEARTBEAT,0);
		mavlink_send_message(0, MSG_LOCATION,0);
		while(1)
		{
		// if(tranlTimer > 100)
		// {
		// tranlTimer = 0;
		// mavlink_send_message(0, MSG_HEARTBEAT, 0);
		// mavlink_send_message(0, MSG_ATTITUDE, 0);
		// mavlink_send_message(0, MSG_AHRS, 0);
		// }
		update();
		}
	}
}