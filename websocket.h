#include "base64.h"
#include "sha1.h"

void WShandshake(char *read, int len, SOCKET *socket){
   	char line[50];
    int x, k;
    k = 0;
    char *handshake_key;
    char match[] = "Sec-WebSocket-Key: ";

    for(x = 0; x < len; x++){
        if (read[x] == '\r'){
            x++;
            line[k] = '\0';
            x++; //skip \n character
            for(k = 0; k < sizeof(line); k++){
            	if(line[k] == match[k]){
            		if(k >= 15){
            			handshake_key = &line[strlen(match)];
            			handshake_key[strlen(handshake_key)] = '\0';
            			ZeroMemory(match,0);
            			goto done;
            		}
            	} else { break; }
            }
            k = 0;
        }
        line[k] = read[x];
        k++;
    }
    done:;

    ZeroMemory(read,0);

    char key[50];
    sprintf(key,"%s%s",handshake_key,"258EAFA5-E914-47DA-95CA-C5AB0DC85B11\0");
    printf("%s\n", key);
    uint32_t result[5];
    SHA1(key,strlen(key),result);

    uint8_t enc[20];
    k = 0;
    for(x = 0; x < 5; x++){
        enc[k] = (result[x] >> 28) << 4;
        enc[k] |= ((result[x] >> 24) & 0x0f);
        k++;
        enc[k] = (result[x] >> 20) << 4;
        enc[k] |= ((result[x] >> 16) & 0x00f);
        k++;
        enc[k] = (result[x] >> 12) << 4;
        enc[k] |= ((result[x] >> 8) & 0x000f);
        k++;
        enc[k] = (result[x] >> 4) << 4;
        enc[k] |= ((result[x]) & 0x0000f);
        k++;
    }
    
    char ws_key[50];
    base64_encode(enc,20,ws_key);
    printf("%s\n", ws_key);

    char resp[1024];
    char resp1[]="HTTP/1.1 101 Web Socket Protocol Handshake\r\n"
                "Upgrade: websocket\r\n"
                "Connection: Upgrade\r\n"
                "Sec-WebSocket-Accept:\0";
    char resp2[] = "\r\n\r\n\0";
   
    sprintf(resp,"%s%s%s",resp1,ws_key,resp2);

    send((SOCKET)*socket,resp,strlen(resp),0);
    printf("%s\n", resp);
 
}

char mask(char foo){

	return foo;
}
char unmask(char bar){

	return bar;
}