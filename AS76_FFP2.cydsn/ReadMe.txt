big easy drive have 16 micro steps
L6470 have 128 micro steps
steps multiplier is 128/16=8
 total number of actual steps in one rotation 200 x 128 = 25600
 total number of assumed steps in one rotation (200 *128)/8 =3200
 
 total number of steps count by quad eccoder is 16000
 total number of encoer count in assumed one step is 5    16000/3200
 total number of encoer count in one step is 0.625    16000/25600
 
 
    USB_transmit[0] = command_status_current; 
    USB_transmit[1] = command_status_current>>8; 
    USB_transmit[2] = ACKwithData; 
    USB_transmit[3] = ACKwithData>>8;
    USB_transmit[4] = position_x;
    USB_transmit[5] = position_x>>8;
    USB_transmit[6] = position_x>>16;
    USB_transmit[7] = position_x>>24;
    USB_transmit[8] = position_y;
    USB_transmit[9] = position_y>>8;
    USB_transmit[10] = position_y>>16;
    USB_transmit[11] = position_y>>24;
    USB_transmit[12] = position_z;
    USB_transmit[13] = position_z>>8;
    USB_transmit[14] = position_z>>16;
    USB_transmit[15] = position_z>>24;
    USB_transmit[16] = velocity_x;
    USB_transmit[17] = velocity_x>>8;
    USB_transmit[18] = velocity_x>>16;
    USB_transmit[19] = velocity_x>>24;
    USB_transmit[20] = velocity_y;
    USB_transmit[21] = velocity_y>>8;
    USB_transmit[22] = velocity_y>>16;
    USB_transmit[23] = velocity_y>>24;
    USB_transmit[24] = velocity_z;
    USB_transmit[25] = velocity_z>>8;
    USB_transmit[26] = velocity_z>>16;
    USB_transmit[27] = velocity_z>>24;
    USB_transmit[28] = steps_x;
    USB_transmit[29] = steps_x>>8;
    USB_transmit[30] = steps_y;
    USB_transmit[31] = steps_y>>8;
    USB_transmit[32] = steps_z;
    USB_transmit[33] = steps_z>>8;
    USB_transmit[34] = sensor_x;
    USB_transmit[35] = sensor_x>>8;
    USB_transmit[36] = sensor_y;
    USB_transmit[37] = sensor_y>>8;
    USB_transmit[38] = sensor_z;
    USB_transmit[39] = sensor_z>>8;
    USB_transmit[40] = sensor_slide;
    USB_transmit[41] = sensor_slide>>8;
    USB_transmit[42] = cov1;
    USB_transmit[43] = cov1>>8;
    USB_transmit[44] = volt1;
    USB_transmit[45] = volt1>>8;
    USB_transmit[46] = time_x;
    USB_transmit[47] = time_x>>8;
    USB_transmit[48] = time_x>>16;
    USB_transmit[49] = time_x>>24;
    USB_transmit[50] = time_y;
    USB_transmit[51] = time_y>>8;
    USB_transmit[52] = time_y>>16;
    USB_transmit[53] = time_y>>24;
    USB_transmit[54] = time_z;
    USB_transmit[55] = time_z>>8;
    USB_transmit[56] = time_z>>16;
    USB_transmit[57] = time_z>>24;
    
    
    
    //check with 1/16, 1/32, 1/64 steps with diffrent diffrent rotation speed
    
    