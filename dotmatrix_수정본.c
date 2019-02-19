#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#define SPI_SPEED 1000000
#define BRIGHT 0
#define SPI_CHANNEL 8


/*
* data_88led()
* LED 점등 함수
* 첫번째 매개변수로 채널, = 줄번호
* 두번째 매개변수로 16진수 코드를 받음
* 즉, arr[] = {0xff,0xff....,0xff }이런 배열이 있으면
* data_88led(1,arr[0],0);
* data_88led(1,arr[1],0);
* 이런식으로 해야 합니다.
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
* 초기화 함수
* 모든 매트릭스를 소등합니다.
*/
void init_88led_spi(void){
	unsigned char out[2];
	int i;
	for(i=1;i<9;i++){
		data_88led(i,0,0);
	}
}


//예시용 배열, 출력 형태는 
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
