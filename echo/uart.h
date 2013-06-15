// uart.h

// init uart interface
//
void InitUart(void);


void putc(unsigned char ch);
void puts(char *str);
void puti(int i);

char *itoa(int i, char *buffer, int len);

unsigned char getc(void);


