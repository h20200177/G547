#include "chardev.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */
#include<stdint.h>


	// THE FOLLOWING CALLS WILL BE SPECIFIC TO THE DEVICE & AXIS READING, 10 CALLS

int ioctl_set_gyroscopeX(int file_desc, int *ch1)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_GYROSCOPEX, ch1);

    if (ret_val < 0) {
        printf("ioctl_sel_gyroscopeX failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_gyroscopeY(int file_desc, int *ch2)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_GYROSCOPEY, ch2);

    if (ret_val < 0) {
        printf("ioctl_sel_gyroscopeY failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_gyroscopeZ(int file_desc, int *ch3)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_GYROSCOPEZ, ch3);

    if (ret_val < 0) {
        printf("ioctl_sel_gyroscopeZ failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_accelerometerX(int file_desc, int *ch4)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_ACCELEROMETERX, ch4);

    if (ret_val < 0) {
        printf("ioctl_sel_accelerometerX failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_accelerometerY(int file_desc, int *ch5)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_ACCELEROMETERY, ch5);

    if (ret_val < 0) {
        printf("ioctl_sel_accelerometerY failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_accelerometerZ(int file_desc, int *ch6)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_ACCELEROMETERZ, ch6);

    if (ret_val < 0) {
        printf("ioctl_sel_accelerometerZ failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_compassX(int file_desc, int *ch7)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_COMPASSX, ch7);

    if (ret_val < 0) {
        printf("ioctl_sel_compassX failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_compassY(int file_desc, int *ch8)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_COMPASSY, ch8);

    if (ret_val < 0) {
        printf("ioctl_sel_compassY failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_compassZ(int file_desc, int *ch9)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_COMPASSZ, ch9);

    if (ret_val < 0) {
        printf("ioctl_sel_compassZ failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}

int ioctl_set_barometer(int file_desc, int *ch10)
{
    int ret_val;
    
    ret_val = ioctl(file_desc, IOCTL_GET_BAROMETER, ch10);

    if (ret_val < 0) {
        printf("ioctl_sel_barometer failed:%d\n", ret_val);
        exit(-1);
    }
       
    return 0;
}


int main()
{
    int file_desc, ret_val;
    //int param_no;
    int read_no;
    uint16_t I2C_out;



     file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }


    printf("Select the device along with axis reading required : ");	//1-gyroX, 2-gyroY, 3-gyroZ, 4-AcceX, 5-AcceY, 6-AcceZ, 7-CompX, 8-CompY, 
									// 9-CompZ, 10-Barom	
    
	scanf("%d",&read_no); //SELECT DEVICE ALONG WITH AXIS READING REQUIRED

//According to the specific device choosen

      
    ioctl_set_gyroscopeX(file_desc,&read_no);

	 
    ioctl_set_gyroscopeY(file_desc,&read_no);

	 
    ioctl_set_gyroscopeZ(file_desc,&read_no);

	
    ioctl_set_accelerometerX(file_desc,&read_no);

	
    ioctl_set_accelerometerY(file_desc,&read_no);

	
    ioctl_set_accelerometerZ(file_desc,&read_no);

	
    ioctl_set_compassX(file_desc,&read_no);

	
    ioctl_set_compassY(file_desc,&read_no);

	
    ioctl_set_compassZ(file_desc,&read_no);

	
    ioctl_set_barometer(file_desc,&read_no);

	


    	read(file_desc,&I2C_out,0);   //reading values from device(imu_char) file
	
		
	
	printf("The reading of a devic specified with axis direction %d is = %d\n",read_no,I2C_out);

    		
    close(file_desc);
    return 0;
}
