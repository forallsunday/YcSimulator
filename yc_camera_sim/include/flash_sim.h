#ifndef FLASH_SIM_H
#define FLASH_SIM_H

void flashRead(int offset, char *data, int len);
void flashWrite(int offset, char *data, int len);

#endif // FLASH_SIM_H
