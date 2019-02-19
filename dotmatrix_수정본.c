#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#define SPI_SPEED 1000000
#define BRIGHT 0
#define SPI_CHANNEL 8


/*
* data_88led()
* LED ���� �Լ�
* ù��° �Ű������� ä��, = �ٹ�ȣ
* �ι�° �Ű������� 16���� �ڵ带 ����
* ��, arr[] = {0xff,0xff....,0xff }�̷� �迭�� ������
* data_88led(1,arr[0],0);
* data_88led(1,arr[1],0);
* �̷������� �ؾ� �մϴ�.
*/
void data_88led (unsigned char msb, int lsb, int select){
	int i;
	unsigned char out[2] = {0};
	out[0] = msb;
	if(select == 2){
		for(i=0;i<8;i++){
			out[1] |= ((lsb%10)<<1);
			lsb = lsb/10;
		}
	}else{
		out[1] = lsb;
	}
	wiringPiSPIDataRW(SPI_CHANNEL,out,2);
}



/*
* �ʱ�ȭ �Լ�
* ��� ��Ʈ������ �ҵ��մϴ�.
*/
void init_88led_spi(void){
	unsigned char out[2];
	int i;
	for(i=1;i<9;i++){
		data_88led(i,0,0);
	}
}


//���ÿ� �迭, ��� ���´� 
/*
10000001
01000010
00100100
00011000
00011000
00100100
01000010
10000001
*/
unsigned char out_x[]={0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};

int main(void){
	if(wiringPiSPISetup(SPI_CHANNEL,SPI_SPEED) == -1){ 
		printf ("error"); 
		return 1;
	}
	int i;
	for(i=1;i<9;i++){
		data_88led(i,out_x[i+1],0);
		delay(100);
	}
	
	return 0;
}
