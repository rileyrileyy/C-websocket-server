char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(uint8_t *str, int size, char *enc){
	int x = 0;
	int temp[4];

	while(x < size){
		if(x <= (size - 3)){

			temp[0] = str[x] >> 2;
			*enc++  = base64[temp[0]];
			temp[1] = ((str[x] << 6) & 0xC0) >> 2;
			x++;
			temp[1] = temp[1] | (str[x] >> 4);
			*enc++  = base64[temp[1]];
			temp[2] = (str[x] & 0x0F) << 2;
			x++;
			temp[2] = temp[2] | ((str[x] & 0xC0) >> 6);
			*enc++ = base64[temp[2]];
			temp[3] = str[x] & 0x3F;
			x++;
			*enc++  = base64[temp[3]];
			continue;

		} else {
			if(x < size){

				if((size - x) == 1){

					temp[0]  = str[x] >> 2;
					*enc++   = base64[temp[0]];
					temp[1]  = ((str[x] << 6) & 0xC0) >> 2;

					*enc++ = base64[temp[1]];
					*enc++ = '=';
					*enc++ = '=';
					*enc++ = '\0';
					
				} else if((size - x) == 2){

					temp[0] = str[x] >> 2;
					*enc++ = base64[temp[0]];
					temp[1] = ((str[x] << 6) & 0xC0) >> 2;
					x++;
					temp[1] = temp[1] | (str[x] >> 4);
					*enc++ = base64[temp[1]];

					temp[2] = (str[x] & 0x0F) << 2;
					*enc++ = base64[temp[2]];

					*enc++ = '=';
					*enc++ = '\0';
				}
			}
		}
		break;
	}
}